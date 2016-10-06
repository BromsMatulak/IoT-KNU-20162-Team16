/*
  Copyright (C) 2009 Sung Ho Park
  Contact: ubinos.org@gmail.com

  This file is part of the exe_helloworld component of the Ubinos.

  GNU General Public License Usage
  This file may be used under the terms of the GNU
  General Public License version 3.0 as published by the Free Software
  Foundation and appearing in the file license_gpl3.txt included in the
  packaging of this file. Please review the following information to
  ensure the GNU General Public License version 3.0 requirements will be
  met: http://www.gnu.org/copyleft/gpl.html.

  GNU Lesser General Public License Usage
  Alternatively, this file may be used under the terms of the GNU Lesser
  General Public License version 2.1 as published by the Free Software
  Foundation and appearing in the file license_lgpl.txt included in the
  packaging of this file. Please review the following information to
  ensure the GNU Lesser General Public License version 2.1 requirements
  will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.

  Commercial Usage
  Alternatively, licensees holding valid commercial licenses may
  use this file in accordance with the commercial license agreement
  provided with the software or, alternatively, in accordance with the
  terms contained in a written agreement between you and rightful owner.
*/

/* -------------------------------------------------------------------------
	Include
 ------------------------------------------------------------------------- */
#include "../ubiconfig.h"

// standard c library include
#include <stdio.h>
#include <sam4e.h>

// ubinos library include
#include "itf_ubinos/itf/bsp.h"
#include "itf_ubinos/itf/ubinos.h"
#include "itf_ubinos/itf/bsp_fpu.h"

// chipset driver include
#include "ioport.h"
#include "pio/pio.h"

// new estk driver include
#include "lib_new_estk_api/itf/new_estk_led.h"
#include "lib_new_estk_api/itf/new_estk_glcd.h"
#include "lib_EV3_sensor/itf/lib_EV3_sensor.h"
#include "lib_i2c/itf/lib_i2c.h"
#include "lib_motor_driver/itf/lib_motor_driver.h"
#include "lib_sensor/itf/lib_sensor.h"
#include "lib_switch/itf/lib_switch.h"

// custom library header file include
#include "../../lib_new/itf/lib_new.h"
#include "../../lib_sensorcalib/itf/lib_sensorcalib.h"

// user header file include

/* -------------------------------------------------------------------------
	Global variables
 ------------------------------------------------------------------------- */

/* -------------------------------------------------------------------------
	Prototypes
 ------------------------------------------------------------------------- */
static void rootfunc(void * arg);


/* -------------------------------------------------------------------------
	Function Definitions
 ------------------------------------------------------------------------- */
int usrmain(int argc, char * argv[]) {
	int r;

	printf("\n\n\n\r");
	printf("================================================================================\n\r");
	printf("exe_ubinos_test (build time: %s %s)\n\r", __TIME__, __DATE__);
	printf("================================================================================\n\r");

	r = task_create(NULL, rootfunc, NULL, task_getmiddlepriority(), 256, "root");
	if (0 != r) {
		logme("fail at task_create\r\n");
	}

	ubik_comp_start();

	return 0;
}

static void rootfunc(void * arg) {

	//초기화
	glcd_init();
	sensor_init(NXT_DIGITAL_SENSOR_SONA,0,0,0);//port0에 sona센서 사용
	motor_init();
	//calibration sensor : port0, sona sensor
	calibSensor(0,MAX_SONA_LEVEL,sona_value);

	glcd_clear();//화면 정리

	for(;;){

		/* Add user code here */

		glcdGotoChar(0,0);//화면의 0,0으로 이동

		//check sensor level
		switch(get_level(sensor_get(0),MAX_SONA_LEVEL,sona_value))//get_level에서 port0 센서 값을 레벨로 바꿈
		{
			case SONA_CLOSE://가까움
				glcd_printf("CLOSE : %d           ",sensor_get(0));
				printf("CLOSE : %d\n\r",sensor_get(0));//터미널에 출력
				motor_set(0,100);//port0, speed100
				break;
			case SONA_LITTLE_CLOSE://조금가까움
				glcd_printf("Little CLOSE : %d    ",sensor_get(0));
				printf("Little CLOSE : %d\n\r",sensor_get(0));
				motor_set(0,200);
				break;
			case SONA_MIDDLE://중간
				glcd_printf("MIDDLE : %d          ",sensor_get(0));
				printf("MIDDLE : %d\n\r",sensor_get(0));
				motor_set(0,300);
				break;
			case SONA_LITTLE_FAR://조금멈
				glcd_printf("Little FAR : %d      ",sensor_get(0));
				printf("Little FAR : %d\n\r",sensor_get(0));
				motor_set(0,400);
				break;
			case SONA_FAR://멈
				glcd_printf("FAR : %d             ",sensor_get(0));
				printf("FAR : %d\n\r",sensor_get(0));
				motor_set(0,500);
				break;
			default:
				glcd_printf("UNDEFINE");
				printf("UNDEFINE\n\r");
				motor_set(0,0);
				break;
		}
		task_sleep(30);//30ms delay
	}
}
