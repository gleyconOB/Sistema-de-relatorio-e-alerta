#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

const char* ssid = "nome da rede wifi";         
const char* password = "senha";    

const String serverUrl = "https://script.google.com/macros/s/AKfycbzS9GbL3tBV5PjC5FDSHdPyQot-DFDeVWg182EBrKJCedOSWxIwGREqf8dOEdvUWvi6/exec";

WiFiClient client;

// Defina o pino do sensor de temperatura
const int lm35Pin = A0;

void setup() {
  Serial.begin(115200); // Inicializa a comunicação serial

  // Conecta ao Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("Conectado ao Wi-Fi");

  HTTPClient http;
}

void loop() {
  // Leitura do sensor de temperatura
  int sensorValue = analogRead(lm35Pin);  
  float temperatura = sensorValue * (5.0 / 1023.0) * 100.0;

  // Define o alerta com base na temperatura
  String alerta = (temperatura != -2.0) ? "Refrigerador com problema" : "Temperatura normal";

  // Preparando os dados para envio
  String postData = "{\"temperatura\":\"" + String(temperatura) + "\",\"alerta\":\"" + alerta + "\"}";

  // Envia os dados somente se a temperatura for diferente de -2.0 pra nao encher a planilha de dados
  if (temperatura != -2.0) {
    HTTPClient http;
    http.begin(client, serverUrl);
    http.addHeader("Content-Type", "application/json");

    // Faz a requisição POST
    int httpResponseCode = http.POST(postData);

    if (httpResponseCode > 0) {
      Serial.println("Dados enviados com sucesso");
    } else {
      Serial.println("Erro ao enviar dados: " + String(httpResponseCode));
    }

    http.end(); 
  }

  
  delay(60000); 
}