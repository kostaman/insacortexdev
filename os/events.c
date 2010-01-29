/*
 * Copyright (C) INSA Toulouse
 * Author: Sebastien DI MERCURIO
 *
 * This file is part of INSA OS.
 *
 * INSA OS is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public
 * License as published by the Free Software Foundation;
 * either version 2, or (at your option) any later version.
 *
 * INSA OS is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied
 * warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
 * PURPOSE.  See the GNU General Public License for more
 * details.
 *
 * You should have received a copy of the GNU General Public
 * License along with INSA OS; see the file COPYING.  If not,
 * write to the Free Software Foundation, Inc., 51 Franklin Street,
 * Fifth Floor, Boston, MA 02110-1301, USA.
 */
 
#include "stm32f10x_type.h"
#include "os_config.h"
#include "kernel.h"
#include "task.h"
#include "events.h"
#include "common.h"

#include "port.h"
#include "scheduler.h"

/* Event services declaration */

/*
 * EventMaskType	DeclareEvent(st_EventInfo *EventInfo)
 * 
 * Ajoute un nouvel event � la tache indiqu�e dans st_EventInfo
 * Renvoi INVALID_EVENT si la tache ne peut plus recevoir d'event 
 */
EventMaskType	DeclareEvent(st_EventInfo *EventInfo)
{
EventMaskType event;

	event = SearchFreeLsb(Task_List[EventInfo->TaskID]->events_list);

	if (event == MAX_EVENT_NBR) return INVALID_EVENT;
	else 
	{
		Task_List[EventInfo->TaskID]->events_list += (1<<event);
		return (1<<event);
	}
}

/*
 * StatusType		SetEvent(TaskType TaskID, EventMaskType Mask)
 * 
 * Active les events indiqu�s dans Mask pour la tache indiqu�e 
 */
StatusType		SetEvent_Int(TaskType TaskID, EventMaskType Mask)
{
	if ((TaskID>= MAX_TASK_NBR) || (Task_List[TaskID] == 0)) return E_OS_ID;
	if ((Task_List[TaskID]->events_list & Mask)!= Mask) return E_OS_ID;
	if (Task_List[TaskID]->state == SUSPENDED) return E_OS_STATE;
	
	if ((Task_List[TaskID]->waiting_events & Mask) != 0) 
	{
		Task_List[TaskID]->events_triggers |= Mask;
		Task_List[TaskID]->state = RUNNING;

		Reschedule();
	}

	return E_OK;
}

/*
 * StatusType		ClearEvent_Int(EventMaskType Mask)
 * 
 * Efface les events contenu dans Mask 
 */
StatusType		ClearEvent_Int(EventMaskType Mask)
{
	Task_List[CurrentTask]->events_triggers &= ~(Mask);
	Task_List[CurrentTask]->waiting_events &= ~(Mask);

	return E_OK;
}

/*
 * StatusType		GetEvent(TaskType TaskID, EventMaskType Mask)
 * 
 * Recupere les events en cours de la tache
 */
StatusType		GetEvent(TaskType TaskID, EventMaskRefType Mask)
{
	if ((TaskID>= MAX_TASK_NBR) || (Task_List[TaskID] == 0)) return E_OS_ID;
	if (Task_List[TaskID]->state == SUSPENDED) return E_OS_STATE;

	*Mask = Task_List[TaskID]->events_triggers;
	 
	return E_OK;
}

/*
 * StatusType		WaitEvent_Int(EventMaskType Mask)
 * 
 * Met la tache active en attente des evenement contenu dans le mask 
 */
StatusType		WaitEvent_Int(EventMaskType Mask)
{
	if (Task_List[CurrentTask]->locksource != LOCK_SOURCE_NONE) return E_OS_RESOURCE;
	
	if ((Task_List[CurrentTask]->events_triggers & Mask) == 0)
	{
		Task_List[CurrentTask]->waiting_events |= Mask;
		Task_List[CurrentTask]->state = WAITING;

		Reschedule();
	}

	return E_OK;
}

/*
 * void Events_Init(void)
 * 
 * Initialisation du module "Events" du noyau 
 */
void Events_Init(void)
{
	/* Rien de special a faire ici */
}

