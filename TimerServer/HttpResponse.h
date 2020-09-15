#ifndef HttpResponse_h
#define HttpResponse_h
#include <Arduino.h>
#include <ESP8266WebServer.h>
#include "Html.h"

void response(ESP8266WebServer &espServer, int httpStatusCode, String menu, String content);
void badRequest(ESP8266WebServer &espServer, String menu, String errorMessage);
void fileNotFound(ESP8266WebServer &espServer, String menu);
void notImplemented(ESP8266WebServer &espServer, String menu, String actionName);
void success(ESP8266WebServer &espServer, String menu, String htmlContent);

#endif// #endif