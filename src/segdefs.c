/**
* \file segdefs.c
*
* Miscellaneous segment definitions.
*
* \internal
* Copyright (c) 2003-2011 \b Erlar (http://erlar.com)
*/

/* ------------------------------------------------------------------------
   Headers
   ------------------------------------------------------------------------ */

#include <hl7parser/config.h>
#include <hl7parser/segdefs.h>
#include <hl7parser/segment.h>
#include <hl7parser/seg_msh.h>
#include <hl7parser/settings.h>

BEGIN_C_DECL()


/* ------------------------------------------------------------------------ */
HL7_EXPORT int hl7_msh_init( HL7_Segment *msh, HL7_Settings *settings )
{
    int rc = -1;

    if ( msh != 0 )
    {
        HL7_Element element;

        hl7_element_init( &element );

        if ( hl7_element_set_ptr( &element, &settings->separator[HL7_ELEMENT_FIELD], 1, false ) == 0 &&
             hl7_msh_set_field_separator( msh, &element ) == 0 )
        {
            static char encoding_characters[4];
            static char processing_id[]         = "P";
            static char version[]               = "2.4";
            static char country_code[]          = "ARG";
            static char accept_ack_type[]       = "NE";
            static char application_ack_type[]  = "AL";

            encoding_characters[0]  = settings->separator[HL7_ELEMENT_COMPONENT];
            encoding_characters[1]  = settings->separator[HL7_ELEMENT_REPETITION];
            encoding_characters[2]  = settings->escape_char;
            encoding_characters[3]  = settings->separator[HL7_ELEMENT_SUBCOMPONENT];

            // Encoding characters
            if ( hl7_element_set_ptr( &element, encoding_characters, sizeof ( encoding_characters ), false ) == 0 &&
                 hl7_msh_set_encoding_characters( msh, &element ) == 0 &&
                 // Message time
                 hl7_msh_set_message_date_time( msh, time( 0 ) ) == 0 &&
                 // Processing ID: P=production
                 hl7_element_set_ptr( &element, processing_id, sizeof ( processing_id ) - 1, false ) == 0 &&
                 hl7_msh_set_processing_id( msh, &element ) == 0 &&
                 // Version: 2.4
                 hl7_element_set_ptr( &element, version, sizeof ( version ) - 1, false ) == 0 &&
                 hl7_msh_set_version( msh, &element ) == 0 &&
                 // Accept ACK type: NE (Never)
                 hl7_element_set_ptr( &element, accept_ack_type, sizeof ( accept_ack_type ) - 1, false ) == 0 &&
                 hl7_msh_set_accept_ack_type( msh, &element ) == 0 &&
                 // Application ACK type: AL (Always)
                 hl7_element_set_ptr( &element, application_ack_type, sizeof ( application_ack_type ) - 1, false ) == 0 &&
                 hl7_msh_set_application_ack_type( msh, &element ) == 0 &&
                 // Country code: ARG (Argentina)
                 hl7_element_set_ptr( &element, country_code, sizeof ( country_code ) - 1, false ) == 0 &&
                 hl7_msh_set_country_code( msh, &element ) == 0 )
            {
                rc = 0;
            }
        }
    }
    return rc;
}

