// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "core/html/HTMLPictureElement.h"

#include "core/HTMLNames.h"
#include "core/dom/ElementTraversal.h"
#include "core/frame/UseCounter.h"
#include "core/html/HTMLImageElement.h"
#include "core/html/HTMLSourceElement.h"
#include "core/loader/ImageLoader.h"

namespace blink {

using namespace HTMLNames;

inline HTMLPictureElement::HTMLPictureElement(Document& document)
    : HTMLElement(pictureTag, document)
{
}

DEFINE_NODE_FACTORY(HTMLPictureElement)

void HTMLPictureElement::sourceOrMediaChanged()
{
    for (HTMLImageElement* imageElement = Traversal<HTMLImageElement>::firstChild(*this);
         imageElement;
         imageElement = Traversal<HTMLImageElement>::nextSibling(*imageElement)) {
        imageElement->selectSourceURL(ImageLoader::UpdateNormal);
    }
}

void HTMLPictureElement::removeListenerFromSourceChildren()
{
    for (HTMLSourceElement* sourceElement = Traversal<HTMLSourceElement>::firstChild(*this);
         sourceElement; sourceElement = Traversal<HTMLSourceElement>::nextSibling(
                            *sourceElement)) {
        sourceElement->removeMediaQueryListListener();
    }
}

void HTMLPictureElement::addListenerToSourceChildren()
{
    for (HTMLSourceElement* sourceElement = Traversal<HTMLSourceElement>::firstChild(*this);
         sourceElement; sourceElement = Traversal<HTMLSourceElement>::nextSibling(
                            *sourceElement)) {
        sourceElement->addMediaQueryListListener();
    }
}

Node::InsertionNotificationRequest HTMLPictureElement::insertedInto(
    ContainerNode* insertionPoint)
{
    UseCounter::count(document(), UseCounter::Picture);
    return HTMLElement::insertedInto(insertionPoint);
}

} // namespace blink
