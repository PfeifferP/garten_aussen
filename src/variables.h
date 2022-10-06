String ssid = "*******";
String password = "*******";

const char* http_username = "admin";
const char* http_password = "admin";
unsigned long previous_time = 0;
const long Delay = 10000; 

struct Config {
    char hostname[16]; 
    char ssid[16];
    char pass[16];
} config;