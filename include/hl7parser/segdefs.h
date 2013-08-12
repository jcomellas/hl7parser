#ifndef HL7PARSER_SEGDEFS_H
#define HL7PARSER_SEGDEFS_H

/**
* \file segdefs.h
*
* Miscellaneous segment definitions.
*
* \internal
* Copyright (c) 2003-2013 Juan Jose Comellas <juanjo@comellas.org>
*/

/* ------------------------------------------------------------------------
   Headers
   ------------------------------------------------------------------------ */

#include <hl7parser/config.h>
#include <hl7parser/export.h>
#include <hl7parser/segment.h>
#include <hl7parser/settings.h>

BEGIN_C_DECL()


/* ------------------------------------------------------------------------
   Macros
   ------------------------------------------------------------------------ */

/* Table HL70103: Processing ID */
#define HL7_MSH_DEBUG                       "D"
#define HL7_MSH_PRODUCTION                  "P"

/* Table TDU0286: Provider role */
#define HL7_PRD_PRIMARY_CARE_PROVIDER       "PS"
#define HL7_PRD_PRESCRIBING_PROVIDER        "PR"
#define HL7_PRD_EFFECTOR_PROVIDER           "EF"
#define HL7_PRD_REFERRED_TO_PROVIDER        "RT"
#define HL7_PRD_LOCATION_PROVIDER           "PL"

#define HL7_PRD_PRIMARY_CARE_PROVIDER_TEXT  "Solicitante"
#define HL7_PRD_PRESCRIBING_PROVIDER_TEXT   "Prescriptor"
#define HL7_PRD_EFFECTOR_PROVIDER_TEXT      "Efector"
#define HL7_PRD_REFERRED_TO_PROVIDER_TEXT   ""
#define HL7_PRD_LOCATION_PROVIDER_TEXT      "Sede"

/* Table TPC0338: Provider ID type */
#define HL7_PRD_ID_TYPE_CUIT                "CU"
#define HL7_PRD_ID_TYPE_PAYOR               "PR"
#define HL7_PRD_ID_TYPE_NATIONAL            "MN"
#define HL7_PRD_ID_TYPE_PROVINCIAL          "MP"

/* Table TDU0007: Admission type. */
#define HL7_PV1_ADMISSION_GUARD             "G"
#define HL7_PV1_ADMISSION_URGENT            "U"
#define HL7_PV1_ADMISSION_PROGRAMMED        "P"

/* Table HL70208: Query response status. */
#define HL7_QAK_OK                          "OK"
#define HL7_QAK_NO_DATA_FOUND               "NF"
#define HL7_QAK_APPLICATION_ERROR           "AE"
#define HL7_QAK_APPLICATION_REJECT          "AR"

/* Table TPC0003: Patient VAT status */
#define HL7_ZIN_VAT_STATUS_FREE             "Exnt"
#define HL7_ZIN_VAT_STATUS_TAXED            "Grav"
#define HL7_ZIN_VAT_STATUS_FREE_TEXT        "Exento"
#define HL7_ZIN_VAT_STATUS_TAXED_TEXT       "Gravado"


/* ------------------------------------------------------------------------
   Function prototypes
   ------------------------------------------------------------------------ */

HL7_EXPORT int hl7_msh_init( HL7_Segment *msh, HL7_Settings *settings );



END_C_DECL()

#endif /* HL7PARSER_SEGDEFS_H */
