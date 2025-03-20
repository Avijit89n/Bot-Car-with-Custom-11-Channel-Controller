#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

#define joy1 A0
#define joy2 A1
int joy1_sw = 2;
int joy2_sw = 3;

int danger_led1 = 4; 
int danger_led2 = 5; 

struct values{
  int left_right_val = 0;
  int forward_backward_val = 0;
  int jbtn1 = 1;
  int jbtn2 = 1;
};

RF24 radio(7, 8);
const byte address[6] = "IETE1";

void setup() {
  Serial.begin(9600);
  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_HIGH);
  radio.stopListening();

  pinMode(joy1, INPUT);
  pinMode(joy2, INPUT);
  pinMode(joy1_sw, INPUT);
  pinMode(joy2_sw, INPUT);

  pinMode(danger_led1, OUTPUT);
  pinMode(danger_led2, OUTPUT);

  digitalWrite(joy1_sw, HIGH);
  digitalWrite(joy2_sw, HIGH);
}

struct values controller_data;

void loop() {
  controller_data.left_right_val = analogRead(joy1);
  controller_data.forward_backward_val = analogRead(joy2);
  controller_data.jbtn1 = digitalRead(joy1_sw);
  controller_data.jbtn2 = digitalRead(joy2_sw);
  
  Serial.print("left-right: "); 
  Serial.print(controller_data.left_right_val);
  Serial.print("  forword backword: ");
  Serial.print(controller_data.forward_backward_val);
  Serial.print("  sw1: ");
  Serial.print(controller_data.jbtn1);
  Serial.print("  sw2: ");
  Serial.print(controller_data.jbtn2);
  Serial.println();

  if(controller_data.jbtn1 == 0) digitalWrite(danger_led1, HIGH);
  else digitalWrite(danger_led1, LOW);

  if(controller_data.jbtn2 == 0) digitalWrite(danger_led2, HIGH);
  else digitalWrite(danger_led2, LOW);

  radio.write(&controller_data, sizeof(controller_data));

}
