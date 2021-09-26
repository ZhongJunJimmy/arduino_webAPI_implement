#include <EtherCard.h>
#include <DHT.h>

//Constants
#define DHTPIN 7     // what pin we're connected to
#define DHTTYPE DHT22   // DHT 22  (AM2302)
//#define DEBUG
DHT dht(DHTPIN, DHTTYPE); //// Initialize DHT sensor for normal 16mhz Arduino

float hum;  //Stores humidity value
float temp; //Stores temperature value

// TCP/IP send/recv buffer:
byte Ethernet::buffer[512];

// Ethernet MAC address - must be unique on the network!
static byte myMAC[] = { 0x74, 0x69, 0x69, 0x2D, 0x30, 0x31 };

const char s200[] PROGMEM = "HTTP/1.0 200 OK\r\n";
const char s503[] PROGMEM = "HTTP/1.0 503 Service Unavailable\r\n";

const char headers[] PROGMEM = "Server: Arduino Uno\r\n"
                               "Content-Type: application/json\r\n"
                               "\r\n";

const char b503[] PROGMEM = "{\"error\":\"service_unavailable\"}";

void setup(){
  Serial.begin(57600);
  dht.begin();
  if (!ether.begin(sizeof Ethernet::buffer, myMAC)) {
    // OOPS, failed to initialise the ethernet board!
    while(1);
  }
  ether.dhcpSetup();
  
}
  
void loop(){
  hum = dht.readHumidity();
  temp= dht.readTemperature();
  // Construct a response:
  char body[4096];
  word len = ether.packetReceive();
  word pos = ether.packetLoop(len);
  int request;

  // Wait for an incoming TCP packet, but ignore its contents.
  if (!pos) {
    return;
  }

  char* data = (char *) Ethernet::buffer + pos;
#ifdef DEBUG
  //Serial.println(data);
  Serial.print("humidity: ");
  Serial.println(hum);
  Serial.print("temperature: ");
  Serial.println(temp);
#endif
  if (strncmp("GET /getdht",data,11) == 0){
    request += sprintf(body+request, "%s", "{\"roomInfo\":{\"humidity\":");
    request += sprintf(body+request, "%s", dtostrf(hum, 0, 2, body+request));
    request += sprintf(body+request, "%s", ",\"temperature\":");
    request += sprintf(body+request, "%s", dtostrf(temp, 0, 2, body+request));
    request += sprintf(body+request, "%s", "}}");

    respond(body, ++request);
  }
    
  
}

void respond(char *body, int size) {
  unsigned int offset;
  memcpy_P(ether.tcpOffset() + offset, s200,    sizeof s200);    offset += sizeof s200 - 1;
  memcpy_P(ether.tcpOffset() + offset, headers, sizeof headers); offset += sizeof headers - 1;
  memcpy  (ether.tcpOffset() + offset, body,    size);           offset += size - 1;
  ether.httpServerReply(offset);
}

void error_503() {
  unsigned int offset;
  memcpy_P(ether.tcpOffset() + offset, s503,    sizeof s503);    offset += sizeof s503 - 1;
  memcpy_P(ether.tcpOffset() + offset, headers, sizeof headers); offset += sizeof headers - 1;
  memcpy_P(ether.tcpOffset() + offset, b503,    sizeof b503);    offset += sizeof b503 - 1;
  ether.httpServerReply(offset);
}
