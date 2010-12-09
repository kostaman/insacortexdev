/**
 * @file tpl_os_error.c
 *
 * @section copyright Copyright
 *
 * Trampoline OS
 *
 * Trampoline is copyright (c) IRCCyN 2005+
 * Copyright ESEO for function and data structures documentation
 * Trampoline is protected by the French intellectual property law.
 *
 * This software is distributed under the Lesser GNU Public Licence
 *
 * @section infos File informations
 *
 * $Date: 2009-01-30 15:37:16 +0100 (Ven, 30 jan 2009) $
 * $Rev: 549 $
 * $Author: jlb $
 * $URL: https://trampoline.rts-software.org/svn/trunk/os/tpl_os_error.c $
 *
 * @section descr File description
 *
 * Trampoline Errors macros, functions and datatypes header
 */

#include "tpl_os_errorhook.h"
#include "tpl_os_error.h"
#include "tpl_os_internal_types.h"
#include "tpl_os_definitions.h"

#ifdef WITH_ERROR_HOOK

#define OS_START_SEC_VAR_UNSPECIFIED
#include "tpl_memmap.h"

VAR(tpl_service_call_desc, OS_VAR) tpl_service;

#define OS_STOP_SEC_VAR_UNSPECIFIED
#include "tpl_memmap.h"


#define OS_START_SEC_CODE
#include "tpl_memmap.h"

/**
 * Function used to call the application error hook
 *
 * @param error error code which raised the hook call
 *
 * Do not call it directly, use #PROCESS_ERROR macro
 *
 * @see #PROCESS_ERROR
 */
FUNC(void, OS_CODE) tpl_call_error_hook(
    CONST(tpl_status, AUTOMATIC) error)
{

/**
 * This flag is used to avoid error hook call recursion
 */
    STATIC VAR(tpl_bool, AUTOMATIC) in_error_hook = FALSE;

    if (!in_error_hook)
    {
        in_error_hook = TRUE;
        ErrorHook(OSEK_STATUS_MASK & (error));
        in_error_hook = FALSE;
    }
}

#define OS_STOP_SEC_CODE
#include "tpl_memmap.h"

#endif /* WITH_ERROR_HOOK */

/* End of file tpl_os_error.c */
