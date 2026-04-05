#include "DHT.h"

#define DPIN D4        // pin DHT11
#define DTYPE DHT11

int ledPin = D5;       // pin LED (lebih aman dari D3)

DHT dht(DPIN, DTYPE);

void setup() {
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
  dht.begin();
}

void loop() {
  delay(2000);
  
  float tc = dht.readTemperature(false);  
  float tf = dht.readTemperature(true);   
  float hu = dht.readHumidity();          

  // Cek error
  if (isnan(tc) || isnan(hu)) {
    Serial.println("Gagal membaca DHT11!");
    return;
  }

  Serial.print("Temp: ");
  Serial.print(tc);
  Serial.print(" C, ");
  Serial.print(tf);
  Serial.print(" F, Hum: ");
  Serial.print(hu);
  Serial.println("%");

  // ====== LOGIKA LED ======
  if (hu > 70) {
    Serial.println("LEMBAP - Lampu NYALA");
    digitalWrite(ledPin, HIGH);
  } else {
    Serial.println("KERING - Lampu MATI");
    digitalWrite(ledPin, LOW);
  }

  Serial.println("----------------------");
}