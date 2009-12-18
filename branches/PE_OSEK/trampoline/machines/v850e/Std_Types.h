/*=============================================================================
** Trampoline OS
**
** Trampoline is copyright (c) IRCCyN 2005+
** Copyright ESEO for function and data structures documentation
** Trampoline is protected by the French intellectual property law.
**
** This software is distributed under the Lesser GNU Public Licence
**-----------------------------------------------------------------------------
** Supported MCUs       : NEC V850E
** Supported Compilers  : GHS Multi
**-----------------------------------------------------------------------------
** File name         : Std_Types.h
**
** Module name       : All AUTOSAR Modules
**
** Summary: Standard Types for all AUTOSAR Modules
**
**= History ====================================================================
** 01.00  N. Cornet 04/19/07
** - Creation
==============================================================================*/

#ifndef STD_TYPES_H
#define STD_TYPES_H

/******************************************************************************/
/* INCLUSIONS                                                                 */
/******************************************************************************/
#include "Platform_Types.h"
#include "Compiler.h"

/******************************************************************************/
/* TYPE DEFINITIONS                                                           */
/******************************************************************************/
typedef uint8 Std_ReturnType;
typedef struct
{
    uint16 vendorID;
    uint8 moduleID;
    uint8 sw_major_version;
    uint8 sw_minor_version;
    uint8 sw_patch_version;
} Std_VersionInfoType;

/******************************************************************************/
/* SYMBOL DEFINITIONS                                                         */
/******************************************************************************/
#ifndef STATUSTYPE_DEFINED
#define STATUSTYPE_DEFINED
typedef unsigned char StatusType; /* OSEK compliance */
#endif

#ifndef E_OK_DEFINED
#define E_OK_DEFINED
#define E_OK 0x00
#endif

#define E_NOT_OK 0x01

#define STD_HIGH 0x01 /* Physical state 5V or 3.3V */
#define STD_LOW 0x00 /* Physical state 0V */

#define STD_ACTIVE 0x01 /* Logical state active */
#define STD_IDLE 0x00 /* Logical state idle */

#define STD_ON 0x01
#define STD_OFF 0x00

/******************************************************************************/
/* PUBLISHED INFORMATION                                                      */
/******************************************************************************/
#define STD_TYPES_AR_MAJOR_VERSION 2
#define STD_TYPES_AR_MINOR_VERSION 1
#define STD_TYPES_AR_PATCH_VERSION 0

#endif /* STD_TYPES_H */

