#include <EnableInterrupt.h>
#define SERIAL_PORT_SPEED 57600
#define RC_NUM_CHANNELS  4
#define RC_CH1  0
#define RC_CH2  1
#define RC_CH1_INPUT  A0
#define RC_CH2_INPUT  A1

int forwardleft = 11;
int forwardright = 10;
int backwardleft = 6;
int backwardright = 5;

int forwardleftpwm = 0;
int backwardleftpwm = 0;
int forwardrightpwm = 0;
int backwardrightpwm = 0;

int pwm1 = 0;
int pwm2 = 0;
int pwm3 = 0;

uint16_t rc_values[RC_NUM_CHANNELS];
uint32_t rc_start[RC_NUM_CHANNELS];
volatile uint16_t rc_shared[RC_NUM_CHANNELS];

void rc_read_values() {
  noInterrupts();
  memcpy(rc_values, (const void *)rc_shared, sizeof(rc_shared));
  interrupts();
}

void calc_input(uint8_t channel, uint8_t input_pin) {
  if (digitalRead(input_pin) == HIGH) {
    rc_start[channel] = micros();
  } else {
    uint16_t rc_compare = (uint16_t)(micros() - rc_start[channel]);
    rc_shared[channel] = rc_compare;
  }
}

void calc_ch1() { calc_input(RC_CH1, RC_CH1_INPUT); }
void calc_ch2() { calc_input(RC_CH2, RC_CH2_INPUT); }


void setup() {
  Serial.begin(SERIAL_PORT_SPEED);

  pinMode(RC_CH1_INPUT, INPUT);
  pinMode(RC_CH2_INPUT, INPUT);
  
  pinMode(forwardleft, OUTPUT);
  pinMode(forwardright, OUTPUT);
  pinMode(backwardleft, OUTPUT);
  pinMode(backwardright, OUTPUT);


  enableInterrupt(RC_CH1_INPUT, calc_ch1, CHANGE);
  enableInterrupt(RC_CH2_INPUT, calc_ch2, CHANGE);

  while(rc_values[RC_CH2]==0){rc_read_values();}

}

void loop() {
  rc_read_values();

//Serial.print("CH1:"); Serial.print(rc_values[RC_CH1]); Serial.print("\t");
//Serial.print("CH2:"); Serial.print(rc_values[RC_CH2]); Serial.println("\t");

 if (rc_values[RC_CH2] > 1550){
        pwm1=map (rc_values[RC_CH2], 1500 , 1950, 0, 255);
        if (pwm1>255){pwm1=255;}
        else if (pwm1<0){pwm1=0;}
        if (rc_values[RC_CH1] > 1500){
              pwm2=map(rc_values[RC_CH1], 1500, 1980, 0, 255);
              if (pwm2>255){pwm2=255;}
              if (pwm2<0){pwm2=0;}
              
              forwardrightpwm = pwm1;
              forwardleftpwm = pwm1 - pwm2;              
              if (forwardleftpwm<0){forwardleftpwm=0;}
              
              analogWrite(forwardleft,forwardleftpwm);
              analogWrite(forwardright,forwardrightpwm);
                  }
         else {
              pwm2=map(rc_values[RC_CH1], 1500, 1000, 0, 255);
              if (pwm2>255){pwm2=255;}
              if (pwm2<0){pwm2=0;}
              
              forwardleftpwm = pwm1;
              forwardrightpwm = pwm1 - pwm2;
              if (forwardrightpwm<0){forwardrightpwm=0;}
              
              analogWrite(forwardleft,forwardleftpwm);
              analogWrite(forwardright,forwardrightpwm);
          }
        }
  
  else if (rc_values[RC_CH2] < 1450){
        pwm1=map (rc_values[RC_CH2], 1500 , 990, 0, 255);
        
        if (pwm1>255){pwm1=255;}
        else if (pwm1<0){pwm1=0;}
        
        if (rc_values[RC_CH1] > 1500){
              pwm2=map(rc_values[RC_CH1], 1500, 1980, 0, 255);
              if (pwm2>255){pwm2=255;}
              if (pwm2<0){pwm2=0;}
              
              backwardrightpwm = pwm1;
              backwardleftpwm = pwm1-pwm2;
              
              if (backwardleftpwm<0){backwardleftpwm=0;}

              /*Serial.print(" solalt: ");
              Serial.print(backwardleftpwm);
              Serial.print(" ");
              Serial.println(backwardrightpwm);*/
              
              analogWrite(backwardleft,backwardleftpwm);
              analogWrite(backwardright,backwardrightpwm);
                  }
         else if (rc_values[RC_CH1] < 1500){
              pwm2=map(rc_values[RC_CH1], 1500, 1100, 0, 255);
              if (pwm2>255){pwm2=255;}
              if (pwm2<0){pwm2=0;}
              
              backwardleftpwm = pwm1;
              backwardrightpwm = pwm1-pwm2;
                            
              if (backwardrightpwm <0){backwardrightpwm=0;}

              /*Serial.print(" sagalt: ");
              Serial.print(backwardleftpwm);
              Serial.print(" ");
              Serial.println(backwardrightpwm);*/
              
              analogWrite(backwardleft,backwardleftpwm);
              analogWrite(backwardright,backwardrightpwm);
          }
        }

        
    else {
             if (rc_values[RC_CH1] > 1520){
              pwm3=map(rc_values[RC_CH1], 1550, 2000, 0, 255);
              if (pwm3>255){pwm3=255;}
              else if (pwm3<0){pwm3=0;}
              
             /* Serial.print(" sol: ");
              Serial.println(pwm1);*/
              
              analogWrite(backwardright,0);
              analogWrite(backwardleft, pwm3);
              analogWrite(forwardleft,0);
              analogWrite(forwardright, pwm3);}

              else if (rc_values[RC_CH1] < 1480){
              pwm3=map(rc_values[RC_CH1], 1450, 1000, 0, 255);
              
              if (pwm3>255){pwm3=255;}
              else if (pwm3<0){pwm3=0;}
              
              /*Serial.print(" sag: ");
              Serial.println(pwm2);*/
              
              analogWrite(backwardleft,0);
              analogWrite(backwardright, pwm3);
              analogWrite(forwardright,0);
              analogWrite(forwardleft, pwm3);}
             
             else {
              analogWrite(backwardleft,0);
              analogWrite(backwardright,0);
              analogWrite(forwardleft,0);
              analogWrite(forwardright,0);}
      
      }

}
