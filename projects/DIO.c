#include "tm4c123gh6pm.h"
#include "types.h"
#include "DIO.h"
#include "bitwise_operation.h"
#include "tm4c123gh6pm.h"
#include "types.h"
#include <time.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include "inc/hw_gpio.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/debug.h"
#include "driverlib/gpio.h"
#include "driverlib/pin_map.h"
#include "driverlib/rom.h"
#include "driverlib/rom_map.h"
#include "driverlib/sysctl.h"

void PinoutSet(void)
{
	// Enable Peripheral Clocks
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD);


	// Configure GPIO Outputs
	GPIOPinTypeGPIOOutput(GPIO_PORTB_BASE, GPIO_PIN_0);// T1 red LED  On PB0
	GPIOPinTypeGPIOOutput(GPIO_PORTB_BASE, GPIO_PIN_1); //T1 YELLOW LED ON PB1
	GPIOPinTypeGPIOOutput(GPIO_PORTB_BASE, GPIO_PIN_2);//T1 GREEN LED ON PB2 
	GPIOPinTypeGPIOOutput(GPIO_PORTB_BASE, GPIO_PIN_3); //Pedestrian 1 GREEN led on PB3
        GPIOPinTypeGPIOOutput(GPIO_PORTB_BASE, GPIO_PIN_4); //Pedestrian 1 RED  led on PB4
	GPIOPinTypeGPIOOutput(GPIO_PORTD_BASE, GPIO_PIN_0);//T2 red LED  On PD0
	GPIOPinTypeGPIOOutput(GPIO_PORTD_BASE, GPIO_PIN_1);//T2 red LED  On PD1
	GPIOPinTypeGPIOOutput(GPIO_PORTD_BASE, GPIO_PIN_2);//T2 red LED  On PD2
        GPIOPinTypeGPIOOutput(GPIO_PORTD_BASE, GPIO_PIN_3);//Pedestrian 2 GREEN led on PD3
        GPIOPinTypeGPIOOutput(GPIO_PORTD_BASE, GPIO_PIN_6);//Pedestrian 2 RED led on PD6
        
        //Configure GPIO Inputs
                                                      //button for pedesterian 1 is pin 5 in portB
                                                      // button for pedesterian 2 is pin 5 in portD 
        
        
}
void NormalSequence(void)
{
	int i = 0;
	while(1)
	{
		if(i < 1){
			GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2, 0);
			GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2, 0);
			GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_0, 1); // B is RED
			GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_0, 1); // D is RED
			delay(1000); // ~1seconds delay
			i++;
		}
		else if(i < 6){
			GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2, 0);
			GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2, 0);
			GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_0, 1); // B is RED
			GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_2, 4); // D is GREEN
			delay(1000); // 5seconds delay
			i++;
		}
		else if(i < 8){
			GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2, 0);
			GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2, 0);
			GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_0, 1); // B is RED
			GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_1, 2); // D is YELLOW
			delay(1000); // ~2seconds delay
			i++;
		}
		else if(i < 9){
			GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2, 0);
			GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2, 0);
			GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_0, 1); // B is RED
			GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_0, 1); // D is RED
			delay(1000); //~1seconds delay
			i++;
		}
		else if(i < 13){
			GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2, 0);
			GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2, 0);
			GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_2, 4); // B is GREEN
			GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_0, 1); // D is RED
			delay(1000); // 5seconds delay
			i++;
		}
		else if(i < 15){
			GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2, 0);
			GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2, 0);
			GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_1, 2); // B is YELLOW
			GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_0, 1); // D is RED
			delay(1000); // 2seconds delay
		}
                else if (i < 17)
                {
		i = 0;

                }
        }

}
void delay(int time)
{
 SYSCTL_RCGCTIMER_R |=0X1;
 TIMER0_CTL_R =0X0;
 TIMER0_CFG_R=0X00;
 TIMER0_TAMR_R=0X02;
 TIMER0_TAILR_R= (16000*time)-1;
 TIMER0_ICR_R=0X01;
 TIMER0_CTL_R|=0X03;
}
void Timer0AInteruptHandler(void)
{
  {
  TIMER0_ICR_R=TIMER_ICR_TATOCINT;
  }
    NVIC_ST_CTRL_R = 0x00;                   
    NVIC_ST_RELOAD_R = ((16000000*1)-1); 
    NVIC_ST_CURRENT_R = 0X00;
    NVIC_ST_CTRL_R = 0x05;
  if(((GPIO_PORTD_DATA_R & 0X01 )==1)&&((GPIO_PORTB_DATA_R &0X20)==0))   // if the 1st buton is pushed and the other traffic is red
  {
    GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_4, 0);  //Pedestrian 1 RED led off
    GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_3, 1);  //Pedestrian 1 GREEN led on
    GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2, 0);
    GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_0, 1);  // B is RED
    while((NVIC_ST_CTRL_R&10000)==0);      // Delay For 2 Seconds
    while((NVIC_ST_CTRL_R&10000)==0);
    GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_4, 1);  //Pedestrian 1 RED led oN
    GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_3, 0);  //Pedestrian 1 GREEN led oFF
  }
  else if (((GPIO_PORTB_DATA_R & 0X01 )==1)&&((GPIO_PORTD_DATA_R &0X20)==0))  //if the 2nd buton is pushed and the other traffic is red
  {
    GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_6, 0);  //Pedestrian 2 RED led off
    GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_3, 1);  //Pedestrian 2 GREEN led on
    GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2, 0);
    GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_0, 1);  // D is RED
    while((NVIC_ST_CTRL_R&10000)==0);      // Delay For 2 Seconds
    while((NVIC_ST_CTRL_R&10000)==0);
    GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_6, 1);  //Pedestrian 2 RED led oN
    GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_3, 0);  //Pedestrian 2 GREEN led oFF
  }
}

