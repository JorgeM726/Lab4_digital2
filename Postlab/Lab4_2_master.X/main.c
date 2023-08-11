// CONFIG1
#pragma config FOSC = INTRC_NOCLKOUT// Oscillator Selection bits (RCIO oscillator: I/O function on RA6/OSC2/CLKOUT pin, RC on RA7/OSC1/CLKIN)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled and can be enabled by SWDTEN bit of the WDTCON register)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config MCLRE = OFF      // RE3/MCLR pin function select bit (RE3/MCLR pin function is digital input, MCLR internally tied to VDD)
#pragma config CP = OFF         // Code Protection bit (Program memory code protection is disabled)
#pragma config CPD = OFF        // Data Code Protection bit (Data memory code protection is disabled)
#pragma config BOREN = OFF      // Brown Out Reset Selection bits (BOR disabled)
#pragma config IESO = OFF       // Internal External Switchover bit (Internal/External Switchover mode is disabled)
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enabled bit (Fail-Safe Clock Monitor is disabled)
#pragma config LVP = OFF        // Low Voltage Programming Enable bit (RB3 pin has digital I/O, HV on MCLR must be used for programming)

// CONFIG2
#pragma config BOR4V = BOR40V   // Brown-out Reset Selection bit (Brown-out Reset set to 4.0V)
#pragma config WRT = OFF        // Flash Program Memory Self Write Enable bits (Write protection off)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

//*****************************************************************************
// Definición e importación de librerías
//*****************************************************************************
#include <stdint.h>
#include <pic16f887.h>
#include "I2C.h"
#include <xc.h>
#include "LCD.h"
#include "IOCB.h"
//*****************************************************************************
// Definición de variables
//*****************************************************************************
#define _XTAL_FREQ 8000000
int year = 23;   //2023
int month = 8;  //agosto
int date = 8;   //8
int hour = 16;   
int min = 59;
int sec = 50;
uint8_t slaveVal;
void uint8ToString(uint8_t num, char *str);
int d2b (int to_convert);
int  b2d(int to_convert);
char buffer[4];
char buffer2[4];
char buffer3[4];
//*****************************************************************************
// Definición de funciones para que se puedan colocar después del main de lo 
// contrario hay que colocarlos todas las funciones antes del main
//*****************************************************************************
void setup(void);

void __interrupt() isr (void){
    
     if (INTCONbits.RBIF){
        
        if (PORTBbits.RB0==0){ 
           
            hour++;
            if (hour > 23){
                hour = 0;
            }
            I2C_Master_Start();
            I2C_Master_Write(0xD0);
            I2C_Master_Write(0x02);
            I2C_Master_Write(d2b(hour));
            I2C_Master_Stop();
            __delay_ms(100);
        } 
        
        else if (PORTBbits.RB1 ==0){ 
            hour--;
            
            I2C_Master_Start();
            I2C_Master_Write(0xD0);
            I2C_Master_Write(0x02);
            I2C_Master_Write(d2b(hour));
            I2C_Master_Stop();
            __delay_ms(100);
        } 
        
        if (PORTBbits.RB2==0){ 
           
            min++;
            if (min > 59){
                min = 0;
            }
            I2C_Master_Start();
            I2C_Master_Write(0xD0);
            I2C_Master_Write(0x01);
            I2C_Master_Write(d2b(min));
            I2C_Master_Stop();
            __delay_ms(100);
        } 
        
        else if (PORTBbits.RB3 ==0){ 
            min--;
            
            I2C_Master_Start();
            I2C_Master_Write(0xD0);
            I2C_Master_Write(0x01);
            I2C_Master_Write(d2b(min));
            I2C_Master_Stop();
            __delay_ms(100);
        } 
        if (PORTBbits.RB4==0){ 
           
            date++;
            if (date > 31){
                date = 1;
            }
            I2C_Master_Start();
            I2C_Master_Write(0xD0);
            I2C_Master_Write(0x04);
            I2C_Master_Write(d2b(date));
            I2C_Master_Stop();
            __delay_ms(100);
        } 
        
        else if (PORTBbits.RB5 ==0){ 
             date--;
            if (date <= 0){
                date = 1;
            }
            I2C_Master_Start();
            I2C_Master_Write(0xD0);
            I2C_Master_Write(0x04);
            I2C_Master_Write(d2b(date));
            I2C_Master_Stop();
            __delay_ms(100);
        } 
        if (PORTBbits.RB6==0){ 
           
            year++;
            
            I2C_Master_Start();
            I2C_Master_Write(0xD0);
            I2C_Master_Write(0x06);
            I2C_Master_Write(d2b(year));
            I2C_Master_Stop();
            __delay_ms(100);
        } 
        
        else if (PORTBbits.RB7 ==0){ 
            year--;
           
            I2C_Master_Start();
            I2C_Master_Write(0xD0);
            I2C_Master_Write(0x06);
            I2C_Master_Write(d2b(year));
            I2C_Master_Stop();
            __delay_ms(100);
        } 
        
        
        INTCONbits.RBIF=0;
    }
    
   
    return;
}

//*****************************************************************************
// Main
//*****************************************************************************
void main(void) {
    setup();
    //Set Time
    //sec
    I2C_Master_Start();
    I2C_Master_Write(0xD0);
    I2C_Master_Write(0x00);
    I2C_Master_Write(d2b(sec));
    I2C_Master_Stop();
    __delay_ms(100);
    
    
     //min
    I2C_Master_Start();
    I2C_Master_Write(0xD0);
    I2C_Master_Write(0x01);
    I2C_Master_Write(d2b(min));
    I2C_Master_Stop();
    __delay_ms(100);
    
     //hour
    I2C_Master_Start();
    I2C_Master_Write(0xD0);
    I2C_Master_Write(0x02);
    I2C_Master_Write(d2b(hour));
    I2C_Master_Stop();
    __delay_ms(100);
    
    
       //day
    I2C_Master_Start();
    I2C_Master_Write(0xD0);
    I2C_Master_Write(0x04);
    I2C_Master_Write(d2b(date));
    I2C_Master_Stop();
    __delay_ms(100);
    
       //month
    I2C_Master_Start();
    I2C_Master_Write(0xD0);
    I2C_Master_Write(0x05);
    I2C_Master_Write(d2b(month));
    I2C_Master_Stop();
    
     //year
    I2C_Master_Start();
    I2C_Master_Write(0xD0);
    I2C_Master_Write(0x06);
    I2C_Master_Write(d2b(year));
    I2C_Master_Stop();
    __delay_ms(100);
    

        
    while(1){
        
        I2C_Master_Start();
        I2C_Master_Write(0x50);
        I2C_Master_Write(0);
        I2C_Master_Stop();
        __delay_ms(200);
       
        I2C_Master_Start();
        I2C_Master_Write(0x51);
        slaveVal = I2C_Master_Read(0);
        I2C_Master_Stop();
        __delay_ms(200);
      
        

        //leer segundos
        I2C_Master_Start();
        I2C_Master_Write(0xD0);
        I2C_Master_Write(0x00);
        I2C_Master_RepeatedStart();
        I2C_Master_Write(0xD1);
        sec = b2d(I2C_Master_Read(0));
        I2C_Master_Stop();
        
          //leer minutos
        I2C_Master_Start();
        I2C_Master_Write(0xD0);
        I2C_Master_Write(0x01);
        I2C_Master_RepeatedStart();
        I2C_Master_Write(0xD1);
        min = b2d(I2C_Master_Read(0));
        I2C_Master_Stop();
        
           //leer horas
        I2C_Master_Start();
        I2C_Master_Write(0xD0);
        I2C_Master_Write(0x02);
        I2C_Master_RepeatedStart();
        I2C_Master_Write(0xD1);
        hour = b2d(I2C_Master_Read(0));
        I2C_Master_Stop();
        
        
            //leer día
        I2C_Master_Start();
        I2C_Master_Write(0xD0);
        I2C_Master_Write(0x04);
        I2C_Master_RepeatedStart();
        I2C_Master_Write(0xD1);
        date = b2d(I2C_Master_Read(0));
        I2C_Master_Stop();
        
            //leer mes
        I2C_Master_Start();
        I2C_Master_Write(0xD0);
        I2C_Master_Write(0x05);
        I2C_Master_RepeatedStart();
        I2C_Master_Write(0xD1);
        month = b2d(I2C_Master_Read(0));
        I2C_Master_Stop();
        
        
            //leer año
        I2C_Master_Start();
        I2C_Master_Write(0xD0);
        I2C_Master_Write(0x06);
        I2C_Master_RepeatedStart();
        I2C_Master_Write(0xD1);
        month = b2d(I2C_Master_Read(0));
        I2C_Master_Stop();
        
        
//        
//      
        uint8ToString(sec,buffer);
        uint8ToString(min,buffer2);
        uint8ToString(slaveVal,buffer3);

        char hour0 = hour%10;
        char hour1 = hour/10;
        char date0 = date%10;
        char date1 = date/10;
        char month0 = month%10;
        char month1 = month/10;
        char year0 = year%10;
        char year1 = year/10;
        
        Lcd_Clear();
        Lcd_Set_Cursor(1,1);
        Lcd_Write_String("S1: ");
        Lcd_Write_Char(hour1+'0');
        Lcd_Write_Char(hour0+'0');
        Lcd_Write_Char(':');
        Lcd_Write_String(buffer2);
        Lcd_Write_Char(':');
        Lcd_Write_String(buffer);
        
        Lcd_Set_Cursor(2,1);
        Lcd_Write_String(buffer3);//-------------------------
        Lcd_Write_String("   ");
        Lcd_Write_Char(date1+'0');
        Lcd_Write_Char(date0+'0');
        Lcd_Write_Char(':');
        Lcd_Write_Char(month1+'0');
        Lcd_Write_Char(month0+'0');
        Lcd_Write_Char(':');
        Lcd_Write_Char(year1+'0');
        Lcd_Write_Char(year0+'0');
        __delay_ms(500); 
   
        
    }
    return;
}
//*****************************************************************************
// Función de Inicialización
//*****************************************************************************
void setup(void){
     // CONFIGURACION DEL OSCILADOR
    OSCCONbits.IRCF2 = 1;
    OSCCONbits.IRCF1 = 1;
    OSCCONbits.IRCF0 = 1; // 8MHZ
    OSCCONbits.SCS = 1;  // OSCILADOR INTERNO 
    ANSEL = 0;
    ANSELH = 0;
    TRISA =0;
    PORTA = 0;
    ioc_init(0xFF);
    TRISD = 0;
    PORTB = 0;
    PORTD = 0;
    
    INTCONbits.PEIE = 1;        // Int. de perifericos
    INTCONbits.GIE = 1;         // Int. globales
    I2C_Master_Init(100000);        // Inicializar Comuncación I2C
    
    Lcd_Init();
     Lcd_Clear();
        Lcd_Set_Cursor(1,1);
        Lcd_Write_String("S1: ");
       
        Lcd_Write_Char(':');
        
        Lcd_Write_Char(':');
        
        
        Lcd_Set_Cursor(2,1);
        Lcd_Write_String("Date: ");
        
        Lcd_Write_Char(':');
        
        Lcd_Write_Char(':');
        
}

int  b2d(int to_convert){
   return (to_convert >> 4) * 10 + (to_convert & 0x0F); 
}

int d2b (int to_convert){
    unsigned int bcd=0;
    unsigned int multiplier = 1;
    
    while (to_convert >0){
        unsigned int digit = to_convert % 10;
        bcd += digit * multiplier;
        multiplier *= 16;
        to_convert /= 10;
    }
   return bcd;
}

void uint8ToString(uint8_t num, char *str) {
    uint8_t temp = num;
    int8_t i = 0;

    // Handle the case when the input number is 0 separately
    if (temp == 0) {
        str[0] = '0';
        str[1] = '\0';
        return;
    }

    // Extract digits from the number and store them in reverse order
    while (temp > 0) {
        str[i++] = '0' + (temp % 10);
        temp /= 10;
    }

    // Add null terminator
    str[i] = '\0';

    // Reverse the string to get the correct order of digits
    int8_t left = 0;
    int8_t right = i - 1;
    while (left < right) {
        char tempChar = str[left];
        str[left] = str[right];
        str[right] = tempChar;
        left++;
        right--;
    }
}