
// Copyright (c) 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CSSPropertyNames_h
#define CSSPropertyNames_h

#include "core/CoreExport.h"
#include "wtf/Assertions.h"
#include <stddef.h>

namespace WTF {
class AtomicString;
class String;
}

namespace blink {

enum CSSPropertyID {
    CSSPropertyInvalid = 0,
    // This isn't a property, but we need to know the position of @apply rules in style rules
    CSSPropertyApplyAtRule = 1,
    CSSPropertyVariable = 2,
    CSSPropertyAnimationDelay = 3,
    CSSPropertyAnimationDirection = 4,
    CSSPropertyAnimationDuration = 5,
    CSSPropertyAnimationFillMode = 6,
    CSSPropertyAnimationIterationCount = 7,
    CSSPropertyAnimationName = 8,
    CSSPropertyAnimationPlayState = 9,
    CSSPropertyAnimationTimingFunction = 10,
    CSSPropertyTransitionDelay = 11,
    CSSPropertyTransitionDuration = 12,
    CSSPropertyTransitionProperty = 13,
    CSSPropertyTransitionTimingFunction = 14,
    CSSPropertyColor = 15,
    CSSPropertyDirection = 16,
    CSSPropertyFontFamily = 17,
    CSSPropertyFontFeatureSettings = 18,
    CSSPropertyFontKerning = 19,
    CSSPropertyFontSize = 20,
    CSSPropertyFontSizeAdjust = 21,
    CSSPropertyFontStretch = 22,
    CSSPropertyFontStyle = 23,
    CSSPropertyFontVariantCaps = 24,
    CSSPropertyFontVariantLigatures = 25,
    CSSPropertyFontVariantNumeric = 26,
    CSSPropertyFontVariationSettings = 27,
    CSSPropertyFontWeight = 28,
    CSSPropertyTextOrientation = 29,
    CSSPropertyTextRendering = 30,
    CSSPropertyWebkitFontSmoothing = 31,
    CSSPropertyWebkitLocale = 32,
    CSSPropertyWebkitTextOrientation = 33,
    CSSPropertyWebkitWritingMode = 34,
    CSSPropertyWritingMode = 35,
    CSSPropertyZoom = 36,
    CSSPropertyAlignContent = 37,
    CSSPropertyAlignItems = 38,
    CSSPropertyAlignSelf = 39,
    CSSPropertyAlignmentBaseline = 40,
    CSSPropertyAll = 41,
    CSSPropertyAnimation = 42,
    CSSPropertyBackdropFilter = 43,
    CSSPropertyBackfaceVisibility = 44,
    CSSPropertyBackground = 45,
    CSSPropertyBackgroundAttachment = 46,
    CSSPropertyBackgroundBlendMode = 47,
    CSSPropertyBackgroundClip = 48,
    CSSPropertyBackgroundColor = 49,
    CSSPropertyBackgroundImage = 50,
    CSSPropertyBackgroundOrigin = 51,
    CSSPropertyBackgroundPosition = 52,
    CSSPropertyBackgroundPositionX = 53,
    CSSPropertyBackgroundPositionY = 54,
    CSSPropertyBackgroundRepeat = 55,
    CSSPropertyBackgroundRepeatX = 56,
    CSSPropertyBackgroundRepeatY = 57,
    CSSPropertyBackgroundSize = 58,
    CSSPropertyBaselineShift = 59,
    CSSPropertyBlockSize = 60,
    CSSPropertyBorder = 61,
    CSSPropertyBorderBottom = 62,
    CSSPropertyBorderBottomColor = 63,
    CSSPropertyBorderBottomLeftRadius = 64,
    CSSPropertyBorderBottomRightRadius = 65,
    CSSPropertyBorderBottomStyle = 66,
    CSSPropertyBorderBottomWidth = 67,
    CSSPropertyBorderCollapse = 68,
    CSSPropertyBorderColor = 69,
    CSSPropertyBorderImage = 70,
    CSSPropertyBorderImageOutset = 71,
    CSSPropertyBorderImageRepeat = 72,
    CSSPropertyBorderImageSlice = 73,
    CSSPropertyBorderImageSource = 74,
    CSSPropertyBorderImageWidth = 75,
    CSSPropertyBorderLeft = 76,
    CSSPropertyBorderLeftColor = 77,
    CSSPropertyBorderLeftStyle = 78,
    CSSPropertyBorderLeftWidth = 79,
    CSSPropertyBorderRadius = 80,
    CSSPropertyBorderRight = 81,
    CSSPropertyBorderRightColor = 82,
    CSSPropertyBorderRightStyle = 83,
    CSSPropertyBorderRightWidth = 84,
    CSSPropertyBorderSpacing = 85,
    CSSPropertyBorderStyle = 86,
    CSSPropertyBorderTop = 87,
    CSSPropertyBorderTopColor = 88,
    CSSPropertyBorderTopLeftRadius = 89,
    CSSPropertyBorderTopRightRadius = 90,
    CSSPropertyBorderTopStyle = 91,
    CSSPropertyBorderTopWidth = 92,
    CSSPropertyBorderWidth = 93,
    CSSPropertyBottom = 94,
    CSSPropertyBoxShadow = 95,
    CSSPropertyBoxSizing = 96,
    CSSPropertyBreakAfter = 97,
    CSSPropertyBreakBefore = 98,
    CSSPropertyBreakInside = 99,
    CSSPropertyBufferedRendering = 100,
    CSSPropertyCaptionSide = 101,
    CSSPropertyCaretColor = 102,
    CSSPropertyClear = 103,
    CSSPropertyClip = 104,
    CSSPropertyClipPath = 105,
    CSSPropertyClipRule = 106,
    CSSPropertyColorInterpolation = 107,
    CSSPropertyColorInterpolationFilters = 108,
    CSSPropertyColorRendering = 109,
    CSSPropertyColumnCount = 110,
    CSSPropertyColumnFill = 111,
    CSSPropertyColumnGap = 112,
    CSSPropertyColumnRule = 113,
    CSSPropertyColumnRuleColor = 114,
    CSSPropertyColumnRuleStyle = 115,
    CSSPropertyColumnRuleWidth = 116,
    CSSPropertyColumnSpan = 117,
    CSSPropertyColumnWidth = 118,
    CSSPropertyColumns = 119,
    CSSPropertyContain = 120,
    CSSPropertyContent = 121,
    CSSPropertyCounterIncrement = 122,
    CSSPropertyCounterReset = 123,
    CSSPropertyCursor = 124,
    CSSPropertyCx = 125,
    CSSPropertyCy = 126,
    CSSPropertyD = 127,
    CSSPropertyDisplay = 128,
    CSSPropertyDominantBaseline = 129,
    CSSPropertyEmptyCells = 130,
    CSSPropertyFill = 131,
    CSSPropertyFillOpacity = 132,
    CSSPropertyFillRule = 133,
    CSSPropertyFilter = 134,
    CSSPropertyFlex = 135,
    CSSPropertyFlexBasis = 136,
    CSSPropertyFlexDirection = 137,
    CSSPropertyFlexFlow = 138,
    CSSPropertyFlexGrow = 139,
    CSSPropertyFlexShrink = 140,
    CSSPropertyFlexWrap = 141,
    CSSPropertyFloat = 142,
    CSSPropertyFloodColor = 143,
    CSSPropertyFloodOpacity = 144,
    CSSPropertyFont = 145,
    CSSPropertyFontDisplay = 146,
    CSSPropertyFontVariant = 147,
    CSSPropertyGrid = 148,
    CSSPropertyGridArea = 149,
    CSSPropertyGridAutoColumns = 150,
    CSSPropertyGridAutoFlow = 151,
    CSSPropertyGridAutoRows = 152,
    CSSPropertyGridColumn = 153,
    CSSPropertyGridColumnEnd = 154,
    CSSPropertyGridColumnGap = 155,
    CSSPropertyGridColumnStart = 156,
    CSSPropertyGridGap = 157,
    CSSPropertyGridRow = 158,
    CSSPropertyGridRowEnd = 159,
    CSSPropertyGridRowGap = 160,
    CSSPropertyGridRowStart = 161,
    CSSPropertyGridTemplate = 162,
    CSSPropertyGridTemplateAreas = 163,
    CSSPropertyGridTemplateColumns = 164,
    CSSPropertyGridTemplateRows = 165,
    CSSPropertyHeight = 166,
    CSSPropertyHyphens = 167,
    CSSPropertyImageOrientation = 168,
    CSSPropertyImageRendering = 169,
    CSSPropertyInlineSize = 170,
    CSSPropertyIsolation = 171,
    CSSPropertyJustifyContent = 172,
    CSSPropertyJustifyItems = 173,
    CSSPropertyJustifySelf = 174,
    CSSPropertyLeft = 175,
    CSSPropertyLetterSpacing = 176,
    CSSPropertyLightingColor = 177,
    CSSPropertyLineHeight = 178,
    CSSPropertyListStyle = 179,
    CSSPropertyListStyleImage = 180,
    CSSPropertyListStylePosition = 181,
    CSSPropertyListStyleType = 182,
    CSSPropertyMargin = 183,
    CSSPropertyMarginBottom = 184,
    CSSPropertyMarginLeft = 185,
    CSSPropertyMarginRight = 186,
    CSSPropertyMarginTop = 187,
    CSSPropertyMarker = 188,
    CSSPropertyMarkerEnd = 189,
    CSSPropertyMarkerMid = 190,
    CSSPropertyMarkerStart = 191,
    CSSPropertyMask = 192,
    CSSPropertyMaskSourceType = 193,
    CSSPropertyMaskType = 194,
    CSSPropertyMaxBlockSize = 195,
    CSSPropertyMaxHeight = 196,
    CSSPropertyMaxInlineSize = 197,
    CSSPropertyMaxWidth = 198,
    CSSPropertyMaxZoom = 199,
    CSSPropertyMinBlockSize = 200,
    CSSPropertyMinHeight = 201,
    CSSPropertyMinInlineSize = 202,
    CSSPropertyMinWidth = 203,
    CSSPropertyMinZoom = 204,
    CSSPropertyMixBlendMode = 205,
    CSSPropertyMotion = 206,
    CSSPropertyObjectFit = 207,
    CSSPropertyObjectPosition = 208,
    CSSPropertyOffset = 209,
    CSSPropertyOffsetAnchor = 210,
    CSSPropertyOffsetDistance = 211,
    CSSPropertyOffsetPath = 212,
    CSSPropertyOffsetPosition = 213,
    CSSPropertyOffsetRotate = 214,
    CSSPropertyOffsetRotation = 215,
    CSSPropertyOpacity = 216,
    CSSPropertyOrder = 217,
    CSSPropertyOrientation = 218,
    CSSPropertyOrphans = 219,
    CSSPropertyOutline = 220,
    CSSPropertyOutlineColor = 221,
    CSSPropertyOutlineOffset = 222,
    CSSPropertyOutlineStyle = 223,
    CSSPropertyOutlineWidth = 224,
    CSSPropertyOverflow = 225,
    CSSPropertyOverflowAnchor = 226,
    CSSPropertyOverflowWrap = 227,
    CSSPropertyOverflowX = 228,
    CSSPropertyOverflowY = 229,
    CSSPropertyPadding = 230,
    CSSPropertyPaddingBottom = 231,
    CSSPropertyPaddingLeft = 232,
    CSSPropertyPaddingRight = 233,
    CSSPropertyPaddingTop = 234,
    CSSPropertyPage = 235,
    CSSPropertyPageBreakAfter = 236,
    CSSPropertyPageBreakBefore = 237,
    CSSPropertyPageBreakInside = 238,
    CSSPropertyPaintOrder = 239,
    CSSPropertyPerspective = 240,
    CSSPropertyPerspectiveOrigin = 241,
    CSSPropertyPointerEvents = 242,
    CSSPropertyPosition = 243,
    CSSPropertyQuotes = 244,
    CSSPropertyR = 245,
    CSSPropertyResize = 246,
    CSSPropertyRight = 247,
    CSSPropertyRotate = 248,
    CSSPropertyRx = 249,
    CSSPropertyRy = 250,
    CSSPropertyScale = 251,
    CSSPropertyScrollBehavior = 252,
    CSSPropertyScrollSnapCoordinate = 253,
    CSSPropertyScrollSnapDestination = 254,
    CSSPropertyScrollSnapPointsX = 255,
    CSSPropertyScrollSnapPointsY = 256,
    CSSPropertyScrollSnapType = 257,
    CSSPropertyShapeImageThreshold = 258,
    CSSPropertyShapeMargin = 259,
    CSSPropertyShapeOutside = 260,
    CSSPropertyShapeRendering = 261,
    CSSPropertySize = 262,
    CSSPropertySnapHeight = 263,
    CSSPropertySpeak = 264,
    CSSPropertySrc = 265,
    CSSPropertyStopColor = 266,
    CSSPropertyStopOpacity = 267,
    CSSPropertyStroke = 268,
    CSSPropertyStrokeDasharray = 269,
    CSSPropertyStrokeDashoffset = 270,
    CSSPropertyStrokeLinecap = 271,
    CSSPropertyStrokeLinejoin = 272,
    CSSPropertyStrokeMiterlimit = 273,
    CSSPropertyStrokeOpacity = 274,
    CSSPropertyStrokeWidth = 275,
    CSSPropertyTabSize = 276,
    CSSPropertyTableLayout = 277,
    CSSPropertyTextAlign = 278,
    CSSPropertyTextAlignLast = 279,
    CSSPropertyTextAnchor = 280,
    CSSPropertyTextCombineUpright = 281,
    CSSPropertyTextDecoration = 282,
    CSSPropertyTextDecorationColor = 283,
    CSSPropertyTextDecorationLine = 284,
    CSSPropertyTextDecorationSkip = 285,
    CSSPropertyTextDecorationStyle = 286,
    CSSPropertyTextIndent = 287,
    CSSPropertyTextJustify = 288,
    CSSPropertyTextOverflow = 289,
    CSSPropertyTextShadow = 290,
    CSSPropertyTextSizeAdjust = 291,
    CSSPropertyTextTransform = 292,
    CSSPropertyTextUnderlinePosition = 293,
    CSSPropertyTop = 294,
    CSSPropertyTouchAction = 295,
    CSSPropertyTransform = 296,
    CSSPropertyTransformOrigin = 297,
    CSSPropertyTransformStyle = 298,
    CSSPropertyTransition = 299,
    CSSPropertyTranslate = 300,
    CSSPropertyUnicodeBidi = 301,
    CSSPropertyUnicodeRange = 302,
    CSSPropertyUserSelect = 303,
    CSSPropertyUserZoom = 304,
    CSSPropertyVectorEffect = 305,
    CSSPropertyVerticalAlign = 306,
    CSSPropertyVisibility = 307,
    CSSPropertyWebkitAppRegion = 308,
    CSSPropertyWebkitAppearance = 309,
    CSSPropertyWebkitBackgroundClip = 310,
    CSSPropertyWebkitBackgroundOrigin = 311,
    CSSPropertyWebkitBorderAfter = 312,
    CSSPropertyWebkitBorderAfterColor = 313,
    CSSPropertyWebkitBorderAfterStyle = 314,
    CSSPropertyWebkitBorderAfterWidth = 315,
    CSSPropertyWebkitBorderBefore = 316,
    CSSPropertyWebkitBorderBeforeColor = 317,
    CSSPropertyWebkitBorderBeforeStyle = 318,
    CSSPropertyWebkitBorderBeforeWidth = 319,
    CSSPropertyWebkitBorderEnd = 320,
    CSSPropertyWebkitBorderEndColor = 321,
    CSSPropertyWebkitBorderEndStyle = 322,
    CSSPropertyWebkitBorderEndWidth = 323,
    CSSPropertyWebkitBorderHorizontalSpacing = 324,
    CSSPropertyWebkitBorderImage = 325,
    CSSPropertyWebkitBorderStart = 326,
    CSSPropertyWebkitBorderStartColor = 327,
    CSSPropertyWebkitBorderStartStyle = 328,
    CSSPropertyWebkitBorderStartWidth = 329,
    CSSPropertyWebkitBorderVerticalSpacing = 330,
    CSSPropertyWebkitBoxAlign = 331,
    CSSPropertyWebkitBoxDecorationBreak = 332,
    CSSPropertyWebkitBoxDirection = 333,
    CSSPropertyWebkitBoxFlex = 334,
    CSSPropertyWebkitBoxFlexGroup = 335,
    CSSPropertyWebkitBoxLines = 336,
    CSSPropertyWebkitBoxOrdinalGroup = 337,
    CSSPropertyWebkitBoxOrient = 338,
    CSSPropertyWebkitBoxPack = 339,
    CSSPropertyWebkitBoxReflect = 340,
    CSSPropertyWebkitColumnBreakAfter = 341,
    CSSPropertyWebkitColumnBreakBefore = 342,
    CSSPropertyWebkitColumnBreakInside = 343,
    CSSPropertyWebkitFontSizeDelta = 344,
    CSSPropertyWebkitHighlight = 345,
    CSSPropertyWebkitHyphenateCharacter = 346,
    CSSPropertyWebkitLineBreak = 347,
    CSSPropertyWebkitLineClamp = 348,
    CSSPropertyWebkitLogicalHeight = 349,
    CSSPropertyWebkitLogicalWidth = 350,
    CSSPropertyWebkitMarginAfter = 351,
    CSSPropertyWebkitMarginAfterCollapse = 352,
    CSSPropertyWebkitMarginBefore = 353,
    CSSPropertyWebkitMarginBeforeCollapse = 354,
    CSSPropertyWebkitMarginBottomCollapse = 355,
    CSSPropertyWebkitMarginCollapse = 356,
    CSSPropertyWebkitMarginEnd = 357,
    CSSPropertyWebkitMarginStart = 358,
    CSSPropertyWebkitMarginTopCollapse = 359,
    CSSPropertyWebkitMask = 360,
    CSSPropertyWebkitMaskBoxImage = 361,
    CSSPropertyWebkitMaskBoxImageOutset = 362,
    CSSPropertyWebkitMaskBoxImageRepeat = 363,
    CSSPropertyWebkitMaskBoxImageSlice = 364,
    CSSPropertyWebkitMaskBoxImageSource = 365,
    CSSPropertyWebkitMaskBoxImageWidth = 366,
    CSSPropertyWebkitMaskClip = 367,
    CSSPropertyWebkitMaskComposite = 368,
    CSSPropertyWebkitMaskImage = 369,
    CSSPropertyWebkitMaskOrigin = 370,
    CSSPropertyWebkitMaskPosition = 371,
    CSSPropertyWebkitMaskPositionX = 372,
    CSSPropertyWebkitMaskPositionY = 373,
    CSSPropertyWebkitMaskRepeat = 374,
    CSSPropertyWebkitMaskRepeatX = 375,
    CSSPropertyWebkitMaskRepeatY = 376,
    CSSPropertyWebkitMaskSize = 377,
    CSSPropertyWebkitMaxLogicalHeight = 378,
    CSSPropertyWebkitMaxLogicalWidth = 379,
    CSSPropertyWebkitMinLogicalHeight = 380,
    CSSPropertyWebkitMinLogicalWidth = 381,
    CSSPropertyWebkitPaddingAfter = 382,
    CSSPropertyWebkitPaddingBefore = 383,
    CSSPropertyWebkitPaddingEnd = 384,
    CSSPropertyWebkitPaddingStart = 385,
    CSSPropertyWebkitPerspectiveOriginX = 386,
    CSSPropertyWebkitPerspectiveOriginY = 387,
    CSSPropertyWebkitPrintColorAdjust = 388,
    CSSPropertyWebkitRtlOrdering = 389,
    CSSPropertyWebkitRubyPosition = 390,
    CSSPropertyWebkitTapHighlightColor = 391,
    CSSPropertyWebkitTextCombine = 392,
    CSSPropertyWebkitTextDecorationsInEffect = 393,
    CSSPropertyWebkitTextEmphasis = 394,
    CSSPropertyWebkitTextEmphasisColor = 395,
    CSSPropertyWebkitTextEmphasisPosition = 396,
    CSSPropertyWebkitTextEmphasisStyle = 397,
    CSSPropertyWebkitTextFillColor = 398,
    CSSPropertyWebkitTextSecurity = 399,
    CSSPropertyWebkitTextStroke = 400,
    CSSPropertyWebkitTextStrokeColor = 401,
    CSSPropertyWebkitTextStrokeWidth = 402,
    CSSPropertyWebkitTransformOriginX = 403,
    CSSPropertyWebkitTransformOriginY = 404,
    CSSPropertyWebkitTransformOriginZ = 405,
    CSSPropertyWebkitUserDrag = 406,
    CSSPropertyWebkitUserModify = 407,
    CSSPropertyWhiteSpace = 408,
    CSSPropertyWidows = 409,
    CSSPropertyWidth = 410,
    CSSPropertyWillChange = 411,
    CSSPropertyWordBreak = 412,
    CSSPropertyWordSpacing = 413,
    CSSPropertyWordWrap = 414,
    CSSPropertyX = 415,
    CSSPropertyY = 416,
    CSSPropertyZIndex = 417,
    CSSPropertyAliasEpubCaptionSide = 613,
    CSSPropertyAliasEpubTextCombine = 904,
    CSSPropertyAliasEpubTextEmphasis = 906,
    CSSPropertyAliasEpubTextEmphasisColor = 907,
    CSSPropertyAliasEpubTextEmphasisStyle = 909,
    CSSPropertyAliasEpubTextOrientation = 545,
    CSSPropertyAliasEpubTextTransform = 804,
    CSSPropertyAliasEpubWordBreak = 924,
    CSSPropertyAliasEpubWritingMode = 546,
    CSSPropertyAliasMotionOffset = 723,
    CSSPropertyAliasMotionPath = 724,
    CSSPropertyAliasMotionRotation = 727,
    CSSPropertyAliasWebkitAlignContent = 549,
    CSSPropertyAliasWebkitAlignItems = 550,
    CSSPropertyAliasWebkitAlignSelf = 551,
    CSSPropertyAliasWebkitAnimation = 554,
    CSSPropertyAliasWebkitAnimationDelay = 515,
    CSSPropertyAliasWebkitAnimationDirection = 516,
    CSSPropertyAliasWebkitAnimationDuration = 517,
    CSSPropertyAliasWebkitAnimationFillMode = 518,
    CSSPropertyAliasWebkitAnimationIterationCount = 519,
    CSSPropertyAliasWebkitAnimationName = 520,
    CSSPropertyAliasWebkitAnimationPlayState = 521,
    CSSPropertyAliasWebkitAnimationTimingFunction = 522,
    CSSPropertyAliasWebkitBackfaceVisibility = 556,
    CSSPropertyAliasWebkitBackgroundSize = 570,
    CSSPropertyAliasWebkitBorderBottomLeftRadius = 576,
    CSSPropertyAliasWebkitBorderBottomRightRadius = 577,
    CSSPropertyAliasWebkitBorderRadius = 592,
    CSSPropertyAliasWebkitBorderTopLeftRadius = 601,
    CSSPropertyAliasWebkitBorderTopRightRadius = 602,
    CSSPropertyAliasWebkitBoxShadow = 607,
    CSSPropertyAliasWebkitBoxSizing = 608,
    CSSPropertyAliasWebkitClipPath = 617,
    CSSPropertyAliasWebkitColumnCount = 622,
    CSSPropertyAliasWebkitColumnGap = 624,
    CSSPropertyAliasWebkitColumnRule = 625,
    CSSPropertyAliasWebkitColumnRuleColor = 626,
    CSSPropertyAliasWebkitColumnRuleStyle = 627,
    CSSPropertyAliasWebkitColumnRuleWidth = 628,
    CSSPropertyAliasWebkitColumnSpan = 629,
    CSSPropertyAliasWebkitColumnWidth = 630,
    CSSPropertyAliasWebkitColumns = 631,
    CSSPropertyAliasWebkitFilter = 646,
    CSSPropertyAliasWebkitFlex = 647,
    CSSPropertyAliasWebkitFlexBasis = 648,
    CSSPropertyAliasWebkitFlexDirection = 649,
    CSSPropertyAliasWebkitFlexFlow = 650,
    CSSPropertyAliasWebkitFlexGrow = 651,
    CSSPropertyAliasWebkitFlexShrink = 652,
    CSSPropertyAliasWebkitFlexWrap = 653,
    CSSPropertyAliasWebkitFontFeatureSettings = 530,
    CSSPropertyAliasWebkitJustifyContent = 684,
    CSSPropertyAliasWebkitOpacity = 728,
    CSSPropertyAliasWebkitOrder = 729,
    CSSPropertyAliasWebkitPerspective = 752,
    CSSPropertyAliasWebkitPerspectiveOrigin = 753,
    CSSPropertyAliasWebkitShapeImageThreshold = 770,
    CSSPropertyAliasWebkitShapeMargin = 771,
    CSSPropertyAliasWebkitShapeOutside = 772,
    CSSPropertyAliasWebkitTextSizeAdjust = 803,
    CSSPropertyAliasWebkitTransform = 808,
    CSSPropertyAliasWebkitTransformOrigin = 809,
    CSSPropertyAliasWebkitTransformStyle = 810,
    CSSPropertyAliasWebkitTransition = 811,
    CSSPropertyAliasWebkitTransitionDelay = 523,
    CSSPropertyAliasWebkitTransitionDuration = 524,
    CSSPropertyAliasWebkitTransitionProperty = 525,
    CSSPropertyAliasWebkitTransitionTimingFunction = 526,
    CSSPropertyAliasWebkitUserSelect = 815,
};

const int firstCSSProperty = 3;
const int numCSSProperties = 415;
const int lastCSSProperty = 417;
const int lastUnresolvedCSSProperty = 924;
const size_t maxCSSPropertyNameLength = 40;

const char* getPropertyName(CSSPropertyID);
const WTF::AtomicString& getPropertyNameAtomicString(CSSPropertyID);
WTF::String getPropertyNameString(CSSPropertyID);
WTF::String getJSPropertyName(CSSPropertyID);

inline bool isCSSPropertyIDWithName(int id)
{
    return id >= firstCSSProperty && id <= lastUnresolvedCSSProperty;
}

inline bool isValidCSSPropertyID(CSSPropertyID id)
{
    return id != CSSPropertyInvalid;
}

inline CSSPropertyID convertToCSSPropertyID(int value)
{
    DCHECK(value >= CSSPropertyInvalid && value <= lastCSSProperty);
    return static_cast<CSSPropertyID>(value);
}

inline CSSPropertyID resolveCSSPropertyID(CSSPropertyID id)
{
    return convertToCSSPropertyID(id & ~512);
}

inline bool isPropertyAlias(CSSPropertyID id) { return id & 512; }

CSSPropertyID unresolvedCSSPropertyID(const WTF::String&);

CSSPropertyID CORE_EXPORT cssPropertyID(const WTF::String&);

} // namespace blink

#endif // CSSPropertyNames_h
