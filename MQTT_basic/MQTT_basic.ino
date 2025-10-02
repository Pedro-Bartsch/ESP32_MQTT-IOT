#include <WiFi.h>
#include <PubSubClient.h>

const String SSID = "iPhone";
const String PSWD = "iot_sul_123";

const String brokerUrl = "test.mosquitto.org";      //URL do broker (servidor)
const int port = 1883;                              // Porta do Broker (servidor)
  
WiFiClient espClient;                              // Criando Cliente WiFi
PubSubClient mqtt(mqttClient);                     // Criando Cliente MQTT

void connectLocalNetworks();

void setup() {
  Serial.begin(115200);
  connectLocalNetworks();
  connectBroker();
}


void loop() {
 // Detecta se o WiFi desconectou e tenta reconexão.
  if (WiFi.status() != WL_CONNECTED){
    Serial.println("Conexão WiFi perdida! Tentando reconexão...");
    connectLocalNetworks();
  }
  if (mqtt != connected()) {
    Serial.println("MQTT desconectado! Tentando reconexão...");
    connectBroker();
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

void connectBroker() {
  mqtt.setServer(brokerUrl, port);

  Serial.println("Conectando ao broker");
  Serial.println(brokerUrl);
  
  String userId = "ESP-PDRO";
  userId += String(random(0xffff), HEX);
  
  mqttClient.setServer(brokerUrl.c_str(),port);
  
  mqttClient.connect(userId.c_str());
  while(!mqttClient.connected()) {
    Serial.println("Erro de conexão");
    delay(500);
  } 
  if (mqtt.connect(userId.c_str)) {

  Serial.println("Conectado ao broker com sucesso!");
  } else{
      Serial.print("Falha, rc=");
      Serial.print(mqtt.state());
      Serial.println(" Tentando novamente...")
      delay(1000);
    }
}