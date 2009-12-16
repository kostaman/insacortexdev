/**
 * @file tpl_os_action.h
 *
 * @section desc File description
 *
 * Trampoline Action header. Actions are used for alarm action. They are
 * also used by COM for notifications.
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
 * $Date: 2009-02-18 14:14:39 +0100 (Mer, 18 fév 2009) $
 * $Rev: 577 $
 * $Author: jlb $
 * $URL: https://trampoline.rts-software.org/svn/trunk/os/tpl_os_action.h $
 */

#ifndef TPL_OS_ACTION_H
#define TPL_OS_ACTION_H

#include "tpl_os_internal_types.h"
#include "tpl_os_task_kernel.h"

struct TPL_ACTION;

/**
 * @typedef tpl_action_func
 *
 * Prototype for action functions
 */
/**********************************************************************
**  J.Monsimier  22/05/2007
**  PR09: for S12: need to add __near for the compiler or the
**        pointer is considered at far and there is a stack pointer
**        error during function return in tpl_action_activate_task
**********************************************************************/
typedef P2FUNC(tpl_status, OS_APPL_CODE, tpl_action_func)(
  P2CONST(struct TPL_ACTION, AUTOMATIC, OS_APPL_CONST)
);

/**
 * @struct TPL_ACTION
 *
 * Action base structure
 *
 * This structure contains the pointer to the action function only.
 * It is the common part for the action descriptor structures and is
 * extended to add the action parameters.
 */
struct TPL_ACTION {
  VAR(tpl_action_func, TYPEDEF) action;    /**<  action function pointer   */
};

/**
 * @typedef tpl_action
 *
 * This is an alias for the structure #TPL_ACTION
 *
 * @see #TPL_ACTION
 */
typedef struct TPL_ACTION tpl_action;

/**
 *  @struct TPL_ACTION_CALLBACK
 *
 *  This structure add a callback function pointer to the action base
 *  structure.
 */
struct TPL_CALLBACK_ACTION {
  /*  base action                 */
  VAR(tpl_action, TYPEDEF)        b_desc;
  /*  callback function pointer   */
  VAR(tpl_callback_func, TYPEDEF) callback;
};

typedef struct TPL_CALLBACK_ACTION
tpl_callback_action;

/**
 *  @struct TPL_TASK_ACTIVATION_ACTION
 *
 *  This structure add a task descriptor pointer to the action base
 *  structure.
 */
struct TPL_TASK_ACTIVATION_ACTION {
  /*  base action                 */
  VAR(tpl_action, TYPEDEF)  b_desc;
  /*  task descriptor pointer     */
  VAR(tpl_task_id, TYPEDEF) task_id;
};

typedef struct TPL_TASK_ACTIVATION_ACTION
tpl_task_activation_action ;

/*!
 *  @struct TPL_SETEVENT_ACTION
 *
 *  This structure add a task descriptor pointer to the action base
 *  structure and an event mask
 */
struct TPL_SETEVENT_ACTION {
  /*  base action                 */
  VAR(tpl_action, TYPEDEF)      b_desc;
  /*  task descriptor pointer     */
  VAR(tpl_task_id, TYPEDEF)     task_id;
  /*  event mask                  */
  VAR(tpl_event_mask, TYPEDEF)  mask;
};

typedef struct TPL_SETEVENT_ACTION
tpl_setevent_action;


#define OS_START_SEC_CODE
#include "tpl_memmap.h"

/*
 * Notification functions prototypes
 */
FUNC(tpl_status, OS_CODE) tpl_action_callback(
  P2CONST(tpl_action, AUTOMATIC, OS_APPL_CONST) action
);
FUNC(tpl_status, OS_CODE) tpl_action_activate_task(
  P2CONST(tpl_action, AUTOMATIC, OS_APPL_CONST) action
);
FUNC(tpl_status, OS_CODE) tpl_action_setevent(
  P2CONST(tpl_action, AUTOMATIC, OS_APPL_CONST) action
);

#define OS_STOP_SEC_CODE
#include "tpl_memmap.h"

#endif /*  TPL_OS_ACTION_H  */

/* End of file tpl_os_action.h */
