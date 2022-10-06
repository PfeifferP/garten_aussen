// Loads the configuration from a file
void loadConfiguration(const char *filename, Config &config) {
  // Open file for reading
  File file = LittleFS.open(filename, "r");

  // Allocate a temporary JsonDocument
  // Don't forget to change the capacity to match your requirements.
  // Use arduinojson.org/v6/assistant to compute the capacity.
  StaticJsonDocument<512> doc;

  // Deserialize the JSON document
  DeserializationError error = deserializeJson(doc, file);
  if (error)
    Serial.println(F("Failed to read file, using default configuration"));

  // Copy values from the JsonDocument to the Config
  strlcpy(config.hostname, doc["hostname"] | "example.com", sizeof(config.hostname)); 

  // Close the file (Curiously, File's destructor doesn't close the file)
  file.close();
}

// Initialize WiFi
bool initialize_Wifi() {
  if(ssid=="" ){
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