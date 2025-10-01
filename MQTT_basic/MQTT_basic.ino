#include <WiFi.h>
#include <PubSubClient.h>

const String SSID = "IPhone";
const String PWSD = "iot_sul_123";

const String brokerUrl = "";      //URL do broker (servidor)
const int port = 1883;            // Porta do Broker (servidor)
  
WiFiClient espClient;             // Criando Cliente WiFi
PubSubClient mqtt(espClient);     // Criando Cliente MQTT

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
    mqttClient.setServer(brokerUrl,port);
    String userId = "ESP-PEDRO";
    mqttClient.connect(userId);

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