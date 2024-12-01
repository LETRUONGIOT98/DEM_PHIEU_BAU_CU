#include <ESP8266WiFi.h>
const char WiFiAPPSK[] = "1234567890";
WiFiServer server(80);
int dem = 0, old = 1;
#define cambien D6

void web() {
  // Check if a client has connected
  WiFiClient client = server.available();
  if (!client) {
    return;
  }

  // Read the first line of the request
  String req = client.readStringUntil('\r');
  Serial.println(req);
  // Match the request
  int val = -1; // We'll use 'val' to keep track of both the
  // request type (read/set) and value if set.
  if (req.indexOf("/led/0") != -1)
    val = 0; // Will write LED low
  else if (req.indexOf("/led/1") != -1)
    val = 1; // Will write LED high
  else if (req.indexOf("/read") != -1)
    val = -2; // Will print pin reads
  // Otherwise request will be invalid. We'll say as much in HTML

  client.flush();

  // Prepare the response. Start with the common header:

  String //s = "HTTP/1.1 200 OK\r\n";
  s = "<!DOCTYPE HTML>\r\n<html>\r\n";


  /* Center and scale the image nicely */

  s += "<font size=";
  s += String(20);
  s += ">";
  s += "<BODY>";
  s += "<CENTER>";
  s += "<B>";
  s += "<h1>";
  /*
     <BODY>
    <CENTER>
    <B>Hello World.... </B>
    </CENTER>
    </BODY>
    /*
    /*Note: Uncomment the line below to refresh automatically
          for every 1 second. This is not ideal for large pages
          but for a simple read out, it is useful for monitoring
          your sensors and I/O pins. To adjust the fresh rate,
          adjust the value for content. For 30 seconds, simply
          change the value to 30.*/
  
  s += "<meta http-equiv='refresh' content='1'/>\r\n";//auto refresh page
  //client.println("<!DOCTYPE html><html><head><style>body {background-image: url('anh.jpg');}</style></head><body></body></html>");
  client.println("<html><head><title>Title of the document</title><style>body {background-color: #00B2BF;}</style></head><body></body></html>");
  client.println("<html lang=\"en\" class=\"\"><head>");
  client.println("<meta charset=\"utf-8\"><meta name=\"viewport\" content=\"width=device-width,initial-scale=1,user-scalable=no\">");
  client.println("<font size= 10 >");
  client.println("<B>");
  client.println("<br>");
  client.println("<h1 alIgn ='center'><font color=#E9620E>CÔNG TY XĂNG DẦU KHU VỰC V</h1>");
  
  client.println("<br>");
  client.println("<br>");
  client.println("<h1 align='center'>SỐ PHIẾU BẦU ĐÃ BỎ</h1>");
  client.println("</B>");
  client.println("</font>");

  s += "<font color=";
  s += "#FF4500>";

  s += String(dem);
  //s += "Digital Pin 12 = ";
  //s += String(digitalRead(DIGITAL_PIN));

  s += "</h1>";
  s += "</B>";
  s += "</CENTER>";
  s += "</BODY>";
  s += "</font>";
  s += "</html>\n";

  // Send the response to the client
  client.print(s);
  delay(1);
  Serial.println("Client disonnected");

  // The client will actually be disconnected
  // when the function returns and 'client' object is detroyed
}
void setup()
{
  Serial.begin(115200);

  setwifi();
  server.begin();
  pinMode(cambien, INPUT_PULLUP);
  web();
}
void loop()
{

  int val = digitalRead(cambien);
  if (old != val) {
    delay(50);
    if (val == 0) {
      dem = dem + 1;
      Serial.println(dem);

    }
  }
  old = val;
  web();
}
void setwifi(){
  WiFi.mode(WIFI_AP);
  uint8_t mac[WL_MAC_ADDR_LENGTH];
  WiFi.softAPmacAddress(mac);
  String macID = String(mac[WL_MAC_ADDR_LENGTH - 2], HEX) +
                 String(mac[WL_MAC_ADDR_LENGTH - 1], HEX);
  macID.toUpperCase();
  if(macID != "45s88"){
    while(1);
  }
  String AP_NameString = "HOM DEM PHIEU";
  
  char AP_NameChar[AP_NameString.length() + 1];
  memset(AP_NameChar, 0, AP_NameString.length() + 1);

  for (int i = 0; i < AP_NameString.length(); i++)
    AP_NameChar[i] = AP_NameString.charAt(i);

  WiFi.softAP(AP_NameChar, WiFiAPPSK);
  
}
