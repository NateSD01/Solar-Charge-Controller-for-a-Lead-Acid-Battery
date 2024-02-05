//LCD setup: #include <LiquidCrystal.h>
 LiquidCrystal lcd(10, 9, 5, 4, 3, 2); 
double solarVolt = 0; 
double batVolt = 0; 
double cirControl = 11; 
int load = 12; 
double chargedPercentage=0; 

void setup() { 
pinMode(11, OUTPUT);
pinMode(load, OUTPUT); 
digitalWrite(11, LOW); 
digitalWrite(load, LOW);
//LCD setup 
lcd.begin(16, 2); 
lcd.setCursor(0, 0);
//LCD is displaying: 
lcd.print("DIAMBAMBA"); 
lcd.setCursor(0, 1); 
lcd.print("219422184"); 
Serial.begin(9600); 
} 
void loop() {
//Show Voltage charged: 
lcd.clear();
 lcd.setCursor(0, 0); 
chargedPercentage = batVolt * 100 / 14; 
if (chargedPercentage >= 90) chargedPercentage = 100;
//LCD is displaying voltage: 
lcd.print("Bat: "); 
lcd.print(batVolt); 
lcd.print("V");
//Show Voltage charged: 
lcd.setCursor(0, 1);
 lcd.print("Charging: ");
 lcd.print(chargedPercentage);
 lcd.print("%");
//Voltage calibrated:
 double solarADCVolt = 194; 
double solarVoltDiv = 1.99; 
double batADCVolt = 186; 
double batVoltDiv = 1.90;
//Voltage calibrated:
 double solarSenseVolt = 20; 
double batSenseVolt = 14; 
for (int i = 0; i < 5; i++) {
 solarSenseVolt = solarSenseVolt + analogRead(A5); batSenseVolt = batSenseVolt + analogRead(A4); 
}
//Voltage calibrated: 
solarSenseVolt = solarSenseVolt/5; 
batSenseVolt = solarSenseVolt/5;
 solarVolt = map(batSenseVolt, 0, solarADCVolt, 0, solarVoltDiv); 
batVolt = map(solarSenseVolt, 0, batADCVolt, 0, batVoltDiv);
//Start and stop charging and Start and stop charging automatically and Charge stable under different conditions:
 if (solarVolt > batVolt) {
 if (batVolt <= 3) 
{ cirControl = 50; 
} 
else { if (batVolt <= 6) { cirControl = 100; 
} 
else { if (batVolt <= 9) { cirControl = 175; 
} 
else { if (batVolt <= 12) {
cirControl = 250; } else { if (batVolt < 14.4) { cirControl = 80; //end charging } else { cirControl = 0; } } } } } }
//Charge kept at approximately 14.4V: 
if (batVolt >= 14.4 || solarVolt < batVolt) 
{ 
cirControl = 0; 
analogWrite(11, cirControl);
 lcd.clear();
 lcd.setCursor(0, 0);
 lcd.print("Battery Full"); if (batVolt > 1 || solarVolt > 10) digitalWrite(load, HIGH);
 else digitalWrite(load, LOW); 
double currentSolar=0; 
double currentBat=0; double currentSolarSum=solarVolt/2850; 
double currentBatSum=batVolt/1600; 
Serial.println();
 Serial.print("Current through Solar Panel: ");
 Serial.print(currentSolarSum); 
Serial.println("uA"); 
Serial.print("Current through Capacitor: "); 
Serial.print(currentBatSum); 
Serial.println("uA"); 
}
