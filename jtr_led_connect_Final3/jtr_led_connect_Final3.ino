#include <Ethernet.h>
#include <SPI.h>
#include <Adafruit_NeoPixel.h>

#define PIN 6

// Parameter 1 = number of pixels in strip
// Parameter 2 = pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
Adafruit_NeoPixel strip = Adafruit_NeoPixel(240, PIN, NEO_GRB + NEO_KHZ800);

boolean reading = false;
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
IPAddress ip(192,168,1,234);

EthernetServer server(4200);

//F

void setup() {
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
  
  Serial.begin(9600);
  Ethernet.begin(mac, ip);
  server.begin();
  Serial.print("server is at ");
  Serial.println(Ethernet.localIP());
}

void loop() {
  // Some example procedures showing how to display to the pixels:
  //colorWipe(strip.Color(250, 40, 0), 0); // Orange
  //colorWipe(strip.Color(200, 0, 255), 0); // Purple
  //colorWipe(strip.Color(0, 255, 0), 0); // Green
  //colorWipe(strip.Color(0, 0, 255), 0); // Blue
  //rainbow(0);
  //rainbowCycle(0);
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
          client.println();
          client.print("<header><body bgcolor=#FFFFFF><h1><c><div style=color:#2B3856><font size=+5><font face=helvetica><left>jtr_LED_Connect v0.23</font></h1>");
          client.print("<left><div style=width:65%;height:2px;background:#232323;></div>");

     //green     
          client.print("<div style=width:65%;height:2px;background:#232323;></div>");
          client.print("<br><center>");
          client.print("<form METHOD=get action=\"");

          client.println("\">");
          client.println("<input type=hidden name=click value=0>");
          client.println("<input type=submit value=\"GrEeN\"></form>"); 
          client.print("<p></center>");
          
        //rainbowcycle  
          client.print("<div style=width:65%;height:2px;background:#232323;></div>");
          client.print("<br><center>");
          client.print("<form METHOD=get action=\"");
 
          client.println("\">");
          client.println("<input type=hidden name=click value=1>");
          client.println("<input type=submit value=\"RaIN\"></form>"); 
          client.print("<p></center>");
          
        //orange
          client.print("<div style=width:65%;height:2px;background:#232323;></div>");
          client.print("<br><center>");
          client.print("<form METHOD=get action=\"");
 
          client.println("\">");
          client.println("<input type=hidden name=click value=2>");
          client.println("<input type=submit value=\"OrAnGE\"></form>"); 
          client.print("<p></center>");  
          
          
        //blue
          client.print("<div style=width:65%;height:2px;background:#232323;></div>");
          client.print("<br><center>");
          client.print("<form METHOD=get action=\"");

          client.println("\">");
          client.println("<input type=hidden name=click value=3>");
          client.println("<input type=submit value=\"BlUE\"></form>"); 
          client.print("<p></center>");  
          
        //off
                  client.print("<div style=width:65%;height:2px;background:#232323;></div>");
          client.print("<br><center>");
          client.print("<form METHOD=get action=\"");

          client.println("\">");
          client.println("<input type=hidden name=click value=4>");
          client.println("<input type=submit value=\"OFF\"></form>"); 
          client.print("<p></center>");
          
  delay(30);  //maybe remove - changed from 300
          
          sentHeader = true;
        }

        char c = client.read();
        if(reading && c == ' ') reading = false;
        if(c == '?') reading = true;
        if(reading){
          Serial.print(c);
          if(c == '0') {
           colorWipe(strip.Color(0, 255, 0), 0); // Green
            break;
          }
          if(c == '1') {
           rainbow(0);  //Rainbow
           break;
          }
          if(c == '2') {
           colorWipe(strip.Color(250, 40, 0), 0); // Orange
           break;
          }
          if(c == '3') {
           colorWipe(strip.Color(0, 0, 255), 0); // Blue
           break;
          }
           if(c == '4') {
            colorWipe(strip.Color(0, 0, 0), 0); // off 
           break;
        }
    }
         if (c == '\n' && currentLineIsBlank)  break;
         if (c == '\n') {
          currentLineIsBlank = true;
        }else if (c != '\r') {
          currentLineIsBlank = false;
        }
      }
    }
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

