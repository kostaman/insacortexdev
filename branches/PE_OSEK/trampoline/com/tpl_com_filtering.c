/*
 * Trampoline OS
 *
 * Trampoline is copyright (c) IRCCyN 2005+
 * Trampoline is protected by the French intellectual property law.
 *
 * This software is distributed under the Lesser GNU Public Licence
 *
 * Trampoline filtering machinery implementation.
 *
 * $Date$
 * $Rev$
 * $Author$
 * $URL$
 */

#include "tpl_com_filtering.h"
#include "tpl_os_definitions.h"

#define OS_START_SEC_CODE
#include "tpl_memmap.h"
/*
 * tpl_filtering handles the filtering of messages.
 * It takes two data pointers (new_data and old_data), cast the
 * data to the tpl_com_value datatype (should be a 32bits unsigned
 * int and calls the appropriate filter to do the job.
 * if compiled with DATA_ALIGNMENT set, the addresses of new and
 * old data are checked for alignement before casting the
 * pointers
 * If the check failed, tpl_filtering returns TRUE
 */
tpl_bool tpl_filtering(
  P2CONST(tpl_com_data, AUTOMATIC, OS_VAR)            old_data,
  P2CONST(tpl_com_data, AUTOMATIC, OS_VAR)            new_data,
  VAR(tpl_message_size, AUTOMATIC)                    size,
  CONSTP2CONST(tpl_filter_desc, AUTOMATIC, OS_CONST)  filter_desc)
{
  /*  two variables to store the old and new value    */
  VAR(tpl_com_value, AUTOMATIC) old_value = 0;
  VAR(tpl_com_value, AUTOMATIC) new_value = 0;
  
  /*  Checks there is a filter set */
  if ((filter_desc != NULL) && (filter_desc->filter != NULL)) {
    /*  Checks the data is compatible with filter. Size have
        to be less or equal than the tpl_com_value data size    */
    if (size <= sizeof(tpl_com_value)) {
      /*  get the data    */
      while (size > 0) {
#if ENDIANESS == BIG
        old_value = (old_value << sizeof(char)) | *old_data++;
        new_value = (new_value << sizeof(char)) | *new_data++;
#else
        old_value = (old_value << sizeof(char))
                    | (*(old_data + size - 1));
        new_value = (new_value << sizeof(char))
                    | (*(new_data + size - 1));
#endif
        --size;
      }
      /*  Call the filter */
      return filter_desc->filter(filter_desc, old_value, new_value);
    }
  }
  return TRUE;
}
#define OS_STOP_SEC_CODE
#include "tpl_memmap.h"

