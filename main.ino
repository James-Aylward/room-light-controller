#include <WiFi.h>
#include <WebServer.h>

#define SERIAL

#define SSID "AYLWARD_2.4G"
#define PASSWORD "0414626649"
#define HOSTNAME "LGBT"

// Colour variables
uint8_t red = 0;
uint8_t green = 0;
uint8_t blue = 0;

WebServer server(80);

// Serial begin with debug guards
void debugBegin(unsigned long baudrate)
{
#ifdef SERAIL
    Serial.begin(baudrate);
#endif
}

// Serial print with debug guards
template <typename T>
void debugPrint(T message)
{
#ifdef SERIAL
    Serial.print(message);
#endif
}

// Serial println with debug guards
template <typename T>
void debugPrintln(T message)
{
#ifdef SERIAL
    Serial.println(message);
#endif
}

// Sets up routes and their handlers
void setupRoutes()
{
    server.on("/", page_root);
}

// Root page
void page_root()
{
    String HTML = "<!DOCTYPE html>\
<html>\
<body>\
<h1>My First Web Server with ESP32 - Station Mode &#128522;</h1>\
</body>\
</html>";
    server.send(200, "text/html", HTML);
}

void setup()
{
    // Begin serial
    debugBegin(115200);

    // Write inbuilt LED low
    pinMode(10, OUTPUT);
    digitalWrite(10, LOW);

    // Begin wifi connection
    WiFi.setHostname(HOSTNAME);
    WiFi.begin(SSID, PASSWORD);

    // Wait till valid connection
    while (WiFi.status() != WL_CONNECTED)
        delay(1000);

    // Set up routes, turn on LED and begin server
    setupRoutes();
    server.begin();
    digitalWrite(10, HIGH);

    // Show IP on serial
    debugPrint("IP address: ");
    debugPrintln(WiFi.localIP());
}

void loop()
{
    server.handleClient();
}