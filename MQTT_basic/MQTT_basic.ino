#include <WiFi.h>
#include <PubSubClient.h>

const String SSID = "iPhone";
const String PSWD = "iot_sul_123";

const String brokerUrl = "test.mosquitto.org";      //URL do broker (servidor)
const int port = 1883;                              // Porta do Broker (servidor)
  
WiFiClient espClient;                              // Criando Cliente WiFi
PubSubClient mqtt(espClient);                     // Criando Cliente MQTT

void connectWifi();

void setup() {
  Serial.begin(115200);
  connectWifi();
  connectBroker();
}


void loop() {
 // Detecta se o WiFi desconectou e tenta reconexão.
  if (WiFi.status() != WL_CONNECTED){
    Serial.println("Conexão WiFi perdida! Tentando reconexão...");
    connectWifi();
  }
  if (!mqttClient.connected()) {
    Serial.println("MQTT desconectado! Tentando reconexão...");
    connectBroker();
  }
  if(Serial.available() > 0){
    String msg = Serial.readStringUntil('\n');
    msg = "Pedro: " + msg;
    mqttClient.publish("AulaIoTSul/Chat", msg.c_str());
  }
  delay(1500);

  mqtt.loop();
}

void connectWifi(){
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
  mqtt.subscribe("AulaIoTSul/Chat");
  mqtt.setCallback(callback);
  Serial.println("Conectado ao broker com sucesso!"); 
}

void callback(char* topic, byte* payload, unsigned long length){
  String resposta = "";
  for(int i = 0; i < length; i++){
    resposta += (char) payload[i];
  }
  Serial.print("Mensagem recebida [");
  Serial.print(topic);
  Serial.print("]: ");
  Serial.println(resposta);
}