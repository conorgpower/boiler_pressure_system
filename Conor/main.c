/*
 * main.c
 *
 *  Created on: 2018 Mar 21 11:12:17
 *  Author: Brendan
 */




#include <DAVE.h>                 //Declarations from DAVE Code Generation (includes SFR declaration)

enum state { CLOSED, OPEN25, OPEN50, OPEN100 };
enum state current = CLOSED;

uint32_t result;

void Adjust_Gates(void)
{
	if(result > 2048 & result < 2457) 
	  {
		  current = OPEN25;
	  }
	
  	if(result > 2457 & result < 3276)
  	{
	  	current = OPEN50;
	  }
	
  	if(result > 3276)
	  {
		  current = OPEN100;
  	}
}

void Adc_Measurement_Handler(void)
{
	result = ADC_MEASUREMENT_GetDetailedResult(&ADC_MEASUREMENT_0);
	
	if(result < 1802) 
	{
		current = CLOSED;
	}
	
	if(current == CLOSED)
	{
		Adjust_Gates();
	}
	
	if(current == OPEN25) 
	{
		Adjust_Gates();
	}
	
	if(current == OPEN50)
	{
		Adjust_Gates();
	}
	
	if(current == OPEN100)
	{
		Adjust_Gates();
	}
}

/**

 * @brief main() - Application entry point
 *
 * <b>Details of function</b><br>
 * This routine is the application entry point. It is invoked by the device startup code. It is responsible for
 * invoking the APP initialization dispatcher routine - DAVE_Init() and hosting the place-holder for user application
 * code.
 */

int main(void)
{
  DAVE_STATUS_t status;

  status = DAVE_Init();           /* Initialization of DAVE APPs  */
	
  if(status != DAVE_STATUS_SUCCESS)
  {
    /* Placeholder for error handler code. The while loop below can be replaced with an user error handler. */
    XMC_DEBUG("DAVE APPs initialization failed\n");

    while(1U)
    {
			
    }
  }

  /* Placeholder for user application code. The while loop below can be replaced with user application code. */
  while(1U)
  {
		switch(current)
		{
			case CLOSED:
				/* Closing gates fully */
			  PWM_SetDutyCycle(&PWM_0, 0);
			  PWM_SetFreq(&PWM_0, 0);
			
			case OPEN25:
				/* Opens gates by 25% */
			  PWM_SetDutyCycle(&PWM_0, 10000);
			  PWM_SetFreq(&PWM_0, 25);
		
		  case OPEN50:
				/* Opens gates by 50% */
			  PWM_SetDutyCycle(&PWM_0, 10000);
			  PWM_SetFreq(&PWM_0, 50);
			
			case OPEN100:
				/* Opens gates fully */
			  PWM_SetDutyCycle(&PWM_0, 10000);
			  PWM_SetFreq(&PWM_0, 100);
		}
	}	
}
