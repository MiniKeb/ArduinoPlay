#include <arduino-timer.h>
#include <Adafruit_NeoPixel.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>

#include "Html.h"
#include "HttpResponse.h"

#ifndef STASSID
#define STASSID "MySupaDupaWifi"
#define STAPSK  "MyWifiPassword"
#define D6_PIN 12
#endif

const char* ssid = STASSID;
const char* password = STAPSK;

ESP8266WebServer server(80);

struct Color{
  byte red;
  byte green;
  byte blue;
};
Color off = {0, 0, 0}; //Black is off
Color defaultLight = { 255, 255, 255 }; //White
Color normal = { 0, 255, 0 }; //Green
// Color normal = { 0, 0, 255 }; //Blue
Color threshold = { 255, 155, 15 }; //Orange
Color warning = { 255, 0, 0 }; //Red

auto timer = timer_create_default();
auto task = timer.in(1000, [](void*) -> bool { return false; });

int ledCount = 60;
int remainingLoop = 0;

Adafruit_NeoPixel strip = Adafruit_NeoPixel(ledCount, D6_PIN, NEO_GRB + NEO_KHZ800);

void setColor(Adafruit_NeoPixel &adafruit, int index, Color color){
  adafruit.setPixelColor(index, color.red, color.green, color.blue);
}

String buildMenu(String selectedLabel){
  return menu(new MenuItem[8]{
    { "Ping", "/ping" },
    { "Timer - Default (10m)", "/timer?units=minutes&duration=10&threshold=2" },
    { "Timer - Pomodoro (25 min + 5 min)", "/timer?units=minutes&duration=30&threshold=5" },
    { "Timer - Food", "/timer?units=minutes&duration=45&threshold=10" },
    { "Light", "/light?red=100&green=150&blue=255&brightness=200" },
    { "Random", "/random" },
    { "Rainbow", "/rainbow" },
    { "Turn Off", "/off" }
  }, 8, selectedLabel);
}

String buildMenu(){
  return buildMenu("");
}

void handleRoot() {
  success(server, buildMenu(), "Hello from ESP8266");
}

bool decrease(){
  remainingLoop--;
  setColor(strip, remainingLoop, off);
  return true;
}

struct TimerInfo{
  int unitsInMillis;
  int duration;
  int threshold;
};
TimerInfo parseTimerParams(ESP8266WebServer &espServer);
TimerInfo parseTimerParams(ESP8266WebServer &espServer){
  TimerInfo info = {0, 0, 0};
  
  for (uint8_t i = 0; i < server.args(); i++) {
    if (server.argName(i).startsWith("unit"))
    {
      String unitInput = server.arg(i);
      if(unitInput.startsWith("sec")){
        info.unitsInMillis = 1000;
      }else if(unitInput.startsWith("min")){
        info.unitsInMillis = 60000;
      }else{
        badRequest(server, buildMenu(), "The units should be seconds or minutes");
      }
    }

    if (server.argName(i).startsWith("duration")){
      info.duration = server.arg(i).toInt();
    }

    if (server.argName(i).startsWith("threshold")){
      info.threshold = server.arg(i).toInt();
    }
  }

  if(info.threshold >= info.duration){
    badRequest(espServer, buildMenu(), "The threshold should be lower than duration.");
  }

  return info;
}

void handleTimer() {
  timer.cancel(task);

  TimerInfo timerInfo = parseTimerParams(server);
  remainingLoop = ledCount;
  int tempoInMillis = (timerInfo.duration * timerInfo.unitsInMillis) / ledCount;
  task = timer.every(tempoInMillis, (bool(*)(void*))decrease);
  
  int ledThreshold = (timerInfo.threshold * ledCount) / timerInfo.duration;
  for (int i = 0; i < ledCount; i++ ) {
    if(i < ledThreshold){
      setColor(strip, i, threshold);
    }else{
      setColor(strip, i, normal);
    }
  }
  strip.setBrightness(200);
  strip.show(); 

  int durationInSec = (timerInfo.duration * timerInfo.unitsInMillis) / 1000;
  String timerDetails  = "Timer : "
    + String(durationInSec / 60) + "min "
    + String(durationInSec % 60) + "sec";
  success(server, buildMenu("Timer - Default (10m)"), timerDetails);
}

struct LightInfo{
  Color color;
  int brightness;
};
LightInfo parseLightParams(ESP8266WebServer &espServer);
LightInfo parseLightParams(ESP8266WebServer &espServer){
  LightInfo info = { defaultLight, 50 };
  
  for (uint8_t i = 0; i < server.args(); i++) {
    if (server.argName(i) == "red"){
      info.color.red = server.arg(i).toInt();
    }

    if (server.argName(i) == "green"){
      info.color.green = server.arg(i).toInt();
    }

    if (server.argName(i) == "blue"){
      info.color.blue = server.arg(i).toInt();
    }

    if (server.argName(i).startsWith("brightness")){
      info.brightness = server.arg(i).toInt();
    }
  }

  if(info.brightness < 0 || info.brightness > 250){
    badRequest(espServer, buildMenu("Light"), "The brightness should be between 0 and 250.");
  }

  return info;
}

void handleLight() {
  timer.cancel(task);

  LightInfo lightInfo = parseLightParams(server);
  for (byte i = 0; i < ledCount; ++i ) {
    setColor(strip, i, lightInfo.color);
  }
  strip.setBrightness(lightInfo.brightness);
  strip.show();

  success(server, buildMenu("Light"), "Light is on");
}

bool randomStrip(){
  Color randomColor = {
    (byte)random(0, 255),
    (byte)random(0, 255),
    (byte)random(0, 255)
  };
  for(int i = 0; i < ledCount; ++i){
    setColor(strip, i, randomColor);
  }
  strip.setBrightness(random(50, 200));
  strip.show(); 
  return true;
}

void handleRandom() {
  timer.cancel(task);

  long tempoInMillis = random(500, 3000);
  task = timer.every(tempoInMillis, (bool(*)(void*))randomStrip);
  
  success(server, buildMenu("Random"), "I'm shuffling...");
}

bool rainbowStrip(){
  byte red = 250;
  byte green = 0;
  byte blue = 0;

  for(int i = 0; i < ledCount; ++i){
    if(red == 250 && green < 250 && blue == 0){
      green += 25;
    }else if(red > 0 && green == 250 && blue == 0){
      red -= 25;
    }else if(red == 0 && green == 250 && blue < 250){
      blue += 25;
    }else if(red == 0 && green > 0 && blue >= 250){
      green -= 25;
    }else if(red < 250 && green == 0 && blue == 250){
      red += 25;
    }else if(red == 250 && green == 0 && blue > 0){
      blue -= 25;
    }

    Color color = { red, green, blue };
    setColor(strip, (remainingLoop + i) % ledCount, color);
  }
  strip.setBrightness(200);
  strip.show(); 
  remainingLoop++;
  return true;
}

void handleRainbow() {
  timer.cancel(task);

  long tempoInMillis = 100;
  remainingLoop = 0;
  task = timer.every(tempoInMillis, (bool(*)(void*))rainbowStrip);
  
  success(server, buildMenu("Rainbow"), "Somewhere over the ...");
}

void handleOff() {
  timer.cancel(task);
  
  for (byte i = 0; i < ledCount; ++i ) {
    setColor(strip, i, off);
  }
  strip.setBrightness(0);
  strip.show(); 

  success(server, buildMenu("Turn Off"), "Il va faire tout noir!");
}

void handleNotFound() {
  fileNotFound(server, buildMenu());
}

void setup(void) {
  Serial.begin(115200);
  strip.begin();
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.println("");

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  if (MDNS.begin("esp8266")) {
    Serial.println("MDNS responder started");
  }

  server.on("/", handleRoot);
  server.on("/ping", []() { success(server, buildMenu("Ping"), "I'm Alive"); });
  server.on("/timer", handleTimer);
  server.on("/light", handleLight);
  server.on("/random", handleRandom);
  server.on("/rainbow", handleRainbow);
  server.on("/off", handleOff);

  server.onNotFound(handleNotFound);

  server.begin();
  Serial.println("HTTP server started");
  randomSeed(317);
}

void loop(void) {
  server.handleClient();
  timer.tick();
  strip.show();
  MDNS.update();
}
