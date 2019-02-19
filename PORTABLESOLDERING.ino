#include <LiquidCrystal.h>
/* Create object named lcd of the class LiquidCrystal */
LiquidCrystal lcd(13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3);  /* For 8-bit mode */
//LiquidCrystal lcd(13, 12, 11, 6, 5, 4, 3);  /* For 4-bit mode */

unsigned char Character1[8] = { 0x04, 0x1F, 0x11, 0x11, 0x1F, 0x1F, 0x1F, 0x1F }; /* Custom Character 1 */
unsigned char Character2[8] = { 0x01, 0x03, 0x07, 0x1F, 0x1F, 0x07, 0x03, 0x01 }; /* Custom Character 2 */

float batt1=0.0 , batt2=0 , batt3=0;
float batt11=0 , batt21=0 , batt31=0;

void setup() {
  lcd.begin(16,2);  /* Initialize 16x2 LCD */
  lcd.clear();  /* Clear the LCD */
  lcd.createChar(0, Character1);  /* Generate custom character */
  lcd.createChar(1, Character2);
}

void loop() {
  
  batt1 = analogRead(A5);
  batt2 = analogRead(A4);
  batt3 = analogRead(A3);
  
  batt3 = 5*(batt3/1024);  
  batt2 = 5*(batt2/1024);
  batt1 = 5*(batt1/1024);

  batt31=batt3;
  batt21 = (2*batt2)-batt31;
  batt11 = (3*batt1)-batt21-batt31;
  
  lcd.setCursor(0,0);
  lcd.print(batt11);
  lcd.setCursor(0,1);
  lcd.print(batt21);
  lcd.setCursor(10,0);
  lcd.print(batt31);
  
  if(batt11<=3.0){  
  lcd.setCursor(6,0);
  lcd.print("LOW");
      }
   else {  
  lcd.setCursor(6,0);
  lcd.print("");
      }
      
  if(batt21<=3.0){  
  lcd.setCursor(6,1);
  lcd.print("LOW");
  }

 /* if(batt3<=3.0){  
  lcd.setCursor(6,0);
  lcd.print("LOW");
  }*/
}
