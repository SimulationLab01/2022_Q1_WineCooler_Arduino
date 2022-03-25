#include <ArduinoBLE.h>
#include <Adafruit_NeoPixel.h>
#define NUM_LEDS 54
#define DATA_PIN 11

BLEService ledService("19B10010-E8F2-537E-4F6C-D104768A1214"); // create service

// create switch characteristic and allow remote device to read and write
BLECharacteristic ledCharacteristic("19B10011-E8F2-537E-4F6C-D104768A1214", BLERead | BLEWrite | BLENotify, 4);
// create button characteristic and allow remote device to get notifications


Adafruit_NeoPixel led_strip = Adafruit_NeoPixel(NUM_LEDS,
                              DATA_PIN,
                              NEO_GRB + NEO_KHZ800);
String PillowNum = "1";
int BurnPin1 = 12;
int BurnPin2 = A1;

int btn1 = 2, btn2 = 3 , btn3 = 4, btn4 = BurnPin1, btn5 = BurnPin2,
    btn6 = 7, btn7 = 8, btn8 = 9, btn9 = 10;
int int_reg1 = 0, int_reg2 = 0, int_reg3 = 0, int_reg4 = 0,
    int_reg5 = 0, int_reg6 = 0, int_reg7 = 0, int_reg8 = 0,
    int_reg9 = 0;
String sendData = "";
byte msg1[4] = {};
byte ack[1] = {0x41};
void setup() {
  Serial.begin(9600);


  led_strip.begin();
  led_strip.clear();
  pinMode(btn1, INPUT);
  pinMode(btn2, INPUT);
  pinMode(btn3, INPUT);
  pinMode(btn4, INPUT);
  pinMode(btn5, INPUT);
  pinMode(btn6, INPUT);
  pinMode(btn7, INPUT);
  pinMode(btn8, INPUT);
  pinMode(btn9, INPUT);

  // begin initialization
  if (!BLE.begin()) {
    Serial.println("starting BLE failed!");
    while (1);
  }

  // set the local name peripheral advertises
  BLE.setLocalName("Pillow02");
  // set the UUID for the service this peripheral advertises:
  BLE.setAdvertisedService(ledService);

  // add the characteristics to the service
  ledService.addCharacteristic(ledCharacteristic);

  // add the service
  BLE.addService(ledService);

  // start advertising
  BLE.advertise();

  for (int i = 0; i < NUM_LEDS; i++) {
    led_strip.setPixelColor(i, 0, 0 , 0);
  }
  led_strip.setBrightness(50);
  led_strip.show();
}

void loop() {
  // poll for BLE events
  BLE.poll();
  if (Serial.available())  {  }

  if (ledCharacteristic.written())
  {
    byte readbyte[2];
    ledCharacteristic.readValue(readbyte, 2);
    Serial.write(readbyte, 2);
    if (readbyte[0]  == 'z')
    {
      LEDAllOff();
      Serial.println("off");
    }
    else
    {
      if ((readbyte[0] & 0x01) == 0x01)
      {
        LEDOn(9);
      }
      for (int i = 1; i <= 8; i++)
      {
        if ((readbyte[1] & 0x01) == 0x01)
        {
          LEDOn(i);
        }
        readbyte[1]  = readbyte[1] >> 1;
      }
    }
    
  }
  if (digitalRead(btn1) == HIGH && int_reg1 == 0)
  {
    sendData = PillowNum + "1I";
    Serial.println(sendData);
    sendData.getBytes(msg1, 4);
    ledCharacteristic.writeValue(msg1, 4);
    int_reg1 = 1;
  }
  else if (digitalRead(btn1) == LOW && int_reg1 == 1)
  {
    sendData = PillowNum + "1O";
    Serial.println(sendData);
    sendData.getBytes(msg1, 4);
    ledCharacteristic.writeValue(msg1, 4);
    LEDOff(1);
    int_reg1 = 0;
    delay(300);
  }
  if (digitalRead(btn2) == HIGH && int_reg2 == 0)
  {
    sendData = PillowNum + "2I";
    Serial.println(sendData);
    sendData.getBytes(msg1, 4);
    ledCharacteristic.writeValue(msg1, 4);
    int_reg2 = 1;
  }
  else if (digitalRead(btn2) == LOW && int_reg2 == 1)
  {
    sendData = PillowNum + "2O";
    Serial.println(sendData);
    sendData.getBytes(msg1, 4);
    ledCharacteristic.writeValue(msg1, 4);
    LEDOff(2);
    int_reg2 = 0;
    delay(300);
  }
  if (digitalRead(btn3) == HIGH && int_reg3 == 0)
  {
    sendData = PillowNum + "3I";
    Serial.println(sendData);
    sendData.getBytes(msg1, 4);
    ledCharacteristic.writeValue(msg1, 4);
    int_reg3 = 1;
  }
  else if (digitalRead(btn3) == LOW && int_reg3 == 1)
  {
    sendData = PillowNum + "3O";
    Serial.println(sendData);
    sendData.getBytes(msg1, 4);
    ledCharacteristic.writeValue(msg1, 4);
    LEDOff(3);
    int_reg3 = 0;
    delay(300);
  }
  if (digitalRead(btn4) == HIGH && int_reg4 == 0)
  {
    sendData = PillowNum + "4I";
    Serial.println(sendData);
    sendData.getBytes(msg1, 4);
    ledCharacteristic.writeValue(msg1, 4);
    int_reg4 = 1;
  }
  else if (digitalRead(btn4) == LOW && int_reg4 == 1)
  {
    sendData = PillowNum + "4O";
    Serial.println(sendData);
    sendData.getBytes(msg1, 4);
    ledCharacteristic.writeValue(msg1, 4);
    LEDOff(4);
    int_reg4 = 0;
    delay(300);
  }
  if (digitalRead(btn5) == HIGH && int_reg5 == 0)
  {
    sendData = PillowNum + "5I";
    Serial.println(sendData);
    sendData.getBytes(msg1, 4);
    ledCharacteristic.writeValue(msg1, 4);
    int_reg5 = 1;
  }
  else if (digitalRead(btn5) == LOW && int_reg5 == 1)
  {
    sendData = PillowNum + "5O";
    Serial.println(sendData);
    sendData.getBytes(msg1, 4);
    ledCharacteristic.writeValue(msg1, 4);
    LEDOff(5);
    int_reg5 = 0;
    delay(300);
  }
  if (digitalRead(btn6) == HIGH && int_reg6 == 0)
  {
    sendData = PillowNum + "6I";
    Serial.println(sendData);
    sendData.getBytes(msg1, 4);
    ledCharacteristic.writeValue(msg1, 4);
    int_reg6 = 1;
  }
  else if (digitalRead(btn6) == LOW && int_reg6 == 1)
  {
    sendData = PillowNum + "6O";
    Serial.println(sendData);
    sendData.getBytes(msg1, 4);
    ledCharacteristic.writeValue(msg1, 4);
    LEDOff(6);
    int_reg6 = 0;
    delay(300);
  }
  if (digitalRead(btn7) == HIGH && int_reg7 == 0)
  {
    sendData = PillowNum + "7I";
    Serial.println(sendData);
    sendData.getBytes(msg1, 4);
    ledCharacteristic.writeValue(msg1, 4);
    int_reg7 = 1;
  }
  else if (digitalRead(btn7) == LOW && int_reg7 == 1)
  {
    sendData = PillowNum + "7O";
    Serial.println(sendData);
    sendData.getBytes(msg1, 4);
    ledCharacteristic.writeValue(msg1, 4);
    LEDOff(7);
    int_reg7 = 0;
    delay(300);
  }
  if (digitalRead(btn8) == HIGH && int_reg8 == 0)
  {
    sendData = PillowNum + "8I";
    Serial.println(sendData);
    sendData.getBytes(msg1, 4);
    ledCharacteristic.writeValue(msg1, 4);
    int_reg8 = 1;
  }
  else if (digitalRead(btn8) == LOW && int_reg8 == 1)
  {
    sendData = PillowNum + "8O";
    Serial.println(sendData);
    sendData.getBytes(msg1, 4);
    ledCharacteristic.writeValue(msg1, 4);
    LEDOff(8);
    int_reg8 = 0;
    delay(300);
  }
  if (digitalRead(btn9) == HIGH && int_reg9 == 0)
  {
    sendData = PillowNum + "9I";
    Serial.println(sendData);
    sendData.getBytes(msg1, 4);
    ledCharacteristic.writeValue(msg1, 4);
    int_reg9 = 1;
  }
  else if (digitalRead(btn9) == LOW && int_reg9 == 1)
  {
    sendData = PillowNum + "9O";
    Serial.println(sendData);
    sendData.getBytes(msg1, 4);
    ledCharacteristic.writeValue(msg1, 4);
    LEDOff(9);
    int_reg9 = 0;
    //  ledCharacteristic.writeValue(0x09);
    delay(300);
  }


}
void LEDOn(int n) {
  for (int i = 0; i < NUM_LEDS; i++) {
    if (i >= (6 * (n - 1)) && i <= ((6 * n) - 1))
      led_strip.setPixelColor(i, 255, 255 , 255);
  }
  led_strip.setBrightness(50);
  led_strip.show();
}
void LEDOff(int n) {
  for (int i = 0; i < NUM_LEDS; i++) {
    if (i >= (6 * (n - 1)) && i <= ((6 * n) - 1))
      led_strip.setPixelColor(i, 0, 0 , 0);
  }
  led_strip.setBrightness(50);
  led_strip.show();
}
void LEDAllOff() {
  for (int i = 0; i < NUM_LEDS; i++) {
    led_strip.setPixelColor(i, 0, 0 , 0);
  }
  led_strip.setBrightness(50);
  led_strip.show();
}
