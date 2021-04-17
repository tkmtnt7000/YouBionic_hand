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
//#include <std_msgs/Int16.h>

ros::NodeHandle nh;
//std_msgs::Int16 rumble_msg;
sensor_msgs::JointState jointstate_msg;

//ros::Publisher rumble_pub("rumble", &rumble_msg);

//char val;
int n=160;

void servo_write(int ch, int ang){ //動かすサーボチャンネルと角度を指定
  ang = map(ang, 0, 180, SERVOMIN, SERVOMAX); //角度（0～180）をPWMのパルス幅（150～500）に変換
  pwm.setPWM(ch, 0, ang);
}

void jointstate_cb(const sensor_msgs::JointState& jointstate_msg);
ros::Subscriber<sensor_msgs::JointState> jointstate_sub("right_hand/joint_state", jointstate_cb);
/*
void sample_cb(const std_msgs::Int16& msg);
ros::Subscriber<std_msgs::Int16> jointstate_sub("manus/right_hand/joint_states", sample_cb);
*/

void jointstate_cb(const sensor_msgs::JointState& jointstate_msg){
  servo_write(0, jointstate_msg.position[4]);
  servo_write(3, jointstate_msg.position[3]);
  servo_write(4, jointstate_msg.position[2]);
  servo_write(7, jointstate_msg.position[1]);
  servo_write(11, jointstate_msg.position[0]);
}
/*
void sample_cb(const std_msgs::Int16& msg){
  servo_write(7, msg.data);
}*/

void pick_up(){
  servo_write(THUMB_CH, 70);
  delay(200);
  servo_write(INDEX_FINGER_CH, 90);
  delay(300);
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

void setup() {
 nh.initNode();
 nh.subscribe(jointstate_sub);
 
 //Serial.begin(9600);
 pwm.begin();                   //初期設定 (アドレス0x40用)
 pwm.setPWMFreq(50);            //PWM周期を50Hzに設定 (アドレス0x40用)
 paper();
}



void loop() {
  //delay(500);
  nh.spinOnce(); 
  delay(200);
}
