#include "main.h"
#include "PIDPosistion.h"
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
int32_t	pos 	= 0;
int32_t	count 	= 10;
//*****************************************************************************
//
// Main Function
//
//*****************************************************************************
//48clk/r
int mycount=0;
int mode=1;
// 13726
void main(void) {
	init();
	//MotorController(1000, 1000);
//    ROM_GPIOPinTypeGPIOOutput(GPIO_PORTE_BASE,
//            GPIO_PIN_4 | GPIO_PIN_5);
	while (1) {
//		SysCtlDelay(SysCtlClockGet()/2);
//		MotorController(-4000, -4000);
//		SysCtlDelay(SysCtlClockGet()/2);
//
		//UARTprintf("\r%8d%8d", QEIPositionGet(QEI0_BASE), QEIPositionGet(QEI1_BASE));
		if(++mycount < 2000)
		{
	        //GPIOPinWrite(GPIO_PORTE_BASE, GPIO_PIN_4 | GPIO_PIN_5, GPIO_PIN_4);
		    //MotorController(1000, 1000);
		    pos=13726;

		}
		else if(mycount < 4000)
		{
		    pos=0;
	       // GPIOPinWrite(GPIO_PORTE_BASE, GPIO_PIN_4 | GPIO_PIN_5, GPIO_PIN_5);
		    //MotorController(-1000, 1000);
		}
		else
		{
		    mycount = 0;
		}


		SysCtlDelay(SysCtlClockGet()/1000);
	}
}
//*****************************************************************************
//
// The Interrupt Vector
//
//*****************************************************************************
// Vector Timer 0
void Timer0IntHandler(void){
    ROM_TimerIntClear(TIMER0_BASE, TIMER_TIMA_TIMEOUT);
    PIDPos(pos, pos);
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

}
void SysTickIntHandler(void){
	GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1, ~GPIOPinRead(GPIO_PORTF_BASE, GPIO_PIN_1));
}
// Vector UART0
void UART0IntHandler(void){
	//GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_3, ~GPIOPinRead(GPIO_PORTF_BASE, GPIO_PIN_3));
	UARTIntClear(UART0_BASE, UART_INT_RX);
}
// Vector PORT F
void PortFIntHandler(void){
	uint32_t PortFmask = GPIOIntStatus(GPIO_PORTF_BASE, GPIO_PIN_0 | GPIO_PIN_4);
	if(PortFmask & GPIO_PIN_0){
		/////////////////////////////////////////////////////////////////////////////////////////////
		UARTprintf("\nButton 2 !");
		//TimerEnable(TIMER0_BASE, TIMER_A);
		/////////////////////////////////////////////////////////////////////////////////////////////
		//SysCtlDelay(SysCtlClockGet()/100);
		GPIOIntClear(GPIO_PORTF_BASE, GPIO_PIN_0);
	}
	if(PortFmask & GPIO_PIN_4){
		/////////////////////////////////////////////////////////////////////////////////////////////
		UARTprintf("\nButton 1 !");
		/////////////////////////////////////////////////////////////////////////////////////////////
		//SysCtlDelay(SysCtlClockGet()/100);
		GPIOIntClear(GPIO_PORTF_BASE, GPIO_PIN_4);
	}
}
// Vector PORT B
void PortBIntHandler(void){
	//GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1, ~GPIOPinRead(GPIO_PORTF_BASE, GPIO_PIN_1));

	//SysCtlDelay(SysCtlClockGet()/100);
	GPIOIntClear(GPIO_PORTB_BASE, GPIO_PIN_4);
}
