/*
 * abstract.c
 *
 *  Created on: Jul 25, 2017
 *      Author: Mert Kara
 */

#include <rtems.h>
#include <bsp.h> /* for device driver prototypes */
#include <stdio.h>
#include <stdlib.h>

//Creates N number of tasks, whose ids will be written to the provided arrays.
//Returns STATUS_CODE
rtems_status_code create_N_tasks(int numberOfTasks, rtems_id* t_ids){
	rtems_status_code status;
	int i;
	for( i = 0; i < numberOfTasks; i++){
		status = rtems_task_create( rtems_build_name( 'T', 'A', i + 48, ' ' ) , 5, RTEMS_MINIMUM_STACK_SIZE, RTEMS_DEFAULT_MODES,
			    RTEMS_DEFAULT_ATTRIBUTES, &t_ids[i]);
	}
	return status;
};


//from rtems c user manual
void prettyPrintObjectId(rtems_id id){
	int tmpAPI, tmpClass;
	tmpAPI = rtems_object_id_get_api(id);
	tmpClass = rtems_object_id_get_class(id);
	printf(
		"API=%s Class=%s Node=%d Index=%d\n",
		rtems_object_get_api_name(tmpAPI),
		rtems_object_get_api_class_name(tmpAPI, tmpClass),
		rtems_object_id_get_node(id),
		rtems_object_id_get_index(id)
	);
}
