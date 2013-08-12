/**
* \file print.c
*
* Functions used to format and print HL7 messages into strings.
*
* \internal
* Copyright (c) 2003-2013 Juan Jose Comellas <juanjo@comellas.org>
*/

/* ------------------------------------------------------------------------
   Headers
   ------------------------------------------------------------------------ */

#include <hl7parser/config.h>
#include <hl7parser/export.h>
#include <hl7parser/sprint.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// BEGIN_C_DECL()


/* ------------------------------------------------------------------------ */
size_t hl7_sprint( char *output_buffer, const size_t output_len,
                   const char *input_buffer, const size_t input_len )
{
    HL7_ASSERT( input_buffer != 0 );
    HL7_ASSERT( input_len >= 0 );

    static const char  INCOMPLETE_END[] = "...";
    static const char  ESCAPE_KEY[]     = "\a\b\f\n\r\t\v\\\"";
    static const char  ESCAPE_REP[]     = {
        'a', 'b', 'f', 'n', 'r', 't', 'v', '\\', '\"'
    };

    const char  *src_end  = input_buffer + input_len;
    const char  *src      = input_buffer;
    char        *dest_end = output_buffer + output_len - 4;
    char        *dest     = output_buffer;
    char        *escaped_pos;
    char        escaped_buffer[6];
    char        *escaped_char;
    size_t      escaped_len;
    char        c;

    while ( src < src_end )
    {
        c = *src++;
        // Check if the character is valid for a C string.
        if ( isprint( c ) && c != '\\' && c != '\"' )
        {
            if ( dest < dest_end )
            {
                *(dest++) = c;
            }
            else
            {
                strcpy( dest, INCOMPLETE_END );
                dest += strlen( INCOMPLETE_END );
                break;
            }
        }
        else
        {
            // Find out if we can escape this character using the
            // normal C escape characters.
            escaped_pos  = ( ( c != '\0' ) ? strchr( ESCAPE_KEY, c ) : 0 );
            escaped_char = escaped_buffer;
            // C escape:                    "\\<c>"   (2 characters)
            // C escape (linefeed):         "\\n[\n]" (3 characters)
            // C escape (carriage return):  "\\r[\n]" (3 characters)
            // C escape (CR+LF):            "\\r\\n[\n]" (5 characters)
            if ( escaped_pos != 0 )
            {
                *(escaped_char++) = '\\';
                *(escaped_char++) = ESCAPE_REP[escaped_pos - ESCAPE_KEY];
                if ( c == '\r' || c == '\n' )
                {
                    if ( c == '\r' )
                    {
                        if ( src < src_end && *src == '\n' )
                        {
                            *(escaped_char++) = '\\';
                            *(escaped_char++) = 'n';
                            ++src;
                        }
                    }
                    // We add a linefeed to the string to make it
                    // more readable.
                    *(escaped_char++) = '\n';
                }
                *escaped_char = '\0';
            }
            else
            {
                // We show unprintable characters that cannot be escaped using
                // the C escaping rules using the hexadecimal representation.
                escaped_char += sprintf( escaped_char, "\\x%02x",
                                         ((unsigned) c ) & 0xff );
            }
            escaped_len = escaped_char - escaped_buffer;
            if ( dest + escaped_len < dest_end )
            {
                strcpy( dest, escaped_buffer );
                dest += escaped_len;
            }
            else
            {
                strcpy( dest, INCOMPLETE_END );
                dest += strlen( INCOMPLETE_END );
                break;
            }
        }
    }
    *dest = '\0';
    return ( src - input_buffer );
}


// END_C_DECL()
