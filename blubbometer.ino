#include <LiquidCrystal.h>
LiquidCrystal lcd(12,11,5,4,3,2);

const int pressurePin = A0;
const int tempPin = A1;
long counter = 0;
long t0 = 0;
long t1 = 1;
const int snittSize = 100;
int snittArray[snittSize];
float snitt;

int pressure;
int tempPinVal;
float tempVoltage;
float temp;
float tempMax = -100;
float tempMin = 100;
float avgTemp;
int tempCount = 0;

void setup() {
  lcd.begin(16,2);
  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);
  lcd.print(" BLUBB-O-METER");
  lcd.setCursor(6,1);
  lcd.print("9000");
  delay(3000);

}

void loop() {
  pressure = analogRead(pressurePin);
  tempPinVal = analogRead(tempPin);
  tempVoltage = (tempPinVal/1024.0)*5.0;
  temp += (tempVoltage-.5)*100;
  tempCount ++;

  
  delay(10);
  if (pressure > 10){
    t1 = millis();
    avgTemp = temp/tempCount;
    if (avgTemp>tempMax){
      tempMax=avgTemp;
    }
    if (avgTemp<tempMin){
      tempMin=avgTemp;
    }
    //Serial.print("Temp avg : ");
    //Serial.print(avgTemp);
    //Serial.print("\n");


    lcd.clear();
    lcd.setCursor(0,0);
    //lcd.print("Blubb#:");
    //lcd.print(counter);
    lcd.print("Tmp:");
    lcd.print(round(avgTemp));
    lcd.print(" M:");
    lcd.print(round(tempMax));
    lcd.print(" m:");
    lcd.print(round(tempMin));
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
    tempCount=0;
    temp=0;
    digitalWrite(LED_BUILTIN, HIGH);
    delay(1000);
    digitalWrite(LED_BUILTIN, LOW);
  }

}
