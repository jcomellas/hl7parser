#ifndef HL7PARSER_BOOL_H
#define HL7PARSER_BOOL_H

/**
* \file bool.h
*
* Definition of boolean types similar to the C++ ones.
*
* \internal
* Copyright (c) 2003-2011 \b Erlar (http://erlar.com)
*/

/* ------------------------------------------------------------------------
   Typedefs
   ------------------------------------------------------------------------ */

#ifndef __cplusplus

#ifndef bool

/**
* \typedef bool
* C++ \c bool data type look-alike.
*/
typedef int bool;

#endif

#ifndef false
#   define false                    ( (bool) 0 )
#endif

#ifndef true
#   define true                     ( (bool) 1 )
#endif

#endif /* __cplusplus */

#endif  /* HL7PARSER_BOOL_H */

