#include <WiFi.h>
#include <WebServer.h>             // Libreria necesaria para crear un servidor web

/*                                            // En caso de ubicar el servidor dentro de nuestra red
const char* ssid = "NOMBRE_DE_RED" ;          // Objeto con el nombre de la red
const char* password = "PASSWORD" ;           // Objeto con el Pasword de la red
*/
const char* ssid = "FeloNet";      // Constante de caracteres para representar la SSID (nombre de la red)
const char* password = "Felo1234"; // Constante de caracteres para representar la pasword de la red 

WebServer server (80);             // Definiendo el puerto para el protocolo http "80" 

const byte ledPin = 19;            // Definiendo el pin para el led
bool state = false;                // Definiendo un estado booleano

void setup (){
  Serial.begin(115200);                    // Inicializando el monitor serial

  pinMode(ledPin, OUTPUT);                 // Definiendo como salida el pin del led
  digitalWrite(state, HIGH);               // Desactivando el estado
  delay(100);

  //WiFi.begin(ssid, password);            // Funcion para iniciar la coneccion a la red (nombre de la red , passwd de la red)
  //Serial.println(WiFi.localIP());        // Imprime la direccion IP asignada por el router

  // Definido como punto de acceso
  WiFi.softAP(ssid,password,1,false,5);    // Configurando el punto de acceso tiene parametros adicioneles revisar la documentacion
  IPAddress ip = WiFi.softAPIP();          // La funcion WiFi.softAPIP define la ip por defecto
  
  Serial.print("Nombre de mi red: ");      // Imprime el texto en el monitor serial
  Serial.println(ssid);                    // Imprime el texto en el monitor serial
  Serial.print("La direccion IP es: ");    // Imprime el texto en el monitor serial
  Serial.println(ip);                      // Imprime en el monitor serial la direccion IP asignada para conocimiento del usuario

  server.on("/", handleRoot);              // Responder cualquier peticion que haga un cliente hacia la raiz
  server.on("/ledon", handleledon);        // Responder la peticion led on a la raiz
  server.on("/ledoff", handleledoff);      // Responder la peticion led off a la raiz
  server.onNotFound(handleNotFound);       // Responder la peticon not found 

  server.begin();                          // Inicializar el servidor 
  Serial.println("Servidor HTTP iniciado");// Imprime el texto en el monitor serial
  delay(150);
}

void loop(){
  server.handleClient();                   // Funcion para gestionar a los clientes 
  if (state){
    digitalWrite(ledPin, HIGH); 
  }
  else{
    digitalWrite(ledPin, LOW);
  }
}

// Respuesta en peticion a la raiz con esqueleto html
String answer = "<!DOCTYPE html>\n<html lang=\"en\">\n  <head>\n    <meta charset = \"UTF-8\">\n    <meta name=\"viewport\" content = \"width=device-width, initial-scale=1.0\">\n    <title>LED CONTROL</title>\n\n    <style>\n        body{\n     background-color: black;\n     margin: 0px auto;\n          text-align: center;\n          font-family: Helvetica;\n        }\n\n        #title{\n          margin-top: 50px;\n          margin-bottom: 15px;\n          color: white;\n        }\n\n        #subtitle{\n          margin-top: 0;\n          margin-bottom: 25px;\n          color: dimgray;\n        }\n\n        .onBtn{\n          background-color: #44c767;\n          border-radius: 28px;\n          border: 1px solid #18ab29;\n          display: inline-block;\n          cursor: pointer;\n          color: #ffffff;\n          font-family: Arial;\n          font-size: 17px;\n          padding: 16px 35px;\n          text-decoration: none;\n          text-shadow: 0px, 1px, 0px, #2f6627;\n          margin-right: 50px;\n        }\n\n        .onBtn:hover{\n          background-color: #64e335;\n        }\n\n        .onBtn:active{\n          position-color:relative;\n          top:1px;\n        }\n\n        .offBtn{\n          background-color: #f05d67;\n          border-radius: 28px;\n          border: 1px solid #e84165;\n          display: inline-block;\n          cursor: pointer;\n          color: #ffffff;\n          font-family: Arial;\n          font-size: 17px;\n          padding: 16px 35px;\n          text-decoration: none;\n          text-shadow: 0px, 1px, 0px, #7a1515;\n        }\n        \n        .offBtn:hover{\n          background-color: #f22954;\n        }\n\n        .offBtn:active{\n          position-color:relative;\n          top:1px;\n        }\n    </style>\n\n  </head>\n<body>\n  <div>\n     <h1 id=\"title\"> SERVIDOR ESP32 ACCES-POINT</h1>\n     <h3 id=\"subtitle\"> Control ON/OFF</h3>\n  </div>\n\n  <a href=\"/ledon\" class=\"onBtn\"> ON </a>\n  <a href=\"/ledoff\" class=\"offBtn\"> OFF </a>\n</body>\n\n</html>\n";

void handleRoot(){
  server.send(200,"text/html",answer);     // Funcion para enviar una respuesta al servidor (codigo de estado, formato de la respuesta, valor)
}

void handleledon(){
  state = true ; 
  server.send(200,"text/html",answer);     // Funcion para enviar una respuesta al servidor (codigo de estado, formato de la respuesta, valor)
}

void handleledoff(){
  state = false ;
  server.send(200,"text/html",answer);     // Funcion para enviar una respuesta al servidor (codigo de estado, formato de la respuesta, valor)
}

void handleNotFound(){
  server.send(404,"text/html","Error 404 NOT FOUND");     // Funcion para enviar una respuesta al servidor de codigo 404 (codigo de estado, formato de la respuesta, valor)
}
