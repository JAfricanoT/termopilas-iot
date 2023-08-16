//Reading and getting a UID

void setupRC522(){
  // Init SPI bus
  SPI.begin();
  // Init MFRC522 card
  mfrc522.PCD_Init();
}


int getidRC522() {
  if (!mfrc522.PICC_IsNewCardPresent()) {
    return 0;
  }
  if (!mfrc522.PICC_ReadCardSerial()) {
    return 0;
  }

  Serial.print("El UID de la tarjeta escaneada es: ");

  for (int i = 0; i < 4; i++) {
    readcard[i] = mfrc522.uid.uidByte[i]; //storing the UID of the tag in readcard
    arrayToStringRC522(readcard, 4, str);
    StrUID = str;
  }
  mfrc522.PICC_HaltA();

  Serial.println(StrUID);

  return 1;
}

//Change the array UID into a string
void arrayToStringRC522(byte array[], unsigned int len, char buffer[]){
  for (unsigned int i = 0; i < len; i++){
    byte nib1 = (array[i] >> 4) & 0x0F;
    byte nib2 = (array[i] >> 0) & 0x0F;
    buffer[i * 2 + 0] = nib1  < 0xA ? '0' + nib1  : 'A' + nib1  - 0xA;
    buffer[i * 2 + 1] = nib2  < 0xA ? '0' + nib2  : 'A' + nib2  - 0xA;
  }
  buffer[len * 2] = '\0';
}