#include <WiFi.h>
#include <WebServer.h>
#include <ArduinoJson.h>
#include "root.h"

// #define SERIAL

// WiFi Parameters
#define SSID "AYLWARD_2.4G"
#define PASSWORD "0414626649"
#define HOSTNAME "LGBT"

// PWM Parameters
#define FREQ 5000
#define RESOLUTION 8

// PWM Channels
#define RED_CHANNEL 3
#define GREEN_CHANNEL 1
#define BLUE_CHANNEL 2

// PWM Pins
#define RED_PIN 20
#define GREEN_PIN 21
#define BLUE_PIN 8

#define CONNECTION_PIN 2
#define INBUILT_LED 10

// Colour variables
StaticJsonDocument<150> jsonDocument;
uint8_t red = 0;
uint8_t green = 0;
uint8_t blue = 0;

WebServer server(80);

// Serial begin with debug guards
void debugBegin(unsigned long baudrate)
{
#ifdef SERIAL
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

// Reconnect function
void WiFiStationDisconnected(WiFiEvent_t event)
{
    digitalWrite(CONNECTION_PIN, LOW);
    digitalWrite(INBUILT_LED, LOW);
    WiFi.begin(SSID, PASSWORD);
}

// Disconnect function
void WiFiStationConnected(WiFiEvent_t event)
{
    digitalWrite(CONNECTION_PIN, HIGH);
    digitalWrite(INBUILT_LED, HIGH);
}

// Sets up routes and their handlers
void setupRoutes()
{
    server.on("/", pageRoot);
    server.on("/change", HTTP_POST, change);
}

// REST endpoint for updating values
void change()
{
    String body = server.arg("plain");
    deserializeJson(jsonDocument, body);

    red = jsonDocument["r"];
    green = jsonDocument["g"];
    blue = jsonDocument["b"];

    debugPrintln(red);
    debugPrintln(green);
    debugPrintln(blue);

    ledcWrite(RED_CHANNEL, red);
    ledcWrite(GREEN_CHANNEL, green);
    ledcWrite(BLUE_CHANNEL, blue);

    server.send(200, "application/json", "{}");
}

// Root page
void pageRoot()
{
    server.send(200, "text/html", root_html);
}

void setup()
{
    // Begin serial
    debugBegin(115200);

    // Set up LEDS
    pinMode(10, OUTPUT);
    pinMode(CONNECTION_PIN, OUTPUT);
    ledcSetup(RED_CHANNEL, FREQ, RESOLUTION);
    ledcSetup(GREEN_CHANNEL, FREQ, RESOLUTION);
    ledcSetup(BLUE_CHANNEL, FREQ, RESOLUTION);
    ledcAttachPin(RED_PIN, RED_CHANNEL);
    ledcAttachPin(GREEN_PIN, GREEN_CHANNEL);
    ledcAttachPin(BLUE_PIN, BLUE_CHANNEL);

    digitalWrite(INBUILT_LED, LOW);
    digitalWrite(CONNECTION_PIN, LOW);
    ledcWrite(RED_CHANNEL, 0);
    ledcWrite(GREEN_CHANNEL, 0);
    ledcWrite(BLUE_CHANNEL, 0);
    
    // Begin wifi connection, set up reconnect
    WiFi.disconnect(true);
    WiFi.onEvent(WiFiStationDisconnected, ARDUINO_EVENT_WIFI_STA_DISCONNECTED);
    WiFi.onEvent(WiFiStationConnected, ARDUINO_EVENT_WIFI_STA_CONNECTED);
    WiFi.setHostname(HOSTNAME);
    WiFi.begin(SSID, PASSWORD);

    // Wait till valid connection
    while (WiFi.status() != WL_CONNECTED)
        delay(100);

    // Set up routes, turn on LED and begin server
    setupRoutes();
    server.begin();
    digitalWrite(INBUILT_LED, HIGH);
    digitalWrite(CONNECTION_PIN, HIGH);


    // Show IP on serial
    debugPrint("IP address: ");
    debugPrintln(WiFi.localIP());
}

void loop()
{
    server.handleClient();
}