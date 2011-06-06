/**
* \file format.c
*
* Functions to encode/decode text elements using the HL7 formatting rules.
*
* \internal
* Copyright (c) 2003-2011 \b Erlar (http://erlar.com)
*/

/* ------------------------------------------------------------------------
   Headers
   ------------------------------------------------------------------------ */

#include <hl7parser/config.h>
#include <hl7parser/defs.h>
#include <hl7parser/error.h>
#include <hl7parser/export.h>
#include <hl7parser/format.h>
#include <hl7parser/settings.h>
#include <stddef.h>

BEGIN_C_DECL()


/* ------------------------------------------------------------------------ */
HL7_EXPORT int hl7_format_encode( HL7_Settings *settings,
                                  char *dest_begin, size_t *dest_length,
                                  char *src_begin, size_t src_length )
{
    int  rc         = 0;
    char *src       = src_begin;
    char *src_end   = src_begin + src_length;
    char *dest      = dest_begin;
    char *dest_end  = dest_begin + *dest_length;
    char formatted;

    HL7_Element_Type    element_type;

    HL7_ASSERT( settings != 0 );
    HL7_ASSERT( dest_begin != 0 );
    HL7_ASSERT( dest_length != 0 );
    HL7_ASSERT( src_begin != 0 );

    while ( src < src_end )
    {
        element_type = hl7_element_type( settings, *src );

        if ( element_type != HL7_ELEMENT_INVALID )
        {
            formatted = settings->separator[element_type];
        }
        else
        {
            formatted = 0;
        }

        if ( dest + HL7_ESCAPED_CHAR_LENGTH < dest_end )
        {
            if ( formatted )
            {
                *dest++ = settings->escape_char;
                *dest++ = formatted;
                *dest++ = settings->escape_char;
                ++src;
            }
            else
            {
                *dest++ = *src++;
            }
        }
        else
        {
            /* rc = -1; */
            rc = HL7_ERROR_BUFFER_TOO_SMALL;
            break;
        }
    }

    *dest_length = dest - dest_begin;

    return rc;
}


/* ------------------------------------------------------------------------ */
HL7_EXPORT int hl7_format_decode( HL7_Settings *settings,
                                  char *dest_begin, size_t *dest_length,
                                  char *src_begin, size_t src_length )
{
    int  rc         = 0;
    char *src       = src_begin;
    char *src_end   = src_begin + src_length;
    char *dest      = dest_begin;
    char *dest_end  = dest_begin + *dest_length;
    char formatted;

    HL7_ASSERT( settings != 0 );
    HL7_ASSERT( dest_begin != 0 );
    HL7_ASSERT( dest_length != 0 );
    HL7_ASSERT( src_begin != 0 );

    while ( src < src_end )
    {
        if ( *src == HL7_ESCAPE_CHAR )
        {
            if ( src + HL7_ESCAPED_CHAR_LENGTH < src_end )
            {
                ++src;

                switch ( *src )
                {
                    case HL7_FORMAT_FIELD:
                        formatted = settings->separator[HL7_ELEMENT_FIELD];
                        break;

                    case HL7_FORMAT_REPETITION:
                        formatted = settings->separator[HL7_ELEMENT_REPETITION];
                        break;

                    case HL7_FORMAT_COMPONENT:
                        formatted = settings->separator[HL7_ELEMENT_COMPONENT];
                        break;

                    case HL7_FORMAT_SUBCOMPONENT:
                        formatted = settings->separator[HL7_ELEMENT_SUBCOMPONENT];
                        break;

                    case HL7_FORMAT_ESCAPE:
                        formatted = settings->escape_char;
                        break;

                    /* FIXME: we need to support hexadecimal escaped characters. */
                    /* Hexadecimal data. */
                    /*
                    case HL7_FORMAT_HEX_DATA:
                        formatted = 0;
                        break;
                    */

                    /* Locally defined escape sequence. */
                    /*
                    case 'Z':
                        formatted = 0;
                        break;
                    */

                    default:
                        formatted = 0;
                        break;
                }

                if ( dest < dest_end )
                {
                    if ( formatted )
                    {
                        *dest++ = formatted;
                        src    += 2;
                    }
                    else
                    {
                        *dest++ = *src++;
                    }
                }
                else
                {
                    /* rc = -1; */
                    rc = HL7_ERROR_BUFFER_TOO_SMALL;
                    break;
                }
            }
            else
            {
                /* Invalid escaped character. */
                /* rc = -1; */
                rc = HL7_ERROR_INVALID_ESCAPED_CHAR;
                break;
            }
        }
    }

    *dest_length = dest - dest_begin;

    return rc;
}


END_C_DECL()
