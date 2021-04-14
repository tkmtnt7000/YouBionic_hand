#include <PCA9685.h>     //PCA9685用ヘッダーファイル
PCA9685 pwm = PCA9685(0x40);    //PCA9685のアドレス指定（アドレスジャンパ未接続時）

#define SERVOMIN 150            //最小パルス幅 (GWS Micro2BBMG)
#define SERVOMAX 500            //最大パルス幅 (GWS Micro2BBMG)
#define LITTLE_FINGER_CH 0
#define RING_FINGER_CH 3
#define MIDDLE_FINGER_CH 4
#define INDEX_FINGER_CH 7
#define THUMB_CH 11
#define THUMB_BASE_CH 8

#include <ros.h>
#include <sensor_msgs/JointState.h>
#include <std_msgs/Int16.h>

ros::NodeHandle nh;
//std_msgs::Int16 rumble_msg;
sensor_msgs::JointState jointstate_msg;

//ros::Publisher rumble_pub("rumble", &rumble_msg);

//char val;

void setup() {
 Serial.begin(9600);
 pwm.begin();                   //初期設定 (アドレス0x40用)
 pwm.setPWMFreq(50);            //PWM周期を50Hzに設定 (アドレス0x40用)
 paper();
}

int n=160;

void loop() {
  
  //delay(500);
  nh.spinOnce();
  delay(500);
}

void servo_write(int ch, int ang){ //動かすサーボチャンネルと角度を指定
  ang = map(ang, 0, 180, SERVOMIN, SERVOMAX); //角度（0～180）をPWMのパルス幅（150～500）に変換
  pwm.setPWM(ch, 0, ang);
}

void jointstate_cb(const sensor_msgs::JointState& msg);
ros::Subscriber<sensor_msgs::JointState> jointstate_sub("degree", jointstate_cb);

void jointstate_cb(const sensor_msgs::JointState& msg){
  
}
void pick_up(){
  servo_write(THUMB_CH, 70);
  delay(200);
  servo_write(INDEX_FINGER_CH, 90);
  delay(300);
}
void push_button(){
  servo_write(INDEX_FINGER_CH, 130);
  delay(500);
}

void scratching(){
  servo_write(LITTLE_FINGER_CH, n);
  servo_write(RING_FINGER_CH, n);
  servo_write(MIDDLE_FINGER_CH, n);
  servo_write(INDEX_FINGER_CH, n);
  
  n=n-140;
  if(n<=10){
    n=160;
  }
  delay(300); 
}

void finger_test(){
  servo_write(LITTLE_FINGER_CH, n);
  servo_write(RING_FINGER_CH, n);
  servo_write(MIDDLE_FINGER_CH, n);
  servo_write(INDEX_FINGER_CH, n);
  
  n=n-10;
  if(n<=10){
    n=160;
  }
  delay(500); 
}

void paper(){
  servo_write(THUMB_CH, 160);
  delay(200);
  servo_write(LITTLE_FINGER_CH, 160);
  servo_write(RING_FINGER_CH, 160);
  servo_write(MIDDLE_FINGER_CH, 160);
  servo_write(INDEX_FINGER_CH, 160);
  delay(100);
  //servo_write(THUMB_BASE_CH, 160);
}
