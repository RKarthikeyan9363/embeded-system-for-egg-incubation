#include <dht.h>
#include <LiquidCrystal_I2C.h>
#include <Servo.h>
LiquidCrystal_I2C lcd(0x3F, 16, 2);

Servo servo;
dht DHT;

const int servoMotor = 9;
const int Relay = 10;
const int Buzzer = 11;

const float outPin = 8;
const float GasSensor = A0;

void setup() {
  Serial.begin(9600);
  lcd.init();
  lcd.clear();
  lcd.backlight();

  pinMode(Relay, OUTPUT);
  pinMode(GasSensor, INPUT);
  servo.attach(servoMotor);
}

void loop() {
  for (int i = 0; i <= 45; i++) {
    temperaturesensor();
    servo.write(i);
  }
  for (int i = 45; i <= 90; i++) {
    temperaturesensor();
    servo.write(i);
  }
  for (int i = 90; i >= 45; i--) {
    temperaturesensor();
    servo.write(i);
  }
  for (int i = 45; i >= 0; i--) {
    temperaturesensor();
    servo.write(i);
  }
}

void temperaturesensor() {
  int readData = DHT.read11(outPin);
  float t = DHT.temperature;
  float gas = analogRead(GasSensor) + 200;

  if (500 >= gas && 1000 <= gas) {
    digitalWrite(Buzzer, HIGH);
  } else {
    digitalWrite(Buzzer, LOW);
  }

  if (t > 37.8) {

    lcd.setCursor(0, 0);
    lcd.print("High Temp: ");
    lcd.print(t);
    lcd.println(" C");

    lcd.setCursor(0, 1);
    lcd.print("Gas : ");
    lcd.print(gas);
    lcd.println(" PPM   ");
    digitalWrite(Relay, HIGH);

  } else if (t >= 37.5 && t <= 37.8) {
    lcd.setCursor(0, 0);
    lcd.print("Ideal temp: ");
    lcd.print(t);
    lcd.println(" C");

    lcd.setCursor(0, 1);
    lcd.print("Gas : ");
    lcd.print(gas);
    lcd.println(" PPM   ");

  } else if (t < 37.5) {
    lcd.setCursor(0, 0);
    lcd.print("Low Temp: ");
    lcd.print(t);
    lcd.println(" C");

    lcd.setCursor(0, 1);
    lcd.print("Gas : ");
    lcd.print(gas);
    lcd.println(" PPM   ");
    digitalWrite(Relay, LOW);
  }
  delay(100);
}