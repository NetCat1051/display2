#include <Adafruit_SSD1306.h>
#include <splash.h>
#include "SPI.h"

#define BUTTON_PIN 4
#define MOTOR1_IN1 5
#define MOTOR1_IN2 6
#define MOTOR2_IN1 7
#define MOTOR2_IN2 8


#define SCREEN_WIDTH 128 // Ширина дисплея в пикселях
#define SCREEN_HEIGHT 64 // Высота дисплея в пикселях

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

int s = 0;

void setup() {
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  pinMode(MOTOR1_IN1, OUTPUT);
  pinMode(MOTOR1_IN2, OUTPUT);
  pinMode(MOTOR2_IN1, OUTPUT);
  pinMode(MOTOR2_IN2, OUTPUT);
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3D for 128x64
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }
  delay(2000);
  display.clearDisplay();
 
  display.setTextSize(1); // установка размера шрифта
  display.setTextColor(WHITE); // установка цвета текста
  display.setCursor(0, 10); // установка курсора
  display.display(); 

}

void loop() {
  // Обработка нажатия кнопки
  if (digitalRead(BUTTON_PIN) == LOW) {
    s += 10;
    display.setCursor(0, 10); // установка курсора
  // Display static text
  display.println(s);
    delay(200);  // Задержка для подавления дребезга кнопки
  }

  // Вращение двигателей
  if (s > 0) {
    digitalWrite(MOTOR1_IN1, HIGH);
    digitalWrite(MOTOR1_IN2, LOW);
    digitalWrite(MOTOR2_IN1, LOW);
    digitalWrite(MOTOR2_IN2, HIGH);
    delay(s);
    digitalWrite(MOTOR1_IN1, LOW);
    digitalWrite(MOTOR1_IN2, HIGH);
    digitalWrite(MOTOR2_IN1, HIGH);
    digitalWrite(MOTOR2_IN2, LOW);
    delay(s);
    display.clearDisplay();
  }
}
