#define bts1_l_rpm 5
#define bts1_r_rpm 6
#define bts2_l_rpm 9
#define bts2_r_rpm 10

int led1 = 12;
int led2 = 13;

struct reciverdata {
  int forward_data = 0;
  int backward_data = 0;
  int left_data = 0;
  int right_data = 0;
  int btn_st1 = 1;
  int btn_st2 = 1;
};

void forward(int fd){
  analogWrite(bts1_l_rpm, fd); 
  analogWrite(bts1_r_rpm, 0);

  analogWrite(bts2_l_rpm, fd); 
  analogWrite(bts2_r_rpm, 0);
}

void backward(int bk){
  analogWrite(bts1_l_rpm, 0); 
  analogWrite(bts1_r_rpm, bk);

  analogWrite(bts2_l_rpm, 0); 
  analogWrite(bts2_r_rpm, bk);
}

void left(int lf){
  analogWrite(bts1_l_rpm, 0); 
  analogWrite(bts1_r_rpm, lf);

  analogWrite(bts2_l_rpm, lf); 
  analogWrite(bts2_r_rpm, 0);
}

void right(int rg){
  analogWrite(bts1_l_rpm, rg); 
  analogWrite(bts1_r_rpm, 0);

  analogWrite(bts2_l_rpm, 0); 
  analogWrite(bts2_r_rpm, rg);
}

void forward_left(int fd, int lf, int btn1, int btn2){
  int max1 = 255;
  int max2 = 255;
  if(btn1 == 0) max1 = 180;
  else max1 = 255;
  if(btn2 == 0) max2 = 180;
  else max2 = 255;
  int normal_val = map(fd+lf, 0, max1+max2, 0, (max1+max2)/2);
  analogWrite(bts1_l_rpm, 0); 
  analogWrite(bts1_r_rpm, 0);

  analogWrite(bts2_l_rpm, normal_val); 
  analogWrite(bts2_r_rpm, 0);
}

void backward_left(int bk, int lf, int btn1, int btn2){
  int max1 = 255;
  int max2 = 255;
  if(btn1 == 0) max1 = 180;
  else max1 = 255;
  if(btn2 == 0) max2 = 180;
  else max2 = 255;
  int normal_val = map(bk+lf, 0, max1+max2, 0, (max1+max2)/2);
  analogWrite(bts1_l_rpm, 0); 
  analogWrite(bts1_r_rpm, 0);

  analogWrite(bts2_l_rpm, 0); 
  analogWrite(bts2_r_rpm, normal_val);
}

void forward_right(int fd, int rg, int btn1, int btn2){
  int max1 = 255;
  int max2 = 255;
  if(btn1 == 0) max1 = 180;
  else max1 = 255;
  if(btn2 == 0) max2 = 180;
  else max2 = 255;
  int normal_val = map(fd+rg, 0, max1+max2, 0, (max1+max2)/2);
  analogWrite(bts1_l_rpm, normal_val); 
  analogWrite(bts1_r_rpm, 0);

  analogWrite(bts2_l_rpm, 0); 
  analogWrite(bts2_r_rpm, 0);
}

void backward_right(int bk, int rg, int btn1, int btn2){
  int max1 = 255;
  int max2 = 255;
  if(btn1 == 0) max1 = 180;
  else max1 = 255;
  if(btn2 == 0) max2 = 180;
  else max2 = 255;
  int normal_val = map(bk+rg, 0, max1+max2, 0, (max1+max2)/2);
  analogWrite(bts1_l_rpm, 0); 
  analogWrite(bts1_r_rpm, normal_val);

  analogWrite(bts2_l_rpm, 0); 
  analogWrite(bts2_r_rpm, 0);
}

void stop(){
  analogWrite(bts1_l_rpm, 0); 
  analogWrite(bts1_r_rpm, 0);

  analogWrite(bts2_l_rpm, 0); 
  analogWrite(bts2_r_rpm, 0);
}


void setup() {
  Serial.begin(115200);

  pinMode(bts1_l_rpm, OUTPUT);
  pinMode(bts1_r_rpm, OUTPUT);
  pinMode(bts2_l_rpm, OUTPUT);
  pinMode(bts2_r_rpm, OUTPUT);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
}

unsigned long lastPacketTime = 0; 
const unsigned long packetTimeout = 100;

void loop() {
  static bool isReceiving = false;
  static uint8_t index = 0;
  static uint8_t buffer[sizeof(reciverdata)];
  struct reciverdata value_recived;

  while (Serial.available() > 0) {
    digitalWrite(led1, HIGH);
    digitalWrite(led2, LOW);
    char incomingByte = Serial.read();

    if (incomingByte == '<') {
      isReceiving = true;
      index = 0;
    } else if (incomingByte == '>') {
      if (isReceiving && index == sizeof(reciverdata)) {
        memcpy(&value_recived, buffer, sizeof(reciverdata));

        Serial.print("fd: ");
        Serial.print(value_recived.forward_data);
        Serial.print("  bk: ");
        Serial.print(value_recived.backward_data);
        Serial.print("  lf: ");
        Serial.print(value_recived.left_data);
        Serial.print("  rg: ");
        Serial.print(value_recived.right_data);
        Serial.println();

        if(value_recived.forward_data > 0 && value_recived.backward_data == 0 && value_recived.left_data == 0 && value_recived.right_data == 0) forward(value_recived.forward_data);
        else if(value_recived.forward_data == 0 && value_recived.backward_data > 0 && value_recived.left_data == 0 && value_recived.right_data == 0) backward(value_recived.backward_data);
        else if(value_recived.forward_data == 0 && value_recived.backward_data == 0 && value_recived.left_data > 0 && value_recived.right_data == 0) left(value_recived.left_data);
        else if(value_recived.forward_data == 0 && value_recived.backward_data == 0 && value_recived.left_data == 0 && value_recived.right_data > 0) right(value_recived.right_data);

        else if(value_recived.forward_data > 0 && value_recived.backward_data == 0 && value_recived.left_data > 0 && value_recived.right_data == 0) forward_left(value_recived.forward_data, value_recived.left_data, value_recived.btn_st1, value_recived.btn_st2);
        else if(value_recived.forward_data == 0 && value_recived.backward_data > 0 && value_recived.left_data > 0 && value_recived.right_data == 0) backward_left(value_recived.backward_data, value_recived.left_data, value_recived.btn_st1, value_recived.btn_st2);
        else if(value_recived.forward_data > 0 && value_recived.backward_data == 0 && value_recived.left_data == 0 && value_recived.right_data > 0) forward_right(value_recived.forward_data, value_recived.right_data, value_recived.btn_st1, value_recived.btn_st2);
        else if(value_recived.forward_data == 0 && value_recived.backward_data > 0 && value_recived.left_data == 0 && value_recived.right_data > 0) backward_right(value_recived.backward_data, value_recived.right_data, value_recived.btn_st1, value_recived.btn_st2);
        else if(value_recived.forward_data == 0 && value_recived.backward_data == 0 && value_recived.left_data == 0 && value_recived.right_data == 0) stop();
        lastPacketTime = millis(); 
      }
      isReceiving = false;
    } else if (isReceiving) {
      if (index < sizeof(reciverdata)) {
        buffer[index++] = incomingByte;
      }
    }
  }

  if (millis() - lastPacketTime > packetTimeout) {
    stop();
    digitalWrite(led1, LOW);
    digitalWrite(led2, HIGH);
  }
}
