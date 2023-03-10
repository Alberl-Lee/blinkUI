// Copyright 2017 the V8 project authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef V8_WASM_MODULE_COMPILER_H_
#define V8_WASM_MODULE_COMPILER_H_

#include <atomic>
#include <functional>
#include <memory>

#include "src/cancelable-task.h"
#include "src/globals.h"
#include "src/wasm/compilation-environment.h"
#include "src/wasm/wasm-features.h"
#include "src/wasm/wasm-module.h"

namespace v8 {
namespace internal {

    class JSArrayBuffer;
    class JSPromise;
    class Counters;
    class WasmModuleObject;
    class WasmInstanceObject;

    template <typename T>
    class Vector;

    namespace wasm {

        struct CompilationEnv;
        class CompilationResultResolver;
        class ErrorThrower;
        class ModuleCompiler;
        class NativeModule;
        class WasmCode;
        struct WasmModule;

        std::shared_ptr<NativeModule> CompileToNativeModule(
            Isolate* isolate, const WasmFeatures& enabled, ErrorThrower* thrower,
            std::shared_ptr<const WasmModule> module, const ModuleWireBytes& wire_bytes,
            Handle<FixedArray>* export_wrappers_out);

        V8_EXPORT_PRIVATE
        void CompileJsToWasmWrappers(Isolate* isolate, const WasmModule* module,
            Handle<FixedArray> export_wrappers);

        V8_EXPORT_PRIVATE Handle<Script> CreateWasmScript(
            Isolate* isolate, const ModuleWireBytes& wire_bytes,
            const std::string& source_map_url);

        // Triggered by the WasmCompileLazy builtin.
        void CompileLazy(Isolate*, NativeModule*, uint32_t func_index);

        // Encapsulates all the state and steps of an asynchronous compilation.
        // An asynchronous compile job consists of a number of tasks that are executed
        // as foreground and background tasks. Any phase that touches the V8 heap or
        // allocates on the V8 heap (e.g. creating the module object) must be a
        // foreground task. All other tasks (e.g. decoding and validating, the majority
        // of the work of compilation) can be background tasks.
        // TODO(wasm): factor out common parts of this with the synchronous pipeline.
        class AsyncCompileJob {
        public:
            AsyncCompileJob(Isolate* isolate, const WasmFeatures& enabled_features,
                std::unique_ptr<byte[]> bytes_copy, size_t length,
                Handle<Context> context,
                std::shared_ptr<CompilationResultResolver> resolver);
            ~AsyncCompileJob();

            void Start();

            std::shared_ptr<StreamingDecoder> CreateStreamingDecoder();

            void Abort();
            void CancelPendingForegroundTask();

            Isolate* isolate() const { return isolate_; }

        private:
            class CompileTask;
            class CompileStep;
            class CompilationStateCallback;

            // States of the AsyncCompileJob.
            class DecodeModule; // Step 1  (async)
            class DecodeFail; // Step 1b (sync)
            class PrepareAndStartCompile; // Step 2  (sync)
            class CompileFailed; // Step 3a (sync)
            class CompileFinished; // Step 3b (sync)

            friend class AsyncStreamingProcessor;

            // Decrements the number of outstanding finishers. The last caller of this
            // function should finish the asynchronous compilation, see the comment on
            // {outstanding_finishers_}.
            V8_WARN_UNUSED_RESULT bool DecrementAndCheckFinisherCount()
            {
                DCHECK_LT(0, outstanding_finishers_.load());
                return outstanding_finishers_.fetch_sub(1) == 1;
            }

            void CreateNativeModule(std::shared_ptr<const WasmModule> module);
            void PrepareRuntimeObjects();

            void FinishCompile();

            void DecodeFailed(const WasmError&);
            void AsyncCompileFailed();

            void AsyncCompileSucceeded(Handle<WasmModuleObject> result);

            void CompileWrappers();

            void FinishModule();

            void StartForegroundTask();
            void ExecuteForegroundTaskImmediately();

            void StartBackgroundTask();

            enum UseExistingForegroundTask : bool {
                kUseExistingForegroundTask = true,
                kAssertNoExistingForegroundTask = false
            };
            // Switches to the compilation step {Step} and starts a foreground task to
            // execute it. Most of the time we know that there cannot be a running
            // foreground task. If there might be one, then pass
            // kUseExistingForegroundTask to avoid spawning a second one.
            template <typename Step,
                UseExistingForegroundTask = kAssertNoExistingForegroundTask,
                typename... Args>
            void DoSync(Args&&... args);

            // Switches to the compilation step {Step} and immediately executes that step.
            template <typename Step, typename... Args>
            void DoImmediately(Args&&... args);

            // Switches to the compilation step {Step} and starts a background task to
            // execute it.
            template <typename Step, typename... Args>
            void DoAsync(Args&&... args);

            // Switches to the compilation step {Step} but does not start a task to
            // execute it.
            template <typename Step, typename... Args>
            void NextStep(Args&&... args);

            Isolate* const isolate_;
            const WasmFeatures enabled_features_;
            // Copy of the module wire bytes, moved into the {native_module_} on its
            // creation.
            std::unique_ptr<byte[]> bytes_copy_;
            // Reference to the wire bytes (held in {bytes_copy_} or as part of
            // {native_module_}).
            ModuleWireBytes wire_bytes_;
            Handle<Context> native_context_;
            const std::shared_ptr<CompilationResultResolver> resolver_;

            Handle<WasmModuleObject> module_object_;
            std::shared_ptr<NativeModule> native_module_;

            std::unique_ptr<CompileStep> step_;
            CancelableTaskManager background_task_manager_;

            std::shared_ptr<v8::TaskRunner> foreground_task_runner_;

            // For async compilation the AsyncCompileJob is the only finisher. For
            // streaming compilation also the AsyncStreamingProcessor has to finish before
            // compilation can be finished.
            std::atomic<int32_t> outstanding_finishers_ { 1 };

            // A reference to a pending foreground task, or {nullptr} if none is pending.
            CompileTask* pending_foreground_task_ = nullptr;

            // The AsyncCompileJob owns the StreamingDecoder because the StreamingDecoder
            // contains data which is needed by the AsyncCompileJob for streaming
            // compilation. The AsyncCompileJob does not actively use the
            // StreamingDecoder.
            std::shared_ptr<StreamingDecoder> stream_;
        };

    } // namespace wasm
} // namespace internal
} // namespace v8

#endif // V8_WASM_MODULE_COMPILER_H_
