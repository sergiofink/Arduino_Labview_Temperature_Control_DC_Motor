#include "DHT.h"

#define DHTPIN 2     // Pino onde o DHT11 está conectado
#define DHTTYPE DHT11   // Tipo do sensor DHT11

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);
  dht.begin();
  pinMode(10, OUTPUT);  // Defina o pino 10 como saída
}

void loop() {
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();

  // Verifica se alguma leitura falhou e tenta novamente
  if (isnan(humidity) || isnan(temperature)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  // Envia os dados para a serial
  Serial.print("Humidity: ");
  Serial.print(humidity);
  Serial.print(" %\t");
  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.println(" *C");


  if (Serial.available() > 0) {
    String command = Serial.readStringUntil(';');
    if (command.startsWith("analogWrite")) {
      int pin, value;
      sscanf(command.c_str(), "analogWrite(%d,%d)", &pin, &value);
      analogWrite(pin, value);
    }
  }

  delay(2000); // Espera 2 segundos entre as leituras
}
