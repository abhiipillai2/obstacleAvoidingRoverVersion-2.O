//this code is developed by Abhijith S Pillai || 2020 
//second version of obstacle avoiding rover that capable for more accurate actions

#include <NewPing.h>
#include <Servo.h>

Servo myservo;

#define TRIGGER_PIN  10
 
#define ECHO_PIN     13
  
#define MAX_DISTANCE 200

#define motor1Forward 2

#define motor1BackWord 3

#define motor2Forward 5

#define motor2backword 4

int distance;
int pos = 0;
int left = false;
int right = false;
int distanceNew = -1;
int rightTurnFlag = false ;
int leftTurnFlag = false ;

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); 

void setup() {
  Serial.begin(115200);
  
  myservo.attach(9);

  pinMode(motor1Forward,OUTPUT);
  pinMode(motor1BackWord,OUTPUT);
  pinMode(motor2Forward,OUTPUT);
  pinMode(motor2backword,OUTPUT);

  digitalWrite(motor1Forward,LOW);
  digitalWrite(motor1BackWord,LOW);
  digitalWrite(motor2Forward,LOW);
  digitalWrite(motor2backword,LOW);

}

void loop() {
  delay(50);
  myservo.write(90); 
  delay(500);       
  distance = sonar.ping_cm(); 
  if(distance == distanceNew){
    selfEscape();
    distanceNew = 0;
  }

  if(distance > 40)
  {
    Serial.print("engine forward");
   // Serial.println(distance);
    forward();
    
    delay(500);
    distanceNew = sonar.ping_cm();
      
  }
  else
  {
        engineStop();
    
            delay(50);
            if(rightTurnFlag)
            {
              Serial.println("alredy turn");
            }
            else
            {
              myservo.write(0); 
              delay(500);
              rightTurnFlag = true;
              leftTurnFlag = false;
            }    
            distance = sonar.ping_cm();
    
                if(distance > 40)
                {
                  Serial.print("engine right");
                  //Serial.println(distance);
                  
                        rigtTurn();
                        delay(500);
                        distanceNew = sonar.ping_cm();
                }
                else
                {
                  engineStop();
          
                  delay(50);
                  if(leftTurnFlag)
                  {
                    Serial.println("allrady turn left");
                  }
                  else
                  {
                    myservo.write(180); 
                    delay(500);
                    leftTurnFlag = true;
                    rightTurnFlag = false;       
                  }
              
                  distance = sonar.ping_cm();
          
                    if(distance > 40 )
                    {
                      Serial.print("engine left");
                      //Serial.println(distance);
          
                            leftTurn();
                            delay(500);
                            distanceNew = sonar.ping_cm();
                    }
          else
          {
            selfEscape();
          }
      }
  }

  
}

void engineStop()
{
                digitalWrite(motor1Forward,LOW);
                digitalWrite(motor2Forward,LOW);
                digitalWrite(motor1BackWord,LOW);
                digitalWrite(motor2backword,LOW);
}


void selfEscape()
{
  myservo.write(0);

              Serial.print("backword");
              Serial.println(distance);
                digitalWrite(motor1BackWord,HIGH);
                digitalWrite(motor2backword,HIGH);
                digitalWrite(motor1Forward,LOW);
                digitalWrite(motor2Forward,LOW);
                delay(4000);
                digitalWrite(motor1BackWord,HIGH);
                digitalWrite(motor2backword,LOW);
                delay(4000);
}

void rigtTurn()
{
  if(right)
              {
                digitalWrite(motor1Forward,HIGH);
                digitalWrite(motor2Forward,HIGH);
                digitalWrite(motor1BackWord,LOW);
                digitalWrite(motor2backword,LOW);
              }
              else
              {
                delay(1000);
                  digitalWrite(motor2Forward,HIGH);
                  digitalWrite(motor1Forward,LOW);
                  digitalWrite(motor1BackWord,LOW);
                  digitalWrite(motor2backword,LOW);
                  delay(50);
                  myservo.write(90); 
                  delay(2000);
                  right = true;
                  left = false;
              }
}
 void leftTurn()
 {
  if(left)
                  {
                    digitalWrite(motor1Forward,HIGH);
                    digitalWrite(motor2Forward,HIGH);
                    digitalWrite(motor1BackWord,LOW);
                    digitalWrite(motor2backword,LOW);
                  }
                  else
                  {
                    digitalWrite(motor1Forward,HIGH);
                    digitalWrite(motor2Forward,LOW);
                    digitalWrite(motor1BackWord,LOW);
                    digitalWrite(motor2backword,LOW);
                    delay(50);
                     myservo.write(90); 
                     delay(2000);
                     left = true;
                     right = false;
                  }
 }

void forward()
{
      digitalWrite(motor1Forward,HIGH);
      digitalWrite(motor2Forward,HIGH);
      digitalWrite(motor1BackWord,LOW);
      digitalWrite(motor2backword,LOW);
      left = false;
      right = false;
}
