#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

#define default_bck_frd 509
#define default_lft_rig 518

RF24 radio(7, 8);
const byte address[6] = "IETE1";

struct values{
  int left_right_val = 0;
  int forward_backward_val = 0;
  int jbtn1 = 1;
  int jbtn2 = 1;
};

struct reciverdata {
  int forward_data = 0;
  int backward_data = 0;
  int left_data = 0;
  int right_data = 0;
  int btn_st1 = 1;
  int btn_st2 = 1;
};

void setup() {
  Serial.begin(115200);
  radio.begin();
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_HIGH);
  radio.startListening();
  pinMode(3, OUTPUT);
}

struct values controller_data;
struct reciverdata reciver_data;
int max_speed_j1 = 255;
int max_speed_j2 = 255;

void loop() {
  if(radio.available()){
    radio.read(&controller_data, sizeof(controller_data));

    if(controller_data.jbtn2 == 1) max_speed_j1 = 180;
    else max_speed_j1 = 255;
    if(controller_data.jbtn1 == 1) max_speed_j2 = 180;
    else max_speed_j2 = 255;
    
    reciver_data.forward_data = map(controller_data.forward_backward_val, default_bck_frd+1, 1023, 0, max_speed_j1);
    reciver_data.backward_data = map(controller_data.forward_backward_val, default_bck_frd-1, 0, 0, max_speed_j1);
    reciver_data.left_data = map(controller_data.left_right_val, default_bck_frd-1, 0, 0, max_speed_j2);
    reciver_data.right_data = map(controller_data.left_right_val, default_lft_rig+1, 1023, 0, max_speed_j2);

    if(reciver_data.forward_data < 0) reciver_data.forward_data = 0;
    if(reciver_data.backward_data < 0) reciver_data.backward_data = 0;
    if(reciver_data.left_data < 0) reciver_data.left_data = 0;
    if(reciver_data.right_data < 0) reciver_data.right_data = 0;

    reciver_data.btn_st1 = controller_data.jbtn2;
    reciver_data.btn_st2 = controller_data.jbtn1;

    Serial.print("forward data: ");
    Serial.print(reciver_data.forward_data);
    Serial.print("  backward data: ");
    Serial.print(reciver_data.backward_data);
    Serial.print("  left data: ");
    Serial.print(reciver_data.left_data);
    Serial.print("  right data: ");
    Serial.print(reciver_data.right_data);
    Serial.print("  btn1: ");
    Serial.print(reciver_data.btn_st1);
    Serial.print("  btn2: ");
    Serial.print(reciver_data.btn_st2);

    Serial.println();

    Serial.write('<');
    Serial.write((uint8_t *)&reciver_data, sizeof(reciver_data)); 
    Serial.write('>');
  }
} 
