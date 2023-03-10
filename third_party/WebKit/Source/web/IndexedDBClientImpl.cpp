/*
 * Copyright (C) 2011 Google Inc. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1.  Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 * 2.  Redistributions in binary form must reproduce the above copyright
 *     notice, this list of conditions and the following disclaimer in the
 *     documentation and/or other materials provided with the distribution.
 * 3.  Neither the name of Apple Computer, Inc. ("Apple") nor the names of
 *     its contributors may be used to endorse or promote products derived
 *     from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY APPLE AND ITS CONTRIBUTORS "AS IS" AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL APPLE OR ITS CONTRIBUTORS BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "web/IndexedDBClientImpl.h"

#include "bindings/core/v8/WorkerOrWorkletScriptController.h"
#include "core/dom/Document.h"
#include "core/dom/ExecutionContext.h"
#include "core/workers/WorkerGlobalScope.h"
#include "platform/weborigin/SecurityOrigin.h"
#include "public/platform/WebSecurityOrigin.h"
#include "public/web/WebContentSettingsClient.h"
#include "public/web/WebKit.h"
#include "web/WebLocalFrameImpl.h"
#include "web/WorkerContentSettingsClient.h"

namespace blink {

IndexedDBClient* IndexedDBClientImpl::create(LocalFrame& frame)
{
    return new IndexedDBClientImpl(frame);
}

IndexedDBClient* IndexedDBClientImpl::create(WorkerClients& workerClients)
{
    return new IndexedDBClientImpl(workerClients);
}

IndexedDBClientImpl::IndexedDBClientImpl(LocalFrame& frame)
    : IndexedDBClient(frame)
{
}

IndexedDBClientImpl::IndexedDBClientImpl(WorkerClients& workerClients)
    : IndexedDBClient(workerClients)
{
}

bool IndexedDBClientImpl::allowIndexedDB(ExecutionContext* context,
    const String& name)
{
    DCHECK(context->isContextThread());
    SECURITY_DCHECK(context->isDocument() || context->isWorkerGlobalScope());

    if (context->isDocument()) {
        WebSecurityOrigin origin(context->getSecurityOrigin());
        Document* document = toDocument(context);
        WebLocalFrameImpl* webFrame = WebLocalFrameImpl::fromFrame(document->frame());
        if (!webFrame)
            return false;
        if (webFrame->contentSettingsClient())
            return webFrame->contentSettingsClient()->allowIndexedDB(name, origin);
        return true;
    }

    WorkerGlobalScope& workerGlobalScope = *toWorkerGlobalScope(context);
    return WorkerContentSettingsClient::from(workerGlobalScope)
        ->allowIndexedDB(name);
}

} // namespace blink
