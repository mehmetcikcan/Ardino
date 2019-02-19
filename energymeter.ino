float volt = 0;
float akim = 0;
float energy = 0;
float kapasite = 0;
int buzzer = 4;
int start = 5;
int yuzde = 0;
int lock = 0;

int serInString[7]={60, 60, 60, 60, 60, 60, 60};
int password[7]={101, 0, 6, 1, 255, 255, 255};
int serInIndx  = 0;
int serOutIndx = 0; 
int sb;

void setup() {
pinMode(buzzer,OUTPUT);
pinMode(start,OUTPUT);
digitalWrite(start,HIGH);
Serial.begin(9600);

Serial.print("t4.txt=");
Serial.print("\"");
Serial.print("BASLATMA BEKLENIYOR");
Serial.print("\"");
Serial.write(0xff);
Serial.write(0xff);
Serial.write(0xff);

while (1)
{
while (Serial.available()){ 
  sb = Serial.read();             
  serInString[serInIndx] = sb;
  serInIndx++;
}

if (serInIndx>=7){
  for(serOutIndx=0; serOutIndx < serInIndx; serOutIndx++) {
    if (serInString[serOutIndx]==password[serOutIndx]){lock++; }
      Serial.println(serInString[serOutIndx]);
      Serial.println(lock);
      }
  serInIndx=0;
}

if (lock==7){
  volt=analogRead(A7);
  volt= (volt/1023)*4.90;
  if (volt>1.0){
        digitalWrite(start,LOW); 
        Serial.print("t4.txt=");
        Serial.print("\"");
        Serial.print("DESARJ BASLADI");
        Serial.print("\"");
        Serial.write(0xff);
        Serial.write(0xff);
        Serial.write(0xff);
        break;}
   
  else {
        Serial.print("t4.txt=");
        Serial.print("\"");
        Serial.print("PIL YOK");
        Serial.print("\"");
        Serial.write(0xff);
        Serial.write(0xff);
        Serial.write(0xff);
        lock==0;          }
      }
}
}

void loop() {
volt=analogRead(A7);

yuzde = map (volt, 895, 640, 100, 0);
if (yuzde>100){yuzde=100;}
else if (yuzde<=0){yuzde=0;}

volt= (volt/1023)*4.90;

akim=volt/4.8;

energy=energy+akim;
kapasite=energy/36;


Serial.print("j0.val=");
Serial.print(yuzde);
Serial.write(0xff);
Serial.write(0xff);
Serial.write(0xff);

Serial.print("t0.txt=");
Serial.print("\"");
Serial.print(volt);
Serial.print(" V");
Serial.print("\"");
Serial.write(0xff);
Serial.write(0xff);
Serial.write(0xff);

Serial.print("t1.txt=");
Serial.print("\"");
Serial.print(akim);
Serial.print(" A");
Serial.print("\"");
Serial.write(0xff);
Serial.write(0xff);
Serial.write(0xff);

Serial.print("t2.txt=");
Serial.print("\"");
Serial.print(kapasite);
Serial.print(" mAH");
Serial.print("\"");
Serial.write(0xff);
Serial.write(0xff);
Serial.write(0xff);

Serial.print("t3.txt=");
Serial.print("\"");
Serial.print(" % ");
Serial.print(yuzde);
Serial.print("\"");
Serial.write(0xff);
Serial.write(0xff);
Serial.write(0xff);

if (volt <= 3.0) {
akim=0;
Serial.print("t1.txt=");
Serial.print("\"");
Serial.print(akim);
Serial.print(" A");
Serial.print("\"");
Serial.write(0xff);
Serial.write(0xff);
Serial.write(0xff);

for (int i=0; i<10; i++){
digitalWrite(start,HIGH);
digitalWrite(buzzer,1);
delay(300);
digitalWrite(buzzer,0);
delay(300);}

while(1){
volt=analogRead(A7);
yuzde = map (volt, 895, 640, 100, 0);
if (yuzde>100){yuzde=100;}
else if (yuzde<=0){yuzde=0;}
volt= (volt/1023)*4.90;



Serial.print("j0.val=");
Serial.print(yuzde);
Serial.write(0xff);
Serial.write(0xff);
Serial.write(0xff);

Serial.print("t0.txt=");
Serial.print("\"");
Serial.print(volt);
Serial.print(" V");
Serial.print("\"");
Serial.write(0xff);
Serial.write(0xff);
Serial.write(0xff);

Serial.print("t3.txt=");
Serial.print("\"");
Serial.print(" % ");
Serial.print(yuzde);
Serial.print("\"");
Serial.write(0xff);
Serial.write(0xff);
Serial.write(0xff);

Serial.print("t4.txt=");
Serial.print("\"");
Serial.print("DESARJ TAMAM");
Serial.print("\"");
Serial.write(0xff);
Serial.write(0xff);
Serial.write(0xff);
}}
delay(100);

}
