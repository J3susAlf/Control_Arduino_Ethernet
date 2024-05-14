
#include <SPI.h>
#include <Ethernet.h>


byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };   //Direccion Fisica MAC
byte ip[] = { 172, 20, 10, 10  };                       // IP Local que usted debe configurar 
byte gateway[] = { 172, 20, 10, 3 };                   // Puerta de enlace
byte subnet[] = { 255, 255, 255, 0 };                  //Mascara de Sub Red
EthernetServer server(80);                             //Se usa el puerto 80 del servidor     
String readString;

void setup() {

  Serial.begin(9600);  // Inicializa el puerto serial 
   while (!Serial) {   // Espera a que el puerto serial sea conectado, Solo necesario para el Leonardo
    ; 
  }
  pinMode(2,OUTPUT); 
  pinMode(3,OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5,OUTPUT);
  
 
  Ethernet.begin(mac, ip, gateway, subnet); // Inicializa la conexion Ethernet y el servidor
  server.begin();
  Serial.print("El Servidor es: ");
  Serial.println(Ethernet.localIP());    // Imprime la direccion IP Local
}


void loop() {
  // Crea una conexion Cliente
  EthernetClient client = server.available();
  if (client) {
      boolean currentLineIsBlank = true;
    while (client.connected()) {   
      if (client.available()) {
        char c = client.read();
     
        //Lee caracter por caracter HTTP
        if (readString.length() < 100) {
          //Almacena los caracteres a un String
          readString += c;
          
         }

         // si el requerimiento HTTP fue finalizado
         if (c == '\n' && currentLineIsBlank) {          
           Serial.println(readString); //Imprime en el monitor serial
     
           client.println("HTTP/1.1 200 OK");           //envia una nueva pagina en codigo HTML
           client.println("Content-Type: text/html");
           client.println("Connection: close"); 
	         client.println("Refresh: 2");  // refresca la pagina automaticamente cada 3 segundos
           client.println();     
           client.println("<HTML>");
           client.println("<HEAD>");
           client.println("<TITLE>Ethernet Arduino</TITLE>");
           client.println("<style>");
           client.println("a {");
           client.println("  text-decoration: none;");
           client.println("}");
           client.println("body {");
           client.println("  text-align: center;");
           client.println("}");
           client.println("</style>");
           client.println("</HEAD>");
           client.println("<BODY>");
           client.println("<hr />");
           client.println("<H1>Arduino Ethernet Shield Controlador de leds</H1>");
           client.println("<br />");  
           
           client.println("<br />"); 
           client.println("<a href=\"/?button3on\"\"> Encender Pin3</a> ");
           client.println(" | | | ");
           client.println("<a href=\"/?button3off\"\"> Apagar Pin3</a><br /> ");   
           client.println("<br />");
           
           client.println("<br />"); 
           client.println("<a href=\"/?button4on\"\"> Encender Pin4</a> ");
           client.println(" | | | ");
           client.println("<a href=\"/?button4off\"\"> Apagar Pin4</a><br /> ");   
           client.println("<br />");
           
           client.println("<br />");  
           client.println("<a href=\"/?button5on\"\"> Encender Pin5</a>");
           client.println(" | | | ");
           client.println("<a href=\"/?button5off\"\"> Apagar Pin5</a><br />");   
           client.println("<br />");
          
           client.println("<br />");
           client.println("<H1>Estado de los pines</H1>");
           
           client.println("<H2>Monitorea A2-A4</H2>");
           client.println("<br />");  
           
           for (int pin = 3; pin <= 5; pin++) {
             int estado = digitalRead(pin);
             client.println("Estado del pin: ");   // Lee el estado del pin
             client.print(pin); 
             client.print(estado ? " Encendido" : " Apagado");
            client.println("<br />"); 
           }
           client.println("<br />");  
           client.println("</BODY>");
           client.println("</HTML>");
     if (c == '\n') {
           currentLineIsBlank = true;
        } 
        else if (c != '\r') {
           currentLineIsBlank = false;
        }
           delay(15);
           //detiene el cliente servidor
           client.stop(); 
           
           //control del arduino si un boton es presionado
                   
           
           if (readString.indexOf("?button3on") >0){
               digitalWrite(3, HIGH);
           }
           if (readString.indexOf("?button3off") >0){
               digitalWrite(3, LOW);
           }
           
           
           if (readString.indexOf("?button4on") >0){
               digitalWrite(4, HIGH);
           }
           if (readString.indexOf("?button4off") >0){
               digitalWrite(4, LOW);
           }
           
            if (readString.indexOf("?button5on") >0){
               digitalWrite(5, HIGH);
           }
           if (readString.indexOf("?button5off") >0){
               digitalWrite(5, LOW);
           }
           
            // Limpia el String(Cadena de Caracteres para una nueva lectura
            readString="";  
           
         }
       }
    }
}
}