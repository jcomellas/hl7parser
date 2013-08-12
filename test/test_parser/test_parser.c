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
#include <hl7parser/message.h>
#include <hl7parser/parser.h>
#include <hl7parser/token.h>
#include <hl7parser/settings.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/* ------------------------------------------------------------------------
   Macros
   ------------------------------------------------------------------------ */

#define TAB_LENGTH  2


/* ------------------------------------------------------------------------
   Function prototypes
   ------------------------------------------------------------------------ */

static void     print_message( HL7_Message *message );
static void     print_node( HL7_Node *node, HL7_Element_Type element_type, const size_t tab_length );
static int      compare_hl7_buffers( HL7_Buffer *buffer_1, HL7_Buffer *buffer_2 );
static void     print_hl7_buffer( HL7_Buffer *buffer );

static char     *element_tab( char *buffer, const size_t max_length, const HL7_Element_Type element_type );
static size_t   element_tab_length( const HL7_Element_Type element_type );
static char     *element_type_name( const HL7_Element_Type element_type );
static char     *attr_name( char *text, const HL7_Token_Attribute attr );


/* ------------------------------------------------------------------------ */
/* int main( int argc, char *argv[] ) */
int main( void )
{
    static char MESSAGE_DATA[] =
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


    int             rc              = 0;
    HL7_Settings    settings;
    HL7_Buffer      input_buffer;
    HL7_Buffer      output_buffer;
    HL7_Allocator   allocator;
    HL7_Message     message;
    HL7_Parser      parser;
    char            *data;
    size_t          message_length  = sizeof ( MESSAGE_DATA ) - 1;

    hl7_settings_init( &settings );

    /* Initialize the buffer excluding the null terminator. */
    hl7_buffer_init( &input_buffer, MESSAGE_DATA, message_length );
    hl7_buffer_move_wr_ptr( &input_buffer, message_length );

    /* Initialize the message */
    hl7_allocator_init( &allocator, malloc, free );
    hl7_message_init( &message, &settings, &allocator );

    /* Initialize the parser. */
    hl7_parser_init( &parser, &settings );

    rc = hl7_parser_read( &parser, &message, &input_buffer );
    if ( rc == 0 )
    {
        print_message( &message );
    }

    /* Write the message an compare it with the original. */
    data = (char *) malloc( message_length );
    hl7_buffer_init( &output_buffer, data, message_length );

    rc = hl7_parser_write( &parser, &output_buffer, &message );

    hl7_buffer_reset( &input_buffer );
    hl7_buffer_move_wr_ptr( &input_buffer, message_length );

    compare_hl7_buffers( &input_buffer, &output_buffer );

    hl7_buffer_fini( &output_buffer );
    free( data );

    hl7_parser_fini( &parser );

    hl7_message_fini( &message );
    hl7_allocator_fini( &allocator );

    hl7_buffer_fini( &input_buffer );
    hl7_settings_fini( &settings );

    return rc;
}

/* ------------------------------------------------------------------------ */
static void print_message( HL7_Message *message )
{
    if ( message != 0 )
    {
        printf( "<Message>\n" );

        print_node( message->head, HL7_ELEMENT_SEGMENT, TAB_LENGTH );

        printf( "</Message>\n" );
    }
}

/* ------------------------------------------------------------------------ */
static void print_node( HL7_Node *node, HL7_Element_Type element_type, const size_t tab_length )
{
    static const char   ELEMENT_TAB[TAB_LENGTH + 1] = "  ";

    if ( node != 0 )
    {
        const char          *type_name;
        char                tab_buffer[32];
        char                characters_buffer[64];
        size_t              characters_length;

        memset( tab_buffer, ' ', tab_length );
        tab_buffer[tab_length] = '\0';

        do
        {
            type_name = element_type_name( element_type );

            printf( "%s<%s>\n", tab_buffer, type_name );

            if ( node->element.length > 0 )
            {
                characters_length = node->element.length;

                if ( characters_length > sizeof ( characters_buffer ) - 1 )
                {
                    characters_length = sizeof ( characters_buffer ) - 1;
                }

                memcpy( characters_buffer, node->element.value, characters_length );
                characters_buffer[characters_length] = '\0';

                printf( "%s%s\"%s\" (%u bytes)\n",
                        tab_buffer, ELEMENT_TAB, characters_buffer,
                        (unsigned) node->element.length );
            }

            if ( node->children != 0 )
            {
                print_node( node->children, hl7_child_type( element_type ), tab_length + TAB_LENGTH );
            }

            printf( "%s</%s>\n", tab_buffer, type_name );

            node = node->sibling;

        } while ( node != 0 );
    }
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

/* ------------------------------------------------------------------------ */
static int compare_hl7_buffers( HL7_Buffer *buffer_1, HL7_Buffer *buffer_2 )
{
    int     rc;
    size_t  length_1    = hl7_buffer_length( buffer_1 );
    size_t  length_2    = hl7_buffer_length( buffer_2 );

    if ( length_1 == length_2 &&
         memcmp( hl7_buffer_rd_ptr( buffer_1 ), hl7_buffer_rd_ptr( buffer_2 ), length_1 ) == 0 )
    {
        printf( "HL7 buffers match perfectly (%u bytes).\n", (unsigned) length_1 );

        rc = 0;
    }
    else
    {
        printf( "HL7 buffers don't match.\n\n"
                "--- buffer_1 (%u bytes):\n", (unsigned) length_1 );
        print_hl7_buffer( buffer_1 );
        printf( "\n"
                "--- buffer_2 (%u bytes):\n", (unsigned) length_2 );
        print_hl7_buffer( buffer_2 );

        rc = 0;
    }
    return rc;
}

/* ------------------------------------------------------------------------ */
static void print_hl7_buffer( HL7_Buffer *buffer )
{
    char    line[256];
    size_t  line_length;
    char    *buffer_end    = hl7_buffer_wr_ptr( buffer );
    char    *segment_begin = hl7_buffer_rd_ptr( buffer );
    char    *segment_end;

    while ( segment_begin < buffer_end )
    {
        segment_end = strchr( segment_begin, HL7_SEPARATOR_SEGMENT );

        if ( segment_end != 0 )
        {
            line_length = segment_end - segment_begin;

            if ( line_length < sizeof ( line ) - 1 )
            {
                memcpy( line, segment_begin, line_length );
                line[line_length] = '\0';
                puts( line );
            }
            else
            {
                memcpy( line, segment_begin, HL7_SEGMENT_ID_LENGTH );
                line[HL7_SEGMENT_ID_LENGTH] = '\0';
                printf( "%s: segment too long to print (%u bytes).\n",
                        line, (unsigned) line_length );
            }
        }
        else
        {
            printf( "Could not find segment separator.\n" );
            break;
        }

        segment_begin = segment_end + 1;
    }
}
