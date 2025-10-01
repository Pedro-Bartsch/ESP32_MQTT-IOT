#include <WiFi.h>

const String SSID = "nome da rede";
const String PSWD = "senha da rede";

// SSID -> Nome da rede
// RSSI -> Intensidade do sinal

void scanLocalNetworks();

void setup() {
  Serial.begin(115200);
  scanLocalNetworks();
  Serial.println("Iniciando conexão com rede WiFi");
  WiFi.begin(SSID, PSWD);
  
  while (WiFi.status() != WL_CONNECTED){
    Serial.print(".");
    delay(200);
  }
  Serial.println("\nConectado com sucesso");
}

void loop() {
}

void scanLocalNetworks(){
  Serial.println("Iniciando Scan de redes Wi-Fi");
  int number = WiFi.scanNetworks();
  delay(500);
  if (number == -1){
    Serial.prinln("ERRO AO ENCONTRAR REDES!");
  } else{
    Serial.printf("Número de redes encontradas: %d\n", number);
    for(int net = 0; net < number; net++){
      Serial.printf("%d - %s | %d db\n", net, WiFi.SSID(net), WiFi.RSSI(net));
    }
  }
}