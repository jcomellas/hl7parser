#ifndef HL7PARSER_EXPORT_H
#define HL7PARSER_EXPORT_H

/**
* \file export.h
*
* Definition of macros used to export symbols from DLLs.
*
* \internal
* Copyright (c) 2003-2013 Juan Jose Comellas <juanjo@comellas.org>
*/

BEGIN_C_DECL()


/* ------------------------------------------------------------------------
   Macros
   ------------------------------------------------------------------------ */

#if !defined( HL7PARSER_DLL ) && !defined( HL7PARSER_STATIC )
#   error You must define 'HL7PARSER_DLL' or 'HL7PARSER_STATIC'
#endif

#if defined( HL7PARSER_DLL ) && defined( WIN32 )
#   if defined( INSIDE_HL7PARSER )
#       define HL7_EXPORT   __declspec(dllexport)
#   else
#       define HL7_EXPORT   __declspec(dllimport)
#   endif
#else
#   define HL7_EXPORT
#endif

END_C_DECL()

#endif /* HL7PARSER_EXPORT_H */
