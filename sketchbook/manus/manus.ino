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
std_msgs::Int16 rumble_msg;
//sensor_msgs::JointState jointstate_msg;

ros::Publisher rumble_pub("rumble", &rumble_msg);

int n=160;

// move servo motor with pwm
void servo_write(int ch, int ang){ //動かすサーボチャンネルと角度を指定
  ang = map(ang, 0, 180, SERVOMIN, SERVOMAX); //角度（0～180）をPWMのパルス幅（150～500）に変換
  pwm.setPWM(ch, 0, ang);
}

////////
// subscribe manus hand jointstate part
// sensor_msgs/JointState cannot be subscribed for some reasons.
////////
void thumb_cb(const std_msgs::Int16& msg);
void finger_cb(const std_msgs::Int16& msg);
void index_cb(const std_msgs::Int16& msg);
void ring_cb(const std_msgs::Int16& msg);
void pinky_cb(const std_msgs::Int16& msg);
ros::Subscriber<std_msgs::Int16> thumb_sub("right_hand/thumb", thumb_cb);
ros::Subscriber<std_msgs::Int16> thumb_base("right_hand/thumb_base", thumb_base_cb);
ros::Subscriber<std_msgs::Int16> index_sub("right_hand/index", index_cb);
ros::Subscriber<std_msgs::Int16> middle_sub("right_hand/middle", middle_cb);
ros::Subscriber<std_msgs::Int16> ring_sub("right_hand/ring", ring_cb);
ros::Subscriber<std_msgs::Int16> pinky_sub("right_hand/pinky", pinky_cb);

void thumb_cb(const std_msgs::Int16& msg){
  if(msg.data>25 && msg.data<165){
    servo_write(THUMB_CH, msg.data);
  }
}
void thumb_base_cb(const std_msgs::Int16& msg){
  if(msg.data>25 && msg.data<165){
    servo_write(THUMB_BASE_CH, msg.data);
  }
}
void index_cb(const std_msgs::Int16& msg){
  servo_write(INDEX_FINGER_CH, msg.data);
}
void middle_cb(const std_msgs::Int16& msg){
  servo_write(MIDDLE_FINGER_CH, msg.data);
}
void ring_cb(const std_msgs::Int16& msg){
  servo_write(RING_FINGER_CH, msg.data);
}

void pinky_cb(const std_msgs::Int16& msg){
  servo_write(LITTLE_FINGER_CH, msg.data);
}

void rumble(){
  rumble_msg.data = 1;
  rumble_pub.publish(&rumble_msg);
}

//void jointstate_cb(const sensor_msgs::JointState& jointstate_msg);
//ros::Subscriber<sensor_msgs::JointState> jointstate_sub("right_hand/joint_state", jointstate_cb);
/*
void sample_cb(const std_msgs::Int16& msg);
ros::Subscriber<std_msgs::Int16> jointstate_sub("right_hand/joint_states", sample_cb);
//ros::Subscriber<std_msgs::Int16> hoge("right_hand/joint", sample_cb);
*/
/*
void jointstate_cb(const sensor_msgs::JointState& jointstate_msg){
  servo_write(7, 30);
  
  if (jointstate_msg.position[4] > 25) {
    servo_write(0, (int)jointstate_msg.position[4]);
  }
  if (jointstate_msg.position[3] > 25) {
    servo_write(3, (int)jointstate_msg.position[3]);
  }
  if (jointstate_msg.position[2] > 25) {
    servo_write(4, (int)jointstate_msg.position[2]);
  }
  if (jointstate_msg.position[1] > 25) {
    servo_write(7, (int)jointstate_msg.position[1]);
  }
  if (jointstate_msg.position[0] > 25) {
    servo_write(11, (int)jointstate_msg.position[0]);
  }
  
}*/

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
 //nh.subscribe(jointstate_sub);
 nh.advertise(rumble_pub);
 nh.subscribe(thumb_sub);
 nh.subscribe(middle_sub);
 nh.subscribe(index_sub);
 nh.subscribe(ring_sub);
 nh.subscribe(pinky_sub);
 //Serial.begin(9600);
 pwm.begin();                   //初期設定 (アドレス0x40用)
 pwm.setPWMFreq(50);            //PWM周期を50Hzに設定 (アドレス0x40用)
 paper();
}


void loop() {
  //delay(500);
  rumble();
  nh.spinOnce(); 
  delay(200);
}
