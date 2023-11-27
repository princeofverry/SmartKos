#include <LiquidCrystal.h>

LiquidCrystal lcd(5, 6, 8, 9, 10, 11);

int redled = 2;
int greenled = 3;
int buzzer = 4;
int sensor = A0;
int sensorThresh = 400;
int tempSensor = A1;

void displayAlert() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("ALERT");
  delay(500);
  lcd.clear();
  lcd.setCursor(0, 1);
  lcd.print("EVACUATE");
  delay(500);
}

void displaySafe(float temperature) {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("SAFE");
  delay(500);
  lcd.clear();
  lcd.setCursor(0, 1);
  lcd.print("Temp: ");
  lcd.print(temperature);
  lcd.print(" C");
  delay(500);
}

float readTemperature() {
  int sensorValue = analogRead(tempSensor);
  float voltage = sensorValue * (5.0 / 1023.0);
  float temperatureC = (voltage - 0.5) * 100.0;
  return temperatureC;
}

void setup() {
  pinMode(redled, OUTPUT);
  pinMode(greenled, OUTPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(sensor, INPUT);
  pinMode(tempSensor, INPUT);
  pinMode(7, OUTPUT);
  Serial.begin(9600);
  lcd.begin(16, 2);
}

void loop() {
  //lampu
 int value = analogRead(A4);
 Serial.println(value);
  
  if (value > 500) {
    digitalWrite(7, HIGH);
    delay(250);
  }
  else  {
  digitalWrite(7, LOW);
  delay(250);
  }
  
  
  int analogValue = analogRead(sensor);
  //Serial.print(analogValue);

  if (analogValue > sensorThresh) {
    digitalWrite(redled, HIGH);
    digitalWrite(greenled, LOW);
    tone(buzzer, 1000, 100);
    displayAlert();
  } else {
    digitalWrite(greenled, HIGH);
    digitalWrite(redled, LOW);
    noTone(buzzer);
    float temperature = readTemperature();
    displaySafe(temperature);
  }
}

