#ifndef HL7PARSER_SEG_MSH_H
#define HL7PARSER_SEG_MSH_H

/**
* \file seg_msh.h
*
* Message header segment (MSH) accessors for the HL7 parser.
*
* \internal
* Copyright (c) 2011 Juan Jose Comellas <juanjo@comellas.org>
*
* \warning DO NOT MODIFY THIS FILE.
*
* Autogenerated by the ./hl7segdef.py script on Mon Jun  6 12:54:47 2011
*/

/* ------------------------------------------------------------------------
   Headers
   ------------------------------------------------------------------------ */

#include <hl7parser/config.h>
#include <hl7parser/element.h>
#include <hl7parser/export.h>
#include <hl7parser/segment.h>

BEGIN_C_DECL()

/* ------------------------------------------------------------------------
   Function prototypes
   ------------------------------------------------------------------------ */

/**
* Get the field_separator (MSH.1) field.
*/
HL7_EXPORT HL7_Element *hl7_msh_field_separator( HL7_Segment *segment );
/**
* Set the field_separator (MSH.1) field.
*/
HL7_EXPORT int hl7_msh_set_field_separator( HL7_Segment *segment, HL7_Element *element );
/**
* Set the field_separator (MSH.1) field as a string.
*/
HL7_EXPORT int hl7_msh_set_field_separator_str( HL7_Segment *segment, const char *value );
/**
* Get the encoding_characters (MSH.2) field.
*/
HL7_EXPORT HL7_Element *hl7_msh_encoding_characters( HL7_Segment *segment );
/**
* Set the encoding_characters (MSH.2) field.
*/
HL7_EXPORT int hl7_msh_set_encoding_characters( HL7_Segment *segment, HL7_Element *element );
/**
* Set the encoding_characters (MSH.2) field as a string.
*/
HL7_EXPORT int hl7_msh_set_encoding_characters_str( HL7_Segment *segment, const char *value );
/**
* Get the sending_application_id (MSH.3.1) component.
*/
HL7_EXPORT HL7_Element *hl7_msh_sending_application_id( HL7_Segment *segment );
/**
* Set the sending_application_id (MSH.3.1) component.
*/
HL7_EXPORT int hl7_msh_set_sending_application_id( HL7_Segment *segment, HL7_Element *element );
/**
* Set the sending_application_id (MSH.3.1) component as a string.
*/
HL7_EXPORT int hl7_msh_set_sending_application_id_str( HL7_Segment *segment, const char *value );
/**
* Get the sending_facility_id (MSH.4.1) component.
*/
HL7_EXPORT HL7_Element *hl7_msh_sending_facility_id( HL7_Segment *segment );
/**
* Set the sending_facility_id (MSH.4.1) component.
*/
HL7_EXPORT int hl7_msh_set_sending_facility_id( HL7_Segment *segment, HL7_Element *element );
/**
* Set the sending_facility_id (MSH.4.1) component as a string.
*/
HL7_EXPORT int hl7_msh_set_sending_facility_id_str( HL7_Segment *segment, const char *value );
/**
* Get the sending_facility_universal_id (MSH.4.2) component.
*/
HL7_EXPORT HL7_Element *hl7_msh_sending_facility_universal_id( HL7_Segment *segment );
/**
* Set the sending_facility_universal_id (MSH.4.2) component.
*/
HL7_EXPORT int hl7_msh_set_sending_facility_universal_id( HL7_Segment *segment, HL7_Element *element );
/**
* Set the sending_facility_universal_id (MSH.4.2) component as a string.
*/
HL7_EXPORT int hl7_msh_set_sending_facility_universal_id_str( HL7_Segment *segment, const char *value );
/**
* Get the sending_facility_universal_id_type (MSH.4.3) component.
*/
HL7_EXPORT HL7_Element *hl7_msh_sending_facility_universal_id_type( HL7_Segment *segment );
/**
* Set the sending_facility_universal_id_type (MSH.4.3) component.
*/
HL7_EXPORT int hl7_msh_set_sending_facility_universal_id_type( HL7_Segment *segment, HL7_Element *element );
/**
* Set the sending_facility_universal_id_type (MSH.4.3) component as a string.
*/
HL7_EXPORT int hl7_msh_set_sending_facility_universal_id_type_str( HL7_Segment *segment, const char *value );
/**
* Get the receiving_application_id (MSH.5.1) component.
*/
HL7_EXPORT HL7_Element *hl7_msh_receiving_application_id( HL7_Segment *segment );
/**
* Set the receiving_application_id (MSH.5.1) component.
*/
HL7_EXPORT int hl7_msh_set_receiving_application_id( HL7_Segment *segment, HL7_Element *element );
/**
* Set the receiving_application_id (MSH.5.1) component as a string.
*/
HL7_EXPORT int hl7_msh_set_receiving_application_id_str( HL7_Segment *segment, const char *value );
/**
* Get the receiving_facility_id (MSH.6.1) component.
*/
HL7_EXPORT HL7_Element *hl7_msh_receiving_facility_id( HL7_Segment *segment );
/**
* Set the receiving_facility_id (MSH.6.1) component.
*/
HL7_EXPORT int hl7_msh_set_receiving_facility_id( HL7_Segment *segment, HL7_Element *element );
/**
* Set the receiving_facility_id (MSH.6.1) component as a string.
*/
HL7_EXPORT int hl7_msh_set_receiving_facility_id_str( HL7_Segment *segment, const char *value );
/**
* Get the receiving_facility_universal_id (MSH.6.2) component.
*/
HL7_EXPORT HL7_Element *hl7_msh_receiving_facility_universal_id( HL7_Segment *segment );
/**
* Set the receiving_facility_universal_id (MSH.6.2) component.
*/
HL7_EXPORT int hl7_msh_set_receiving_facility_universal_id( HL7_Segment *segment, HL7_Element *element );
/**
* Set the receiving_facility_universal_id (MSH.6.2) component as a string.
*/
HL7_EXPORT int hl7_msh_set_receiving_facility_universal_id_str( HL7_Segment *segment, const char *value );
/**
* Get the receiving_facility_universal_id_type (MSH.6.3) component.
*/
HL7_EXPORT HL7_Element *hl7_msh_receiving_facility_universal_id_type( HL7_Segment *segment );
/**
* Set the receiving_facility_universal_id_type (MSH.6.3) component.
*/
HL7_EXPORT int hl7_msh_set_receiving_facility_universal_id_type( HL7_Segment *segment, HL7_Element *element );
/**
* Set the receiving_facility_universal_id_type (MSH.6.3) component as a string.
*/
HL7_EXPORT int hl7_msh_set_receiving_facility_universal_id_type_str( HL7_Segment *segment, const char *value );
/**
* Get the message_date (MSH.7) field.
*/
HL7_EXPORT time_t hl7_msh_message_date( HL7_Segment *segment );
/**
* Set the message_date (MSH.7) field.
*/
HL7_EXPORT int hl7_msh_set_message_date( HL7_Segment *segment, HL7_Element *element );
/**
* Set the message_date (MSH.7) field as a time_t.
*/
HL7_EXPORT int hl7_msh_set_message_date_time( HL7_Segment *segment, const time_t value );
/**
* Get the message_type (MSH.9.1) component.
*/
HL7_EXPORT HL7_Element *hl7_msh_message_type( HL7_Segment *segment );
/**
* Set the message_type (MSH.9.1) component.
*/
HL7_EXPORT int hl7_msh_set_message_type( HL7_Segment *segment, HL7_Element *element );
/**
* Set the message_type (MSH.9.1) component as a string.
*/
HL7_EXPORT int hl7_msh_set_message_type_str( HL7_Segment *segment, const char *value );
/**
* Get the trigger_event (MSH.9.2) component.
*/
HL7_EXPORT HL7_Element *hl7_msh_trigger_event( HL7_Segment *segment );
/**
* Set the trigger_event (MSH.9.2) component.
*/
HL7_EXPORT int hl7_msh_set_trigger_event( HL7_Segment *segment, HL7_Element *element );
/**
* Set the trigger_event (MSH.9.2) component as a string.
*/
HL7_EXPORT int hl7_msh_set_trigger_event_str( HL7_Segment *segment, const char *value );
/**
* Get the message_structure (MSH.9.3) component.
*/
HL7_EXPORT HL7_Element *hl7_msh_message_structure( HL7_Segment *segment );
/**
* Set the message_structure (MSH.9.3) component.
*/
HL7_EXPORT int hl7_msh_set_message_structure( HL7_Segment *segment, HL7_Element *element );
/**
* Set the message_structure (MSH.9.3) component as a string.
*/
HL7_EXPORT int hl7_msh_set_message_structure_str( HL7_Segment *segment, const char *value );
/**
* Get the message_control_id (MSH.10) field.
*/
HL7_EXPORT HL7_Element *hl7_msh_message_control_id( HL7_Segment *segment );
/**
* Set the message_control_id (MSH.10) field.
*/
HL7_EXPORT int hl7_msh_set_message_control_id( HL7_Segment *segment, HL7_Element *element );
/**
* Set the message_control_id (MSH.10) field as a string.
*/
HL7_EXPORT int hl7_msh_set_message_control_id_str( HL7_Segment *segment, const char *value );
/**
* Get the processing_id (MSH.11) field.
*/
HL7_EXPORT HL7_Element *hl7_msh_processing_id( HL7_Segment *segment );
/**
* Set the processing_id (MSH.11) field.
*/
HL7_EXPORT int hl7_msh_set_processing_id( HL7_Segment *segment, HL7_Element *element );
/**
* Set the processing_id (MSH.11) field as a string.
*/
HL7_EXPORT int hl7_msh_set_processing_id_str( HL7_Segment *segment, const char *value );
/**
* Get the version (MSH.12) field.
*/
HL7_EXPORT HL7_Element *hl7_msh_version( HL7_Segment *segment );
/**
* Set the version (MSH.12) field.
*/
HL7_EXPORT int hl7_msh_set_version( HL7_Segment *segment, HL7_Element *element );
/**
* Set the version (MSH.12) field as a string.
*/
HL7_EXPORT int hl7_msh_set_version_str( HL7_Segment *segment, const char *value );
/**
* Get the accept_ack_type (MSH.15) field.
*/
HL7_EXPORT HL7_Element *hl7_msh_accept_ack_type( HL7_Segment *segment );
/**
* Set the accept_ack_type (MSH.15) field.
*/
HL7_EXPORT int hl7_msh_set_accept_ack_type( HL7_Segment *segment, HL7_Element *element );
/**
* Set the accept_ack_type (MSH.15) field as a string.
*/
HL7_EXPORT int hl7_msh_set_accept_ack_type_str( HL7_Segment *segment, const char *value );
/**
* Get the application_ack_type (MSH.16) field.
*/
HL7_EXPORT HL7_Element *hl7_msh_application_ack_type( HL7_Segment *segment );
/**
* Set the application_ack_type (MSH.16) field.
*/
HL7_EXPORT int hl7_msh_set_application_ack_type( HL7_Segment *segment, HL7_Element *element );
/**
* Set the application_ack_type (MSH.16) field as a string.
*/
HL7_EXPORT int hl7_msh_set_application_ack_type_str( HL7_Segment *segment, const char *value );
/**
* Get the country_code (MSH.17) field.
*/
HL7_EXPORT HL7_Element *hl7_msh_country_code( HL7_Segment *segment );
/**
* Set the country_code (MSH.17) field.
*/
HL7_EXPORT int hl7_msh_set_country_code( HL7_Segment *segment, HL7_Element *element );
/**
* Set the country_code (MSH.17) field as a string.
*/
HL7_EXPORT int hl7_msh_set_country_code_str( HL7_Segment *segment, const char *value );

END_C_DECL()

#endif /* HL7_SEG_MSH_H */
