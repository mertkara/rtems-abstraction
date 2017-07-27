/*
 * main.c
 *
 *  Created on: Jul 26, 2017
 *      Author: Mert Kara
 */
//#include "abstract.c"
#include <rtems.h>
#include <bsp.h> /* for device driver prototypes */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#define NUM_OF_TASKS 3


rtems_task Init(rtems_task_argument argument);

rtems_task talk( rtems_task_argument x ){
	char buf[16] = "I AM AWAKE!!!";
	puts(buf);
	rtems_status_code stat = rtems_message_queue_send( (rtems_id)(x), &buf, 16);
	assert(stat == RTEMS_SUCCESSFUL);
}

rtems_task Init(
  rtems_task_argument ignored
)
{
	rtems_status_code status;
  	rtems_id tid[NUM_OF_TASKS];
  	rtems_id msgId;
	char buf[16];
	size_t s;
	//Create tasks
	int i = 0;
	status = create_N_tasks( 1, &tid);
	assert(status == RTEMS_SUCCESSFUL );
  	//prettyPrintObjectId(tid[i]);
	for(i = 0; i < NUM_OF_TASKS; i++)
		printf( "ID of task %d: %d\n", i ,(int)tid[i] );

	for(i = 0; i < NUM_OF_TASKS ; i++ ){
		status = rtems_message_queue_create( rtems_build_name('M','S','G','Q'), (uint32_t)(100),
						(size_t)(16), RTEMS_FIFO, &msgId );
		//if(status == RTEMS_SUCCESSFUL) puts("Queue Created\n");
  		//else if(status == RTEMS_INVALID_NAME) puts("RTEMS_INVALID_NAME");
  		//else if(status == RTEMS_INVALID_ADDRESS)puts("RTEMS_INVALID_ADDRESS");
  		//else if(status == RTEMS_INVALID_NUMBER)puts("RTEMS_INVALID_NUMBER");
  		//else if(status == RTEMS_INVALID_SIZE)puts("RTEMS_INVALID_SIZE");
  		//else if(status == RTEMS_TOO_MANY)puts("RTEMS_TOO_MANY");
  		//else if(status == RTEMS_UNSATISFIED)puts("RTEMS_UNSATISFIED");
  		//else if(status == RTEMS_MP_NOT_CONFIGURED)puts(" RTEMS_MP_NOT_CONFIGURED");
  		//else if(status == RTEMS_TOO_MANY)puts("RTEMS_TOO_MANY");

		assert(status==RTEMS_SUCCESSFUL);


		status = rtems_task_start( tid[i], talk, (rtems_task_argument)(msgId) );
		if(status == RTEMS_SUCCESSFUL) puts("Task started(not preempted)\n");
		status = rtems_message_queue_receive( msgId,
			&buf, &s,
			//size_t         ,
			RTEMS_WAIT,
			RTEMS_NO_TIMEOUT);
		if(status == RTEMS_SUCCESSFUL) puts( "IT IS ALIVEE!!! IT IS ALIIIIVEEE!!! He said"); puts(buf); puts("HOW ARE YOU FEELING SON?? \n\n");
	}
	assert( RTEMS_SUCCESSFUL==rtems_task_suspend(RTEMS_SELF));
	assert(status == RTEMS_SUCCESSFUL);

	exit( 0 );
}

int main(){return 0;}
// NOTICE: the clock driver is explicitly disabled
#define CONFIGURE_APPLICATION_DOES_NOT_NEED_CLOCK_DRIVER
#define CONFIGURE_APPLICATION_NEEDS_CONSOLE_DRIVER

#define CONFIGURE_MAXIMUM_TASKS            10
#define CONFIGURE_MAXIMUM_MESSAGE_QUEUES    3
#define CONFIGURE_USE_DEVFS_AS_BASE_FILESYSTEM
#define CONFIGURE_RTEMS_INIT_TASKS_TABLE

//#define CONFIGURE_INITIAL_EXTENSIONS RTEMS_TEST_INITIAL_EXTENSION

#define CONFIGURE_INIT
#include <rtems/confdefs.h>
