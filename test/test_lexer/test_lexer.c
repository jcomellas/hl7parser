/* ------------------------------------------------------------------------
   $Id$

   Copyright (c) 2003 Novamens (http://www.novamens.com)

   Program to test the HL7 lexer.
   ------------------------------------------------------------------------ */

/* ------------------------------------------------------------------------
   Headers
   ------------------------------------------------------------------------ */

#include <hl7parser/buffer.h>
#include <hl7parser/element.h>
#include <hl7parser/lexer.h>
#include <hl7parser/settings.h>
#include <hl7parser/token.h>
#include <stdio.h>
#include <string.h>

/* ------------------------------------------------------------------------
   Macros
   ------------------------------------------------------------------------ */

#define TAB_LENGTH  2


/* ------------------------------------------------------------------------
   Function prototypes
   ------------------------------------------------------------------------ */

static char     *element_tab( char *buffer, const size_t max_length, const HL7_Element_Type element_type );
static size_t   element_tab_length( const HL7_Element_Type element_type );
static char     *element_type_name( const HL7_Element_Type element_type );
static char     *attr_name( char *text, const HL7_Token_Attribute attr );


/* ------------------------------------------------------------------------ */
/* int main( int argc, char *argv[] ) */
int main( void )
{
    static char message[] =
        "MSH|^~\\&|SERV|601818^^II|POSA|TECNET^ME0186^IP|20030304183039||RPA^I09|5538098|P|2.3|||NE|NE\r"
        "MSA|AA|ME018620030304182723||||B003^\r"
        "AUT||601818^^II||20030304||5538098||0|0\r"
        "PRD|9||||||20043153146^CU^\r"
        "PID|||0     1000109787027=9 2004009  00||9^\r"
        "DG1|1||Z71.8^^ICD10\r"
        "NTE|1|| DIAGNOSTICO INGRESADO\r";

    int                 rc              = 0;
    HL7_Settings        settings;
    HL7_Buffer          buffer;
    HL7_Lexer           lexer;
    HL7_Token           token;
    HL7_Element_Type    element_type    = HL7_ELEMENT_SEGMENT;
    char                attr_text[128];
    char                tab_buffer[32];

    hl7_settings_init( &settings );

    /* Initialize the buffer excluding the null terminator. */
    hl7_buffer_init( &buffer, message, sizeof ( message ) - 1 );
    hl7_buffer_set_wr_ptr( &buffer, message + sizeof ( message ) - 1 );

    hl7_lexer_init( &lexer, &settings, &buffer );

    while ( hl7_lexer_read( &lexer, &token ) == 0 && lexer.state != HL7_LEXER_STATE_END )
    {
        if ( token.attr & HL7_TOKEN_ATTR_SEPARATOR )
        {
            element_type = hl7_element_type( &settings, *token.value );

            printf( "%s<%s separator>\n",
                    element_tab( tab_buffer, sizeof ( tab_buffer ) - 1, element_type ),
                    element_type_name( element_type ) );
        }
        else
        {
            printf( "%s\"%.*s\" (%u bytes) %s\n",
                    element_tab( tab_buffer, sizeof ( tab_buffer ) - 1, element_type ),
                    (int) token.length,
                    ( token.value != 0 ? token.value : "" ),
                    (unsigned) token.length,
                    attr_name( attr_text, token.attr ) );
        }
    }

    hl7_lexer_fini( &lexer);
    hl7_buffer_fini( &buffer );
    hl7_settings_fini( &settings );

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
