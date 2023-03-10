// Copyright 2018 the V8 project authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef V8_ELEMENTS_INL_H_
#define V8_ELEMENTS_INL_H_

#include "src/elements.h"

#include "src/handles-inl.h"
#include "src/objects-inl.h"

namespace v8 {
namespace internal {

    inline void ElementsAccessor::CollectElementIndices(Handle<JSObject> object,
        KeyAccumulator* keys)
    {
        CollectElementIndices(object, handle(object->elements(), keys->isolate()),
            keys);
    }

    inline MaybeHandle<FixedArray> ElementsAccessor::PrependElementIndices(
        Handle<JSObject> object, Handle<FixedArray> keys, GetKeysConversion convert,
        PropertyFilter filter)
    {
        return PrependElementIndices(object,
            handle(object->elements(), object->GetIsolate()),
            keys, convert, filter);
    }

    inline bool ElementsAccessor::HasElement(JSObject holder, uint32_t index,
        PropertyFilter filter)
    {
        return HasElement(holder, index, holder->elements(), filter);
    }

} // namespace internal
} // namespace v8

#endif // V8_ELEMENTS_INL_H_
