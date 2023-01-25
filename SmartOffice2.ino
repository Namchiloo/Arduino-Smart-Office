#include "DHT.h"
#define DHTPIN 4
#define DHTTYPE DHT11   // DHT 11
#define button_pin 12

int led = 13;                // the pin that the LED is atteched to
int pir_sensor = 2;              // the pin that the pir sensor is atteched to
int state = LOW;             // by default, no motion detected
int val = 0;                 // variable to store the sensor status (value)
int stanje = 0;
int blue = 10;
int green = 11;

int In1 = 7;
int In2=8;
int ENA=5;
int SPEED = 100;
int value;
int button_stanje = 0;
int button_value=0;

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);
  Serial.println(F("DHT11 test!"));
  pinMode(In1, OUTPUT);
  pinMode(In2, OUTPUT);
  pinMode (ENA, OUTPUT);
  pinMode(led, OUTPUT);      // initalize LED as an output
  pinMode(pir_sensor, INPUT);    // initialize sensor as an input
  dht.begin();
}

void loop () {

float h = dht.readHumidity();        // read humidity
float t = dht.readTemperature();     // read temperature
float f = dht.readTemperature(true);

if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
}

float hif = dht.computeHeatIndex(f, h);
float hic = dht.computeHeatIndex(t, h, false);

Serial.print(F(" Humidity: "));
Serial.print(h);
Serial.print(F("%  Temperature: "));
Serial.print(t);
Serial.print(F("°C "));
Serial.print(f);
Serial.print(F("°F  Heat index: "));
Serial.print(hic);
Serial.print(F("°C "));
Serial.print(hif);
Serial.println(F("°F"));

button_value = digitalRead(button_pin);
if(button_value== HIGH && button_stanje == 0) {
if (t > 30)
{
  digitalWrite(In1, HIGH);
  analogWrite(ENA, 200);
}
else if (t<15){
        digitalWrite(In1, LOW);
        analogWrite(ENA, 0);
        digitalWrite(blue, HIGH);
        digitalWrite(green, LOW);
  }
else
{
     digitalWrite(In1, HIGH);
     analogWrite(ENA, 100);
     digitalWrite(green, HIGH);
     digitalWrite(blue, LOW);
     // digitalWrite(red, LOW);
}
button_stanje = 1;
}
else if (button_value == HIGH && button_stanje == 1){
  digitalWrite(In1, LOW);
  digitalWrite(In2, LOW);
  analogWrite(ENA,0);
  button_stanje = 0;
  digitalWrite(green, LOW);
  digitalWrite(blue, LOW);
  }

 int photores = analogRead(A0);
 Serial.println("Analog value : ");
 Serial.println(photores);
 val = digitalRead(pir_sensor);   // read sensor value
 if (val == HIGH && stanje==0 && photores < 25) {           // check if the sensor is HIGH
    digitalWrite(led, HIGH);   // turn LED ON
    delay(100);                // delay 100 milliseconds
    stanje=1;
    if (state == LOW) {
      Serial.println("Motion detected!");
      state = HIGH;       // update variable state to HIGH
    }
  }
else if (photores > 25 && stanje == 1){
      digitalWrite(led, LOW); // turn LED OFF
      delay(200);             // delay 200 milliseconds
     stanje = 0;
      if (state == HIGH){
        Serial.println("Motion stopped!");
        state = LOW;       // update variable state to LOW
    }
  }
}
