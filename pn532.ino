void setupPN532() {
  nfc.begin(); //Comienza la comunicación del PN532

  uint32_t versiondata = nfc.getFirmwareVersion();//Obtiene información de la placa

  if (! versiondata) { //Si no se encuentra comunicación con la placa --->
    Serial.print("No se encontró la placa PN53x");
    while (1); // Detener
  }

  Serial.print("Chip encontrado PN5 ");
  Serial.println((versiondata >> 24) & 0xFF, HEX); //Imprime en el serial que version de Chip es el lector
  Serial.print("Firmware ver. ");
  Serial.print((versiondata >> 16) & 0xFF, DEC); // Imprime que versión de firmware tiene la placa
  Serial.print('.'); Serial.println((versiondata >> 8) & 0xFF, DEC);

  //Establezca el número máximo de reintentos para leer de una tarjeta.
  //Esto evita que tengamos que esperar eternamente por una tarjeta,
  //que es el comportamiento predeterminado del PN532.
  nfc.setPassiveActivationRetries(0xFF);

  nfc.SAMConfig(); //Configura la placa para realizar la lectura

  Serial.println("Esperando una tarjeta ISO14443A ...");
}

int getidPN532(){
  bool successPN532; //Variable para almacenar la detección de una tarjeta
  uint8_t uid[] = { 0, 0, 0, 0, 0, 0, 0 };  // Búfer para almacenar el UID devuelto
  uint8_t uidLength; //Variable para almacenar la longitud del UID de la tarjeta

  //Recepción y detección de los datos de la tarjeta y almacenamiento en la variable "successPN532"
  successPN532 = nfc.readPassiveTargetID(PN532_MIFARE_ISO14443A, &uid[0], &uidLength);

    //Si no se detecta tarjeta
  if (!successPN532){
    return 0;
  }

  Serial.println("Tarjeta encontrada");
  Serial.print("Longitud del UID: ");
  Serial.print(uidLength, DEC); //Imprime la longitud de los datos de la tarjeta en decimal
  Serial.println(" bytes");
  Serial.print("Valor del UID: ");
  // Imprime los datos almacenados en la tarjeta en Hexadecimal
  for (uint8_t i = 0; i < uidLength; i++){
    //Serial.print(uid[i], HEX);
    arrayToStringPN532(uid, uidLength, str);
    StrUID = str;
  }
  Serial.println(StrUID);
  return 1;

}

void arrayToStringPN532(uint8_t array[], unsigned int len, char buffer[]){
  for (unsigned int i = 0; i < len; i++){
    byte nib1 = (array[i] >> 4) & 0x0F;
    byte nib2 = (array[i] >> 0) & 0x0F;
    buffer[i * 2 + 0] = nib1  < 0xA ? '0' + nib1  : 'A' + nib1  - 0xA;
    buffer[i * 2 + 1] = nib2  < 0xA ? '0' + nib2  : 'A' + nib2  - 0xA;
  }
  buffer[len * 2] = '\0';
}

