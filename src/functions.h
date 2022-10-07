// Loads the configuration from a file
bool readConfigFile(char* fileName)
{
  File configFile = LittleFS.open(fileName, "r");
  if (!configFile) {
    Serial.println("Failed to open config file");
    return false;
  }

  size_t size = configFile.size();
  if (size > 1024) {
    Serial.println("Config file size is too large");
    return false;
  }

  // Allocate the memory pool on the stack.
  // Use arduinojson.org/assistant to compute the capacity.
  StaticJsonDocument<256> doc;

  // Deserialize the JSON document
  DeserializationError error = deserializeJson(doc, configFile);
  if (error)
    Serial.println(F("Failed to read file, using default configuration"));

  // Copy values from the JsonObject to the Config
  settings.sta_ssid = doc["ssid"];
  Config.pass = root["pass"];
  if (whichFile)
  {
    Config.hFlag = root["hFlag"];
  }

  // We don't need the file anymore
  configFile.close();

  return true;
}

// Initialize WiFi
bool initialize_Wifi() {
  if(settings.sta_ssid=="" ){
    Serial.println("Undefined SSID or IP address.");
    return false;
  }

  WiFi.mode(WIFI_STA);
  

  
  WiFi.begin(ssid.c_str(), password.c_str());
  Serial.println("Connecting to WiFi...");

  unsigned long current_time = millis();
  previous_time = current_time;

  while(WiFi.status() != WL_CONNECTED) {
    current_time = millis();
    if (current_time - previous_time >= Delay) {
      Serial.println("Failed to connect.");
      return false;
    }
  }

  Serial.println(WiFi.localIP());
  return true;
}