
const char* http_username = "admin";
const char* http_password = "admin";
unsigned long previous_time = 0;
const long Delay = 10000; 

struct strSettings {
    char hostname[16]; 
    char sta_ssid[16];
    char sta_pass[16];
    char ap_ssid[16];
    char ap_pass[16];
} settings;