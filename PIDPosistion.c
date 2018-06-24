/*
 * PIDPosistion.c
 *
 *  Created on: Jun 29, 2014
 *      Author: TDNC
 */
#include "PIDPosistion.h"
/*
 *
 */
int32_t rPos_l, Err_l, pre_err_l, pPart_l, dPart_l, iPart_l, output_l;
int32_t kp_l = 100;
int32_t ki_l = 0;
int32_t kd_l = 40;
// 100 10 15
// 110 20 15
// 110 40 20 100sps
// 110 00 80 200sps
// 100 00 80 200sps

int32_t rPos_r, Err_r, pre_err_r, pPart_r, dPart_r, iPart_r, output_r;
int32_t kp_r = 1;
int32_t ki_r = 1;
int32_t kd_r = 1;

/*
 *
 */
__inline void PIDPos(int32_t pos_l, int32_t pos_r){
	rPos_l 	= 	QEIPositionGet(QEI0_BASE);
	Err_l 	= 	pos_l-rPos_l;
	pPart_l 	= 	kp_l*Err_l;
	dPart_l 	= 	kd_l*(Err_l-pre_err_l)*inv_sampling_time;
	iPart_l 	+= 	(ki_l*sampling_time*Err_l)/1000;

	output_l 	= 	pPart_l + dPart_l + iPart_l;

	if(output_l >= 5000){
		output_l = 4999;
	}
	if(output_l <= -5000){
		output_l = -4999;
	}
	MotorController(output_l, output_l);
//	pre_err_l = Err_l;
	if(!UARTBusy(UART0_BASE)){
		UARTprintf("\npPart : %5d iPart : %5d dPart : %5d Output : %5d Pos : %5d", pPart_l, iPart_l, dPart_l, output_l, rPos_l);
	}
}
void MotorController(int32_t spd_l, int32_t spd_r) {
	int dir_l = 1;
	int dir_r = 0;
	if (spd_l < 0) {
		dir_l = 0;
		spd_l *= -1;
	}
	PWMPulseWidthSet(PWM0_BASE, PWM_OUT_4, 6);
	PWMPulseWidthSet(PWM0_BASE, PWM_OUT_5, 6);
	if(dir_l == 0)
	{
	    PWMPulseWidthSet(PWM0_BASE, PWM_OUT_4, spd_l);
	}
	else
	{
	    PWMPulseWidthSet(PWM0_BASE, PWM_OUT_5, spd_l);
	}
}
