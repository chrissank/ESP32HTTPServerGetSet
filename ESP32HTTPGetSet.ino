#include <WiFi.h>
#include <AsyncTCP.h> // Download on Github
#include <ESPAsyncWebServer.h> // Download on Github
#include <ArduinoJson.h> // import from Arduino IDE

AsyncWebServer server(80); 

StaticJsonDocument<200> doc;

void configureJsonDocument() {
  doc["active"] = false;
}

void setup() {
  Serial.begin(9600);

  WiFi.mode(WIFI_STA);
  WiFi.disconnect();

  delay(100);

  WiFi.begin("<SSID>", "<Password>");

  while (WiFi.status() != WL_CONNECTED) {
    delay(100);
  }

  delay(100);

  Serial.println("WiFi Info: ");
  Serial.println(WiFi.localIP()); // this is the IP address you'll use to make requests to

  configureJsonDocument();

  server.on("/get", HTTP_GET, [] (AsyncWebServerRequest *request) {
    String response;
    serializeJson(doc, response);
    request->send(200, "application/json", response); 
  });

  server.on("/set", HTTP_POST , [] (AsyncWebServerRequest *request) {
    String field;
    String val;
    if (request->hasParam("value") && request->hasParam("field")) {
      field = request->getParam("field")->value();
      val = request->getParam("value")->value();

      if(val == "true") {
        doc[field] = true;
      } else if(val == "false") {
        doc[field] = false;
      } else if(isValidNumber(val)) {
        doc[field] = val.toInt();
      } else {
        doc[field] = val;
      }
      
      request->send(200, "text/plain", "Success"); 
    } else {
      request->send(400, "text/plain", "Field or value not provided");  
    }
  });

  server.onNotFound(
  
  server.begin();
  Serial.println("Server initialized"); 
}

void loop() {
  delay(100);

//  check state of variables. e.g:
//  
//  if(doc["active"] == true) {
//    digitalWrite(activePin, HIGH);
//  } else {
//    digitalWrite(activePin, LOW);
//  }
  
}

boolean isValidNumber(String str ){
  bool isValid = true;
  for(byte i=0; i < str.length(); i++)
  {
    if(!isDigit(str.charAt(i))) {
      isValid = false;
      break;
    }
  }
  return isValid;
}
