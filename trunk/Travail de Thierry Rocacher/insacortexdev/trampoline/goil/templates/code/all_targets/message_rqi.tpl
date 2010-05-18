/*
 * Static internal receiving queued message object $MESSAGE_NAME$
 */

$CTYPE$ $BUFFER$[$QUEUE_SIZE$];

tpl_queue_dyn $DYN_QUEUE$ = {
    /*  pointer to the last written element */  NULL_PTR,
    /*  current size of the queue           */  0,
    /*  read index                          */  0,
    /*  overflow flag                       */  FALSE
};

tpl_internal_receiving_queued_mo $MESSAGE$ = {
    {   /* data receiving mo struct     */
        {   /* base receiving mo struct */
            /* notification pointer     */  (tpl_action *)$NOTIFICATION_PTR$,
            /* next receiving mo        */  (tpl_base_receiving_mo *)$TARGET_PTR$
        },
        /*  receiving function      */  (tpl_receiving_func)tpl_receive_static_internal_queued_message,
        /*  copy function           */  (tpl_data_copy_func)tpl_copy_from_queued,
        /*  filter pointer          */  (tpl_filter_desc *)$FILTER_PTR$
    },
    {   /*  queue structure   */
        /*  pointer to the dynamic descriptor   */  &$DYN_QUEUE$,
        /*  max size of the queue               */  $QUEUE_SIZE$*sizeof($CTYPE$),
        /*  element size of the queue           */  sizeof($CTYPE$),
        /*  pointer to the buffer               */  (tpl_com_data *)$BUFFER$
    }
};
