// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef GPU_COMMAND_BUFFER_SERVICE_ASYNC_PIXEL_TRANSFER_MANAGER_EGL_H_
#define GPU_COMMAND_BUFFER_SERVICE_ASYNC_PIXEL_TRANSFER_MANAGER_EGL_H_

#include "gpu/command_buffer/service/async_pixel_transfer_manager.h"

#include "base/memory/ref_counted.h"

namespace gpu {
class AsyncPixelTransferDelegateEGL;
class AsyncPixelTransferUploadStats;

class AsyncPixelTransferManagerEGL : public AsyncPixelTransferManager {
public:
    AsyncPixelTransferManagerEGL();
    ~AsyncPixelTransferManagerEGL() override;

    // AsyncPixelTransferManager implementation:
    void BindCompletedAsyncTransfers() override;
    void AsyncNotifyCompletion(
        const AsyncMemoryParams& mem_params,
        AsyncPixelTransferCompletionObserver* observer) override;
    uint32 GetTextureUploadCount() override;
    base::TimeDelta GetTotalTextureUploadTime() override;
    void ProcessMorePendingTransfers() override;
    bool NeedsProcessMorePendingTransfers() override;
    void WaitAllAsyncTexImage2D() override;

    // State shared between Managers and Delegates.
    struct SharedState {
        SharedState();
        ~SharedState();

        scoped_refptr<AsyncPixelTransferUploadStats> texture_upload_stats;
        bool is_imagination;
        bool is_qualcomm;
        typedef std::list<base::WeakPtr<AsyncPixelTransferDelegateEGL>>
            TransferQueue;
        TransferQueue pending_allocations;
    };

private:
    // AsyncPixelTransferManager implementation:
    AsyncPixelTransferDelegate* CreatePixelTransferDelegateImpl(
        gles2::TextureRef* ref,
        const AsyncTexImage2DParams& define_params) override;

    SharedState shared_state_;

    DISALLOW_COPY_AND_ASSIGN(AsyncPixelTransferManagerEGL);
};

} // namespace gpu

#endif // GPU_COMMAND_BUFFER_SERVICE_ASYNC_PIXEL_TRANSFER_MANAGER_EGL_H_
