/*
**********************************************************************
* Copyright (c) 2004, International Business Machines
* Corporation and others.  All Rights Reserved.
**********************************************************************
* Author: Alan Liu
* Created: April 20, 2004
* Since: ICU 3.0
**********************************************************************
*/
#include "unicode/utypes.h"

#if !UCONFIG_NO_FORMATTING

#include "currfmt.h"
#include "unicode/numfmt.h"

U_NAMESPACE_BEGIN

CurrencyFormat::CurrencyFormat(const Locale& locale, UErrorCode& ec) :
    fmt(NULL) {
    fmt = NumberFormat::createCurrencyInstance(locale, ec);
}

CurrencyFormat::CurrencyFormat(const CurrencyFormat& other) :
    fmt(NULL) {
    fmt = (NumberFormat*) other.fmt->clone();
}

CurrencyFormat::~CurrencyFormat() {
    delete fmt;
}

UBool CurrencyFormat::operator==(const Format& other) const {
    if (this == &other) {
        return TRUE;
    }
    if (other.getDynamicClassID() != CurrencyFormat::getStaticClassID()) {
        return FALSE;
    }
    const CurrencyFormat* c = (const CurrencyFormat*) &other;
    return *fmt == *c->fmt;
}

Format* CurrencyFormat::clone() const {
    return new CurrencyFormat(*this);
}

UnicodeString& CurrencyFormat::format(const Formattable& obj,
                                      UnicodeString& appendTo,
                                      FieldPosition& pos,
                                      UErrorCode& ec) const {
    return fmt->format(obj, appendTo, pos, ec);
}

UnicodeString& CurrencyFormat::format(const Formattable& obj,
                                      UnicodeString& appendTo,
                                      UErrorCode& ec) const {
    return MeasureFormat::format(obj, appendTo, ec);
}

void CurrencyFormat::parseObject(const UnicodeString& source,
                                 Formattable& result,
                                 ParsePosition& pos) const {
    fmt->parseCurrency(source, result, pos);
}

void CurrencyFormat::parseObject(const UnicodeString& source,
                                 Formattable& result,
                                 UErrorCode& ec) const {
    MeasureFormat::parseObject(source, result, ec);
}

UOBJECT_DEFINE_RTTI_IMPLEMENTATION(CurrencyFormat)

U_NAMESPACE_END

#endif /* #if !UCONFIG_NO_FORMATTING */
