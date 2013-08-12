#ifndef HL7PARSER_SEG_PV1_H
#define HL7PARSER_SEG_PV1_H

/**
* \file seg_pv1.h
*
* Patient visit segment (PV1) accessors for the HL7 parser.
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
* Get the set_id (PV1.1) field.
*/
HL7_EXPORT HL7_Element *hl7_pv1_set_id( HL7_Segment *segment );
/**
* Set the set_id (PV1.1) field.
*/
HL7_EXPORT int hl7_pv1_set_set_id( HL7_Segment *segment, HL7_Element *element );
/**
* Set the set_id (PV1.1) field as a string.
*/
HL7_EXPORT int hl7_pv1_set_set_id_str( HL7_Segment *segment, const char *value );
/**
* Get the patient_class (PV1.2) field.
*/
HL7_EXPORT HL7_Element *hl7_pv1_patient_class( HL7_Segment *segment );
/**
* Set the patient_class (PV1.2) field.
*/
HL7_EXPORT int hl7_pv1_set_patient_class( HL7_Segment *segment, HL7_Element *element );
/**
* Set the patient_class (PV1.2) field as a string.
*/
HL7_EXPORT int hl7_pv1_set_patient_class_str( HL7_Segment *segment, const char *value );
/**
* Get the patient_point_of_care (PV1.3.1) component.
*/
HL7_EXPORT HL7_Element *hl7_pv1_patient_point_of_care( HL7_Segment *segment );
/**
* Set the patient_point_of_care (PV1.3.1) component.
*/
HL7_EXPORT int hl7_pv1_set_patient_point_of_care( HL7_Segment *segment, HL7_Element *element );
/**
* Set the patient_point_of_care (PV1.3.1) component as a string.
*/
HL7_EXPORT int hl7_pv1_set_patient_point_of_care_str( HL7_Segment *segment, const char *value );
/**
* Get the patient_location_facility (PV1.3.4) component.
*/
HL7_EXPORT HL7_Element *hl7_pv1_patient_location_facility( HL7_Segment *segment );
/**
* Set the patient_location_facility (PV1.3.4) component.
*/
HL7_EXPORT int hl7_pv1_set_patient_location_facility( HL7_Segment *segment, HL7_Element *element );
/**
* Set the patient_location_facility (PV1.3.4) component as a string.
*/
HL7_EXPORT int hl7_pv1_set_patient_location_facility_str( HL7_Segment *segment, const char *value );
/**
* Get the admission_type (PV1.4) field.
*/
HL7_EXPORT HL7_Element *hl7_pv1_admission_type( HL7_Segment *segment );
/**
* Set the admission_type (PV1.4) field.
*/
HL7_EXPORT int hl7_pv1_set_admission_type( HL7_Segment *segment, HL7_Element *element );
/**
* Set the admission_type (PV1.4) field as a string.
*/
HL7_EXPORT int hl7_pv1_set_admission_type_str( HL7_Segment *segment, const char *value );
/**
* Get the attending_doctor_id (PV1.7.1) component.
*/
HL7_EXPORT HL7_Element *hl7_pv1_attending_doctor_id( HL7_Segment *segment );
/**
* Set the attending_doctor_id (PV1.7.1) component.
*/
HL7_EXPORT int hl7_pv1_set_attending_doctor_id( HL7_Segment *segment, HL7_Element *element );
/**
* Set the attending_doctor_id (PV1.7.1) component as a string.
*/
HL7_EXPORT int hl7_pv1_set_attending_doctor_id_str( HL7_Segment *segment, const char *value );
/**
* Get the attending_doctor_last_name (PV1.7.2) component.
*/
HL7_EXPORT HL7_Element *hl7_pv1_attending_doctor_last_name( HL7_Segment *segment );
/**
* Set the attending_doctor_last_name (PV1.7.2) component.
*/
HL7_EXPORT int hl7_pv1_set_attending_doctor_last_name( HL7_Segment *segment, HL7_Element *element );
/**
* Set the attending_doctor_last_name (PV1.7.2) component as a string.
*/
HL7_EXPORT int hl7_pv1_set_attending_doctor_last_name_str( HL7_Segment *segment, const char *value );
/**
* Get the attending_doctor_first_name (PV1.7.3) component.
*/
HL7_EXPORT HL7_Element *hl7_pv1_attending_doctor_first_name( HL7_Segment *segment );
/**
* Set the attending_doctor_first_name (PV1.7.3) component.
*/
HL7_EXPORT int hl7_pv1_set_attending_doctor_first_name( HL7_Segment *segment, HL7_Element *element );
/**
* Set the attending_doctor_first_name (PV1.7.3) component as a string.
*/
HL7_EXPORT int hl7_pv1_set_attending_doctor_first_name_str( HL7_Segment *segment, const char *value );
/**
* Get the attending_doctor_assigning_authority (PV1.7.9) component.
*/
HL7_EXPORT HL7_Element *hl7_pv1_attending_doctor_assigning_authority( HL7_Segment *segment );
/**
* Set the attending_doctor_assigning_authority (PV1.7.9) component.
*/
HL7_EXPORT int hl7_pv1_set_attending_doctor_assigning_authority( HL7_Segment *segment, HL7_Element *element );
/**
* Set the attending_doctor_assigning_authority (PV1.7.9) component as a string.
*/
HL7_EXPORT int hl7_pv1_set_attending_doctor_assigning_authority_str( HL7_Segment *segment, const char *value );
/**
* Get the referring_doctor_id (PV1.8.1) component.
*/
HL7_EXPORT HL7_Element *hl7_pv1_referring_doctor_id( HL7_Segment *segment );
/**
* Set the referring_doctor_id (PV1.8.1) component.
*/
HL7_EXPORT int hl7_pv1_set_referring_doctor_id( HL7_Segment *segment, HL7_Element *element );
/**
* Set the referring_doctor_id (PV1.8.1) component as a string.
*/
HL7_EXPORT int hl7_pv1_set_referring_doctor_id_str( HL7_Segment *segment, const char *value );
/**
* Get the referring_doctor_last_name (PV1.8.2) component.
*/
HL7_EXPORT HL7_Element *hl7_pv1_referring_doctor_last_name( HL7_Segment *segment );
/**
* Set the referring_doctor_last_name (PV1.8.2) component.
*/
HL7_EXPORT int hl7_pv1_set_referring_doctor_last_name( HL7_Segment *segment, HL7_Element *element );
/**
* Set the referring_doctor_last_name (PV1.8.2) component as a string.
*/
HL7_EXPORT int hl7_pv1_set_referring_doctor_last_name_str( HL7_Segment *segment, const char *value );
/**
* Get the referring_doctor_first_name (PV1.8.3) component.
*/
HL7_EXPORT HL7_Element *hl7_pv1_referring_doctor_first_name( HL7_Segment *segment );
/**
* Set the referring_doctor_first_name (PV1.8.3) component.
*/
HL7_EXPORT int hl7_pv1_set_referring_doctor_first_name( HL7_Segment *segment, HL7_Element *element );
/**
* Set the referring_doctor_first_name (PV1.8.3) component as a string.
*/
HL7_EXPORT int hl7_pv1_set_referring_doctor_first_name_str( HL7_Segment *segment, const char *value );
/**
* Get the referring_doctor_assigning_authority (PV1.8.9) component.
*/
HL7_EXPORT HL7_Element *hl7_pv1_referring_doctor_assigning_authority( HL7_Segment *segment );
/**
* Set the referring_doctor_assigning_authority (PV1.8.9) component.
*/
HL7_EXPORT int hl7_pv1_set_referring_doctor_assigning_authority( HL7_Segment *segment, HL7_Element *element );
/**
* Set the referring_doctor_assigning_authority (PV1.8.9) component as a string.
*/
HL7_EXPORT int hl7_pv1_set_referring_doctor_assigning_authority_str( HL7_Segment *segment, const char *value );
/**
* Get the hospital_service (PV1.10) field.
*/
HL7_EXPORT HL7_Element *hl7_pv1_hospital_service( HL7_Segment *segment );
/**
* Set the hospital_service (PV1.10) field.
*/
HL7_EXPORT int hl7_pv1_set_hospital_service( HL7_Segment *segment, HL7_Element *element );
/**
* Set the hospital_service (PV1.10) field as a string.
*/
HL7_EXPORT int hl7_pv1_set_hospital_service_str( HL7_Segment *segment, const char *value );
/**
* Get the readmission_indicator (PV1.13) field.
*/
HL7_EXPORT HL7_Element *hl7_pv1_readmission_indicator( HL7_Segment *segment );
/**
* Set the readmission_indicator (PV1.13) field.
*/
HL7_EXPORT int hl7_pv1_set_readmission_indicator( HL7_Segment *segment, HL7_Element *element );
/**
* Set the readmission_indicator (PV1.13) field as a string.
*/
HL7_EXPORT int hl7_pv1_set_readmission_indicator_str( HL7_Segment *segment, const char *value );
/**
* Get the discharge_diposition (PV1.36) field.
*/
HL7_EXPORT HL7_Element *hl7_pv1_discharge_diposition( HL7_Segment *segment );
/**
* Set the discharge_diposition (PV1.36) field.
*/
HL7_EXPORT int hl7_pv1_set_discharge_diposition( HL7_Segment *segment, HL7_Element *element );
/**
* Set the discharge_diposition (PV1.36) field as a string.
*/
HL7_EXPORT int hl7_pv1_set_discharge_diposition_str( HL7_Segment *segment, const char *value );
/**
* Get the admit_date (PV1.44) field.
*/
HL7_EXPORT time_t hl7_pv1_admit_date( HL7_Segment *segment );
/**
* Set the admit_date (PV1.44) field.
*/
HL7_EXPORT int hl7_pv1_set_admit_date( HL7_Segment *segment, HL7_Element *element );
/**
* Set the admit_date (PV1.44) field as a time_t.
*/
HL7_EXPORT int hl7_pv1_set_admit_date_time( HL7_Segment *segment, const time_t value );
/**
* Get the discharge_date (PV1.45) field.
*/
HL7_EXPORT time_t hl7_pv1_discharge_date( HL7_Segment *segment );
/**
* Set the discharge_date (PV1.45) field.
*/
HL7_EXPORT int hl7_pv1_set_discharge_date( HL7_Segment *segment, HL7_Element *element );
/**
* Set the discharge_date (PV1.45) field as a time_t.
*/
HL7_EXPORT int hl7_pv1_set_discharge_date_time( HL7_Segment *segment, const time_t value );
/**
* Get the visit_indicator (PV1.51) field.
*/
HL7_EXPORT HL7_Element *hl7_pv1_visit_indicator( HL7_Segment *segment );
/**
* Set the visit_indicator (PV1.51) field.
*/
HL7_EXPORT int hl7_pv1_set_visit_indicator( HL7_Segment *segment, HL7_Element *element );
/**
* Set the visit_indicator (PV1.51) field as a string.
*/
HL7_EXPORT int hl7_pv1_set_visit_indicator_str( HL7_Segment *segment, const char *value );

END_C_DECL()

#endif /* HL7_SEG_PV1_H */
