/* ------------------------------------------------------------------------
   Headers
   ------------------------------------------------------------------------ */

#include <hl7parser/buffer.h>
#include <hl7parser/defs.h>
#include <hl7parser/element.h>
#include <hl7parser/message.h>
#include <hl7parser/parser.h>
#include <hl7parser/segdefs.h>
#include <hl7parser/seg_err.h>
#include <hl7parser/seg_msa.h>
#include <hl7parser/seg_msh.h>
#include <hl7parser/settings.h>
#include <hl7parser/sprint.h>
#include <hl7parser/token.h>
#include <stdio.h>
#include <stdlib.h>


/* ------------------------------------------------------------------------
   Function prototypes
   ------------------------------------------------------------------------ */

int append_msh_error_segment( HL7_Message *hl7_response );
int append_msa_error_segment( HL7_Message *hl7_response, const char *message_control_id,
                              const char *error_code, const char *error_text );
int append_err_error_segment( HL7_Message *hl7_response, const char *error_code,
                              const char *error_text );

static char *get_message_control_id( void );


// ------------------------------------------------------------------------ //
int main( void )
{
    int             rc;
    HL7_Settings    parser_settings;
    HL7_Allocator   parser_allocator;
    HL7_Parser      parser;
    HL7_Message     output_message;
    HL7_Buffer      output_buffer;

    hl7_settings_init( &parser_settings );
    hl7_allocator_init( &parser_allocator, malloc, free );

    /* Initialize the parser. */
    hl7_parser_init( &parser, &parser_settings );

    /* Initialize the output message. */
    hl7_message_init( &output_message, &parser_settings, &parser_allocator );

    if ( append_msh_error_segment( &output_message ) == 0 &&
         append_msa_error_segment( &output_message, get_message_control_id(), "M001",
                                   "ERROR EN BASE DE DATOS" ) == 0 &&
         append_err_error_segment( &output_message, "M001", "ERROR TECNICO" ) == 0 )
    {
        char output_str[2048];
        char formatted_str[2048];

        /* Initialize the input buffer. */
        hl7_buffer_init( &output_buffer, output_str, sizeof ( output_str ) - 1 );

        /* Write the HL7 message into the response buffer. */
        rc = hl7_parser_write( &parser, &output_buffer, &output_message );

        hl7_sprint( formatted_str, sizeof ( formatted_str ),
                    hl7_buffer_rd_ptr( &output_buffer ),
                    hl7_buffer_length( &output_buffer ) );

        hl7_buffer_fini( &output_buffer );

        puts( formatted_str );

        rc = 0;
    }
    else
    {
        rc = -1;
    }

    hl7_message_fini( &output_message );

    hl7_parser_fini( &parser );

    hl7_allocator_fini( &parser_allocator );
    hl7_settings_fini( &parser_settings );

    return rc;
}

// ------------------------------------------------------------------------ //
int append_msh_error_segment( HL7_Message *hl7_response )
{
    int         rc = -1;
    HL7_Segment msh;

    if ( hl7_segment_create( &msh, "MSH", hl7_response->allocator ) == 0 &&
         hl7_msh_init( &msh, hl7_response->settings ) == 0 )
    {
        /* Sender: server */
        hl7_msh_set_sending_application_id_str( &msh, "SERV" );
        hl7_msh_set_sending_facility_id_str( &msh, "HMO" );
        hl7_msh_set_sending_facility_universal_id_str( &msh, "223344" );
        hl7_msh_set_sending_facility_universal_id_type_str( &msh, "IIN" );
        /* Receiver: client */
        hl7_msh_set_receiving_application_id_str( &msh, "TIPO0100M" );
        hl7_msh_set_receiving_facility_id_str( &msh, "TIPO00000001" );
        hl7_msh_set_receiving_facility_universal_id_str( &msh, "99999999999" );
        hl7_msh_set_receiving_facility_universal_id_type_str( &msh, "CARRIER" );
        /* Message time */
        hl7_msh_set_message_date_time( &msh, time( 0 ) );
        /* Message type */
        hl7_msh_set_message_type_str( &msh, "ACK" );
        /*
        hl7_msh_set_trigger_event_str( &msh, message_type->hl7_trigger_event );
        hl7_msh_set_message_structure_str( &msh, message_type->hl7_message_structure );
        */
        /* Message control ID */
        hl7_msh_set_message_control_id_str( &msh, get_message_control_id() );
        // Processing ID
        hl7_msh_set_processing_id_str( &msh, "P" );

        rc = hl7_message_append_segment( hl7_response, &msh );
    }
    return rc;
}

// ------------------------------------------------------------------------ //
int append_msa_error_segment( HL7_Message *hl7_response, const char *message_control_id,
                              const char *error_code, const char *error_text )
{
    int         rc = -1;
    HL7_Segment msa;

    if ( hl7_segment_create( &msa, "MSA", hl7_response->allocator ) == 0 )
    {
        hl7_msa_set_ack_code_str( &msa, "AE" );
        hl7_msa_set_message_control_id_str( &msa, message_control_id );
        hl7_msa_set_error_code_str( &msa, error_code );
        hl7_msa_set_error_text_str( &msa, error_text );

        rc = hl7_message_append_segment( hl7_response, &msa );
    }
    return rc;
}

// ------------------------------------------------------------------------ //
int append_err_error_segment( HL7_Message *hl7_response, const char *error_code,
                              const char *error_text )
{
    int         rc = -1;
    HL7_Segment err;

    if ( hl7_segment_create( &err, "ERR", hl7_response->allocator ) == 0 )
    {
        hl7_err_set_error_code_str( &err, error_code );
        hl7_err_set_error_text_str( &err, error_text );

        rc = hl7_message_append_segment( hl7_response, &err );
    }
    return rc;
}

// ------------------------------------------------------------------------ //
static char *get_message_control_id( void )
{
    static char message_control_id[24];

    time_t      current_time        = time( 0 );
    struct tm   *datetime           = localtime( &current_time );

    snprintf( message_control_id, sizeof ( message_control_id ),
              "%04d%02d%02d%02d%02d%02d%03d",
              datetime->tm_year + 1900, datetime->tm_mon + 1,
              datetime->tm_mday, datetime->tm_hour,
              datetime->tm_min, datetime->tm_sec, rand() % 1000 );

    return ( message_control_id );
}
