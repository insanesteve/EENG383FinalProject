
#include "mcc_generated_files/mcc.h"
#define NUM_STEPS 3200
#define STEPS_PER_NUM 80
#define FULL_ROTATION 40
#define CCW 0
#define CW  1

bool readSwitch(void);
bool openLock(void);
void spinStepper(int16_t nums);
void delay(uint16_t ms);
void moveLockTo(uint8_t pos, uint8_t dir);
void enterCombo(uint8_t a, uint8_t b, uint8_t c);

uint8_t lockPosition = 0;

void main(void)
{
    // Initialize the device
    SYSTEM_Initialize();
    DIR_SetHigh();
    ENABLE_SetHigh();
    
    uint8_t lastNum;

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
                printf("k: reset lock position to 0");
                printf("\r\n");
                break;
            
            case 's':
                
                enterCombo(14,20,2);
                
                break;
            case 'o':
                openLock();
                break;
            case 'r':
                printf("%u\r\n", readSwitch());
                break;
            case 'k':
                lockPosition = 0;
                break;
        }
    }
}

void enterCombo(uint8_t a, uint8_t b, uint8_t c){
    uint8_t lastNum;
    spinStepper(-2*FULL_ROTATION);
    moveLockTo(a, CW);
    printf("Now at position %u\r\n", lockPosition);
    delay(20);

    spinStepper(1*FULL_ROTATION);
    moveLockTo(b, CCW);
    printf("Now at position %u\r\n", lockPosition);
    delay(20);

    for(lastNum = 39; lastNum != 0; lastNum--){
        moveLockTo(lastNum, CW);
        printf("Now at position %u\r\n", lockPosition);
        delay(20);
        if (openLock()) break;
    }

}

void moveLockTo(uint8_t pos, uint8_t dir){
    int16_t delta;
    if (dir == CW)
        delta = -((lockPosition + FULL_ROTATION - pos) % FULL_ROTATION);
    else
        delta = ((pos - lockPosition + FULL_ROTATION) % FULL_ROTATION);
    spinStepper(delta);
    if (delta < 0) delta += FULL_ROTATION;
    lockPosition = (lockPosition + delta) % FULL_ROTATION;
   
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

bool openLock(void){
    uint8_t opened = false;
    uint16_t i;
    OPENER_SetHigh();
    for (i=0; i < 1000; i++){
        delay(1);
        if (readSwitch()) opened = true;
    }
    if(opened) printf("OPENED!\r\n");
    OPENER_SetLow();
    delay(50);
    return opened;
}

bool readSwitch(void){
    return REED_GetValue();
}


void delay(uint16_t ms){
    uint16_t i = 0;
    // 1 ms per loop
    for (i = 0; i < ms; i++){
        INTCONbits.TMR0IF = 0;
        TMR0_Reload();
        while(!TMR0_HasOverflowOccured());
    }
}
