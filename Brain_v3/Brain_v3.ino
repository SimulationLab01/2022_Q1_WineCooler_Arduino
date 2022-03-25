#include <Timer.h>
#include <SoftwareSerial.h>
#include "Adafruit_VL53L1X.h"
#define IRQ_PIN 2
#define XSHUT_PIN 3

SoftwareSerial BTSerial(A2, A1); // RX | TX
Timer Timer1;
Adafruit_VL53L1X vl53 = Adafruit_VL53L1X(XSHUT_PIN, IRQ_PIN);

int closeLimit = 130;
int closeSetTime = 5000;
int TerminalA = 0, TerminalB = 0;
int PreviousA = 0, PreviousB = 0;
boolean TerminalStateA = false;
boolean TerminalStateB = false;
int LedLeft = 11;
int LedRight = 12;
int EncoderCont = 0;
int TimerCont = 0;
int StateChangeOfTerminalA = 0;
int StateChangeOfTerminalB = 0;
int encoderA[5] = {1, 0, 0, 1, 1};
int encoderB[5] = {1, 1, 0, 0, 1};
int EncoderBtn = 4;
int TerminalAPIN = 5;
int TerminalBPIN = 6;
int BtnPlus = 7;
int BtnMinus = 8;
int presstime = 0;
int distance = 0;
int closeTime = 0;
int int_reg1 = 0, int_reg2 = 0, int_reg3 = 0, int_reg4 = 0, int_reg5 = 0;
bool isClosed = false;
bool isOpen = true;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  BTSerial.begin(9600);
  pinMode(EncoderBtn, INPUT);
  pinMode(TerminalAPIN, INPUT);
  pinMode(TerminalBPIN, INPUT);
  pinMode(BtnPlus, INPUT);
  pinMode(BtnMinus, INPUT);
  pinMode(LedLeft, OUTPUT);
  pinMode(LedRight, OUTPUT);
  Timer1.every(1, TimerConter);

  if (! vl53.begin(0x29, &Wire)) {
    Serial.print(F("Error on init of VL sensor: "));
    Serial.println(vl53.vl_status);
    while (1)       delay(10);
  }

  if (! vl53.startRanging()) {
    Serial.print(F("Couldn't start ranging: "));
    Serial.println(vl53.vl_status);
    while (1)       delay(10);
  }
  // Valid timing budgets: 15, 20, 33, 50, 100, 200 and 500ms!
  vl53.setTimingBudget(50);

}
bool isA = false;
bool isB = false;
int plus = 0;
int minus = 0;
bool isEnable = true;
void loop() {
  //  Serial.print(TimerCont);
  //  Serial.print("  "  );
  //Serial.print(closeTime);
  //Serial.print("  "  );
  //Serial.println((TimerCont - closeTime));
  if (vl53.dataReady()) {

    distance = vl53.distance();
    //    Serial.print(F("Distance: "));
    //    Serial.print(distance);
    //    Serial.println(" mm");

    vl53.clearInterrupt();
    if (distance > closeLimit && isClosed == true)
    {
      closeTime = TimerCont;
      isClosed = false;
    }
    else if (distance <= closeLimit && isClosed == false)
    {
      closeTime = TimerCont;
      isClosed = true;
    }
  }
  if (BTSerial.available())
  {
    char c =  BTSerial.read();
    Serial.print(c);
    Serial.println("-re");
    if (c == 'c') // 左燈亮
    {
      digitalWrite(LedLeft, HIGH);
    }
    else if (c == 'd') // 左燈暗
    {
      digitalWrite(LedLeft, LOW);
    }
    else if (c == 'e') // 右燈亮
    {
      digitalWrite(LedRight, HIGH);
    }
    else if (c == 'f') // 右燈暗
    {
      digitalWrite(LedRight, LOW);
    }
    else if (c == 'h') // enable
    {
      Serial.println("enable");
      isEnable = true;
    }
    else if (c == 'g') // disable
    {
      Serial.println("Disable");
      isEnable = false;
    }


  }
  //  digitalWrite(11,HIGH);
  //  digitalWrite(12,LOW);
  //  delay(1000);
  //  digitalWrite(11,LOW);
  //  digitalWrite(12,HIGH);
  //  delay(1000);
  // put your main code here, to run repeatedly:
  Timer1.update();
  TerminalA = digitalRead(TerminalAPIN);
  TerminalB = digitalRead(TerminalBPIN);
  if (TerminalA == TerminalB)
  {
    PreviousA = TerminalA;
    PreviousB = TerminalB;
    isA = true;
  }
  else
  {
    if (isA == true)
    {
      if (PreviousA != TerminalA )
      {
        EncoderCont++;
        minus++;
        if (minus >= 5)
        {
          Serial.print("p");
          BTSerial.print("p");
          plus = 0;
          minus = 0;
        }
      }
      else if (PreviousB != TerminalB)
      {
        EncoderCont--;
        plus++;
        if (plus >= 5)
        {
          Serial.print("m");
          BTSerial.print("m");
          minus = 0;
          plus = 0;
        }
      }
      isA = false;
    }
    //Serial.println(EncoderCont);
  }

  if (digitalRead(EncoderBtn) == HIGH && int_reg1 == 0)
  {
    presstime = TimerCont;
    int_reg1 = 1;
  }
  else if (digitalRead(EncoderBtn) == LOW && int_reg1 == 1)
  {
    if (TimerCont - presstime > 1000)
    {

    }
    else
    {
      Serial.println("s");
      BTSerial.print("s");
      presstime = 0;
      plus = 0;
      minus = 0;
    }
    delay(300);
    int_reg1 = 0;
  }
  if (digitalRead(BtnPlus) == HIGH && int_reg2 == 0)
  {
    int_reg2 = 1;
  }
  else if (digitalRead(BtnPlus) == LOW && int_reg2 == 1)
  {
    int_reg2 = 0;
    Serial.println("b");
    BTSerial.print("b");
    delay(300);
  }

  if (digitalRead(BtnMinus) == HIGH && int_reg3 == 0)
  {
    int_reg3 = 1;
  }
  else if (digitalRead(BtnMinus) == LOW && int_reg3 == 1)
  {
    int_reg3 = 0;
    Serial.println("a");
    BTSerial.print("a");
    delay(300);
  }
  if (isEnable == true)
  {
    //Serial.println("Enable");
    if (distance < closeLimit && isOpen == true && distance != 0)
    {
      //    Serial.println((TimerCont - closeTime));
      if (TimerCont - closeTime >= closeSetTime)
      {
        digitalWrite(LedLeft, LOW);
        digitalWrite(LedRight, LOW);
        Serial.println("x");
        BTSerial.print("x");
        isOpen = false;
        isClosed = false;
      }
    }
    else if (distance > closeLimit && isOpen == false && distance != 0)
    {
      digitalWrite(LedLeft, HIGH);
      digitalWrite(LedRight, HIGH);
      Serial.println("z");
      BTSerial.print("z");
      isOpen = true;
    }
  }
}
void TimerConter()
{
  TimerCont++;
  if (TimerCont - presstime > 1000 && presstime != 0)
  {
    Serial.println("l");
    BTSerial.print("l");
    presstime = 0;
    plus = 0;
    minus = 0;
  }
}
