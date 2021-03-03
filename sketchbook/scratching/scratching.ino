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

//int inputkey = 10000;
char val;

void setup() {
 Serial.begin(9600);
 pwm.begin();                   //初期設定 (アドレス0x40用)
 pwm.setPWMFreq(50);            //PWM周期を50Hzに設定 (アドレス0x40用)
}

int n=160;

void loop() {
    if (Serial.available()>0) {
      val = Serial.read();
      if (val == 'a'){
        Serial.println("a");
        int i=0;
        for (i=0;i<=3;i++){
           scratching();
           delay(500);
        }
      }
      if (val == 'f'){
        Serial.println("finish");
      }
    }
    //finger_test();
    delay(500);
}

void servo_write(int ch, int ang){ //動かすサーボチャンネルと角度を指定
  ang = map(ang, 0, 180, SERVOMIN, SERVOMAX); //角度（0～180）をPWMのパルス幅（150～500）に変換
  pwm.setPWM(ch, 0, ang);
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
