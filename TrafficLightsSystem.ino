/* Name: Shenelle Jayakody, Mona Afshar, Radha Kotra
Teacher: Mr. Wong
Date: May 19, 2022
Description: Traffic light and streetlight system*/

#include <Servo.h>
#define motor 7

Servo myservo;
int angle = 0;
int servoTime=0;

int led_red = 13; // the red LED on the left is connected to Pin 0 of the Arduino
int led_yellow = 12; // the yellow LED on the left is connected to Pin 1 of the Arduino
int led_green = 11; // the green LED on the left is connected to Pin 2 of the Arduino
int led_red2 = 10; // the red LED on the right is connected to Pin 10 of the Arduino
int led_yellow2 = 9; // the yellow LED on the right is connected to Pin 9 of the Arduino
int led_green2 = 8; // the green LED on the right is connected to Pin 8 of the Arduino

int ifRead;
int gateTime;
int timeBtwn;
int timeStart;
int gateCheck;

const int ledPin = 5;  // the streetlight is connected to Pin 4 of the Arduino
const int ldrPin = A1;  //the LDR is connected to A0 of the Arduino

long timeCounter; //milliseconds counter
long timePassed; //how many milliseconds have passed

int pushButton = 2;
int green_pLight = 4;
int red_pLight = 3;
int btwnIntervals = 0;
int buttonPressedTime;
int saveTimeInterval;

int buttonPressed;
int buttonState;
int cycle = 0;
int cycleTracker;

int saveButton;
int checkTime = 0;
int firstCycle;
int lastCycle;

int ti1;
int ti2;
int ti3;
int ti4;
int ti5;
int ti6;
int ti7;
int ti8;
int ti9;
int ti10;
int ti11;

void setup ()
{
  myservo.attach(7);
 
  Serial.begin(9600);

  //pinMode(motor, OUTPUT);
  pinMode(A0, INPUT);
 
    timeCounter = millis ();
    Serial.begin (9600);
   
    //streetlight
    pinMode (ledPin, OUTPUT);
    pinMode (ldrPin, INPUT);

    //traffic light left
    // set up all the LEDs as OUTPUT
    pinMode (led_red, OUTPUT);
    pinMode (led_yellow, OUTPUT);
    pinMode (led_green, OUTPUT);

    //traffic light right
    // set up all the LEDs as OUTPUT
    pinMode (led_red2, OUTPUT);
    pinMode (led_yellow2, OUTPUT);
    pinMode (led_green2, OUTPUT);

    pinMode (pushButton, INPUT);
    pinMode (red_pLight, OUTPUT);
    pinMode (green_pLight, OUTPUT);
}

void gate (){
  ifRead = analogRead(A3);
 
  if(ifRead ==0 && servoTime == 0){
    gateCheck += 1;
    if(gateCheck == 3)
    {
      servoTime = millis();
      gateTime = 1;
    }
   
    Serial.println("working");
    Serial.println(ifRead);
   
  }
  else if(servoTime == 0)
  {
    gateCheck = 0;
   
  }
  if(millis() > servoTime + 2000 && gateTime == 1){
     
      for (angle = 0; angle <= 180; angle += 1) { // goes from 0 degrees to 180 degrees
        myservo.write(angle); // tell servo to go to position in variable 'pos'  
        if(angle == 180)
        {
          gateTime = 2;
        }
      }
    }
   else if(millis() > servoTime + 3500 && gateTime == 2)
   {
   
      for (angle = 180; angle >= 0; angle -= 1) { // goes from 0 degrees to 180 degrees
        myservo.write(angle);              // tell servo to go to position in variable 'pos'
        if(angle == 1)
        {
          gateTime = 3;
        }
      }
   }
   else if(gateTime == 3)
   {
      servoTime=0;
      gateTime = 0;
   }
}

void streetLight(){

    int ldrStatus = analogRead (ldrPin);
    if (ldrStatus < 30){
        digitalWrite (ledPin, HIGH);
    }
    else{
        digitalWrite (ledPin, LOW);
    }
}

void trafficLights(){
  timePassed = millis () - timeCounter;
  buttonState = digitalRead (pushButton);
    if (buttonState == 1)
    {
        firstCycle = cycle;
        buttonPressed = timePassed;
    }


    if (firstCycle != 0)
    {
        if (cycleTracker == 1 && cycle == 1)
        {
            ti1 = 4500;
        }
        else if (cycleTracker == 1 && cycle == 2)
        {
            firstCycle = 0;
            cycleTracker = 0;
        }
        else
        {
            ti1 = 3000;
        }

        if (firstCycle == 2)
        {
            ti3 = (ti1 + 3000 + buttonPressed) / 2;
        }
        else
        {
            ti3 = ti1 + 3000;
        }

        ti5 = ti3 + 1000;

        if (firstCycle == 4)
        {
            ti7 = ti5 + 3000;
        }
        else
        {
            ti7 = ti5 + 3000;
        }

        if (firstCycle == 5)
        {
            ti9 = (ti7 + 3000 + buttonPressed) / 2;
        }
        else
        {
            ti9 = ti7 + 3000;
        }

        ti11 = ti9 + 1000;
    }


    else
    {
        ti1 = 3000;
        ti3 = ti1 + 3000;
        ti5 = ti3 + 1000;
        ti7 = ti5 + 3000;
        ti9 = ti7 + 3000;
        ti11 = ti9 + 1000;
    }


    ti2 = ti1;
    ti4 = ti3;
    ti6 = ti5;
    ti8 = ti7;
    ti10 = ti9;


    if (timePassed > ti1)
    {
        digitalWrite (red_pLight, HIGH);
        digitalWrite (green_pLight, LOW);
    }


    if (timePassed < ti1)
    {
        //left
        // turn the green LED on and the other LEDs off
        digitalWrite (led_red, LOW);
        digitalWrite (led_yellow, LOW);
        digitalWrite (led_green, HIGH);
        //right
        // turn the red LED on and the other LEDs off
        digitalWrite (led_red2, HIGH);
        digitalWrite (led_yellow2, LOW);
        digitalWrite (led_green2, LOW);
        cycle = 1;
        digitalWrite (red_pLight, LOW);
        digitalWrite (green_pLight, HIGH);
    }



    if (timePassed > ti2 && timePassed < ti3)
    {
        //left
        // turn the yellow LED on and the other LEDs off
        digitalWrite (led_red, LOW);
        digitalWrite (led_yellow, HIGH);
        digitalWrite (led_green, LOW);
        //right
        // turn the red LED on and the other LEDs off
        digitalWrite (led_red2, HIGH);
        digitalWrite (led_yellow2, LOW);
        digitalWrite (led_green2, LOW);
        cycle = 2;
    }


    if (timePassed > ti4 && timePassed < ti5)
    {
        //left
        // turn the red LED on and the other LEDs off
        digitalWrite (led_red, HIGH);
        digitalWrite (led_yellow, LOW);
        digitalWrite (led_green, LOW);
        //right
        // turn the green LED on and the other LEDs off
        digitalWrite (led_red2, HIGH);
        digitalWrite (led_yellow2, LOW);
        digitalWrite (led_green2, LOW);
        cycle = 3;
    }


    if (timePassed > ti6 && timePassed < ti7)
    {
        //left
        // turn the red LED on and the other LEDs off
        digitalWrite (led_red, HIGH);
        digitalWrite (led_yellow, LOW);
        digitalWrite (led_green, LOW);
        //right
        // turn the green LED on and the other LEDs off
        digitalWrite (led_red2, LOW);
        digitalWrite (led_yellow2, LOW);
        digitalWrite (led_green2, HIGH);
        cycle = 4;
    }


    if (timePassed > ti8 && timePassed < ti9)
    {
        //left
        // turn the red LED on and the other LEDs off
        digitalWrite (led_red, HIGH);
        digitalWrite (led_yellow, LOW);
        digitalWrite (led_green, LOW);
        //right
        // turn the yellow LED on and the other LEDs off
        digitalWrite (led_red2, LOW);
        digitalWrite (led_yellow2, HIGH);
        digitalWrite (led_green2, LOW);
        cycle = 5;
    }


    if (timePassed > ti10 && timePassed < ti11)
    {
        //left
        // turn the red LED on and the other LEDs off
        digitalWrite (led_red, HIGH);
        digitalWrite (led_yellow, LOW);
        digitalWrite (led_green, LOW);
        //right
        // turn the green LED on and the other LEDs off
        digitalWrite (led_red2, HIGH);
        digitalWrite (led_yellow2, LOW);
        digitalWrite (led_green2, LOW);
        cycle = 6;
    }


    if (timePassed > ti11) //reset timer
    {
        timeCounter = millis ();
        if (firstCycle != 0)
        {
            cycleTracker = 1;
        }
    }
}

void loop ()
{
  gate();
  streetLight();
  trafficLights();
 
}