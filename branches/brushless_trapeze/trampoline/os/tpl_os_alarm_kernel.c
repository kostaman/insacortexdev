/**
 * @file tpl_os_alarm_kernel.c
 *
 * @section desc File description
 *
 * Trampoline Alarm Kernel implementation file
 *
 * @section copyright Copyright
 *
 * Trampoline OS
 *
 * Trampoline is copyright (c) IRCCyN 2005-2007
 * Trampoline is protected by the French intellectual property law.
 *
 * This software is distributed under the Lesser GNU Public Licence
 *
 * @section infos File informations
 *
 * $Date: 2009-11-16 18:01:52 +0100 (Lun, 16 nov 2009) $
 * $Rev: 968 $
 * $Author: jlb $
 * $URL: https://trampoline.rts-software.org/svn/trunk/os/tpl_os_alarm_kernel.c $
 */

#include "tpl_os_alarm_kernel.h"
#include "tpl_os_definitions.h"
#include "tpl_os_kernel.h"
#include "tpl_os_error.h"
#include "tpl_os_errorhook.h"
#include "tpl_machine_interface.h"
#include "tpl_trace.h"

#include "tpl_debug.h"

#ifdef WITH_AUTOSAR
#include "tpl_as_protec_hook.h"
#endif

#define OS_START_SEC_CONST_UNSPECIFIED
#include "tpl_memmap.h"
/**
 * @def INVALID_ALARM
 *
 * This value is used to specify an invalid alarm ID
 */
CONST(tpl_alarm_id, AUTOMATIC) INVALID_ALARM = (-1);
#define OS_STOP_SEC_CONST_UNSPECIFIED
#include "tpl_memmap.h"

#define OS_START_SEC_CODE
#include "tpl_memmap.h"
/**
 * @internal
 *
 * tpl_raise_alarm is called by tpl_counter_tick
 * when an alarm time object is raised.
 *
 * @param time_obj  The alarm to raise.
 */
FUNC(tpl_status, OS_CODE) tpl_raise_alarm(
    P2VAR(tpl_time_obj, AUTOMATIC, OS_APPL_DATA) time_obj)
{
    VAR(tpl_status, AUTOMATIC) result = E_OK;

    /*
     * A tpl_time_obj_static * is cast to a tpl_alarm_static *
     * This violate MISRA rule 45. However, since the
     * first member of tpl_alarm_static is a tpl_time_obj_static
     * This cast behaves correctly.
     */
    /*  Get the alarm descriptor                            */
    P2VAR(tpl_alarm_static, AUTOMATIC, OS_APPL_DATA) stat_alarm = (tpl_alarm_static *)time_obj->stat_part;
    /*  Get the action to perform from the alarm descriptor */
    P2CONST(tpl_action, AUTOMATIC, OS_APPL_CONST) action_desc = stat_alarm->action;
    
    TRACE_ALARM_EXPIRE(time_obj)
    /*  Call the action                                     */
    result = (action_desc->action)(action_desc) ;

    return result;
}


FUNC(tpl_status, OS_CODE) tpl_get_alarm_base_service(
    CONST(tpl_alarm_id, AUTOMATIC)                  alarm_id,
    P2VAR(tpl_alarm_base, AUTOMATIC, OS_APPL_DATA)  info)
{
    VAR(tpl_status, AUTOMATIC) result = E_OK;

#ifndef NO_ALARM
    P2VAR(tpl_time_obj, AUTOMATIC, OS_APPL_DATA) alarm;
#endif

    LOCK_KERNEL()

	/* check interrupts are not disabled by user    */
    CHECK_INTERRUPT_LOCK(result)

    STORE_SERVICE(OSServiceId_GetAlarmBase)
    STORE_ALARM_ID(alarm_id)
    STORE_ALARM_BASE_REF(info)

    CHECK_ALARM_ID_ERROR(alarm_id,result)
	
	/* check access right */
	CHECK_ACCESS_RIGHTS_ALARM_ID(alarm_id,result)
	
#ifndef NO_ALARM
    IF_NO_EXTENDED_ERROR(result)
        alarm = tpl_alarm_table[alarm_id];

        info->ticksperbase = alarm->stat_part->counter->ticks_per_base;
        info->maxallowedvalue = alarm->stat_part->counter->max_allowed_value;
        info->mincycle = alarm->stat_part->counter->min_cycle;
    IF_NO_EXTENDED_ERROR_END()
#endif

    PROCESS_ERROR(result)

    UNLOCK_KERNEL()

    return result;
}

FUNC(tpl_status, OS_CODE) tpl_get_alarm_service(
  CONST(tpl_alarm_id, AUTOMATIC)              alarm_id,
  P2VAR(tpl_tick, AUTOMATIC, OS_APPL_DATA)    tick)
{
  VAR(tpl_status, AUTOMATIC) result = E_OK;

#ifndef NO_ALARM
  P2VAR(tpl_time_obj, AUTOMATIC, OS_APPL_DATA) alarm;
#endif

  LOCK_KERNEL()

  /* check interrupts are not disabled by user    */
  CHECK_INTERRUPT_LOCK(result)

  STORE_SERVICE(OSServiceId_GetAlarm)
  STORE_ALARM_ID(alarm_id)
  STORE_TICK_REF_1(tick)

  CHECK_ALARM_ID_ERROR(alarm_id,result)
	
  /* check access right */
  CHECK_ACCESS_RIGHTS_ALARM_ID(alarm_id,result)
	
#ifndef NO_ALARM
  IF_NO_EXTENDED_ERROR(result)
    alarm = tpl_alarm_table[alarm_id];

    /*  verify the alarm is active  */
    if (alarm->state == (tpl_time_obj_state)ALARM_ACTIVE)
    {
      VAR(tpl_tick, AUTOMATIC) alarm_date = alarm->date;
      VAR(tpl_tick, AUTOMATIC) current_date =
        alarm->stat_part->counter->current_date;
      if (alarm_date < current_date)
      {
        alarm_date += alarm->stat_part->counter->max_allowed_value;
      }
      *tick = alarm_date - current_date;
    }
    else
    {
      result = E_OS_NOFUNC;
    }
  IF_NO_EXTENDED_ERROR_END()
#endif

  PROCESS_ERROR(result)

  UNLOCK_KERNEL()

  return result;
}

FUNC(tpl_status, OS_CODE) tpl_set_rel_alarm_service(
    CONST(tpl_alarm_id, AUTOMATIC)  alarm_id,
    CONST(tpl_tick, AUTOMATIC)      increment,
    CONST(tpl_tick, AUTOMATIC)      cycle)
{
    VAR(tpl_status, AUTOMATIC) result = E_OK;

#ifndef NO_ALARM
    P2VAR(tpl_time_obj, AUTOMATIC, OS_APPL_DATA) alarm;
    P2VAR(tpl_counter, AUTOMATIC, OS_APPL_DATA) cnt;
    VAR(tpl_tick, AUTOMATIC) date;
#endif

    LOCK_KERNEL()

	/* check interrupts are not disabled by user    */
    CHECK_INTERRUPT_LOCK(result)

    STORE_SERVICE(OSServiceId_SetRelAlarm)
    STORE_ALARM_ID(alarm_id)
    STORE_TICK_1(increment)
    STORE_TICK_2(cycle)

    CHECK_ALARM_ID_ERROR(alarm_id,result)
	
	/* check access right */
	CHECK_ACCESS_RIGHTS_ALARM_ID(alarm_id,result)
	
    CHECK_ALARM_INCREMENT_ERROR(alarm_id,increment,result)
    CHECK_ALARM_MIN_CYCLE_ERROR(alarm_id,cycle,result)

#ifndef NO_ALARM
    IF_NO_EXTENDED_ERROR(result)
        alarm = tpl_alarm_table[alarm_id];

        if (alarm->state == (tpl_time_obj_state)ALARM_SLEEP)
        {
            cnt = alarm->stat_part->counter;
            /*  the alarm is not in use, proceed    */
            date = cnt->current_date + increment;
            if (date > cnt->max_allowed_value)
            {
                date -= (cnt->max_allowed_value + 1);
            }
            alarm->date = date;
            alarm->cycle = cycle;
            alarm->state = ALARM_ACTIVE;
            tpl_insert_time_obj(alarm);
	    TRACE_ALARM_SCHEDULED(alarm)
        }
        else
        {
            /*  the alarm is in use, return the proper error code   */
            result = E_OS_STATE;
        }
    IF_NO_EXTENDED_ERROR_END()
#endif

    PROCESS_ERROR(result)

    UNLOCK_KERNEL()

    return result;
}

/*
 * SetAbsAlarm
 *
 * See page 64 of the OSEK spec
 */
FUNC(tpl_status, OS_CODE) tpl_set_abs_alarm_service(
    CONST(tpl_alarm_id, AUTOMATIC)  alarm_id,
    CONST(tpl_tick, AUTOMATIC)      start,
    CONST(tpl_tick, AUTOMATIC)      cycle)
{
    VAR(tpl_status, AUTOMATIC) result = E_OK;

#ifndef NO_ALARM
    P2VAR(tpl_time_obj, AUTOMATIC, OS_APPL_DATA) alarm;
#endif

    LOCK_KERNEL()

	/* check interrupts are not disabled by user    */
    CHECK_INTERRUPT_LOCK(result)

    STORE_SERVICE(OSServiceId_SetAbsAlarm)
    STORE_ALARM_ID(alarm_id)
    STORE_TICK_1(start)
    STORE_TICK_2(cycle)

    CHECK_ALARM_ID_ERROR(alarm_id,result)
	
	/* check access right */
	CHECK_ACCESS_RIGHTS_ALARM_ID(alarm_id,result)
	
    CHECK_ALARM_INCREMENT_ERROR(alarm_id,start,result)
    CHECK_ALARM_MIN_CYCLE_ERROR(alarm_id,cycle,result)

#ifndef NO_ALARM
    IF_NO_EXTENDED_ERROR(result)
    alarm = tpl_alarm_table[alarm_id];

    if (alarm->state == (tpl_time_obj_state)ALARM_SLEEP)
    {
        /*  the alarm is not in use, proceed    */
        alarm->date = start;
        alarm->cycle = cycle;
        alarm->state = ALARM_ACTIVE;
        tpl_insert_time_obj(alarm);
	TRACE_ALARM_SCHEDULED(alarm)
    }
    else
    {
        /*  the alarm is in use, return the proper error code   */
        result = E_OS_STATE;
    }
    IF_NO_EXTENDED_ERROR_END()
#endif

    PROCESS_ERROR(result)

    UNLOCK_KERNEL()

    return result;
}

/*
 * CancelAlarm
 *
 * See page 65 of the OSEK spec
 */
FUNC(tpl_status, OS_CODE) tpl_cancel_alarm_service(
    CONST(tpl_alarm_id, AUTOMATIC) alarm_id)
{
    VAR(tpl_status, AUTOMATIC) result = E_OK;

#ifndef NO_ALARM
    P2VAR(tpl_time_obj, AUTOMATIC, OS_APPL_DATA) alarm;
#endif

    LOCK_KERNEL()

	/* check interrupts are not disabled by user    */
    CHECK_INTERRUPT_LOCK(result)

    STORE_SERVICE(OSServiceId_CancelAlarm)
    STORE_ALARM_ID(alarm_id)

    CHECK_ALARM_ID_ERROR(alarm_id,result)
	
	/* check access right */
	CHECK_ACCESS_RIGHTS_ALARM_ID(alarm_id,result)

#ifndef NO_ALARM
    IF_NO_EXTENDED_ERROR(result)
    alarm = tpl_alarm_table[alarm_id];

    if (alarm->state == (tpl_time_obj_state)ALARM_ACTIVE)
    {
        tpl_remove_time_obj(alarm);
	TRACE_ALARM_CANCEL(alarm_id)
        alarm->state = ALARM_SLEEP;
    }
    else
    {
        result = E_OS_NOFUNC;
    }
    IF_NO_EXTENDED_ERROR_END()
#endif

    PROCESS_ERROR(result)

    UNLOCK_KERNEL()

    return result;
}

#define OS_STOP_SEC_CODE
#include "tpl_memmap.h"

/* End of file tpl_alarm_kernel.c */
