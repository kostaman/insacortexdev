/*
 * Expiry points of schedule table $SCHEDTABLE_NAME$ 
 */
$EXPIRY_POINTS$

tpl_schedtable_static stat_$SCHEDTABLE$ = {
  { /* static time object part */
    /* counter            */  $COUNTER$,
    /* expire function    */  tpl_process_schedtable
#if (WITH_TRACE == YES)
    /* id of the table for tracing  */  , $SCHEDTABLE_NAME$_id
#endif
#ifdef WITH_OSAPPLICATION
    /* OS application id  */  , $APP_ID$
#endif
  },
  /* expiry points        */  $EXPIRY_TABLE$,
  /* expiry points count  */  $EXPIRY_TABLE_SIZE$,
  /* sync strategy        */  $SYNC_STRATEGY$,
  /* periodic             */  $PERIODIC$,
  /* length               */  $LENGTH$,
  /* precision            */  $PRECISION$
};

tpl_schedule_table $SCHEDTABLE$ = {
    {   /* dynamic time object part */
        /* ptr to the static part   */  (tpl_time_obj_static *)&stat_$SCHEDTABLE$,
        /* next time object         */  NULL_PTR,
        /* prev time object         */  NULL_PTR,
        /* cycle                    */  0,
        /* date                     */  $SCHEDTABLE_DATE$,
        /* state of the time object */  $SCHEDTABLE_STATE$
    },
    /* next schedule table          */  NULL_PTR,
    /* current expiry point         */  0,
    /* deviation 					*/	0				
};
