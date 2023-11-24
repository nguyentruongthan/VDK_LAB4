/*
 * scheduler.c
 *
 *  Created on: Nov 24, 2023
 *      Author: than
 */

#include "scheduler.h"

#define SCH_MAX_TASKS		10

struct s_task{
	// Pointer to the task (must be a ’ void ( void ) ’ function )
	void (*pTask)(void);

	// Delay (ticks) until the function will ( next ) be run
	uint32_t delay ;

	// Interval (ticks) between subsequent runs .
	uint32_t period ;
	// Incremented (by scheduler) when task i s due to execute
	uint8_t run_me;
	// this is not only ID of task but also position of this task in SCH_tasks_G
	uint32_t task_ID ;
};
struct s_task SCH_tasks_G[SCH_MAX_TASKS];

void SCH_Init(void){
	for(uint8_t i = 0; i < SCH_MAX_TASKS; i++){
		//initial all element in SCH_tasks_G is not filled
		SCH_tasks_G[i].pTask = 0;
	}
}

//This function will be updated the remaining time of each
//tasks that are added to a queue. It will be called in the interrupt timer,
//for example 10 ms.
void SCH_Update(void){
	for(uint8_t i = 0; i < SCH_MAX_TASKS; i++){
		if(SCH_tasks_G[i].pTask == 0) continue;

		if(SCH_tasks_G[i].delay == 0){
			SCH_tasks_G[i].run_me = 1;
			if(SCH_tasks_G[i].period){
				SCH_tasks_G[i].delay = SCH_tasks_G[i].period;
			}
		}else{
			SCH_tasks_G[i].delay --;
		}
	}
}

//This function will get the task in the queue to run
void SCH_Dispatch_Tasks(void){
	for(uint8_t i = 0; i < SCH_MAX_TASKS; i++){
		if(SCH_tasks_G[i].run_me > 0){
			(*SCH_tasks_G[i].pTask)();
			SCH_tasks_G[i].run_me = 0;
			if(SCH_tasks_G[i].period == 0){
				SCH_Delete_Task(i);
			}
		}
	}
}
//This function is used to add a task to the queue.
//It should return an ID that is corresponding with the added task
uint32_t SCH_Add_Task(void (* pFunction)(), uint32_t DELAY, uint32_t PERIOD){
	uint8_t i;
	for(i = 0; i < SCH_MAX_TASKS; i++){
		if(SCH_tasks_G[i].pTask == 0){
			//TODO
			SCH_tasks_G[i].pTask = pFunction;
			SCH_tasks_G[i].delay = DELAY;
			SCH_tasks_G[i].period = PERIOD;
			SCH_tasks_G[i].task_ID = i;
			break;
		}
	}
	return i;
}

//This function is used to delete the task based on its ID.
uint8_t SCH_Delete_Task(uint32_t taskID){
	if(taskID >= SCH_MAX_TASKS) return 0; //ERROR
	if(SCH_tasks_G[taskID].pTask == 0) return 0; //ERROR

	SCH_tasks_G[taskID].pTask = 0x0000;
	SCH_tasks_G[taskID].delay = 0;
	SCH_tasks_G[taskID].period = 0;
	SCH_tasks_G[taskID].run_me = 0;

	return 1;
}
