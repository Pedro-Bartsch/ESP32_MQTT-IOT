#include <WiFi.h>
#include <PubSubClient.h>

const String SSID = "IPhone";
const String PWSD = "iot_sul_123";

const String brokerUrl = "";
const int port = 1883;

WiFiClient espClient;

void connectLocalNetworks();

void setup() {
  Serial.begin(115200);
  connectLocalNetworks();
}

void loop() {
 // Detecta se o WiFi desconectou e tenta reconexão.
  if (WiFi.status() != WL_CONNECTED){
    Serial.println("Conexão perdida! Tentando reconexão.");
    connectLocalNetworks();
  }
}

void connectLocalNetworks(){
  Serial.println("Iniciando conexão com rede WiFi");
  WiFi.begin(SSID, PSWD);
  
  while (WiFi.status() != WL_CONNECTED){
    Serial.print(".");
    delay(200);
  }
  if (WiFi.status() == WL_CONNECTED){
  Serial.println("\nConectado com sucesso!");
  } else{
    Serial.println("\nFalha ao conectar.");
  }
}