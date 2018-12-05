
#include "mcc_generated_files/mcc.h"
#define NUM_STEPS 3200
#define STEPS_PER_NUM 80
#define FULL_ROTATION 40
#define READ_TIME 300 //ms
#define CCW 0
#define CW  1

bool readSwitch(void);
bool openLock(void);
void spinStepper(int16_t nums);
void delay(uint16_t ms);
void moveLockTo(uint8_t pos, uint8_t dir);
uint8_t enterCombo(uint8_t a, uint8_t b, uint8_t c, uint8_t v);

uint8_t lockPosition = 0;

void main(void)
{
    // Initialize the device
    SYSTEM_Initialize();
    DIR_SetHigh();
    //ENABLE_SetHigh();
    ENABLE_SetLow();
    
    uint8_t first = 0, second = 0;

    while (true){
        
        while (!EUSART1_DataReady);
        char cmd = EUSART1_Read();
        printf("%c\r\n", cmd);
        
        switch(cmd){
            case '?':
                printf("Welcome to the Lock PIC\r\n");
                printf("-----------------------\r\n");
                printf("s: input the correct combo and open the lock!\r\n");
                printf("l: loop through last digit combos\r\n");
                printf("o: open da thing!\r\n");
                printf("r: is da thing open????s\r\n");
                printf("k: reset lock position to 0\r\n");
                
                printf("\r\n");
                break;
            
            case 's':
                enterCombo(14,20,2,true);
                break;
            case 'l':
                //enterCombo(10,30,40,true);
                enterCombo(14,20,40,true);
            case 'o':
                openLock();
                break;
            case 'r':
                printf("%u\r\n", readSwitch());
                break;
            case 'k':
                lockPosition = 0;
                break;
            case 't':
                ENABLE_Toggle();
                break;
            case '1':
                enterCombo(14,20,2,true);
                break;
            case '2':
                if (enterCombo(4,7,9,true)) break;
                if (enterCombo(10,20,5,true)) break;
                if (enterCombo(30,10,2,true)) break;
                if (enterCombo(14,20,2,true)) break;
                if (enterCombo(1,2,3,true)) break;
                break;
            case '3':
                break;
                
                
        }
    }
}

uint8_t enterCombo(uint8_t a, uint8_t b, uint8_t c, uint8_t v){
    int8_t lastNum;
    if (v) printf("Trying %u %u %u\r\n", a, b, c);
    //enter first number
    spinStepper(-2*FULL_ROTATION);
    moveLockTo(a, CW);
    delay(20);

    //enter second number
    spinStepper(1*FULL_ROTATION);
    moveLockTo(b, CCW);
    delay(20);
    
    if (c != 40){
        moveLockTo(c, CW);
        return openLock();
    }
    else {
        //try all variations of the last number 
        for(lastNum = b-3; lastNum != b; lastNum -= 3){
            if (lastNum < 0) lastNum += FULL_ROTATION;
            moveLockTo(lastNum, CW);
            printf("Now at position %u\r\n", lockPosition);
            delay(20);
            if (openLock()) return true;
        }
        return false;
    }

}

void moveLockTo(uint8_t pos, uint8_t dir){
    //determine difference between current pos and target pos
    int16_t delta;
    if (dir == CW)
        delta = -((lockPosition + FULL_ROTATION - pos) % FULL_ROTATION);
    else
        delta = ((pos - lockPosition + FULL_ROTATION) % FULL_ROTATION);
    
    //spin the stepper according to difference
    spinStepper(delta);
    
    //update the lock position
    if (delta < 0) delta += FULL_ROTATION;
    lockPosition = (lockPosition + delta) % FULL_ROTATION;
   
}

void spinStepper(int16_t nums){
    uint16_t i;
    
    //turn the stepper on
    ENABLE_SetLow();
    
    //determine direction
    DIR_SetHigh();
    if (nums < 0){
        DIR_SetLow();
        nums = -nums;
    }
    
    //spin stepper for nums steps
    for (i = 0; i < nums*STEPS_PER_NUM; i++){
            STEP_SetHigh();
            STEP_SetLow();
            PIR1bits.TMR1IF = 0;
            TMR1_Reload();
            while(!TMR1_HasOverflowOccured());
    }
    
    //turn the stepper off
    //ENABLE_SetHigh();
}

bool openLock(void){
    uint8_t opened = false;
    uint16_t i;
    
    //fire the solenoid
    OPENER_SetHigh();
    
    //hold it open until we get a read, if any
    for (i=0; i < READ_TIME; i++){
        delay(1);
        if (readSwitch()){ 
            opened = true;
        }
    }
    
    if(opened) printf("OPENED!\r\n");
    
    //turn off the solenoid
    OPENER_SetLow();
    delay(50);
    
    return opened;
}

bool readSwitch(void){
    return REED_GetValue();
}


void delay(uint16_t ms){
    uint16_t i;
    for (i = 0; i < ms; i++){
        INTCONbits.TMR0IF = 0;
        TMR0_Reload();
        while(!TMR0_HasOverflowOccured());
    }
}
