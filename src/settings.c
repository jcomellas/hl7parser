/**
* \file settings.c
*
* HL7 parser settings.
*
* \internal
* Copyright (c) 2003-2013 Juan Jose Comellas <juanjo@comellas.org>
*/

/* ------------------------------------------------------------------------
   Headers
   ------------------------------------------------------------------------ */

#include <hl7parser/config.h>
#include <hl7parser/element.h>
#include <hl7parser/format.h>
#include <hl7parser/settings.h>
#include <stdlib.h>
#include <string.h>

BEGIN_C_DECL()


/* ------------------------------------------------------------------------ */
HL7_EXPORT void hl7_settings_init( HL7_Settings *settings )
{
    HL7_ASSERT( config != 0 );

    /* HL7 element separators. */
    settings->separator[HL7_ELEMENT_SUBCOMPONENT] = HL7_SEPARATOR_SUBCOMPONENT;
    settings->separator[HL7_ELEMENT_COMPONENT]    = HL7_SEPARATOR_COMPONENT;
    settings->separator[HL7_ELEMENT_REPETITION]   = HL7_SEPARATOR_REPETITION;
    settings->separator[HL7_ELEMENT_FIELD]        = HL7_SEPARATOR_FIELD;
    settings->separator[HL7_ELEMENT_SEGMENT]      = HL7_SEPARATOR_SEGMENT;

    /* HL7 escape character. */
    settings->escape_char = HL7_ESCAPE_CHAR;

    /*  Strip whitespace by default. */
    settings->strip_whitespace = true;
    /* Should the parser escape the characters in each HL7_Element automatically? */
    settings->auto_escape = true;
}

/* ------------------------------------------------------------------------ */
HL7_EXPORT void hl7_settings_fini( HL7_Settings *settings )
{
    HL7_ASSERT( settings != 0 );

    memset( settings, 0, sizeof ( HL7_Settings ) );
}

/* ------------------------------------------------------------------------ */
HL7_EXPORT char hl7_separator( const HL7_Settings *settings, const HL7_Element_Type element_type )
{
    HL7_ASSERT( settings != 0 );

    return ( element_type < HL7_ELEMENT_TYPE_COUNT ?
             settings->separator[element_type] : HL7_SEPARATOR_INVALID );
}

/* ------------------------------------------------------------------------ */
HL7_EXPORT void hl7_set_separator( HL7_Settings *settings, const HL7_Element_Type element_type, const char separator )
{
    HL7_ASSERT( settings != 0 );

    if ( element_type < HL7_ELEMENT_TYPE_COUNT )
    {
        settings->separator[element_type] = separator;
    }
}

/* ------------------------------------------------------------------------ */
HL7_EXPORT bool hl7_is_separator( HL7_Settings *settings, const char separator )
{
    return ( hl7_element_type( settings, separator ) != -1 );
}

/* ------------------------------------------------------------------------ */
HL7_EXPORT char hl7_escape_char( const HL7_Settings *settings )
{
    return settings->escape_char;
}

/* ------------------------------------------------------------------------ */
HL7_EXPORT void hl7_set_escape_char( HL7_Settings *settings, const char escape_char )
{
    settings->escape_char = escape_char;
}

/* ------------------------------------------------------------------------ */
HL7_EXPORT HL7_Element_Type hl7_element_type( HL7_Settings *settings, const char separator )
{
    HL7_Element_Type element_type = HL7_ELEMENT_INVALID;
    HL7_Element_Type i;

    HL7_ASSERT( settings != 0 );

    for ( i = 0; i < HL7_ELEMENT_TYPE_COUNT; ++i )
    {
        if ( hl7_separator( settings, i ) == separator )
        {
            element_type = i;
            break;
        }
    }
    return element_type;
}

/* ------------------------------------------------------------------------ */
HL7_EXPORT HL7_Element_Type hl7_child_type( const HL7_Element_Type element_type )
{
    return ( element_type > HL7_ELEMENT_SUBCOMPONENT ?
             element_type - 1 :
             HL7_ELEMENT_INVALID );
}

/* ------------------------------------------------------------------------ */
HL7_EXPORT bool hl7_is_child_type( const HL7_Element_Type child_type, const HL7_Element_Type parent_type )
{
    return ( hl7_child_type( parent_type ) == child_type );
}

/* ------------------------------------------------------------------------ */
HL7_EXPORT bool hl7_is_descendant_type( const HL7_Element_Type descendant_type, const HL7_Element_Type ancestor_type )
{
    return ( descendant_type < ancestor_type );
}

/* ------------------------------------------------------------------------ */
HL7_EXPORT HL7_Element_Type hl7_parent_type( const HL7_Element_Type element_type )
{
    return ( element_type < HL7_ELEMENT_SEGMENT ?
             element_type + 1 :
             HL7_ELEMENT_INVALID );
}

/* ------------------------------------------------------------------------ */
HL7_EXPORT bool hl7_is_parent_type( const HL7_Element_Type parent_type, const HL7_Element_Type child_type )
{
    return ( hl7_parent_type( child_type ) == parent_type );
}

/* ------------------------------------------------------------------------ */
HL7_EXPORT bool hl7_is_ancestor_type( const HL7_Element_Type ancestor_type, const HL7_Element_Type descendant_type )
{
    return ( descendant_type < ancestor_type );
}

/* ------------------------------------------------------------------------ */
HL7_EXPORT void hl7_child_separators( HL7_Settings *settings, const HL7_Element_Type element_type,
                                      const char **separator_begin, const char **separator_end )
{
    HL7_ASSERT( settings != 0 );

    if ( element_type > HL7_SEPARATOR_SUBCOMPONENT )
    {
        *separator_begin = settings->separator;
        *separator_end   = settings->separator + element_type - 1;
    }
    else
    {
        *separator_begin = 0;
        *separator_end   = 0;
    }
}

/* ------------------------------------------------------------------------ */
HL7_EXPORT char hl7_terminator( HL7_Settings *settings, const HL7_Element_Type element_type )
{
    HL7_ASSERT( settings != 0 );

    return ( settings->separator[element_type] );
}

/* ------------------------------------------------------------------------ */
HL7_EXPORT void hl7_parent_terminators( HL7_Settings *settings, const HL7_Element_Type element_type,
                                        const char **separator_begin, const char **separator_end )
{
    HL7_ASSERT( settings != 0 );

    *separator_begin = settings->separator + element_type;
    *separator_end   = settings->separator + HL7_ELEMENT_TYPE_COUNT;
}


END_C_DECL()
