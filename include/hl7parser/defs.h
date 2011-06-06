#ifndef HL7PARSER_DEFS_H
#define HL7PARSER_DEFS_H

/**
* \file defs.h
*
* Miscellaneous definitions used by the HL7 parser.
*
* \internal
* Copyright (c) 2003-2011 \b Erlar (http://erlar.com)
*/

/* ------------------------------------------------------------------------
   Headers
   ------------------------------------------------------------------------ */

#include <hl7parser/config.h>
#include <time.h>

BEGIN_C_DECL()


/* ------------------------------------------------------------------------
   Macros
   ------------------------------------------------------------------------ */

/* HL7 Element types. */
/* IMPORTANT: DO NOT CHANGE the following values under any circumstance.
              All the parsing routines assume these values. */
#define HL7_ELEMENT_SUBCOMPONENT    0
#define HL7_ELEMENT_COMPONENT       1
#define HL7_ELEMENT_REPETITION      2
#define HL7_ELEMENT_FIELD           3
#define HL7_ELEMENT_SEGMENT         4
#define HL7_ELEMENT_TYPE_COUNT      5

#define HL7_ELEMENT_INVALID         -1

/* HL7 separators. */
#define HL7_SEPARATOR_SUBCOMPONENT  '&'
#define HL7_SEPARATOR_COMPONENT     '^'
#define HL7_SEPARATOR_REPETITION    '~'
#define HL7_SEPARATOR_FIELD         '|'
#define HL7_SEPARATOR_SEGMENT       '\r'
#define HL7_SEPARATOR_INVALID       '\xff'

#define HL7_ESCAPE_CHAR             '\\'

/* Formatting codes. */
#define HL7_ESC                     '\x1b'

#define HL7_FORMAT_HIGHLIGHT        'H'
#define HL7_FORMAT_NORMAL_TEXT      'N' /* end highlighting */
#define HL7_FORMAT_FIELD            'F'
#define HL7_FORMAT_COMPONENT        'S'
#define HL7_FORMAT_SUBCOMPONENT     'T'
#define HL7_FORMAT_REPETITION       'R'
#define HL7_FORMAT_ESCAPE           'E'
#define HL7_FORMAT_HEX_DATA         'X'
/* #define HL7_FORMAT_LOCAL_DATA_BEGIN             'Z' */

/* Length of standard elements. */
#define HL7_SEGMENT_ID_LENGTH       3
#define HL7_ESCAPED_CHAR_LENGTH     3

#define HL7_INVALID_DATE            ( (time_t) -1 )
#define HL7_INVALID_TIME            ( (time_t) -1 )

/* Checks whether a character is a space. */
#define HL7_IS_SPACE( c )           ( ( c ) == ' ' || ( c ) == '\t' )


/* ------------------------------------------------------------------------
   Typedefs
   ------------------------------------------------------------------------ */

typedef signed char                             HL7_Element_Type;
typedef signed char                             HL7_Element_Index;
typedef unsigned short                          HL7_Element_Length;
/* typedef HL7_Element_Index[HL7_ELEMENT_COUNT]    HL7_Element_Coord; */


END_C_DECL()

#endif /* HL7PARSER_DEFS_H */
