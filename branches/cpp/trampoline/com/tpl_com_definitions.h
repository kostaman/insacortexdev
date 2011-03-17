/*
 * Trampoline OS
 *
 * Trampoline is copyright (c) IRCCyN 2005+
 * Trampoline est protÈgÈ par la loi sur la propriÈtÈ intellectuelle
 *
 * This software is distributed under the Lesser GNU Public Licence
 *
 * Trampoline Definition for OSEK/COM
 *
 * $Date: 2005-04-07 15:20:19 +0200 (Thu, 07 Apr 2005) $
 * $Rev: 777 $
 * $Author: jlb $
 * $URL: http://localhost:8888/Trampoline/svn/tpl_com_definitions.h $
 */

#ifndef TPL_COM_DEFINITIONS_H
#define TPL_COM_DEFINITIONS_H

#include "tpl_com_private_types.h"

#define COM_TRUE        ((tpl_flag_value)1)
#define COM_FALSE       ((tpl_flag_value)0)

/*
 * Result codes
 */
#define E_COM_ID        17
#define E_COM_LENGTH    18
#define E_COM_LIMIT     19
#define E_COM_NOMSG     20
#define E_COM_FILTEREDOUT 21

#ifdef WITH_EXTERNAL_COM
/*
 * message type
 */
#endif

#endif
