/*
Author: Dotnetmobile
Email: dotnetmobile@gmail.com
Purpose: reengineering the code written by Ben-Tommy Eriksen
         Why? The LCD and the Remote Controller didn't work with my material
Orginal code: https://github.com/BenTommyE/Micro_robot_RC_servo_IR_remote
*/

#include <Wire.h>
#include <LCD.h>
#include <LiquidCrystal_I2C.h>
#include <IRremote.h>

#define I2C_ADDR    0x27  // Define I2C Address where the PCF8574A is
#define BACKLIGHT_PIN     3
#define En_pin  2
#define Rw_pin  1
#define Rs_pin  0
#define D4_pin  4
#define D5_pin  5
#define D6_pin  6
#define D7_pin  7
#define IR_pin 23

#define BTN_0	        0xFF6897 
#define BTN_1           0xFF30CF 
#define BTN_2	        0xFF18E7 
#define BTN_3	        0xFF7A85 
#define BTN_4	        0xFF10EF 
#define BTN_5	        0xFF38C7 
#define BTN_BACKWARD	0xFF22DD 
#define BTN_FORWARD	0xFF02FD 
#define BTN_PLAY_PAUSE	0xFFC23D 
#define BTN_MINUS	0xFFE01F 
#define BTN_PLUS	0xFFA857 
#define BTN_EQ	        0xFF906F 

IRrecv irrecv(IR_pin);
decode_results results;

LiquidCrystal_I2C lcd(I2C_ADDR,En_pin,Rw_pin,Rs_pin,D4_pin,D5_pin,D6_pin,D7_pin);

void setup()
{
  
  lcd.begin (20,2);
  
  // Switch on the backlight
  lcd.setBacklightPin(BACKLIGHT_PIN,POSITIVE);
  lcd.setBacklight(HIGH);
  lcd.home ();                   // go home
  
  Serial.begin(9600);
  // Start the receiver
  irrecv.enableIRIn(); 
}

void loop() {
  if (irrecv.decode(&results)) 
    {
      Serial.println(results.value, DEC);
      switch (results.value) {
        case BTN_0: 
          displayCommand("Button 0");
          break;
        case BTN_1: 
          displayCommand("Button 1"); 
          break;
        case BTN_2: 
          displayCommand("Button 2"); 
          break;
        case BTN_3: 
          displayCommand("Button 3"); 
          break;
        case BTN_4: 
          displayCommand("Button 4"); 
          break;
        case BTN_5: 
          displayCommand("Button 5"); 
          break;
        case BTN_BACKWARD: 
          displayCommand("Button |<<"); 
          break;
        case BTN_FORWARD: 
          displayCommand("Button >>|"); 
          break;
        case BTN_PLAY_PAUSE: 
          displayCommand("Button >||"); 
          break;
        case BTN_MINUS: 
          displayCommand("Button -"); 
          break;
        case BTN_PLUS: 
          displayCommand("Button +"); 
          break;
        case BTN_EQ: 
          displayCommand("Button EQ"); 
          break;
        default:
          break;
      }
      
      // Receive the next value
      irrecv.resume();   
    }
    
}

void displayCommand(char *message) {
  lcd.clear();
  lcd.setCursor(0,0);
  if (message!=NULL) lcd.print(message);
}

