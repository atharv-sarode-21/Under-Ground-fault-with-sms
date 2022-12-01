  ##Under ground fault detection code##

#include <SoftwareSerial.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>



LiquidCrystal_I2C lcd(0x27,20,4);
SoftwareSerial mySerial(7, 8);

#define sensor A0  

#define relay1 10
#define relay2 9
#define relay3 13

#define buzzer 13  

int read_ADC;
int distance;

byte symbol[8] = {
        B00000,
        B00100,
        B00100,
        B00100,
        B11111,
        B01110,
        B00100,
        B00000};

void setup() {

  
  mySerial.begin(9600);   // Setting the baud rate of GSM Module  
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
  delay(100);

  
pinMode(sensor,INPUT); 
pinMode(relay1, OUTPUT);
pinMode(relay2, OUTPUT);
pinMode(relay3, OUTPUT);



lcd.createChar(1, symbol);
    
lcd.begin(16, 2);
lcd.clear();
lcd.setCursor(0, 0); // set the cursor to column 0, line 2
lcd.print("Welcome to Cable");
lcd.setCursor(0, 1); // set the cursor to column 0, line 2
lcd.print("Fault  Detection");
delay(2000);
lcd.clear();
}

void loop(){
lcd.setCursor(1,0);
lcd.print("R");
lcd.write(1);  

lcd.setCursor(7,0);
lcd.print("Y");
lcd.write(1); 

lcd.setCursor(13,0);
lcd.print("B");
lcd.write(1); 
        
digitalWrite(relay1,HIGH);
digitalWrite(relay2,LOW);
digitalWrite(relay3,LOW);  
delay(500);

data();
lcd.setCursor(0,1);
if(distance>0){lcd.print(distance); lcd.print("KM  ");
  sms();}
else{lcd.print(" NF ");}

digitalWrite(relay1,LOW);
digitalWrite(relay2,HIGH);
digitalWrite(relay3,LOW);  
delay(500);

data();

lcd.setCursor(6,1);
if(distance>0){lcd.print(distance); lcd.print("KM  ");
sms();}
else{lcd.print(" NF ");}

digitalWrite(relay1,LOW);
digitalWrite(relay2,LOW);
digitalWrite(relay3,HIGH);  
delay(500);

data();

lcd.setCursor(12,1);
if(distance>0){lcd.print(distance); 
lcd.print("KM  ");
sms();
}
else{lcd.print(" NF ");}

}


void data(){
read_ADC = analogRead(sensor);  
distance = read_ADC/100;

if(distance>9)distance = 0;

}

void sms(){
  
      mySerial.println("AT+CMGF=1");   
     delay(1000);  
     mySerial.println("AT+CMGS=\"+919834996915\"\r"); 
     delay(1000);
     mySerial.println("Fault detected");
     delay(100);
     mySerial.println((char)26); 
      delay(1000); }
