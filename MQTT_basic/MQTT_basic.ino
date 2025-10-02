#include <WiFi.h>
#include <PubSubClient.h>

const String SSID = "iPhone";
const String PSWD = "iot_sul_123";

const String brokerUrl = "test.mosquitto.org";      //URL do broker (servidor)
const int port = 1883;                              // Porta do Broker (servidor)
  
WiFiClient espClient;                              // Criando Cliente WiFi
PubSubClient mqtt(espClient);                     // Criando Cliente MQTT

void connectLocalNetworks();

void setup() {
  Serial.begin(115200);
  connectLocalNetworks();
  Serial.println("Conectando ao broker");
  mqttClient.setServer(brokerUrl.c_str(),port);
  String userId = "ESP-PDRO";
  userId += String(random(0xffff), HEX);
  mqttClient.connect(userId.c_str());
  while(!mqttClient.connected()) {
    Serial.println("Erro de conexão");
    delay(500);
  } 
  Serial.println("Conectado com sucesso!");
}


void loop() {
 // Detecta se o WiFi desconectou e tenta reconexão.
  if (WiFi.status() != WL_CONNECTED){
    Serial.println("Conexão perdida! Tentando reconexão.");
    connectLocalNetworks();
  }
  delay(1500);
  mqttClient.loop();
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