/* ------------------------------------------------------------------------
   $Id$

   Copyright (c) 2003-2013 Juan Jose Comellas <juanjo@comellas.org>

   Program to test the HL7 parser.
   ------------------------------------------------------------------------ */

/* ------------------------------------------------------------------------
   Headers
   ------------------------------------------------------------------------ */

#include <hl7parser/buffer.h>
#include <hl7parser/defs.h>
#include <hl7parser/element.h>
#include <hl7parser/settings.h>
#include <hl7parser/token.h>
#include <hl7parser/cbparser.h>
#include <stdio.h>
#include <string.h>


/* ------------------------------------------------------------------------
   Macros
   ------------------------------------------------------------------------ */

#define TAB_LENGTH  2


/* ------------------------------------------------------------------------
   Typedefs
   ------------------------------------------------------------------------ */

typedef unsigned int Element_Counter;

typedef struct Element_Stats_Struct
{
    Element_Counter element_count[HL7_ELEMENT_TYPE_COUNT];
    Element_Counter total_count;
    Element_Counter empty_count;
} Element_Stats;


/* ------------------------------------------------------------------------
   Function prototypes
   ------------------------------------------------------------------------ */

static int      start_document( HL7_Parser *parser );
static int      end_document( HL7_Parser *parser );
static int      start_element( HL7_Parser *parser, HL7_Element_Type element_type );
static int      end_element( HL7_Parser *parser, HL7_Element_Type element_type );
static int      characters( HL7_Parser *parser, HL7_Element_Type element_type, HL7_Element *element );

static char     *element_tab( char *buffer, const size_t max_length, const HL7_Element_Type element_type );
static size_t   element_tab_length( const HL7_Element_Type element_type );
static char     *element_type_name( const HL7_Element_Type element_type );
static char     *attr_name( char *text, const HL7_Token_Attribute attr );


/* ------------------------------------------------------------------------ */
/* int main( int argc, char *argv[] ) */
int main( void )
{
    static char message[] =
        "MSH|^~\\&|SERV|223344^^II|POSM|CARRIER^CL9999^IP|20030127202538||RPA^I08|5307938|P|2.3|||NE|NE\r"
        "MSA|AA|CL999920030127203647||||B006^\r"
        "AUT|TESTPLAN|223344^^II||||5307938||0|0\r"
        "PRD|RT|NOMBRE PRESTADOR SALUD|||||99999999999^CU^GUARDIA\r"
        "PRD|RP||||||9^^N\r"
        "PID|||2233441000013527101=0000000000002|1|NOMBRE PACIENTE^\r"
        "PR1|1||420101^CONSULTA EN CONSULTORIO^NA^||20030127203642|Z\r"
        "AUT|PLANSALUD|||20030127|20030127|5307938|0.00^$|1|1\r"
        "NTE|1||SIN CARGO\r"
        "NTE|2||IVA: SI\r";


    int                 rc              = 0;
    HL7_Settings        settings;
    HL7_Buffer          buffer;
    HL7_Parser          parser;
    HL7_Parser_Callback callback;
    Element_Stats       stats;

    hl7_settings_init( &settings );

    /* Initialize the buffer excluding the null terminator. */
    hl7_buffer_init( &buffer, message, sizeof ( message ) - 1 );
    hl7_buffer_set_wr_ptr( &buffer, message + sizeof ( message ) - 1 );

    /* Initialize the callback parser. */
    hl7_parser_cb_init( &parser, &callback, &settings );

    hl7_parser_set_user_data( &parser, &stats );

    /* Set the parser callbacks. */
    callback.start_document = start_document;
    callback.end_document   = end_document;
    callback.start_element  = start_element;
    callback.end_element    = end_element;
    callback.characters     = characters;

    /* Parse the contents of the buffer with the callback parser. */
    rc = hl7_parser_cb_read( &parser, &callback, &buffer );

    hl7_parser_cb_fini( &parser );
    hl7_buffer_fini( &buffer );
    hl7_settings_fini( &settings );

    return rc;
}

/* ------------------------------------------------------------------------ */
static int start_document( HL7_Parser *parser )
{
    int         rc = 0;

    memset( parser->user_data, 0, sizeof ( Element_Stats ) );

    printf( "<Message>\n" );

    return rc;
}

/* ------------------------------------------------------------------------ */
static int end_document( HL7_Parser *parser )
{
    int         rc = 0;

    printf( "</Message>\n\n" );

    if ( parser->user_data != 0 )
    {
        Element_Stats       *stats = (Element_Stats *) parser->user_data;
        HL7_Element_Type    element_type;

        printf( "Done: %u character elements parsed (%u empty).\n\n",
                stats->total_count, stats->empty_count );

        for ( element_type = HL7_ELEMENT_SEGMENT;
              element_type != HL7_ELEMENT_INVALID;
              element_type = hl7_child_type( element_type ) )
        {
            printf( "  %-15s: %u elements.\n",
                    element_type_name( element_type ), stats->element_count[element_type] );
        }
    }

    return rc;
}

/* ------------------------------------------------------------------------ */
static int start_element( HL7_Parser *parser, HL7_Element_Type element_type )
{
    int         rc = 0;
    char        tab_buffer[32];

    if ( parser->user_data != 0 )
    {
        Element_Stats *stats = (Element_Stats *) parser->user_data;

        stats->element_count[element_type]++;
    }

    printf( "%s<%s>\n",
            element_tab( tab_buffer, sizeof ( tab_buffer ) - 1, element_type ),
            element_type_name( element_type ) );

    return rc;
}

/* ------------------------------------------------------------------------ */
static int end_element( HL7_UNUSED HL7_Parser *parser, HL7_UNUSED HL7_Element_Type element_type )
{
    int         rc = 0;
    char        tab_buffer[32];

    printf( "%s</%s>\n",
            element_tab( tab_buffer, sizeof ( tab_buffer ) - 1, element_type ),
            element_type_name( element_type ) );

    return rc;
}

/* ------------------------------------------------------------------------ */
static int characters( HL7_Parser *parser, HL7_Element_Type element_type, HL7_Element *element )
{
    int         rc = 0;

    if ( parser->user_data != 0 )
    {
        Element_Stats *stats = (Element_Stats *) parser->user_data;

        stats->total_count++;

        if ( element->attr & HL7_TOKEN_ATTR_EMPTY )
        {
            stats->empty_count++;
        }
    }

    if ( element->length > 0 )
    {
        char        tab_buffer[32];
        char        characters_buffer[64];
        size_t      characters_length   = element->length;

        if ( characters_length > sizeof ( characters_buffer ) - 1 )
        {
            characters_length = sizeof ( characters_buffer ) - 1;
        }

        memcpy( characters_buffer, element->value, characters_length );
        characters_buffer[characters_length] = '\0';

        printf( "%s\"%s\" (%u bytes)\n",
                element_tab( tab_buffer, sizeof ( tab_buffer ) - 1, element_type - 1 ),
                characters_buffer,
                (unsigned) element->length );
    }

    return rc;
}


/* ------------------------------------------------------------------------ */
static char *element_tab( char *buffer, const size_t max_length, const HL7_Element_Type element_type )
{
    size_t tab_length = element_tab_length( element_type );

    if ( tab_length > max_length )
    {
        tab_length = max_length;
    }

    memset( buffer, ' ', tab_length );

    buffer[tab_length] = '\0';

    return buffer;
}

/* ------------------------------------------------------------------------ */
static size_t element_tab_length( const HL7_Element_Type element_type )
{
    return ( (int) HL7_ELEMENT_TYPE_COUNT - (int) element_type ) * TAB_LENGTH;
}

/* ------------------------------------------------------------------------ */
static char *element_type_name( const HL7_Element_Type element_type )
{
    static char *ELEMENT_TYPE_NAME[HL7_ELEMENT_TYPE_COUNT] = {
        "Subcomponent",
        "Component",
        "Repetition",
        "Field",
        "Segment"
    };

    return ( element_type < HL7_ELEMENT_TYPE_COUNT ? ELEMENT_TYPE_NAME[(int) element_type] : "Unknown" );
}

/* ------------------------------------------------------------------------ */
static char *attr_name( char *text, const HL7_Token_Attribute attr )
{
    static char *TOKEN_ATTR_NAME[HL7_TOKEN_ATTR_COUNT] = {
        "separator",
        "empty",
        "null",
        "formatted"
    };

    HL7_Token_Attribute attr_probe = 1;
    int                 i;

    *text = '\0';

    for ( i = 0; i < HL7_TOKEN_ATTR_COUNT; ++i )
    {
        if ( attr_probe & attr )
        {
            if ( *text == '\0' )
            {
                strcat( text, "(" );
            }
            else if ( attr_probe > 1 )
            {
                strcat( text, "|" );
            }

            strcat( text, TOKEN_ATTR_NAME[i] );
        }

        attr_probe <<= 1;
    }

    if ( *text != '\0' )
    {
        strcat( text, ")" );
    }

    return ( text );
}
