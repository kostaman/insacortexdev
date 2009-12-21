/**
 * @file tpl_asm_macros.h
 *
 * @section descr File description
 *
 * Macros to be used in preprocessed assembler source files.
 *
 * @section copyright Copyright
 *
 * Trampoline OS
 *
 * Trampoline is copyright (c) IRCCyN 2005+
 * Copyright ESEO for function and data structures documentation and ARM port
 * Trampoline is protected by the French intellectual property law.
 *
 * This software is distributed under the Lesser GNU Public Licence
 *
 * @section infos File informations
 *
 * $Date: 2009-02-19 13:27:37 +0100 (Jeu, 19 fév 2009) $
 * $Rev $
 * $Author: ilias $
 * $URL: https://trampoline.rts-software.org/svn/trunk/machines/arm/simtec-eb675001/tpl_asm_macros.h $
 */
#ifndef TPL_ASM_MACROS_H
#define TPL_ASM_MACROS_H

/**
 * This instruction is used to load a tpl_proc_id typed variable
 */
#define LDR_PROC_ID ldr

/*
 * This instruction is used to store a tpl_proc_id typed variable
 */
#define STR_PROC_ID str

#endif /* TPL_ASM_MACROS_H */

