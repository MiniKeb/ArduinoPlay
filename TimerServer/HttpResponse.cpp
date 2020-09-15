#include <Arduino.h>
#include <ESP8266WebServer.h>
#include "Html.h"


void response(ESP8266WebServer &espServer, int httpStatusCode, String menu, String content){
  String htmlResponse = html(new String[2]{
    menu,
    content
  }, 2);
  espServer.send(httpStatusCode, "text/html", htmlResponse);
}

void badRequest(ESP8266WebServer &espServer, String menu, String errorMessage){
  response(espServer, 400, menu, error("Bad Request", errorMessage));
}

void fileNotFound(ESP8266WebServer &espServer, String menu){
  response(espServer, 404, menu, error("Bad Request"));
}

void notImplemented(ESP8266WebServer &espServer, String menu, String actionName){
  response(espServer, 404, menu, error("File Not Found", actionName +" - Not Implemented Yet"));
}

void success(ESP8266WebServer &espServer, String menu, String htmlContent){
  response(espServer, 200, menu, content(htmlContent));
}
