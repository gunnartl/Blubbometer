#include <LiquidCrystal.h>
LiquidCrystal lcd(12,11,5,4,3,2);

int p = A0;
int c = 0;
long t0 = 0;
long t1 = 1;
int sS = 100;
int a[sS];
float s;
void setup() {
  lcd.begin(16,2);
  pinMode(LED_BUILTIN, OUTPUT);
  lcd.print(" BLUBB-O-METER");
  lcd.setCursor(6,1);
  lcd.print("9000");
  delay(3000);
}
void loop() {
  int v = analogRead(p);
  delay(10);
  if (v > 10){
    t1 = millis();
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Blubb#:");
    lcd.print(counter);
    lcd.setCursor(0,1);
    lcd.print("T:");
    lcd.print((t1-t0)/1000.);
    a[c%sS] = t1-t0;
    if(c >=sS){
      s = 0;
      for(int i=0; i < sS; i++){
        s += a[i];
      }
      s = s/(1000. * sS);
      lcd.print(" avg:");
      lcd.print(s);
    }
    t0=t1;
    c ++;
  }

}
