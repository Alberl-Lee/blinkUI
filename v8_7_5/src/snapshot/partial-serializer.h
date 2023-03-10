// Copyright 2016 the V8 project authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef V8_SNAPSHOT_PARTIAL_SERIALIZER_H_
#define V8_SNAPSHOT_PARTIAL_SERIALIZER_H_

#include "src/address-map.h"
#include "src/contexts.h"
#include "src/snapshot/serializer.h"

namespace v8 {
namespace internal {

    class StartupSerializer;

    class V8_EXPORT_PRIVATE PartialSerializer : public Serializer {
    public:
        PartialSerializer(Isolate* isolate, StartupSerializer* startup_serializer,
            v8::SerializeEmbedderFieldsCallback callback);

        ~PartialSerializer() override;

        // Serialize the objects reachable from a single object pointer.
        void Serialize(Context* o, bool include_global_proxy);

        bool can_be_rehashed() const { return can_be_rehashed_; }

    private:
        void SerializeObject(HeapObject o) override;

        bool ShouldBeInThePartialSnapshotCache(HeapObject o);

        bool SerializeJSObjectWithEmbedderFields(Object obj);

        void CheckRehashability(HeapObject obj);

        StartupSerializer* startup_serializer_;
        v8::SerializeEmbedderFieldsCallback serialize_embedder_fields_;
        // Indicates whether we only serialized hash tables that we can rehash.
        // TODO(yangguo): generalize rehashing, and remove this flag.
        bool can_be_rehashed_;
        Context context_;

        // Used to store serialized data for embedder fields.
        SnapshotByteSink embedder_fields_sink_;
        DISALLOW_COPY_AND_ASSIGN(PartialSerializer);
    };

} // namespace internal
} // namespace v8

#endif // V8_SNAPSHOT_PARTIAL_SERIALIZER_H_
