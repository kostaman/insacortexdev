
#define APP_Task_$EXEC_NAME$_START_SEC_CODE
#include "tpl_memmap.h"
/*
 * Task $EXEC_NAME$ function prototype
 */
FUNC(void, OS_APPL_CODE) $EXEC_FUNCTION$(void);
#define APP_Task_$EXEC_NAME$_STOP_SEC_CODE
#include "tpl_memmap.h"


#ifdef WITH_AUTOSAR_TIMING_PROTECTION
#define OS_START_SEC_VAR_UNSPECIFIED
#include "tpl_memmap.h"
$TIMING_PROT_STRUCT$
#define OS_STOP_SEC_VAR_UNSPECIFIED
#include "tpl_memmap.h"
#endif


#define OS_START_SEC_CONST_UNSPECIFIED
#include "tpl_memmap.h"
/*
 * Static descriptor of task $EXEC_NAME$
 */
CONST(tpl_proc_static, OS_CONST) $EXEC_STATIC$ = {
    /* context                  */  $EXEC_CONTEXT$,
    /* stack                    */  $EXEC_STACK$,
    /* entry point (function)   */  $EXEC_FUNCTION$,
    /* internal ressource       */  $RESOURCE_PTR$,
    /* task id                  */  $TASK_ID$,
#ifdef WITH_OSAPPLICATION
    /* OS application id        */  $APP_ID$,
#endif
    /* task base priority       */  $TASK_PRIORITY$,
    /* max activation count     */  $TASK_MAX_ACT_COUNT$,
    /* task type                */  $TASK_TYPE$,
#ifdef WITH_AUTOSAR_TIMING_PROTECTION
    /* pointer to the timing
       protection descriptor    */  $TIMING_PROT_REF$
#endif
};

#define OS_STOP_SEC_CONST_UNSPECIFIED
#include "tpl_memmap.h"


#define OS_START_SEC_VAR_UNSPECIFIED
#include "tpl_memmap.h"
/*
 * Dynamic descriptor of task $EXEC_NAME$
 */
VAR(tpl_proc, OS_VAR) $TASK$ = {
    /* resources                      */  NULL,
#if WITH_MEMORY_PROTECTION == YES
    /* if > 0 the process is trusted  */  $TRUSTED_COUNT$,    
#endif /* WITH_MEMORY_PROTECTION */
    /* activate count                 */  0,
    /* task priority                  */  (tpl_priority)$TASK_PRIORITY$,
    /* task state                     */  $TASK_STATE$
#ifdef WITH_AUTOSAR_TIMING_PROTECTION
    /* activation allowed             */  ,TRUE
#endif
};

$TASK_EVTS$

#define OS_STOP_SEC_VAR_UNSPECIFIED
#include "tpl_memmap.h"