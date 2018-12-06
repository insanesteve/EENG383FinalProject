
#include "mcc_generated_files/mcc.h"
#define NUM_STEPS 3200
#define STEPS_PER_NUM 80
#define FULL_ROTATION 40
#define READ_TIME 300 //ms
#define CCW 0
#define CW  1

#define LOOP 40

bool readSwitch(void);
bool openLock(void);
void spinStepper(int16_t nums);
void delay(uint16_t ms);
void moveLockTo(uint8_t pos, uint8_t dir);
uint8_t enterCombo(uint8_t a, uint8_t b, uint8_t c, uint8_t v);

uint8_t lockPosition = 0;

void main(void)
{
    uint8_t solved = false;
    // Initialize the device
    SYSTEM_Initialize();
    DIR_SetHigh();
    
    uint8_t first = 0, second = 0, third = 0;

    while (true){
        ENABLE_SetHigh();
        while (!EUSART1_DataReady);
        char cmd = EUSART1_Read();
        printf("%c\r\n", cmd);
        
        switch(cmd){
            case '?':
                printf("Welcome to the Lock PIC\r\n");
                printf("-----------------------\r\n");
                printf("l: loop through last digit combos\r\n");
                printf("o: open da thing!\r\n");
                printf("r: is da thing open????\r\n");
                printf("k: reset lock position to 0\r\n");
                printf("1-3: Run milestone 2 demos 1-3\r\n");
                printf("\r\n");
                break;
                
            case 'l':
                enterCombo(10,30,LOOP,true);
                //enterCombo(14,20,LOOP,true);
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
            case 't':
                ENABLE_SetLow();
                openLock();
                ENABLE_SetHigh();
                break;
            case 'u':
                OPENER_SetHigh();
                while (!EUSART1_DataReady);
                EUSART1_Read();
                OPENER_SetLow();
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
                solved = false;
                for (first = 14; first <= 39 && !solved; first += 2){
                    for (second = 10; second <= 39 && !solved; second += 2){
                        if (first != second){
                            third = enterCombo(first, second, LOOP, true);
                            if(third != 255) {
                                solved = true;
                            }
                            if (EUSART1_DataReady) {
                                solved = true;
                                EUSART1_Read();
                            }
                        }
                    }
                }
                if (solved)
                    printf("Done! The combination is %u-%u-%u\r\n", first-2, second-2, third);
                break;
        }
    }
    

}

uint8_t enterCombo(uint8_t a, uint8_t b, uint8_t c, uint8_t v){
    ENABLE_SetLow();
    int8_t lastNum;
    uint8_t opened = false;
    
    
    //enter first number
    spinStepper(-2*FULL_ROTATION);
    moveLockTo(a, CW);
    delay(20);

    //enter second number
    spinStepper(1*FULL_ROTATION);
    moveLockTo(b, CCW);
    delay(20);
    
    if (c != LOOP){
        if (v) printf("Trying %u-%u-%u\r\n", a, b, c);
        moveLockTo(c, CW);
        opened = openLock();
    }
    else {
        //try all variations of the last number 
        for(lastNum = b-2; (lastNum - b + FULL_ROTATION) % FULL_ROTATION >= 2 ; lastNum -= 2){
            if (lastNum < 0) lastNum += FULL_ROTATION;
            moveLockTo(lastNum, CW);
            if (v) printf("Trying %u-%u-%u\r\n", a, b, lastNum);
            delay(20);
            if (openLock()) {
                opened = true;
                break;
            }
            if (EUSART1_DataReady) break;
        }
        if (!opened) return 255;
        return lastNum;
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
