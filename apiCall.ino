void apiCall(){
  if(WiFi.status() == WL_CONNECTED){
    HTTPClient http;
    String api = apiUrl;
    String data;

    //Data
    StaticJsonDocument<128> bodyRequest;
    StaticJsonDocument<255> apiResponse;

    bodyRequest["apiKey"] = apiKey;
    bodyRequest["moduleID"] = moduleID;
    bodyRequest["credentialUID"] = StrUID;

    // Serial.println(apiKey);
    // Serial.println(moduleID);
    // Serial.println(StrUID);

    serializeJson(bodyRequest, data);
    // Serial.println(data);

    http.begin(apiUrl.c_str());
    // Serial.println(apiUrl.c_str());
    http.addHeader("Content-Type", "application/x-<www-form-urlencoded"); //application/x-<www-form-urlencoded

    int httpResponseCode = http.POST(data);
    Serial.print("1. Codigo de Respuesta HTTP: ");
    Serial.println(httpResponseCode);
    
    if (httpResponseCode > 0){
      Serial.print("2. Codigo de Respuesta HTTP: ");
      Serial.println(httpResponseCode);
      String payload = http.getString();
      Serial.print("Respuesta: ");
      Serial.println(payload);
      DeserializationError error = deserializeJson(apiResponse, payload);

      if (error) {
        Serial.print("Hubo un error al descerializar el JSON: ");
        Serial.println(error.c_str());
        return;
      }

      success = apiResponse["success"];
    } else {
      Serial.print("Error Codigo: ");
      Serial.println(httpResponseCode);
    }

    http.end();

    if(success == true){
      isEntrance = apiResponse["moduleIsEntrance"];
      Serial.println(isEntrance);
      turnstileControl();
    }

    delay(1000);

  } else{
    Serial.println("WiFi Desconectado");
  }

  lastTime = millis();
}