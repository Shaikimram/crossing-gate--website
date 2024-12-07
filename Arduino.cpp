#include<LiquidCrystal.h>
#include <RTClib.h>
#include <Wire.h>
RTC_DS3231 rtc;
LiquidCrystal lcd(2, 3, 4, 5, 6, 7);
char t[32];
int timer1;
int timer2;
int timeA;
int timeB;
int timeC;
int imran;
int sumanth;
int sairam;
float Time;
int min;
int sec;
int hour;
int flag1 = 0;
int flag2 = 0;

float distance = 5.0;
float time;

int ir_s1 = A0;
int ir_s2 = A1;

int buzzer = 13;

void setup(){
  Wire.begin();
  rtc.begin();
  rtc.adjust(DateTime(2023,03,22,12,48,00));
  //rtc.adjust(DateTime(2022, 10, 14, 5, 0, 0));
  pinMode(ir_s1, INPUT);
  pinMode(ir_s2, INPUT);
  pinMode(buzzer, OUTPUT);
  Serial.begin(9600);
  // DateTime now = rtc.now();
    
  lcd.begin(16,2);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print(" TECHNICAL ");
  lcd.setCursor(0,1);
  lcd.print("GUDACHARI");
  delay(2000);
  lcd.clear();
}




void loop() {
   DateTime now = rtc.now();
//  sprintf(t, "%02d:%02d:%02d %02d/%02d/%02d", now.hour(), now.minute(), now.second(), now.day(), now.month(), now.year());
  imran= now.hour();
   sumanth= now.minute();
   sairam=now.second();  
 // Serial.print(F("Date/Time: "));
  //Serial.println(t);
  delay(1000);
if(digitalRead (ir_s1) == LOW && flag1==0){timer1 = millis(); flag1=1;}

if(digitalRead (ir_s2) == LOW && flag2==0){timer2 = millis(); flag2=1;}

if (flag1==1 && flag2==1){
     if(timer1 > timer2){Time = timer1 - timer2;}
else if(timer2 > timer1){Time = timer2 - timer1;}
 Time=Time/1000;//convert millisecond to second
 time=(distance/Time);//v=d/t
 time=time*3600;//multiply by seconds per hr
 time=time/1000;//division by meters per Km
 //Serial.println(time);
 timeC=150/time;
 timeA=timeC/60;
 timeB =timeA/60;
 sec =  timeC+sairam;
 min = timeA+ sumanth;
 hour = timeB+ imran;
 while (sec>=60){
  sec-=60;
  min++;
 }
 while (min>60){
  min-=60;
  hour++;
 }
 

  //Serial.println("closing time");
  //Serial.print("hours:");
  Serial.print(hour );
  //delay(2000);
 //Serial.print(" minutes:");
  Serial.print(",");
  Serial.print( min);
   //delay(2000);
 //Serial.print(" seconds:");
 // Serial.println(sec);
   //delay(2000);


 
   }

if(time==0){ 
lcd.setCursor(0, 1); 
if(flag1==0 && flag2==0){lcd.print("No car  detected");}
                    else{lcd.print("Searching...    ");} 
}
else{
    lcd.clear(); 
    lcd.setCursor(0, 0); 
    lcd.print("Speed:");
    lcd.print(time,1);
    lcd.print("Km/Hr  ");
    lcd.setCursor(0, 1); 
  if(time > 50){lcd.print("  Over Speeding  "); digitalWrite(buzzer, HIGH);}
            else{lcd.print("  Normal Speed   "); }    
    delay(3000);
    digitalWrite(buzzer, LOW);
    time = 0;
    flag1 = 0;
    flag2 = 0;    
 }
}
