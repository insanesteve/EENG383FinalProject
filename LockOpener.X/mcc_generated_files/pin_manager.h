/**
  @Generated Pin Manager Header File

  @Company:
    Microchip Technology Inc.

  @File Name:
    pin_manager.h

  @Summary:
    This is the Pin Manager file generated using PIC10 / PIC12 / PIC16 / PIC18 MCUs

  @Description
    This header file provides APIs for driver for .
    Generation Information :
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.65.2
        Device            :  PIC18F26K22
        Driver Version    :  2.11
    The generated drivers are tested against the following:
        Compiler          :  XC8 1.45
        MPLAB 	          :  MPLAB X 4.15	
*/

/*
    (c) 2018 Microchip Technology Inc. and its subsidiaries. 
    
    Subject to your compliance with these terms, you may use Microchip software and any 
    derivatives exclusively with Microchip products. It is your responsibility to comply with third party 
    license terms applicable to your use of third party software (including open source software) that 
    may accompany Microchip software.
    
    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER 
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY 
    IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS 
    FOR A PARTICULAR PURPOSE.
    
    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP 
    HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO 
    THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL 
    CLAIMS IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT 
    OF FEES, IF ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS 
    SOFTWARE.
*/

#ifndef PIN_MANAGER_H
#define PIN_MANAGER_H

#define INPUT   1
#define OUTPUT  0

#define HIGH    1
#define LOW     0

#define ANALOG      1
#define DIGITAL     0

#define PULL_UP_ENABLED      1
#define PULL_UP_DISABLED     0

// get/set STEP aliases
#define STEP_TRIS                 TRISAbits.TRISA0
#define STEP_LAT                  LATAbits.LATA0
#define STEP_PORT                 PORTAbits.RA0
#define STEP_ANS                  ANSELAbits.ANSA0
#define STEP_SetHigh()            do { LATAbits.LATA0 = 1; } while(0)
#define STEP_SetLow()             do { LATAbits.LATA0 = 0; } while(0)
#define STEP_Toggle()             do { LATAbits.LATA0 = ~LATAbits.LATA0; } while(0)
#define STEP_GetValue()           PORTAbits.RA0
#define STEP_SetDigitalInput()    do { TRISAbits.TRISA0 = 1; } while(0)
#define STEP_SetDigitalOutput()   do { TRISAbits.TRISA0 = 0; } while(0)
#define STEP_SetAnalogMode()      do { ANSELAbits.ANSA0 = 1; } while(0)
#define STEP_SetDigitalMode()     do { ANSELAbits.ANSA0 = 0; } while(0)

// get/set DIR aliases
#define DIR_TRIS                 TRISAbits.TRISA1
#define DIR_LAT                  LATAbits.LATA1
#define DIR_PORT                 PORTAbits.RA1
#define DIR_ANS                  ANSELAbits.ANSA1
#define DIR_SetHigh()            do { LATAbits.LATA1 = 1; } while(0)
#define DIR_SetLow()             do { LATAbits.LATA1 = 0; } while(0)
#define DIR_Toggle()             do { LATAbits.LATA1 = ~LATAbits.LATA1; } while(0)
#define DIR_GetValue()           PORTAbits.RA1
#define DIR_SetDigitalInput()    do { TRISAbits.TRISA1 = 1; } while(0)
#define DIR_SetDigitalOutput()   do { TRISAbits.TRISA1 = 0; } while(0)
#define DIR_SetAnalogMode()      do { ANSELAbits.ANSA1 = 1; } while(0)
#define DIR_SetDigitalMode()     do { ANSELAbits.ANSA1 = 0; } while(0)

// get/set ENABLE aliases
#define ENABLE_TRIS                 TRISAbits.TRISA2
#define ENABLE_LAT                  LATAbits.LATA2
#define ENABLE_PORT                 PORTAbits.RA2
#define ENABLE_ANS                  ANSELAbits.ANSA2
#define ENABLE_SetHigh()            do { LATAbits.LATA2 = 1; } while(0)
#define ENABLE_SetLow()             do { LATAbits.LATA2 = 0; } while(0)
#define ENABLE_Toggle()             do { LATAbits.LATA2 = ~LATAbits.LATA2; } while(0)
#define ENABLE_GetValue()           PORTAbits.RA2
#define ENABLE_SetDigitalInput()    do { TRISAbits.TRISA2 = 1; } while(0)
#define ENABLE_SetDigitalOutput()   do { TRISAbits.TRISA2 = 0; } while(0)
#define ENABLE_SetAnalogMode()      do { ANSELAbits.ANSA2 = 1; } while(0)
#define ENABLE_SetDigitalMode()     do { ANSELAbits.ANSA2 = 0; } while(0)

// get/set OPENER aliases
#define OPENER_TRIS                 TRISBbits.TRISB0
#define OPENER_LAT                  LATBbits.LATB0
#define OPENER_PORT                 PORTBbits.RB0
#define OPENER_WPU                  WPUBbits.WPUB0
#define OPENER_ANS                  ANSELBbits.ANSB0
#define OPENER_SetHigh()            do { LATBbits.LATB0 = 1; } while(0)
#define OPENER_SetLow()             do { LATBbits.LATB0 = 0; } while(0)
#define OPENER_Toggle()             do { LATBbits.LATB0 = ~LATBbits.LATB0; } while(0)
#define OPENER_GetValue()           PORTBbits.RB0
#define OPENER_SetDigitalInput()    do { TRISBbits.TRISB0 = 1; } while(0)
#define OPENER_SetDigitalOutput()   do { TRISBbits.TRISB0 = 0; } while(0)
#define OPENER_SetPullup()          do { WPUBbits.WPUB0 = 1; } while(0)
#define OPENER_ResetPullup()        do { WPUBbits.WPUB0 = 0; } while(0)
#define OPENER_SetAnalogMode()      do { ANSELBbits.ANSB0 = 1; } while(0)
#define OPENER_SetDigitalMode()     do { ANSELBbits.ANSB0 = 0; } while(0)

// get/set REED aliases
#define REED_TRIS                 TRISCbits.TRISC0
#define REED_LAT                  LATCbits.LATC0
#define REED_PORT                 PORTCbits.RC0
#define REED_SetHigh()            do { LATCbits.LATC0 = 1; } while(0)
#define REED_SetLow()             do { LATCbits.LATC0 = 0; } while(0)
#define REED_Toggle()             do { LATCbits.LATC0 = ~LATCbits.LATC0; } while(0)
#define REED_GetValue()           PORTCbits.RC0
#define REED_SetDigitalInput()    do { TRISCbits.TRISC0 = 1; } while(0)
#define REED_SetDigitalOutput()   do { TRISCbits.TRISC0 = 0; } while(0)

// get/set RC6 procedures
#define RC6_SetHigh()            do { LATCbits.LATC6 = 1; } while(0)
#define RC6_SetLow()             do { LATCbits.LATC6 = 0; } while(0)
#define RC6_Toggle()             do { LATCbits.LATC6 = ~LATCbits.LATC6; } while(0)
#define RC6_GetValue()              PORTCbits.RC6
#define RC6_SetDigitalInput()    do { TRISCbits.TRISC6 = 1; } while(0)
#define RC6_SetDigitalOutput()   do { TRISCbits.TRISC6 = 0; } while(0)
#define RC6_SetAnalogMode()         do { ANSELCbits.ANSC6 = 1; } while(0)
#define RC6_SetDigitalMode()        do { ANSELCbits.ANSC6 = 0; } while(0)

// get/set RC7 procedures
#define RC7_SetHigh()            do { LATCbits.LATC7 = 1; } while(0)
#define RC7_SetLow()             do { LATCbits.LATC7 = 0; } while(0)
#define RC7_Toggle()             do { LATCbits.LATC7 = ~LATCbits.LATC7; } while(0)
#define RC7_GetValue()              PORTCbits.RC7
#define RC7_SetDigitalInput()    do { TRISCbits.TRISC7 = 1; } while(0)
#define RC7_SetDigitalOutput()   do { TRISCbits.TRISC7 = 0; } while(0)
#define RC7_SetAnalogMode()         do { ANSELCbits.ANSC7 = 1; } while(0)
#define RC7_SetDigitalMode()        do { ANSELCbits.ANSC7 = 0; } while(0)

/**
   @Param
    none
   @Returns
    none
   @Description
    GPIO and peripheral I/O initialization
   @Example
    PIN_MANAGER_Initialize();
 */
void PIN_MANAGER_Initialize (void);

/**
 * @Param
    none
 * @Returns
    none
 * @Description
    Interrupt on Change Handling routine
 * @Example
    PIN_MANAGER_IOC();
 */
void PIN_MANAGER_IOC(void);



#endif // PIN_MANAGER_H
/**
 End of File
*/