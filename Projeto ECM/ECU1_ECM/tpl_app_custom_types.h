/**
 * @file tpl_app_custom_types.h
 *
 * @section File description
 *
 * This file gathers all data types which are generated from the application.
 * Please refer to comment of each type for more details.
 * Generated from application test
 * Automatically generated by goil on Mon Jun 12 17:45:43 2023
 * from root OIL file ECU1_ECM.oil
 *
 * @section File informations
 *
 * $Date$
 * $Rev$
 * $Author$
 * $URL$
 */

#ifndef TPL_APP_CUSTOM_TYPES_H
#define TPL_APP_CUSTOM_TYPES_H

#include "tpl_compiler.h"
#include "tpl_os_std_types.h"

/**
 * tpl_heap_key is the datatype used to store the key of a heap entry.
 */
typedef uint8 tpl_heap_key;

/**
 * tpl_rank_count is the datatype used to store the rank of an activation
 * It is the lower part of a tpl_heap_key
 */
typedef uint8 tpl_rank_count;

/**
 * tpl_proc_id is used for task and isrs identifiers.
 *
 * @warning This data type must be signed
 * because -1 is used for INVALID_TASK and INVALID_ISR
 */
typedef sint8 tpl_proc_id;

/**
 * tpl_appmode_mask is used for AUTOSTART objects.
 *
 * Each bit in the mask corresponds to an application mode. The size of the mask
 * is computed according to the number of application modes.
 */
typedef uint8 tpl_appmode_mask;

/**
 * tpl_priority represents a task's or a resource's priority.
 *
 * The data type is computed according to the number of ISR2 and jobs that can * be present in the list of ready tasks.
 */
typedef uint8 tpl_priority;

/**
 * tpl_activate_counter is used to count
 * how many time a task has been activated while
 * it was not suspended.
 */
typedef uint8 tpl_activate_counter;

/**
 * tpl_event_mask is used for event.
 * An event is a bit vector. According to the maximum number of events
 * defined in the application, it can be uint8 (8 events), uint16 (16 events) or
 * uint32 (32 events).
 */
typedef uint8 tpl_event_mask;

/**
 * tpl_alarm_type is used for alarm identifiers.
 */
typedef uint8 tpl_alarm_id;

/**
 * tpl_resource_id is used for resource identifiers.
 *
 * @warning RES_SCHEDULER is set to the higher resource id + 1
 */
typedef uint8 tpl_resource_id;

#if (WITH_TRACE == YES)
/**
 * @internal
 *
 * Type used to store the id of an alarm or a schedule table
 * This is used only for tracing
 */
typedef uint8 tpl_timeobj_id;

/**
 * @internal
 *
 * one id for each counter.
 */
typedef uint8 tpl_trace_counter_id;
#endif

#ifdef WITH_AUTOSAR
/**
 * @internal
 *
 * @todo: document this
 */
typedef uint8 tpl_counter_id;

/**
 * @internal
 *
 * @todo: document this
 */
typedef uint8 tpl_schedtable_id;

/**
 * @internal
 *
 * Type used to store the id of an OS Application
 * Its size is computed according to the number of OS Applications
 */
typedef uint8 tpl_app_id;

/**
 * @internal
 *
 * Generic type used in OS Application API
 * Its size is computed by doing the max of all object kind
 */
typedef uint8 tpl_generic_id;



#endif /* WITH_AUTOSAR */

/* target specific types */

 
/**
 * tpl_tick is used for relative and absolute dates.
 * tpl_tick should be an unsigned datatype.
 *
 * Default aliased type is "unsigned long int"
 */
typedef uint32 tpl_tick;


#endif /* TPL_APP_CUSTOM_TYPES_H */

/* End of file tpl_app_custom_types.h */

