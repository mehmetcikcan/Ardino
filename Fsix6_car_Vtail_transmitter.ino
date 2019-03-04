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

  /*if (1480 < rc_values[RC_CH1] < 1520 and 1480 < rc_values[RC_CH2] < 1520) {
analogWrite(forwardleft,0);
analogWrite(backwardleft,0);
analogWrite(forwardright,0);
analogWrite(backwardright,0);

  }*/

if (rc_values[RC_CH2] > 1520){
    forwardrightpwm = map (rc_values[RC_CH2], 1500 , 1950, 0, 255);

    if (forwardrightpwm > 255){forwardrightpwm = 255;}
    else if (forwardrightpwm < 0){forwardrightpwm = 0;}

    analogWrite(forwardright,forwardrightpwm);
    analogWrite(backwardright,0);
}

else if (rc_values[RC_CH2] < 1480){
    backwardrightpwm = map (rc_values[RC_CH2], 1500 , 1100, 0, 255);

    if (backwardrightpwm > 255){backwardrightpwm = 255;}
    else if (backwardrightpwm < 0){backwardrightpwm = 0;}

    analogWrite(backwardright,backwardrightpwm);
    analogWrite(forwardright,0);
}

else {
    analogWrite(forwardright,0);
    analogWrite(backwardright,0);}

if (rc_values[RC_CH1] > 1520){
    forwardleftpwm = map (rc_values[RC_CH1], 1500 , 1950, 0, 255);

    if (forwardleftpwm > 255){forwardleftpwm = 255;}
    else if (forwardleftpwm < 0){forwardleftpwm = 0;}

    analogWrite(forwardleft,forwardleftpwm);
    analogWrite(backwardleft,0);
}

else if (rc_values[RC_CH1] < 1480){
    backwardleftpwm = map (rc_values[RC_CH1], 1500 , 1100, 0, 255);

    if (backwardleftpwm > 255){backwardleftpwm = 255;}
    else if (backwardleftpwm < 0){backwardleftpwm = 0;}

    analogWrite(backwardleft,backwardleftpwm);
    analogWrite(forwardleft,0);
}

else {
    analogWrite(forwardleft,0);
    analogWrite(backwardleft,0);
  }

}
