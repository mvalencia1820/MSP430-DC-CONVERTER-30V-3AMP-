#include "Energia.h"
#include <stdio.h>

void setup();
void loop();

void lcd_send_nibble(int nibble, int rs_bit);
void lcd_send_byte(int address, int n);
void lcd_init(void);
void lcd_gotoxy(int x, int y);
void lcd_putc(char c);
void lcd_clear();

void lcd_text(char* textptr);

int RS_bit;
#define lcd_type 2        // 0=5x7, 1=5x10, 2=2 lines
#define lcd_line_two 0x40 // LCD RAM address for the 2nd line
//------------ Pines del LCD ---------------------//
#define LCD_E     P2_2
#define LCD_CK    P2_0
#define LCD_DAT   P2_1


int const LCD_INIT_STRING[4] =
{
 0x20 | (lcd_type << 2), // Func set: 4-bit, 2 lines, 5x8 dots
 0xc,                    // Display on
 1,                      // Clear display
 6                       // Increment cursor
 };

char Mensaje[20]="0";
char Mensaje1[20]="0";

float current,vol;
// the setup routine runs once when you press reset:
void setup() {
    pinMode(P2_4, OUTPUT);

    digitalWrite(P2_4,0);




	pinMode(LCD_E, OUTPUT);
	pinMode(LCD_CK, OUTPUT);
	pinMode(LCD_DAT, OUTPUT);
    lcd_init();              // inicializamos el LCD

    lcd_clear();
    sprintf(Mensaje,"DC Buck MSP430");

    lcd_text(Mensaje);
}

// the loop routine runs over and over again forever:
void loop() {
    // set the frequency:
    analogFrequency(100e3);
    analogWrite(P2_4,16);       // 16 - 5v
    int R0,R1;



      while(1){
          int Voltaje = analogRead(A4);
          int Current = analogRead(A5);

           vol=(float)Voltaje*3.8/1000*12.195;   //27.5 //2.1V
           current=(float)Current*3.3/1023;



          R0=(int)vol;
          R1=(int)((vol-R0)*10);
          sprintf(Mensaje,"V = %d.%d v",R0,R1);


          R0=(int)current;
           R1=(int)((current-R0)*10);

          // sprintf(Mensaje1,"I = %d.%d A",R0,R1);
           sprintf(Mensaje1,"I = %d",Current);

          /*

          Voltaje=(int)Voltaje*3.3/1023*12.195;
          Current=(int)((Current*3.3/1023)/4.3)/0.22;*/



          lcd_clear();
          lcd_text(Mensaje);
          lcd_gotoxy(1,2);
          lcd_text(Mensaje1);
          delay(500);

      }
    //PWM (Pin, Duty Cycle) - Maximum = 100% = 255
/*
    for(int ii=5;ii<=255;ii=ii+5){
        lcd_clear();

        sprintf(Mensaje,"ii = %d",ii);

        lcd_text(Mensaje);

        analogWrite(P2_4,ii);
        delay(5000);

    }*/
/*    int sensorValue = analogRead(A0);
    double voltage =(double)sensorValue*3/1023;

    lcd_clear();
	sprintf(Mensaje,"A0 = %d",sensorValue);
    sprintf(Mensaje1,"3 pin LCD",voltage);

	lcd_text(Mensaje);
	lcd_gotoxy(1,2);
	lcd_text(Mensaje1);
	delay(200);*/

}



void lcd_text(char* textptr)
{

   for(; *textptr != '\0'; ++textptr)                              // Bucle sobre las letras a escribir
   {
       lcd_putc(*textptr);
   }
}


//-------------------------------------
void lcd_send_nibble(int nibble, int rs_bit)
{

int x;
if(RS_bit==1)
   nibble=nibble|0x10;





for(x=0;x<5;x++){
       //  output_bit(LCD_DAT,shift_right(&nibble,1,0));

		digitalWrite(LCD_DAT, (((nibble>>x)&0x1)!=0));


			delayMicroseconds(1);
         digitalWrite(LCD_CK,LOW);
         delayMicroseconds(1);
         digitalWrite(LCD_CK,HIGH);
         }


		digitalWrite(LCD_E,HIGH);
		delayMicroseconds(2);
		digitalWrite(LCD_E,LOW);


}

//-----------------------------------
//----------------------------------------
// Send a byte to the LCD.
void lcd_send_byte(int address, int n)
{
//output_low(LCD_RS);
RS_bit=0;
//delay_us(100);
delayMicroseconds(100);

if(address)
   //output_high(LCD_RS);
   RS_bit=1;
else
   //output_low(LCD_RS);
   RS_bit=0;

// delay_cycles(1);
delayMicroseconds(1);

//output_low(LCD_E);
digitalWrite(LCD_E,LOW);
lcd_send_nibble(n >> 4,RS_bit);
lcd_send_nibble(n & 0xf,RS_bit);
}

//----------------------------
void lcd_init(void)
{
int i;

//output_low(LCD_RS);
RS_bit=0;
digitalWrite(LCD_E,LOW);
//output_low(LCD_E);

delay(20);

for(i=0 ;i < 3; i++)
   {
    lcd_send_nibble(0x03,RS_bit);
    delay(5);
   }

lcd_send_nibble(0x02,RS_bit);

    for(i=0; i<4; i++)
   {
    lcd_send_byte(0, LCD_INIT_STRING[i]);

    delay(5);

   }
delay(20);
}

//----------------------------

void lcd_gotoxy(int x, int y)
{
int address;

if(y != 1)
   address = lcd_line_two;
else
   address=0;

address += x-1;
lcd_send_byte(0, 0x80 | address);
}


void lcd_clear()
{
    lcd_send_byte(0,1);
    delay(8);
 }

void lcd_putc(char c)
{
  lcd_send_byte(1,c);
}

