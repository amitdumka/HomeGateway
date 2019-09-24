#include <TTP229.h>

/*---------------------------------------------------------------------
      ESP8266 - TTP229 - With INT Using GPIO9 and GPIO10
Programa: Netto Scaff for Kameda Corp.  |  Curitiba - Brazil
/---------------------------------------------------------------------*/
int     SCLPin = 10;  //GPIO10 - INPUT or OUTPUT
int     SDOPin = 9;   //GPIO9 - INPUT ONLY | OUTPUT -> WDG
int     Key=0; //  Key 1 to 16 (No Key=0 is optional)
boolean Touch=0;//1=On 0=Off
boolean In;
unsigned int DTA=0;
unsigned int DTB=0;
//---------------------------------------------------------------------
//    **** INT 16 KEY READ ***
//---------------------------------------------------------------------
void Int_Key(){
  
  digitalWrite(SCLPin,HIGH);
  detachInterrupt(digitalPinToInterrupt(SDOPin));//Stop Int
  Serial.println();
  Serial.println("Int Pino L->H");
  DTA = 0;
  Key=0;
  delayMicroseconds(93);
  digitalWrite(SDOPin, LOW);
  delayMicroseconds(10);
  pinMode(SDOPin , INPUT);
  //------------------------            
  for (int i = 0; i < 17; i++)//Read 17 Bits for Safe
  { digitalWrite(SCLPin, HIGH);
    delayMicroseconds(1);
    digitalWrite(SCLPin, LOW);
    delayMicroseconds(1);
    In=digitalRead(SDOPin);
    if(Key==0 && In==0){Key=i+1;}
    DTA |= In << i;
  }

  digitalWrite(SCLPin,HIGH);
  delayMicroseconds(2);
  //------------------------
  if(DTB!=DTA && DTA!=131071){
    DTB=DTA;
    //Serial.println(DTA,BIN);
    //Serial.println(DTA,HEX);
    //Serial.println(DTA,DEC);
    Serial.println(Key);
    Serial.println("Touch 1");
    Touch=1;
    }else{
    //Key=0;// Optional
    Serial.println("Touch 0");
    DTB=0;
    Touch=0;}
  attachInterrupt(digitalPinToInterrupt(SDOPin), Int_Key, RISING);//Restart Int for new Key
}
//---------------------------------------------------------------------
//    **** SETUP ***
//---------------------------------------------------------------------
void setup() {
  Serial.begin(115200);
  pinMode(SDOPin,INPUT_PULLUP);
  pinMode(SCLPin,OUTPUT);//
  digitalWrite(SDOPin,HIGH);
  digitalWrite(SCLPin,HIGH);
  attachInterrupt(digitalPinToInterrupt(SDOPin), Int_Key, RISING);
  Serial.println();
  Serial.println("Start Key 16");
}
//---------------------------------------------------------------------
//    **** LOOP ***
//---------------------------------------------------------------------
void loop() {
 yield();
 ESP.wdtFeed(); 
}


//
// Created by kiryanenko on 14.09.19.
//

//////////////////////////////////////////////////////////////////
// Connections
//
// Uno:   SDA <-> A4 (SDA)
//        SCL <-> A5 (SCL)
//
// Mega:  SDA <-> 20 (SDA)
//        SCL <-> 21 (SCL)
//
// Leo:   SDA <-> 2 (SDA)
//        SCL <-> 3 (SCL)
//
//////////////////////////////////////////////////////////////////


#include <Wire.h>
#include <TTP229.h>

TTP229 ttp229;

void setup_1()
{
    Wire.begin();
    Serial.begin(9600);
}

void loop_1()
{
    ttp229.readKeys();

    Serial.print("Key states: ");
    for (int i = 0; i < 16; ++i) {
        if (ttp229.isKeyPress(i)) {
            Serial.print("1 ");
        } else {
            Serial.print("0 ");
        }
    }

    int key = ttp229.getKey();
    Serial.print("Pressed key: ");
    Serial.print(key);

    Serial.print("   ");
    if (ttp229.isKeyDown(0)) {
        Serial.print("Key 0 is down");
    } else if (ttp229.isKeyUp(0)) {
        Serial.print("Key 0 is up");
    }

    Serial.println();
    delay(500);
}
