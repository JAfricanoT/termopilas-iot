void wifiSetup(){

  /*if(!WiFi.config(local_IP, gateway, subnet, primaryDNS, secondaryDNS)){
    Serial.println("Hubo un error en la configuración de la IP");
  }*/

  // Wifi Connection
  WiFi.begin(ssid, password); 
  Serial.println("");
  pinMode(ON_Board_LED, OUTPUT);
  digitalWrite(ON_Board_LED, HIGH);

  Serial.print("Conectando...");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    digitalWrite(ON_Board_LED, LOW);
    delay(250);
    digitalWrite(ON_Board_LED, HIGH);
    delay(250);
  }
  digitalWrite(ON_Board_LED, HIGH);
  
  //Successfully connected to the wifi
  Serial.println("");
  Serial.print("Conectado a: ");
  Serial.println(ssid);
  
  // Get the IP address and MAC address
  IPAddress ip = WiFi.localIP();
  
  uint8_t mac[6];
  WiFi.macAddress(mac);

  // Print the IP address and MAC address to the serial port
  Serial.print("IP: ");
  Serial.println(ip);
  Serial.print("MAC: ");
  for (int i = 0; i < 6; i++) {
    Serial.print(mac[i], HEX);
    if (i != 5) {
      Serial.print(":");
    }
  }
  Serial.println(""); 
  digitalWrite(ON_Board_LED, LOW);
}

void wifiCheck(){
  while (WiFi.status() != WL_CONNECTED) {
    wifiSetup();
  }

  Serial.println("Conectado a la red"); 

}