/**
 * @file tpl_os_definitions.h
 *
 * @section descr File description
 *
 * Here are defined all global symbolic values used in Trampoline.
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
 * $Date: 2009-11-13 17:46:22 +0100 (Ven, 13 nov 2009) $
 * $Rev: 965 $
 * $Author: jlb $
 * $URL: https://trampoline.rts-software.org/svn/trunk/os/tpl_os_definitions.h $
 */

#ifndef TPL_OS_DEFINITIONS_H
#define TPL_OS_DEFINITIONS_H

#include "tpl_os_application_def.h"

/**
 * @def FALSE
 *
 * boolean false value
 *
 * @see #tpl_bool
 */
#ifndef FALSE
#define FALSE   ((tpl_bool)0)
#endif
/**
 * @def TRUE
 *
 * boolean true value
 *
 * @see #tpl_bool
 */
#ifndef TRUE
#define TRUE    ((tpl_bool)1)
#endif

#ifndef NULL
#define NULL 0
#endif

/***********************
 * Conformance classes *
 ***********************/

/**
 * @def CONFORM_ECC1
 *
 * identifies the ECC1 conformance class
 *
 * @see #CONFORMANCE_CLASS
 */
#define CONFORM_ECC1        1

/**
 * @def CONFORM_ECC2
 *
 * identifies the ECC2 conformance class
 *
 * @see #CONFORMANCE_CLASS
 */
#define CONFORM_ECC2        2

/**
 * @def CONFORMANCE_CLASS
 *
 * represents the configured conformance class
 *
 * @warning at this time, Trampoline only supports ECC2
 */
#define CONFORMANCE_CLASS   CONFORM_ECC2


/****************
 * Result codes *
 ****************/

/**
 * @def E_OK
 *
 * This error code means : no error
 *
 * @warning OSEK error code meanings are not globally defined. Refer to each
 * standard service definition to know the exact meaning in this specific
 * context.
 */
#ifndef E_OK_DEFINED
#define E_OK_DEFINED
#define E_OK            0
#endif
/**
 * @def E_OS_ACCESS
 *
 * This error code means : calling task is not an extended task"
 *
 * @warning OSEK error code meanings are not globally defined. Refer to each
 * standard service definition to know the exact meaning.
 */
#define E_OS_ACCESS     1

/**
 * @def E_OS_CALLEVEL
 *
 * This error code means : call at interrupt level
 *
 * @warning OSEK error code meanings are not globally defined. Refer to each
 * standard service definition to know the exact meaning.
 */
#define E_OS_CALLEVEL   2

/**
 * @def E_OS_ID
 *
 * This error code means : invalid identifier
 *
 * @warning OSEK error code meanings are not globally defined. Refer to each
 * standard service definition to know the exact meaning.
 */
#define E_OS_ID         3

/**
 * @def E_OS_LIMIT
 *
 * This error code means : limit exceeded. The only limit known to raise this
 * error is the number of task activations
 *
 * @warning OSEK error code meanings are not globally defined. Refer to each
 * standard service definition to know the exact meaning.
 */
#define E_OS_LIMIT      4

/**
 * @def E_OS_NOFUNC
 *
 * This error code means : not appropriate.
 *
 * @warning OSEK error code meanings are not globally defined. Refer to each
 * standard service definition to know the exact meaning.
 */
#define E_OS_NOFUNC     5

/**
 * @def E_OS_RESOURCE
 *
 * This error code means : calling task still occupies resources
 *
 * @warning OSEK error code meanings are not globally defined. Refer to each
 * standard service definition to know the exact meaning.
 */
#define E_OS_RESOURCE   6

/**
 * @def E_OS_STATE
 *
 * This error code means : related state not appropriate
 *
 * @warning OSEK error code meanings are not globally defined. Refer to each
 * standard service definition to know the exact meaning.
 */
#define E_OS_STATE      7

/**
 * @def E_OS_VALUE
 *
 * This error code means : value outside of the admissible limits
 *
 * @warning OSEK error code meanings are not globally defined. Refer to each
 * standard service definition to know the exact meaning.
 */
#define E_OS_VALUE      8

/*#ifdef WITH_AUTOSAR*/

/**
 * @def E_OS_DISABLEDINT
 *
 * A service of the OS is called inside an interrupt disable/enable pair 
 */
#define E_OS_DISABLEDINT          19

/*#endif*/

/**************************************
 * Special result code for Trampoline *
 * as long as associated masks        *
 **************************************/

/**
 * @def NO_SPECIAL_CODE
 *
 * Nothing particular to Trampoline in this code.
 *
 * @note This is a Trampoline result code, not an OSEK one.
 *
 * @see #tpl_status
 */
#define NO_SPECIAL_CODE         0

/**
 * @def NEED_RESCHEDULING
 *
 * Scheduler have to be called, probably because the ready list
 * has changed.
 *
 * @note This is a Trampoline result code, not an OSEK one.
 *
 * @see #tpl_status
 */
#define NEED_RESCHEDULING       32

/**
 * @def E_OK_AND_SCHEDULE
 *
 * Combines OSEK-E_OK and Trampoline-NEED_RESCHEDULING result codes
 *
 * @see #tpl_status
 */
#define E_OK_AND_SCHEDULE   ((tpl_status)E_OK | (tpl_status)NEED_RESCHEDULING)

/**
 * @def OSEK_STATUS_MASK
 *
 * This AND mask can be used to keep only result code
 * specific to OSEK in a tpl_status (StatusType)
 * result code.
 *
 * @see #tpl_status
 */
#define OSEK_STATUS_MASK        0x1F

/**
 * @def TRAMPOLINE_STATUS_MASK
 *
 * This AND mask can be used to keep only result code
 * specific to Trampoline in a tpl_status (StatusType)
 * result code.
 *
 * @see #tpl_status
 */
#define TRAMPOLINE_STATUS_MASK  0xE0


/************************************
 * Public states of a task or ISR2  *
 ************************************/
/**
 * @def SUSPENDED
 *
 * Task is suspended.
 *
 * @see #tpl_exec_state
 */
#define SUSPENDED       0x0

/**
 * @def READY
 *
 * Task is ready (to be run, or elected by scheduler).
 *
 * @see #tpl_exec_state
 */
#define READY           0x1

/**
 * @def RUNNING
 *
 * Task is currently running.
 *
 * @see #tpl_exec_state
 */
#define RUNNING         0x2

#if (CONFORMANCE_CLASS == CONFORM_ECC1) || (CONFORMANCE_CLASS == CONFORM_ECC2)
/**
 * @def WAITING
 *
 * Task is waiting
 *
 * @see #tpl_exec_state
 */
#define WAITING         0x3
#endif


/************************************
 * bits of tpl_need_switch          *
 ************************************/

/**
 * @def NO_NEED_SWITCH
 *
 * Used for tpl_need_switch variable. No context switch should occur
 *
 * @see #tpl_need_switch
 */
#define NO_NEED_SWITCH  0x0

/**
 * @def NEED_SWITCH
 *
 * Used for tpl_need_switch variable. A context switch should occur
 *
 * @see #tpl_need_switch
 */
#define NEED_SWITCH     0x1

/**
 * @def NEED_SAVE
 *
 * Used for tpl_need_switch variable. The context of the process that
 * loses the CPU should be saved
 *
 * @see #tpl_need_switch
 */
#define NEED_SAVE       0x2

/************************************
 * Always existing application mode *
 ************************************/

/**
 * @def OSDEFAULTAPPMODE
 *
 * Default application mode, always a valid parameter to StartOS.
 *
 * @see #StartOS
 * @see #AppModeType
 */
#define OSDEFAULTAPPMODE    0

/*********************************
 * Task flags for the type field *
 *********************************/

/**
 * @def TASK_BASIC
 *
 * identifies a basic task
 *
 * @see #tpl_exec_obj_type
 * @see #TPL_EXEC_STATIC
 */
#define TASK_BASIC              0x0

/**
 * @def TASK_EXTENDED
 *
 * identifies an extended task
 *
 * @see #tpl_exec_obj_type
 * @see #TPL_EXEC_STATIC
 */
#define TASK_EXTENDED           0x1

/**
 * @def IS_ROUTINE
 *
 * identifies a category 2 Interrupt Service Routine
 *
 * @see #tpl_exec_obj_type
 * @see #TPL_EXEC_STATIC
 */
#define IS_ROUTINE              0x2

/**
 * @def FULL_PREEMTABLE_TASK
 *
 * exec object characteristic is : fully preemptable
 *
 * @see #tpl_exec_obj_type
 * @see #TPL_EXEC_STATIC
 */
#define FULL_PREEMPTABLE_TASK   0x0

/**
 * @def NON_PREEMPTABLE_TASK
 *
 * exec object characteristic is : non-preemptable
 *
 * @see #tpl_exec_obj_type
 * @see #TPL_EXEC_STATIC
 */
#define NON_PREEMPTABLE_TASK    0x4

/*****************************
 * Alarms states and actions *
 *****************************/
#define TIME_OBJ_SLEEP      0
#define TIME_OBJ_ACTIVE     1
#define TIME_OBJ_AUTOSTART  2
/**
 * @def ALARM_SLEEP
 *
 * This state means the related alarm is not in use (de-activated)
 *
 * @see #tpl_alarm_state
 * @see #TPL_ALARM
 */
#define ALARM_SLEEP     TIME_OBJ_SLEEP

/**
 * @def ALARM_ACTIVE
 *
 * This state means the related alarm is in use (activated)
 *
 * @see #tpl_alarm_state
 * @see #TPL_ALARM
 */
#define ALARM_ACTIVE    TIME_OBJ_ACTIVE

/**
 * @def ALARM_AUTOSTART
 *
 * This state means alarm should be automatically activated at system startup.
 *
 * @see #tpl_alarm_state
 * @see #TPL_ALARM
 */
#define ALARM_AUTOSTART TIME_OBJ_AUTOSTART

/**
 * @def ALARM_CALLBACK
 *
 * The alarm is a callback (call a function when raise)
 *
 * @see #tpl_alarm_kind
 * @see #TPL_ALARM
 */
#define ALARM_CALLBACK          10

/**
 * @def ALARM_TASK_ACTIVATION
 *
 * The alarm activates a task when raised
 *
 * @see #tpl_alarm_kind
 * @see #TPL_ALARM
 */
#define ALARM_TASK_ACTIVATION   11

/**
 * @def ALARM_EVENT_SETTING
 *
 * The alarm sets an event when raised
 *
 * @see #tpl_alarm_kind
 * @see #TPL_ALARM
 */
#define ALARM_EVENT_SETTING     12

/***************************************
 * selector for tpl_schedule parameter *
 ***************************************/

/**
 * @def FROM_TASK_LEVEL
 *
 * Scheduler is called from a task (either directly or indirectly, but not
 * from an interrupt)
 *
 * @see #tpl_schedule
 */
#define FROM_TASK_LEVEL 0

/**
 * @def FROM_IT_LEVEL
 *
 * Scheduler is called from a task (either directly or indirectly, but not
 * from an interrupt)
 *
 * @see #tpl_schedule
 */
#define FROM_IT_LEVEL   1

/**
 * @def TASK
 *
 * Macro used to define (declare) a task
 *
 * @param name the name (C identifier) of the task
 */
#define TASK(name)              \
    DeclareTask(name);          \
    FUNC(void, OS_APPL_CODE) name##_function(void)

/**
 * @def ISR2
 *
 * Macro used to define (declare) a category 2 interrupt service routine.
 *
 * @param name the name (C identifier) of the IRS
 */
#define ISR(name)               \
    FUNC(void, OS_APPL_CODE) name##_function(void)

/**
 * @def ALARMCALLBACK
 *
 * Macro used to define an alarm callback function
 *
 * @param name callback name
 *
 * @warning don't be confused with ALARM_CALLBACK
 */
#define ALARMCALLBACK(name)     \
    void name##_callback(void)

/**
 * @def MASK_EXECTYPE
 *
 * Don't use this macro directly, use one of the following macros instead :
 *
 * @see #tpl_is_basic
 * @see #tpl_is_extended
 * @see #tpl_is_full_preemptable
 * @see #tpl_is_non_preemptable
 * @see #tpl_is_isr
 */
#define MASK_EXECTYPE       0x3

/**
 * @def PREEMPTABLE_MASK
 *
 * Don't use this macro directly, use one of the following macros instead :
 *
 * @see #tpl_is_basic
 * @see #tpl_is_extended
 * @see #tpl_is_full_preemptable
 * @see #tpl_is_non_preemptable
 * @see #tpl_is_isr
 */
#define PREEMPTABLE_MASK    0x4

/**
 * @def tpl_is_basic
 *
 * @param obj exec object to test
 *
 * true if obj is a basic task
 */
#define tpl_is_basic(obj)     \
    ((obj->static_desc->type & MASK_EXECTYPE) == TASK_BASIC)

/**
 * @def tpl_is_extended
 *
 * @param obj exec object to test
 *
 * true if obj is an extended task
 */
#define tpl_is_extended(obj)  \
    ((obj->static_desc->type & MASK_EXECTYPE) == TASK_EXTENDED)

/**
 * @def tpl_is_full_preemptable
 *
 * @param obj exec object to test
 *
 * true if obj is preemptable
 */
#define tpl_is_full_preemptable(obj)   \
    ((obj->static_desc->type & PREEMPTABLE_MASK) == FULL_PREEMTABLE_TASK)

/**
 * @def tpl_is_non_preemptable
 *
 * @param obj exec object to test
 *
 * true if obj is not preemptable
 */
#define tpl_is_non_preemptable(obj)    \
    ((obj->static_desc->type & PREEMPTABLE_MASK) == NON_PREEMPTABLE_TASK)

/**
 * @def tpl_is_isr
 *
 * @param obj exec object to test
 *
 * true if obj is an ISR
 */
#define tpl_is_isr(obj)     \
    ((obj->static_desc->type & MASK_EXECTYPE) == IS_ROUTINE)



#ifdef WITH_AUTOSAR
/**
 * @def HARDWARE_COUNTER
 *
 * Identifies a hardware counter
 *
 * @see #tpl_counter_kind
 */
#define HARDWARE_COUNTER    0

/**
 * @def SOFTWARE_COUNTER
 *
 * Identifies a software counter
 *
 * @see #tpl_counter_kind
 */
#define SOFTWARE_COUNTER    1

#if (AUTOSAR_SC == 3) || (AUTOSAR_SC == 4)
/**
 *  @def INVALID_OSAPPLICATION
 *
 *  No OS Application is running
 *
 *  @see  #tpl_app_id
 */
#define INVALID_OSAPPLICATION   APP_COUNT
#endif

#endif


#endif /* TPL_OS_DEFINITIONS_H */

/* End of file tpl_os_definitions.h */
