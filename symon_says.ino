#include<SPI.h>
#include <Adafruit_GFX.h>
#include <Wire.h>
#include <Adafruit_SSD1306.h>
#define sw 128 //width screen
#define sh 32 //hight screen
#define OLED_RESET            4
Adafruit_SSD1306 display(sw, sh, &Wire, OLED_RESET);
#define blue  7 //input 
#define yellow   6
#define red  5
#define redLED  8 //output
#define yellowLED  9
#define blueLED  10
int score;




void glowLED(byte memory[100],int p){
  byte LEDs[3]={blueLED,redLED,yellowLED};
  
  for(int i=0;i<p;i++){
    int num = random() % 3;
    digitalWrite(LEDs[num],HIGH);
    delay(500);
    digitalWrite(LEDs[num],LOW);
    delay(500);
   
    memory[i]=num;
  }
}
void printScore(int  score) {
  display.clearDisplay();
  display.setCursor(0, 0); 
  display.print("GAME OVER");
  display.setCursor(0, 10);
  display.print("Score: ");
  display.print(score); 
  display.display();    
}
void printGood(int  score) {
  display.clearDisplay();
  display.setCursor(0, 0); 
  display.print("Good");
  display.setCursor(0, 10);
  display.print("Score: ");
  display.print(score); 
  display.display();    
}




bool InputTester(byte memory[100], int p) {
  

  byte buttons[3] = {blue, red, yellow};
  byte leds[3] = {blueLED, redLED, yellowLED};  

  for (int i = 0; i < p; i++) {
    bool pressed = false;

    while (!pressed) {
      for (int j = 0; j < 3; j++) {
        if (digitalRead(buttons[j]) == HIGH) {
          if (memory[i] == j) {
            score += 10;
            printGood(score);

            pressed = true;
          } else {
            return false; 
          }

          // Wait for release
          while (digitalRead(buttons[j]) == HIGH);
          delay(100);
        }
      }
    }
  }

  return true;
}
  


void game(int p){
  int points;
  

  byte states[100];
  glowLED(states,p);

  if(InputTester(states,p)){
    delay(700);
    
    game(p+1);

  }else{
    printScore(score);
  }



}









void setup() {

  pinMode(red, INPUT);
  pinMode(yellow, INPUT);
  pinMode(blue, INPUT);
  pinMode(redLED, OUTPUT);
  pinMode(blueLED, OUTPUT);
  pinMode(yellowLED, OUTPUT);
  
  Serial.begin(9600);
  
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    while (true);
  }

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  display.println("Ready to play!");
  display.display();
  delay(1000);



}


void loop() {
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(1, 1);
  display.println("Simon says game");
  display.display();
  delay(1000);
  score =0;
  int p=1;
  game(p);
  delay(5000);

  
  
  


  

}
