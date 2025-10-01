#include <WiFi.h>

// SSID -> Nome da rede
// RSSI -> Intensidade do sinal

void setup() {
  Serial.begin(115200);
  Serial.println("Iniciando Scan de redes Wi-Fi");
}

void loop() {
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
