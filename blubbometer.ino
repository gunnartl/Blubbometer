#include <LiquidCrystal.h>
LiquidCrystal lcd(12,11,5,4,3,2);

const int sensorPin = A0;
int counter = 0;
long t0 = 0;
long t1 = 1;
const int snittSize = 100;
int snittArray[snittSize];
float snitt;
void setup() {
  lcd.begin(16,2);
  //Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);
  lcd.print(" BLUBB-O-METER");
  lcd.setCursor(6,1);
  lcd.print("9000");
  delay(3000);

}

void loop() {
  int sensorVal = analogRead(sensorPin);
  //#Serial.print("Sensor value: ");
  //#Serial.print(sensorVal);
  //#Serial.print("\n");
  delay(10);
  if (sensorVal > 10){
    t1 = millis();
    //Serial.print(" BLUBB! #");
    //Serial.print(counter);
    //Serial.print(", sec since last blubb: ");
    //Serial.print((t1-t0)/1000.);
    //Serial.print(" sec");

    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Blubb#:");
    lcd.print(counter);
    lcd.setCursor(0,1);
    lcd.print("T:");
    lcd.print((t1-t0)/1000.);

    snittArray[counter%snittSize] = t1-t0;
    if(counter >=snittSize){
      snitt = 0;
      for(int i=0; i < snittSize; i++){
        snitt += snittArray[i];
      }
      snitt = snitt/(1000. * snittSize);
      //Serial.print(", average last ");
      //Serial.print(snittSize); 
      //Serial.print(" measurements: ");
      //Serial.print(snitt);
      //Serial.print(" sec");

      lcd.print(" avg:");
      lcd.print(snitt);
    }

    

    //Serial.print(".\n");

    t0 = t1;
    counter ++;
    digitalWrite(LED_BUILTIN, HIGH);
    delay(1000);
    digitalWrite(LED_BUILTIN, LOW);
  }

}
