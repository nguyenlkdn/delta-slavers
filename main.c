#include "main.h"
/*
 * System Function
 */

/*
 * User Function
 */
//*****************************************************************************
//
// The System Variables
//
//*****************************************************************************
int k=1800;
//*****************************************************************************
//
// Main Function
//
//*****************************************************************************
//PWMPulseWidthSet(PWM1_BASE, PWM_OUT_5, k); //2600
//PWMPulseWidthSet(PWM1_BASE, PWM_OUT_6, k+800);//3400
void main(void) {
	init();
	int j;
	for(j=2000;j<4000;j+=100){
		PWMPulseWidthSet(PWM0_BASE, PWM_OUT_6, j);
		PWMPulseWidthSet(PWM0_BASE, PWM_OUT_7, j);
		SysCtlDelay(SysCtlClockGet()/2);
	}
	while(1){
			SysCtlDelay(SysCtlClockGet()/10000);
	}
}
/*
 * User Function
 */
//*****************************************************************************
//
// The Interrupt Vector
//
//*****************************************************************************
// Vector Timer 0
void Timer0IntHandler(void){
    ROM_TimerIntClear(TIMER0_BASE, TIMER_TIMA_TIMEOUT);
}
// Vector Timer 1
void Timer1IntHandler(void){
    ROM_TimerIntClear(TIMER1_BASE, TIMER_TIMA_TIMEOUT);
}
// Vector Timer 2
void Timer2IntHandler(void){
	ROM_TimerIntClear(TIMER2_BASE, TIMER_TIMA_TIMEOUT);
}
void Timer3IntHandler(void){
    ROM_TimerIntClear(TIMER3_BASE, TIMER_TIMA_TIMEOUT);
}
void Timer4IntHandler(void){
    ROM_TimerIntClear(TIMER4_BASE, TIMER_TIMA_TIMEOUT);
}
void Timer5IntHandler(void){
    ROM_TimerIntClear(TIMER5_BASE, TIMER_TIMA_TIMEOUT);
    //GPIOPinWrite(GPIO_PORTE_BASE, GPIO_PIN_3, ~GPIOPinRead(GPIO_PORTE_BASE, GPIO_PIN_3));

}
void SysTickIntHandler(void){
	GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1, ~GPIOPinRead(GPIO_PORTF_BASE, GPIO_PIN_1));
}
// Vector PORT F
void PortFIntHandler(void){
	uint32_t PortFmask = GPIOIntStatus(GPIO_PORTF_BASE, GPIO_PIN_0 | GPIO_PIN_4);
	if(PortFmask & GPIO_PIN_0){
		/////////////////////////////////////////////////////////////////////////////////////////////
		UARTprintf("\nButton 2 !");
		PWMPulseWidthSet(PWM0_BASE, PWM_OUT_6, 3400);
		PWMPulseWidthSet(PWM0_BASE, PWM_OUT_7, 3400);
		/////////////////////////////////////////////////////////////////////////////////////////////
		SysCtlDelay(SysCtlClockGet()/50);
		GPIOIntClear(GPIO_PORTF_BASE, GPIO_PIN_0);
	}
	if(PortFmask & GPIO_PIN_4){
		/////////////////////////////////////////////////////////////////////////////////////////////
		k+=50;
		UARTprintf("\nButton 1 ! k=%d",k);
		PWMPulseWidthSet(PWM0_BASE, PWM_OUT_6, k);
		PWMPulseWidthSet(PWM0_BASE, PWM_OUT_7, k);
		/////////////////////////////////////////////////////////////////////////////////////////////
		SysCtlDelay(SysCtlClockGet()/50);
		GPIOIntClear(GPIO_PORTF_BASE, GPIO_PIN_4);
	}
}
