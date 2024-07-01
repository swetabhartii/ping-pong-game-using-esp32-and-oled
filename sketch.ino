#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include<Adafruit_GFX.h>
int Screen_width = 128;
int Screen_ht = 64;
int reset = -1 ;
int address = 0x3C;
int a =64; 
int b=32;//position coordinates of the centre of the ball
int x=55; 
int y=60; // Top left corner coordinates of the paddle
int x_speed=1; int y_speed=1; //speed of the ball
int score=0;
int k1, k2;
Adafruit_SSD1306 display(Screen_width,Screen_ht,&Wire,reset);

void setup(){
  pinMode(16, INPUT_PULLDOWN);
  pinMode(18, INPUT_PULLDOWN);
  pinMode(19, OUTPUT);
  Serial.begin(9600);
  if (!display.begin(SSD1306_SWITCHCAPVCC,address)){
    Serial.println("display not connected");
    for(;;);
  }
  display.clearDisplay();
}

void loop(){
  //Current score display on the screen
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(115, 1);
  display.print(score);
  //Code for movement of Paddle
  k1=digitalRead(18);
  if(k1==1 &&x+20<=127){
    x=x+3.5;
    Serial.println("Right");
  }
  k2=digitalRead(16);
  if(k2==1 &&x>=1){
    x=x-3.5;
    Serial.println("Left");
  } 



  //BOUNDARY CONDITIONS 
  if(2<a<125 && 0<b){
    x_speed=x_speed;
    y_speed=y_speed;
  }
  if(a==125||a==2){ //Left and the right edges
    x_speed=-x_speed;
    y_speed=y_speed;
  }
  if(b==2){ //Top edge
    y_speed=-y_speed;
    x_speed=x_speed;
  }
  if(x<=a && a<=x+20 && b+2==59){ //When ball hits the paddle
    y_speed=-y_speed;
    x_speed=x_speed;
    score =score +1;
    digitalWrite(19, HIGH);
    delay(20);
    digitalWrite(19, LOW);
  }

  a=a+x_speed;
  b=b+y_speed;
  display.fillCircle(a, b, 2, WHITE);
  display.fillRect(x, y, 20, 4, WHITE);
  
  display.display();
  display.clearDisplay();

  if(b>=61){ //Game Over
    digitalWrite(19, HIGH);
    delay(1000);
    digitalWrite(19, LOW);
    display.clearDisplay();
    display.setTextSize(2);
    display.setTextColor(WHITE);
    display.setCursor(25, 25);
    display.print("score ");
    display.print(score);
    display.display();
    delay(2000); // score will be displayed for 2 seconds
    display.clearDisplay();
    a=64;
    b=32;
    score=0;
    x=55;
    y=60;
  }
}