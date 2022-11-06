#include "DHT.h"
#define DHTPIN 12
#define DHTTYPE DHT11
#define sensorPower 7
#define sensorPin A0

int val = 0;

const int trigPin = 9;
const int echoPin = 10;
float duration, distance;

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);
	pinMode(sensorPower, OUTPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
	digitalWrite(sensorPower, LOW);
  dht.begin();
}

void loop() {
  delay(500);
  float humidity = dht.readHumidity();
  float temp = dht.readTemperature(true);

  if (isnan(humidity) || isnan(temp)) {
    Serial.println(F("Sensor Reading N/A"));
    return;
  }

  float hif = dht.computeHeatIndex(temp, humidity);
  int level = readSensor();

  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distance = (duration*.0343)/2;

  Serial.print(humidity);
  Serial.print(F(","));
  Serial.print(temp);
  Serial.print(F(","));
  Serial.print(hif);
  Serial.print(F(""));
	
	Serial.print(",");
	Serial.print(level);
  Serial.print(",");

  if (distance < 100) {
    Serial.println(1);
  } else {
    Serial.println(0);
  }
	
	delay(1000);
}

int readSensor() {
	digitalWrite(sensorPower, HIGH);	
	delay(10);						
	val = analogRead(sensorPin);		
	digitalWrite(sensorPower, LOW);	
	return val;					
}