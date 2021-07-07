#define motorRight_forward 6
#define motorRight_backward 7
#define motorRight_EN 5
#define motorLeft_forward 4 
#define motorLeft_backward 2
#define motorLeft_EN 3

#define echoPin_mid 10
#define trigPin_mid 11
#define echoPin_right 8
#define trigPin_right 9
#define echoPin_left 12
#define trigPin_left 13

const int referenceInput = 20;
int mid_distance;
int right_distance;
int left_distance;
int measured_mid;
int measured_right;
int measured_left;
int error, derivative_error, last_error;
long Kp, Kd, PD;

void setup() {
  pinMode(trigPin_mid, OUTPUT);
  pinMode(echoPin_mid, INPUT);
  pinMode(trigPin_right, OUTPUT);
  pinMode(echoPin_right, INPUT);
  pinMode(trigPin_left, OUTPUT);
  pinMode(echoPin_left, INPUT);
  pinMode(trigPin_left, OUTPUT);
  pinMode(echoPin_left, INPUT);
  pinMode(motorRight_forward, OUTPUT);
  pinMode(motorRight_backward, OUTPUT);
  pinMode(motorRight_EN, OUTPUT);
  pinMode(motorLeft_forward , OUTPUT);
  pinMode(motorLeft_backward, OUTPUT);
  pinMode(motorLeft_EN, OUTPUT);
}

void loop() {
    measured_right=sensorRight();
    measured_left=sensorLeft();
    if((measured_right <14) and (measured_right<measured_left)){
      turnRight();
      delay(500);
    }
    if((measured_left <14) and (measured_left<measured_right)){
      turnLeft();
      delay(500);
    }
    measured_mid = sensorMid();
    error = measured_mid-referenceInput;
    derivative_error=error-last_error;
    last_error = error;
    Kp=3;
    Kd=1;
    PD= (Kp*error)+(Kd*derivative_error);
    if(PD>0) forward(PD);
    else if(PD<0) backward(PD);
    else dontMove();
}

void forward(long hiz){
  digitalWrite(motorRight_forward, HIGH);
  digitalWrite(motorLeft_forward, HIGH);
  
  digitalWrite(motorRight_backward, LOW);
  digitalWrite(motorLeft_backward, LOW);
  if (hiz>255){
    analogWrite(motorRight_EN, 255);
    analogWrite(motorLeft_EN, 255);
    }if (hiz<100){
      analogWrite(motorRight_EN, 100);
      analogWrite(motorLeft_EN, 100);
    }else{
      analogWrite(motorRight_EN, hiz);
      analogWrite(motorLeft_EN, hiz);
    }
}
      

void backward(long hiz){
  digitalWrite(motorRight_backward, HIGH);
  digitalWrite(motorLeft_backward, HIGH);
  
  digitalWrite(motorRight_forward, LOW);
  digitalWrite(motorLeft_forward, LOW);
  if (-hiz>200){
    analogWrite(motorRight_EN, 200);
    analogWrite(motorLeft_EN, 200);
  }else if (-hiz<100){
      analogWrite(motorRight_EN, 100);
      analogWrite(motorLeft_EN, 100);
      }else{
        analogWrite(motorRight_EN, -hiz);
        analogWrite(motorLeft_EN, -hiz); 
      }
}

void dontMove(){
  digitalWrite(motorRight_EN, LOW);
  digitalWrite(motorLeft_EN, LOW);
}

void turnRight(){
  digitalWrite(motorLeft_backward, HIGH);
  digitalWrite(motorLeft_forward, LOW);
  digitalWrite(motorRight_backward, LOW);
  digitalWrite(motorRight_forward, HIGH);
  analogWrite(motorLeft_EN, 100);
  analogWrite(motorRight_EN, 100);
}

void turnLeft(){
  digitalWrite(motorRight_backward, HIGH);
  digitalWrite(motorRight_forward, LOW);
  digitalWrite(motorLeft_backward, LOW);
  digitalWrite(motorLeft_forward, HIGH);
  analogWrite(motorRight_EN, 100);
  analogWrite(motorLeft_EN, 100);
}

int sensorMid(){
  digitalWrite(trigPin_mid, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin_mid, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin_mid, LOW);
  mid_distance = (pulseIn(echoPin_mid, HIGH))*0.034/2;
  return mid_distance;
}

int sensorRight(){
  digitalWrite(trigPin_right, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin_right, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin_right, LOW);
  right_distance = (pulseIn(echoPin_right, HIGH))*0.034/2;
  return right_distance;
}

int sensorLeft(){
  digitalWrite(trigPin_left, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin_left, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin_left, LOW);
  left_distance = (pulseIn(echoPin_left, HIGH))*0.034/2;
  return left_distance;
}
