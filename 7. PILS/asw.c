#include "ee.h"
#include "Arduino.h"
#include "serial.h"
#include "Sense.h"
#include "Compute.h"
#include "Actuate.h"


void mdelay(unsigned long delay_ms);

void StartupHook(void)
{
	/* write below your code */
	Sense_initialize();
	Compute_initialize();
	Actuate_initialize();
               /*end*/

    printfSerial("\nOS Begins... ", 0ul);
}

/* Timer1 ISR2 */
ISR2(TimerISR)
{
    static long c = -5;
    IncrementCounter(counter1);
    printfSerial("\n%4ld: ", ++c);
}


/* write below your code */
TASK(Task1)
{
	Sense_step();
	Compute_U.in = Sense_Y.out;
	printfSerial("%f", Sense_Y.out);
	TerminateTask();
}

TASK(Task2)
{
	Compute_step();
	Actuate_U.in = Compute_Y.out;
	printfSerial("    %f", Compute_Y.out);
	TerminateTask();
}

TASK(Task3)
{
	Actuate_step();
	printfSerial("    %f", Actuate_Y.out);
	TerminateTask();
}



        /*end*/

