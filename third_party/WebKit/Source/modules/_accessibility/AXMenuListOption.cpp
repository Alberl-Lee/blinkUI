/*
 * Copyright (C) 2010 Apple Inc. All Rights Reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY APPLE INC. ``AS IS'' AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL APPLE INC. OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY
 * OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "modules/accessibility/AXMenuListOption.h"

#include "SkMatrix44.h"
#include "modules/accessibility/AXMenuListPopup.h"
#include "modules/accessibility/AXObjectCacheImpl.h"

namespace blink {

using namespace HTMLNames;

AXMenuListOption::AXMenuListOption(HTMLOptionElement* element,
    AXObjectCacheImpl& axObjectCache)
    : AXMockObject(axObjectCache)
    , m_element(element)
{
}

AXMenuListOption::~AXMenuListOption()
{
    ASSERT(!m_element);
}

void AXMenuListOption::detach()
{
    m_element = nullptr;
    AXMockObject::detach();
}

AccessibilityRole AXMenuListOption::roleValue() const
{
    const AtomicString& ariaRole = getAttribute(roleAttr);
    if (ariaRole.isEmpty())
        return MenuListOptionRole;

    AccessibilityRole role = ariaRoleToWebCoreRole(ariaRole);
    if (role)
        return role;
    return MenuListOptionRole;
}

Element* AXMenuListOption::actionElement() const
{
    return m_element;
}

bool AXMenuListOption::isEnabled() const
{
    // isDisabledFormControl() returns true if the parent <select> element is
    // disabled, which we don't want.
    return m_element && !m_element->ownElementDisabled();
}

bool AXMenuListOption::isVisible() const
{
    if (!m_parent)
        return false;

    // In a single-option select with the popup collapsed, only the selected
    // item is considered visible.
    return !m_parent->isOffScreen() || isSelected();
}

bool AXMenuListOption::isOffScreen() const
{
    // Invisible list options are considered to be offscreen.
    return !isVisible();
}

bool AXMenuListOption::isSelected() const
{
    AXMenuListPopup* parent = static_cast<AXMenuListPopup*>(parentObject());
    if (parent && !parent->isOffScreen())
        return parent->activeDescendant() == this;
    return m_element && m_element->selected();
}

void AXMenuListOption::setSelected(bool b)
{
    if (!m_element || !canSetSelectedAttribute())
        return;

    m_element->setSelected(b);
}

bool AXMenuListOption::canSetSelectedAttribute() const
{
    return isEnabled();
}

bool AXMenuListOption::computeAccessibilityIsIgnored(
    IgnoredReasons* ignoredReasons) const
{
    return accessibilityIsIgnoredByDefault(ignoredReasons);
}

void AXMenuListOption::getRelativeBounds(
    AXObject** outContainer,
    FloatRect& outBoundsInContainer,
    SkMatrix44& outContainerTransform) const
{
    *outContainer = nullptr;
    outBoundsInContainer = FloatRect();
    outContainerTransform.setIdentity();

    AXObject* parent = parentObject();
    if (!parent)
        return;
    ASSERT(parent->isMenuListPopup());

    AXObject* grandparent = parent->parentObject();
    if (!grandparent)
        return;
    ASSERT(grandparent->isMenuList());
    grandparent->getRelativeBounds(outContainer, outBoundsInContainer,
        outContainerTransform);
}

String AXMenuListOption::textAlternative(bool recursive,
    bool inAriaLabelledByTraversal,
    AXObjectSet& visited,
    AXNameFrom& nameFrom,
    AXRelatedObjectVector* relatedObjects,
    NameSources* nameSources) const
{
    // If nameSources is non-null, relatedObjects is used in filling it in, so it
    // must be non-null as well.
    if (nameSources)
        ASSERT(relatedObjects);

    if (!getNode())
        return String();

    bool foundTextAlternative = false;
    String textAlternative = ariaTextAlternative(
        recursive, inAriaLabelledByTraversal, visited, nameFrom, relatedObjects,
        nameSources, &foundTextAlternative);
    if (foundTextAlternative && !nameSources)
        return textAlternative;

    nameFrom = AXNameFromContents;
    textAlternative = m_element->displayLabel();
    if (nameSources) {
        nameSources->push_back(NameSource(foundTextAlternative));
        nameSources->back().type = nameFrom;
        nameSources->back().text = textAlternative;
        foundTextAlternative = true;
    }

    return textAlternative;
}

DEFINE_TRACE(AXMenuListOption)
{
    visitor->trace(m_element);
    AXMockObject::trace(visitor);
}

} // namespace blink
