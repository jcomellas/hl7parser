/**
* \file element.c
*
* Data types and functions used to handle an HL7 element.
*
* \internal
* Copyright (c) 2003-2013 Juan Jose Comellas <juanjo@comellas.org>
*/

/* ------------------------------------------------------------------------
   Headers
   ------------------------------------------------------------------------ */

#include <hl7parser/config.h>
#include <hl7parser/alloc.h>
#include <hl7parser/defs.h>
#include <hl7parser/element.h>
#include <hl7parser/export.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

BEGIN_C_DECL()


/* ------------------------------------------------------------------------ */
HL7_EXPORT void hl7_element_init( HL7_Element *element )
{
    element->value          = 0;
    element->length         = 0;
    element->attr           = HL7_TOKEN_ATTR_EMPTY;
    element->auto_delete    = false;
}

/* ------------------------------------------------------------------------ */
HL7_EXPORT void hl7_element_fini( HL7_Element *element, HL7_Allocator *allocator )
{
    if ( element->auto_delete )
    {
        allocator->mfree( element->value );
    }
    hl7_element_init( element );
}

/* ------------------------------------------------------------------------ */
HL7_EXPORT int hl7_element_create( HL7_Element *element, HL7_Token *token,
                                   HL7_Allocator *allocator )
{
    int rc = -1;

    HL7_ASSERT( element != 0 );

    element->value         = 0;
    element->auto_delete   = false;

    if ( token != 0 && token->value != 0 && token->length != 0 )
    {
        element->value = (char *) allocator->malloc( token->length );
        if ( element->value != 0 )
        {
            memcpy( element->value, token->value, token->length );
            element->auto_delete    = true;
            rc                      = 0;
        }
    }
    element->length         = token->length;
    element->attr           = token->attr;

    return rc;
}

/* ------------------------------------------------------------------------ */
HL7_EXPORT int hl7_element_create_copy( HL7_Element *dest, const HL7_Element *src,
                                        HL7_Allocator *allocator )
{
    int rc = -1;

    HL7_ASSERT( allocator != 0 );
    HL7_ASSERT( dest != 0 );
    HL7_ASSERT( src != 0 );

    dest->value         = 0;
    dest->auto_delete   = false;

    if ( src->value != 0 && src->length != 0 )
    {
        dest->value = (char *) allocator->malloc( src->length );
        if ( dest->value != 0 )
        {
            memcpy( dest->value, src->value, src->length );
            dest->auto_delete   = true;
            rc                  = 0;
        }
    }
    dest->length        = src->length;
    dest->attr          = src->attr;

    return rc;
}

/* ------------------------------------------------------------------------ */
HL7_EXPORT void hl7_element_destroy( HL7_Element *element, HL7_Allocator *allocator )
{
    HL7_ASSERT( allocator != 0 );

    if ( element != 0 && element->value != 0 && element->auto_delete )
    {
        allocator->mfree( element->value );
    }
    memset( element, 0, sizeof ( HL7_Element ) );
}

/* ------------------------------------------------------------------------ */
HL7_EXPORT HL7_Element *hl7_element_null( void )
{
    static HL7_Element null_element =
    {
        0,                      /* char                *value; */
        0,                      /* size_t              length; */
        0,                      /* HL7_Token_Attribute attr; */
        false                   /* bool                auto_delete; */
    };

    return &null_element;
}

/* ------------------------------------------------------------------------ */
HL7_EXPORT void hl7_element_set( HL7_Element *element, const HL7_Token *token,
                                 const bool auto_delete )
{
    HL7_ASSERT( element != 0 );
    HL7_ASSERT( token != 0 );

    element->value          = token->value;
    element->length         = token->length;
    element->attr           = token->attr;
    element->auto_delete    = auto_delete;
}

/* ------------------------------------------------------------------------ */
HL7_EXPORT int hl7_element_set_str( HL7_Element *element, char *str,
                                    const bool auto_delete )
{
    return hl7_element_set_ptr( element, str, ( str != 0 ? strlen( str ) : 0 ), auto_delete );
}

/* ------------------------------------------------------------------------ */
HL7_EXPORT int hl7_element_set_ptr( HL7_Element *element, char *value, const size_t length,
                                    const bool auto_delete )
{
    int rc;

    if ( element != 0 )
    {
        /*
        if ( element->auto_delete )
        {
            allocator->mfree( element->value );
        }
        */

        element->value          = value;
        element->length         = length;

        if ( value != 0 && length > 0 )
        {
            element->attr           = 0;
            element->auto_delete    = auto_delete;
        }
        else
        {
            element->attr           = HL7_TOKEN_ATTR_EMPTY;
            element->auto_delete    = false;
        }
        rc = 0;
    }
    else
    {
        rc = -1;
    }
    return rc;
}

/* ------------------------------------------------------------------------ */
HL7_EXPORT int hl7_element_copy( HL7_Element *dest, HL7_Element *src,
                                 HL7_Allocator *allocator,
                                 const bool assume_ownership )
{
    int rc = 0;

    HL7_ASSERT( src != 0 );
    HL7_ASSERT( dest != 0 );

    if ( dest != 0 )
    {
        if ( dest->auto_delete )
        {
            allocator->mfree( dest->value );
        }
        if ( src != 0 )
        {
            dest->value             = src->value;
            dest->length            = src->length;
            dest->attr              = src->attr;

            /* We need to avoid calling allocator->mfree() more than once for each pointer. */
            if ( assume_ownership && src->auto_delete )
            {
                dest->auto_delete   = true;
                src->auto_delete    = false;
            }
            else
            {
                dest->auto_delete   = false;
            }
        }
        else
        {
            hl7_element_init( dest );
        }
    }
    else
    {
        rc = -1;
    }
    return rc;
}

/* ------------------------------------------------------------------------ */
HL7_EXPORT int hl7_element_copy_str( HL7_Element *element, const char *str,
                                     HL7_Allocator *allocator )
{
    return hl7_element_copy_ptr( element, str, ( str != 0 ? strlen( str ) : 0 ), allocator );
}

/* ------------------------------------------------------------------------ */
HL7_EXPORT int hl7_element_copy_ptr( HL7_Element *element, const char *value, const size_t length,
                                     HL7_Allocator *allocator )
{
    int rc;

    if ( element != 0 )
    {
        HL7_ASSERT( allocator != 0 );

        /*
        if ( element->auto_delete )
        {
            allocator->mfree( element->value );
        }
        */

        if ( length > 0 && value != 0 &&
             ( element->value = (char *) allocator->malloc( length ) ) != 0 )
        {
            memcpy( element->value, value, length );
            element->length         = length;
            element->attr           = 0;
            element->auto_delete    = true;
        }
        else
        {
            element->value          = 0;
            element->length         = 0;
            element->attr           = HL7_TOKEN_ATTR_EMPTY;
            element->auto_delete    = false;
        }
        rc = 0;
    }
    else
    {
        rc = -1;
    }
    return rc;
}

/* ------------------------------------------------------------------------ */
HL7_EXPORT int hl7_element_int( HL7_Element *element )
{
    int number = 0;

    if ( element != 0 && element->value != 0 )
    {
        int  sign;
        char *value;
        char *value_end;

        value       = element->value;
        value_end   = value + element->length;

        while ( value < value_end && isspace( *value ) )
        {
            ++value;
        }

        if ( *value == '-' )
        {
            sign = -1;
            value++;
        }
        else
        {
            sign = 1;

            if ( *value == '+' )
            {
                value++;
            }
        }

        while ( value < value_end )
        {
            if ( isdigit( *value ) )
            {
                number = number * 10 + ( *value - '0' );
            }
            else
            {
                break;
            }
            value++;
        }
        number *= sign;
    }

    return ( number );
}

/* ------------------------------------------------------------------------ */
HL7_EXPORT int hl7_element_set_int( HL7_Element *element, const int value,
                                    HL7_Allocator *allocator )
{
    int rc = -1;

   HL7_ASSERT( allocator != 0 );

    if ( element != 0 )
    {
        char number[12];

        /*
        if ( element->auto_delete )
        {
            allocator->mfree( element->value );
        }
        */

        element->length = sprintf( number, "%d", value );

        element->value  = (char *) allocator->malloc( element->length );
        if ( element->value != 0 )
        {
            memcpy( element->value, number, element->length );
            element->attr           = 0;
            element->auto_delete    = true;

            rc = 0;
        }
        else
        {
            element->attr           = HL7_TOKEN_ATTR_EMPTY;
            element->auto_delete    = false;
        }
    }
    return rc;
}

/* ------------------------------------------------------------------------ */
HL7_EXPORT time_t hl7_element_date( HL7_Element *element )
{
    time_t      result          = HL7_INVALID_DATE;

    if ( element != 0 && element->value != 0 )
    {
        char        *value          = element->value;
        size_t      length          = ( element->length <= 14 ? element->length : 14 );
        struct tm   datetime;
        int         number;
        bool        valid_syntax    = false;
        size_t      i;

        memset( (char *) &datetime, '\0', sizeof ( struct tm ) );

        number = 0;

        for ( i = 0; i < length; i++ )
        {
            number = number * 10 + ( value[i] - '0' );

            if ( i % 2 != 0 && i >= 3 )
            {
                switch ( i )
                {
                    case 3:     /* tm_year: year - 1900 */
                        datetime.tm_year    = number - 1900;
                        break;

                    case 5:     /* tm_mon: [0,11] */
                        datetime.tm_mon     = number - 1;
                        break;

                    case 7:     /* tm_mday: [1,31] */
                        datetime.tm_mday    = number;
                        valid_syntax        = true;
                        break;

                    case 9:     /* tm_hour: [0,23] */
                        datetime.tm_hour    = number;
                        valid_syntax        = false;
                        break;

                    case 11:    /* tm_min: [0,59] */
                        datetime.tm_min     = number;
                        valid_syntax        = true;
                        break;

                    case 13:    /* tm_sec: [0,59] */
                        datetime.tm_sec     = number;
                        break;

                    default:
                        break;
                }
                number = 0;
            }
        }

        if ( valid_syntax )
        {
            result = mktime( &datetime );
        }
    }
    return result;
}

/* ------------------------------------------------------------------------ */
HL7_EXPORT int hl7_element_set_date( HL7_Element *element, const time_t value,
                                     const bool include_time, const bool include_secs,
                                     HL7_Allocator *allocator )
{
    int rc = -1;

   HL7_ASSERT( allocator != 0 );

    if ( element != 0 )
    {
        /*
        if ( element->auto_delete )
        {
            allocator->mfree( element->value );
        }
        */

        if ( value != HL7_INVALID_DATE )
        {
            element->length = 8;
            if ( include_time )
            {
                element->length += ( include_secs ? 6 : 4 );
            }

            /* We must take into account the NULL terminator added by sprintf(). */
            element->value  = (char *) allocator->malloc( element->length + 1 );
            if ( element->value != 0 )
            {
                struct tm   *datetime = localtime( &value );
                int         current_length;

                current_length = sprintf( element->value, "%04d%02d%02d",
                                          datetime->tm_year + 1900, datetime->tm_mon + 1,
                                          datetime->tm_mday );
                if ( include_time )
                {
                    current_length += sprintf( element->value + current_length, "%02d%02d",
                                               datetime->tm_hour, datetime->tm_min );

                    if ( include_secs )
                    {
                        current_length += sprintf( element->value + current_length, "%02d",
                                                   datetime->tm_sec );
                    }
                }
                element->attr           = 0;
                element->auto_delete    = true;

                rc = 0;
            }
            else
            {
                hl7_element_init( element );
            }
        }
        else
        {
            hl7_element_init( element );
        }
    }
    return rc;
}

/* ------------------------------------------------------------------------ */
HL7_EXPORT bool hl7_element_is_empty( const HL7_Element *element )
{
    return ( element == 0 || element->value == 0 || element->length == 0 );
}

/* ------------------------------------------------------------------------ */
HL7_EXPORT int hl7_element_strcmp( const HL7_Element *element, const char *str )
{
    int result = -1;

    if ( element != 0 && element->value != 0 && str != 0 )
    {
        size_t str_length = strlen( str );

        if ( element->length == str_length )
        {
            result = memcmp( element->value, str, str_length );
        }
        else
        {
            result = ( element->length < str_length ? -1 : 1 );
        }
    }
    return ( result );
}


END_C_DECL()
