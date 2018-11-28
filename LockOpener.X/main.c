
#include "mcc_generated_files/mcc.h"
#define NUM_STEPS 3200
void main(void)
{
    // Initialize the device
    SYSTEM_Initialize();
    DIR_SetHigh();

    // If using interrupts in PIC18 High/Low Priority Mode you need to enable the Global High and Low Interrupts
    // If using interrupts in PIC Mid-Range Compatibility Mode you need to enable the Global and Peripheral Interrupts
    // Use the following macros to:

    // Enable the Global Interrupts
    //INTERRUPT_GlobalInterruptEnable();

    // Disable the Global Interrupts
    //INTERRUPT_GlobalInterruptDisable();

    // Enable the Peripheral Interrupts
    //INTERRUPT_PeripheralInterruptEnable();

    // Disable the Peripheral Interrupts
    //INTERRUPT_PeripheralInterruptDisable();

    while (1)
    {
        uint16_t i;
        for (i = 0; i < NUM_STEPS; i++){
            STEP_SetHigh();
            //INTCONbits.TMR0IF = 0;
            //TMR0_Reload();
            //while(!TMR0_HasOverflowOccured());
            STEP_SetLow();
            INTCONbits.TMR0IF = 0;
            TMR0_Reload();
            while(!TMR0_HasOverflowOccured());
        }
        DIR_Toggle();
        //printf("got here.\r\n");
    }
}
