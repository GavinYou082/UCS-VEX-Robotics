/** @file opcontrol.c
 * @brief File for operator control code
 *
 * This file should contain the user operatorControl() function and any functions related to it.
 *
 * Any copyright is dedicated to the Public Domain.
 * http://creativecommons.org/publicdomain/zero/1.0/
 *
 * PROS contains FreeRTOS (http://www.freertos.org) whose source code may be
 * obtained from http://sourceforge.net/projects/freertos/files/ or on request.
 */

#include "main.h"
#include "init.h"
#include "control.h"
#include "config.h"
#include "keynotify.h"

TaskHandle taskH_shoot;

/* Callback function for direction */
void callback_direction() {
	isReversed = !isReversed;
}
void callback_switchBallCollector() {
	if (collectorState != COLLECTOR_STOP) {
		collectorState = COLLECTOR_STOP;
	}
	else {
		collectorState = COLLECTOR_ON;
	}
}

void shoot_task() {
	unsigned long start;
	start = millis();

	motorSet(MOTOR_SHOOT1, 127);
	motorSet(MOTOR_SHOOT2, 127);

	for (; (start - millis()) >= 2000;) delay(1);
	/* TODO: Use analog encoder to control the rotation of gears */

	motorSet(MOTOR_SHOOT1, 0);
	motorSet(MOTOR_SHOOT2, 0);
	taskSuspend(NULL);
}


void callback_shoot() {
	DBG_PRINT("Shoot Callback.");
	/* We're going to create a task here since it should not be blocked */
	if (!taskH_shoot)
		taskH_shoot = taskRunLoop(shoot_task, 0); /* Don't know if task will
																									delete itself by the end */
	if (taskGetState(taskH_shoot) != TASK_RUNNING)
		taskResume(taskH_shoot);
}

void callback_lowSpeed() {
	DBG_PRINT("Switch to %ix speed", MOTORSPEED_LOW);
	motorSpeed = MOTORSPEED_LOW;
}

void callback_normalSpeed() {
	DBG_PRINT("Switch to %ix speed", MOTORSPEED_NORMAL);
	motorSpeed = MOTORSPEED_NORMAL;
}

void operatorControl() {
	//initialising
	char vertical, angular;
	resetConfig();
	taskRunLoop(keynotify_loop, 20);
	//set key events
	set_keynotify(0, MASTER_JOYSTICK, 7, JOY_DOWN, callback_direction);//reverse
	set_keynotify(1, MASTER_JOYSTICK, 7, JOY_LEFT, callback_lowSpeed);//switch to low speed
	set_keynotify(2, MASTER_JOYSTICK, 7, JOY_RIGHT, callback_normalSpeed);//switch to normal speed
	set_keynotify(3, MASTER_JOYSTICK, 5, JOY_UP, callback_switchBallCollector);//switch on/off ball collector
	//set_keynotify(2, MASTER_JOYSTICK, 8, JOY_DOWN, callback_shoot);//TODO: one key shoot

	while (true) {
		vertical = joystickGetAnalog(MASTER_JOYSTICK, JOYSTICK_VERTICAL_CH);
		angular = joystickGetAnalog(MASTER_JOYSTICK, JOYSTICK_ANGULAR_CH);
		/* JOYSTICK_THROT to prevent errors */
		if (abs(vertical) <= JOYSTICK_THROT_START) {
			vertical = 0;
		}
		if (abs(angular) <= JOYSTICK_THROT_START) {
			angular = 0;
		}

		//button functions pooling
		if (collectorState != COLLECTOR_STOP) {
			if (joystickGetDigital(MASTER_JOYSTICK, 5, JOY_DOWN)) {
				collectorState = COLLECTOR_REVERSE;
			}
			else {
				collectorState = COLLECTOR_ON;
			}
		}

		if (joystickGetDigital(MASTER_JOYSTICK, 6, JOY_UP)) {
			motorSet(MOTOR_CLAW, 127);
		}
		else if (joystickGetDigital(MASTER_JOYSTICK, 6, JOY_DOWN)) {
			motorSet(MOTOR_CLAW, -127);
		}
		else {
			motorSet(MOTOR_CLAW, 0);
		}

		if (joystickGetDigital(MASTER_JOYSTICK, 8, JOY_DOWN)) {
			SET_SHOOT_MOTORS(127);
		}
		else {
			SET_SHOOT_MOTORS(0);
		}

		//execute motors
		motorSet(MOTOR_COLLECTOR, collectorState);
		setMovement(vertical, angular);
	}
}
