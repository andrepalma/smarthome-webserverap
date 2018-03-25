
#include <ESP8266WebServer.h>


ESP8266WebServer server(80);   //instantiate server at port 80 (http port)

String page = "";
String text = "";
String luxdata;
int coverPos;
String dhtdata;
String pirdata;

void webserverSetup(){
 // Wait for connection
 while (WiFi.status() != WL_CONNECTED) {
 delay(500);
}

 Serial.print("Webserver connected to ");
 Serial.println(ssid);

 server.on("/data.txt", [](){
   text = (String)luxdata;
   server.send(200, "text/html", text);
 });
 server.on("/", [](){
   page = "<h1>Sensor Web Server</h1>\r\n\r\n";
   page += "<h2>Cover Pos:</h2> <h2 id=\"coverPos\">""</h2>\r\n";
   page += "<h2>DHT:</h2> <h2 id=\"dhtdata\">""</h2>\r\n";
   page += "<h2>PIR:</h2> <h2 id=\"pirdata\">""</h2>\r\n";
   page += "<h2>Lux:</h2> <h2 id=\"luxdata\">""</h2>\r\n";
   page += "<script>\r\n";
   page += "var x = setInterval(function() {loadData(\"data.txt\",updateData)}, 1000);\r\n";
   page += "function loadData(url, callback){\r\n";
   page += "var xhttp = new XMLHttpRequest();\r\n";
   page += "xhttp.onreadystatechange = function(){\r\n";
   page += " if(this.readyState == 4 && this.status == 200){\r\n";
   page += " callback.apply(xhttp);\r\n";
   page += " }\r\n";
   page += "};\r\n";
   page += "xhttp.open(\"GET\", url, true);\r\n";
   page += "xhttp.send();\r\n";
   page += "}\r\n";
   page += "function updateData(){\r\n";
   page += " document.getElementById(\"coverPos\").innerHTML = this.responseText;\r\n";
   page += " document.getElementById(\"dhtdata\").innerHTML = this.responseText;\r\n";
   page += " document.getElementById(\"pirdata\").innerHTML = this.responseText;\r\n";
   page += " document.getElementById(\"luxdata\").innerHTML = this.responseText;\r\n";
   page += "}\r\n";
   page += "</script>\r\n";
   server.send(200, "text/html", page);
});

 server.begin();
 Serial.println("Web server started!");
}

void webserverLoop(){
 coverPos = gv_coverPos;
 dhtdata = gv_dhtdata;
 pirdata = gv_pirdata;
 luxdata = gv_luxdata;

 // delay(1000);
 server.handleClient();
}
