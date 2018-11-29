
#include "mcc_generated_files/mcc.h"
#define NUM_STEPS 3200
#define STEPS_PER_NUM 80

bool readSwitch(void);
void openLock(void);
void spinStepper(int16_t nums);


void main(void)
{
    // Initialize the device
    SYSTEM_Initialize();
    DIR_SetHigh();
    ENABLE_SetHigh();

    /*EXAMPLE OF STEPPER OPERATION*/
    while (1){
        
        while (!EUSART1_DataReady);
        char cmd = EUSART1_Read();
        printf("%c\r\n", cmd);
        
        switch(cmd){
            case '?':
                printf("Welcome to the Lock PIC\r\n");
                printf("-----------------------\r\n");
                printf("s: input the correct combo and open the lock!\r\n");
                printf("o: open da thing!\r\n");
                printf("r: is da thing open????s\r\n");
                printf("\r\n");
                break;
            
            
            case 's':
                spinStepper(-80);
                spinStepper(-26);
                INTCONbits.TMR0IF = 0;
                TMR0_Reload();
                while(!TMR0_HasOverflowOccured());
                spinStepper(40);
                spinStepper(6);
                INTCONbits.TMR0IF = 0;
                TMR0_Reload();
                while(!TMR0_HasOverflowOccured());
                spinStepper(-18);
                INTCONbits.TMR0IF = 0;
                TMR0_Reload();
                while(!TMR0_HasOverflowOccured());
                openLock();
                break;
            case 'o':
                openLock();
                break;
            case 'r':
                printf("%u\r\n", readSwitch());
                break;
        }
    }
}



void spinStepper(int16_t nums){
    ENABLE_SetLow();
    uint16_t i;
    DIR_SetHigh();
    if (nums < 0){
        DIR_SetLow();
        nums = -nums;
    }
    
    for (i = 0; i < nums*STEPS_PER_NUM; i++){
            STEP_SetHigh();
            STEP_SetLow();
            PIR1bits.TMR1IF = 0;
            TMR1_Reload();
            while(!TMR1_HasOverflowOccured());
    }
    ENABLE_SetHigh();
}

void openLock(void){
    uint8_t opened = false;
    OPENER_SetHigh();
    INTCONbits.TMR0IF = 0;
    TMR0_Reload();
    while(!TMR0_HasOverflowOccured()){
        opened = readSwitch();
    }
    if(opened) printf("OPENED!\r\n");
    OPENER_SetLow();
}

bool readSwitch(void){
    return REED_GetValue();
}
