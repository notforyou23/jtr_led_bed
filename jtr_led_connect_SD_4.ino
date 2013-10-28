#include <Ethernet.h>
#include <SPI.h>
#include <Adafruit_NeoPixel.h>
#include <SD.h>
#define REQ_BUF_SZ   60
#define PIN 6

// Parameter 1 = number of pixels in strip
// Parameter 2 = pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
Adafruit_NeoPixel strip = Adafruit_NeoPixel(480, PIN, NEO_GRB + NEO_KHZ800);

boolean reading = false;
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
IPAddress ip(192,168,1,234);
File webFile;               // the web page file on the SD card
char HTTP_req[REQ_BUF_SZ] = {0}; // buffered HTTP request stored as null terminated string
char req_index = 0;              // index into HTTP_req buffer
EthernetServer server(80);
//F

void setup() {
  // disable Ethernet chip
    pinMode(10, OUTPUT);
    digitalWrite(10, HIGH);
    
    Serial.begin(9600);       // for debugging
    
    // initialize SD card
    Serial.println("Initializing SD card...");
    if (!SD.begin(4)) {
        Serial.println("ERROR - SD card initialization failed!");
        return;    // init failed
    }
    Serial.println("SUCCESS - SD card initialized.");
    // check for index.htm file
    if (!SD.exists("index.htm")) {
        Serial.println("ERROR - Can't find index.htm file!");
        return;  // can't find index file
    }
    Serial.println("SUCCESS - Found index.htm file.");
    
    Ethernet.begin(mac, ip);  // initialize Ethernet device
    server.begin();           // start to listen for clients
}
void loop() {
  // Some example procedures showing how to display to the pixels:
  //colorWipe(strip.Color(250, 40, 0), 0); // Orange
  //colorWipe(strip.Color(200, 0, 255), 0); // Purple
  //colorWipe(strip.Color(0, 255, 0), 0); // Green
  //colorWipe(strip.Color(0, 0, 255), 0); // Blue
  //rainbow(0);
  //rainbowCycle(0);
  char *filename;
{


  
  checkForClient();
}
}
void checkForClient() {
  EthernetClient client = server.available();

  if (client) {
    boolean currentLineIsBlank = true;
    boolean sentHeader = false;

    while (client.connected()) {
      if (client.available()) {
        if(!sentHeader){
      Serial.println("\n");
 client.println("HTTP/1.1 200 OK");
          client.println("Content-Type: text/html");
          // client.println("Content-Type: image/png");
          client.println();
           webFile = SD.open("index.htm");        // open web page file
                        if (webFile) {
                            while(webFile.available()) {
                                client.write(webFile.read()); // send web page to client
                            }
                            webFile.close();
                            // display received HTTP request on serial port
                    //Serial.print(HTTP_req);
                    // reset buffer index and all buffer elements to 0
                    //req_index = 0;
                    //StrClear(HTTP_req, REQ_BUF_SZ);
                    break;
                }
        }
               
                
            } // end if (client.available())
        } // end while (client.connected())
        delay(1);      // give the web browser time to receive the data
        client.stop(); // close the connection
    } // end if (client)
  boolean currentLineIsBlank = true;
    boolean sentHeader = false;
 char c = client.read();
        if(reading && c == ' ') reading = false;
        if(c == '?') reading = true;
if(reading){
          //Serial.print(c);
          if(c == '0') {
           colorWipe(strip.Color(0, 255, 0), 0); // Green
            //break;
          }
          if(c == '1') {
           colorWipe(strip.Color(0, 0, 255), 0); // Blue
           //break;
          }
          if(c == '2') {
           colorWipe(strip.Color(255, 0, 0), 0); // Red
           //break;
          }
          if(c == '3') {
           colorWipe(strip.Color(250, 40, 0), 0); // Orange
           //break;
          }
           if(c == '4') {
            colorWipe(strip.Color(0, 0, 0), 0); // off 
           //break;
        }
    
         if (c == '\n' && currentLineIsBlank)  //break;
         if (c == '\n') {
          currentLineIsBlank = true;
        }else if (c != '\r') {
          currentLineIsBlank = false;
        }
      }
    

{
    delay(1); // give the web browser time to receive the data
    client.stop(); // close the connection:
  } 
}
 
// Fill the dots one after the other with a color
void colorWipe(uint32_t c, uint8_t wait) {
  for(uint16_t i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, c);
      strip.show();
      delay(wait);
  }
}

void rainbow(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256; j++) {
    for(i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel((i+j) & 255));
    }
    strip.show();
    delay(wait);
  }
}

// Slightly different, this makes the rainbow equally distributed throughout
void rainbowCycle(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256*5; j++) { // 5 cycles of all colors on wheel
    for(i=0; i< strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel(((i * 256 / strip.numPixels()) + j) & 255));
    }
    strip.show();
    delay(wait);
  }
}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  if(WheelPos < 85) {
   return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  } else if(WheelPos < 170) {
   WheelPos -= 85;
   return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  } else {
   WheelPos -= 170;
   return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }

}
