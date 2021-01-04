#include <ProTrinketGamepad.h>

#define CLOCK 1
#define LATCH 0

#define DATA1 12
#define DATA2 14
#define DATA3 3
#define DATA4 4

#define LED1 10
#define LED2 11
#define LED3 5
#define LED4 6
#define ONLED 9


uint8_t buttons[] = { 1, 3, 7, 8, 9, 10, 11, 12, 2, 4, 5, 6, 13, 14, 15, 16 };
uint16_t buttonMap1;
uint16_t buttonMap2;
uint16_t buttonMap3;
uint16_t buttonMap4;
bool controller1Connected;
bool controller2Connected;
bool controller3Connected;
bool controller4Connected;
uint16_t controller1Data;
uint16_t controller2Data;
uint16_t controller3Data;
uint16_t controller4Data;

void setup() {
  // put your setup code here, to run once:
  pinMode(CLOCK, OUTPUT);
  pinMode(LATCH, OUTPUT);

  pinMode(DATA1, INPUT);
  pinMode(DATA2, INPUT);
  pinMode(DATA3, INPUT);
  pinMode(DATA4, INPUT);

  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  pinMode(LED4, OUTPUT);
  pinMode(ONLED, OUTPUT);


  digitalWrite(CLOCK, HIGH);
  digitalWrite(LATCH, LOW);

  digitalWrite(ONLED, HIGH);


  TrinketGamepad.begin();
}

void loop()
{
  // put your main code here, to run repeatedly:
  delay(16.67);
  analogWrite(LED1, 0);
  analogWrite(LED2, 0);
  analogWrite(LED3, 0);
  analogWrite(LED4, 0);


  CheckControllers();
  ReadControllers();
  if (controller1Connected)
  {
    MapButtons(controller1Data, buttonMap1);
  }
  else
    buttonMap1 = 0;

  if (controller2Connected)
  {
    MapButtons(controller2Data, buttonMap2);
  }
  else
    buttonMap2 = 0;
    
  if (controller3Connected)
  {
    MapButtons(controller3Data, buttonMap3);
  }
  else
    buttonMap3 = 0;
    
  if (controller4Connected)
  {
    MapButtons(controller4Data, buttonMap4);
  }
  else
    buttonMap4 = 0;
    
  if (buttonMap1)
    analogWrite(LED1, 255);

  if (buttonMap2)
    analogWrite(LED2, 255);

  if (buttonMap3)
    analogWrite(LED3, 255);

  if (buttonMap4)
    analogWrite(LED4, 255);

  TrinketGamepad.move(buttonMap1, buttonMap2, buttonMap3, buttonMap4);
}

void CheckControllers()
{
  if (digitalRead(DATA1))
    controller1Connected = false;
  else
  {
    controller1Connected = true;
    analogWrite(LED1, 180);
  }

  if (digitalRead(DATA2))
    controller2Connected = false;
  else
  {
    controller2Connected = true;
    analogWrite(LED2, 180);
  }

  if (digitalRead(DATA3))
    controller3Connected = false;
  else
  {
    controller3Connected = true;
    analogWrite(LED3, 180);
  }

  if (digitalRead(DATA4))
    controller4Connected = false;
  else
  {
    controller4Connected = true;
    analogWrite(LED4, 180);
  }

}

void MapButtons(uint16_t controllerData, uint16_t& buttonMap)
{
  for (int i = 0; i < 16; i++)
  {
    bool b = controllerData & (0x8000 >> i);
    bitWrite(buttonMap, buttons[i] - 1, b);
  }
}

void ReadControllers()
{
  controller1Data = 0x00;
  controller2Data = 0x00;
  controller3Data = 0x00;
  controller4Data = 0x00;
  digitalWrite(LATCH, HIGH);
  delayMicroseconds(12);
  digitalWrite(LATCH, LOW);

  for (int i = 0; i < 16; i++)
  {
    delayMicroseconds(6);
    digitalWrite(CLOCK, LOW);
    controller1Data = (controller1Data << 1) | (digitalRead(DATA1));
    controller2Data = (controller2Data << 1) | (digitalRead(DATA2));
    controller3Data = (controller3Data << 1) | (digitalRead(DATA3));
    controller4Data = (controller4Data << 1) | (digitalRead(DATA4));

    delayMicroseconds(6);
    digitalWrite(CLOCK, HIGH);
  }
  controller1Data = ~controller1Data;
  controller2Data = ~controller2Data;
  controller3Data = ~controller3Data;
  controller4Data = ~controller4Data;
}
