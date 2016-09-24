/*
 * Copyright (C) 2012 Grigori Goronzy <greg@kinoho.net>
 *
 * Permission to use, copy, modify, and/or distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#ifndef UCDN_H
#define UCDN_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include "ucdn_export.h"
#include "ucdn_macros.h"

#define UCDN_GENERAL_CATEGORY_CC 0
#define UCDN_GENERAL_CATEGORY_CF 1
#define UCDN_GENERAL_CATEGORY_CN 2
#define UCDN_GENERAL_CATEGORY_CO 3
#define UCDN_GENERAL_CATEGORY_CS 4
#define UCDN_GENERAL_CATEGORY_LL 5
#define UCDN_GENERAL_CATEGORY_LM 6
#define UCDN_GENERAL_CATEGORY_LO 7
#define UCDN_GENERAL_CATEGORY_LT 8
#define UCDN_GENERAL_CATEGORY_LU 9
#define UCDN_GENERAL_CATEGORY_MC 10
#define UCDN_GENERAL_CATEGORY_ME 11
#define UCDN_GENERAL_CATEGORY_MN 12
#define UCDN_GENERAL_CATEGORY_ND 13
#define UCDN_GENERAL_CATEGORY_NL 14
#define UCDN_GENERAL_CATEGORY_NO 15
#define UCDN_GENERAL_CATEGORY_PC 16
#define UCDN_GENERAL_CATEGORY_PD 17
#define UCDN_GENERAL_CATEGORY_PE 18
#define UCDN_GENERAL_CATEGORY_PF 19
#define UCDN_GENERAL_CATEGORY_PI 20
#define UCDN_GENERAL_CATEGORY_PO 21
#define UCDN_GENERAL_CATEGORY_PS 22
#define UCDN_GENERAL_CATEGORY_SC 23
#define UCDN_GENERAL_CATEGORY_SK 24
#define UCDN_GENERAL_CATEGORY_SM 25
#define UCDN_GENERAL_CATEGORY_SO 26
#define UCDN_GENERAL_CATEGORY_ZL 27
#define UCDN_GENERAL_CATEGORY_ZP 28
#define UCDN_GENERAL_CATEGORY_ZS 29

#define UCDN_BIDI_CLASS_L 0
#define UCDN_BIDI_CLASS_LRE 1
#define UCDN_BIDI_CLASS_LRO 2
#define UCDN_BIDI_CLASS_R 3
#define UCDN_BIDI_CLASS_AL 4
#define UCDN_BIDI_CLASS_RLE 5
#define UCDN_BIDI_CLASS_RLO 6
#define UCDN_BIDI_CLASS_PDF 7
#define UCDN_BIDI_CLASS_EN 8
#define UCDN_BIDI_CLASS_ES 9
#define UCDN_BIDI_CLASS_ET 10
#define UCDN_BIDI_CLASS_AN 11
#define UCDN_BIDI_CLASS_CS 12
#define UCDN_BIDI_CLASS_NSM 13
#define UCDN_BIDI_CLASS_BN 14
#define UCDN_BIDI_CLASS_B 15
#define UCDN_BIDI_CLASS_S 16
#define UCDN_BIDI_CLASS_WS 17
#define UCDN_BIDI_CLASS_ON 18
#define UCDN_BIDI_CLASS_LRI 19
#define UCDN_BIDI_CLASS_RLI 20
#define UCDN_BIDI_CLASS_FSI 21
#define UCDN_BIDI_CLASS_PDI 22

#define UCDN_BIDI_PAIRED_BRACKET_TYPE_OPEN 0
#define UCDN_BIDI_PAIRED_BRACKET_TYPE_CLOSE 1
#define UCDN_BIDI_PAIRED_BRACKET_TYPE_NONE 2

/**
 * Return version of the Unicode database.
 *
 * @return Unicode database version
 */
UCDN_EXPORT const char *ucdn_get_unicode_version(void);

/**
 * Get combining class of a codepoint.
 *
 * @param code Unicode codepoint
 * @return combining class value, as defined in UAX#44
 */
UCDN_EXPORT int ucdn_get_combining_class(uint32_t code);

/**
 * Get east-asian width of a codepoint.
 *
 * @param code Unicode codepoint
 * @return value according to UCDN_EAST_ASIAN_* and as defined in UAX#11.
 */
UCDN_EXPORT int ucdn_get_east_asian_width(uint32_t code);

/**
 * Get general category of a codepoint.
 *
 * @param code Unicode codepoint
 * @return value according to UCDN_GENERAL_CATEGORY_* and as defined in
 * UAX#44.
 */
UCDN_EXPORT int ucdn_get_general_category(uint32_t code);

/**
 * Get bidirectional class of a codepoint.
 *
 * @param code Unicode codepoint
 * @return value according to UCDN_BIDI_CLASS_* and as defined in UAX#44.
 */
UCDN_EXPORT int ucdn_get_bidi_class(uint32_t code);

/**
 * Get script of a codepoint.
 *
 * @param code Unicode codepoint
 * @return value according to UCDN_SCRIPT_* and as defined in UAX#24.
 */
UCDN_EXPORT int ucdn_get_script(uint32_t code);

/**
 * Get unresolved linebreak class of a codepoint. This does not take
 * rule LB1 of UAX#14 into account. See ucdn_get_resolved_linebreak_class()
 * for resolved linebreak classes.
 *
 * @param code Unicode codepoint
 * @return value according to UCDN_LINEBREAK_* and as defined in UAX#14.
 */
UCDN_EXPORT int ucdn_get_linebreak_class(uint32_t code);

/**
 * Get resolved linebreak class of a codepoint. This resolves characters
 * in the AI, SG, XX, SA and CJ classes according to rule LB1 of UAX#14.
 * In addition the CB class is resolved as the equivalent B2 class and
 * the NL class is resolved as the equivalent BK class.
 *
 * @param code Unicode codepoint
 * @return value according to UCDN_LINEBREAK_* and as defined in UAX#14.
 */
UCDN_EXPORT int ucdn_get_resolved_linebreak_class(uint32_t code);

/**
 * Check if codepoint can be mirrored.
 *
 * @param code Unicode codepoint
 * @return 1 if mirrored character exists, otherwise 0
 */
UCDN_EXPORT int ucdn_get_mirrored(uint32_t code);

/**
 * Mirror a codepoint.
 *
 * @param code Unicode codepoint
 * @return mirrored codepoint or the original codepoint if no
 * mirrored character exists
 */
UCDN_EXPORT uint32_t ucdn_mirror(uint32_t code);

/**
 * Get paired bracket for a codepoint.
 *
 * @param code Unicode codepoint
 * @return paired bracket codepoint or the original codepoint if no
 * paired bracket character exists
 */
UCDN_EXPORT uint32_t ucdn_paired_bracket(uint32_t code);

/**
 * Get paired bracket type for a codepoint.
 *
 * @param code Unicode codepoint
 * @return value according to UCDN_BIDI_PAIRED_BRACKET_TYPE_* and as defined
 * in UAX#9.
 *
 */
UCDN_EXPORT int ucdn_paired_bracket_type(uint32_t code);

/**
 * Pairwise canonical decomposition of a codepoint. This includes
 * Hangul Jamo decomposition (see chapter 3.12 of the Unicode core
 * specification).
 *
 * Hangul is decomposed into L and V jamos for LV forms, and an
 * LV precomposed syllable and a T jamo for LVT forms.
 *
 * @param code Unicode codepoint
 * @param a filled with first codepoint of decomposition
 * @param b filled with second codepoint of decomposition, or 0
 * @return success
 */
UCDN_EXPORT int ucdn_decompose(uint32_t code, uint32_t *a, uint32_t *b);

/**
 * Compatibility decomposition of a codepoint.
 *
 * @param code Unicode codepoint
 * @param decomposed filled with decomposition, must be able to hold 18
 * characters
 * @return length of decomposition or 0 in case none exists
 */
UCDN_EXPORT int ucdn_compat_decompose(uint32_t code, uint32_t *decomposed);

/**
 * Pairwise canonical composition of two codepoints. This includes
 * Hangul Jamo composition (see chapter 3.12 of the Unicode core
 * specification).
 *
 * Hangul composition expects either L and V jamos, or an LV
 * precomposed syllable and a T jamo. This is exactly the inverse
 * of pairwise Hangul decomposition.
 *
 * @param code filled with composition
 * @param a first codepoint
 * @param b second codepoint
 * @return success
 */
UCDN_EXPORT int ucdn_compose(uint32_t *code, uint32_t a, uint32_t b);

#ifdef __cplusplus
}
#endif

#endif
