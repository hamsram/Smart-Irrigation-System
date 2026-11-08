#include <LiquidCrystal_I2C.h>
#include <MQ135.h>

MQ135 gasSensor = MQ135(A0);
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
  lcd.clear();
  pinMode(2, OUTPUT);
  digitalWrite(2, HIGH);
  delay(1000);
  
  // Print air quality data at the start
  int airQuality = gasSensor.getPPM();
  lcd.setCursor(0, 0);
  lcd.print("Air Quality: ");
  if (airQuality < 200) {
    lcd.setCursor(0, 1);
    lcd.print("Good");
  } else if (airQuality < 400) {
    lcd.setCursor(0, 1);
    lcd.print("Medium");
  } else {
    lcd.setCursor(0, 1);
    lcd.print("Bad");
  }
  delay(6000);
  lcd.clear();
  
  lcd.setCursor(0, 0);
  lcd.print("IRRIGATION");
  lcd.setCursor(0, 1);
  lcd.print("SYSTEM IS ON ");
  lcd.print("");
  delay(3000);
  lcd.clear();
}

void loop() {
  int moisture = analogRead(A1);
  int airQuality = gasSensor.getPPM();
  
  // Control water pump based on moisture level
  if (moisture > 1200) {
    digitalWrite(2, LOW);
    lcd.setCursor(0, 0);
    lcd.print("Water Pump is ON ");
  } else {
    digitalWrite(2, HIGH);
    lcd.setCursor(0, 0);
    lcd.print("Water Pump is OFF");
  }
 
  // Display moisture level
  if (moisture < 300 ) {
    lcd.setCursor(0, 1);
    lcd.print("Moisture : HIGH");
  } else if (moisture > 300 && moisture < 1200) {
    lcd.setCursor(0, 1);
    lcd.print("Moisture : MID ");
  } else if (moisture > 1200 ) {
    lcd.setCursor(0, 1);
    lcd.print("Moisture : LOW ");
  }
}
