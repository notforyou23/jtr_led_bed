#include <Ethernet.h>
#include <SPI.h>
#include <Adafruit_NeoPixel.h>

#define PIN 6

// Parameter 1 = numbejtr_led_connect_Final3r of pixels in strip
// Parameter 2 = pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
Adafruit_NeoPixel strip = Adafruit_NeoPixel(380, PIN, NEO_GRB + NEO_KHZ800);

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
          client.print("<header><body bgcolor=gray>");
          client.print("<div style=color:#FFFFFF;width:960px;padding:5px;border:5px;margin:0px><font size=+7><center><font face=helvetica>J&M LED_BEDv.23</font></center></div>");
          client.print("<div style=width:960px;height:2pxbackground:white;border:0px;margin:0px></div>");
                  
                   client.print("<hr>");
                            client.print("<hr>");

     //green     
          client.print("<div style=width:960px;height:150px;padding:5px;background:#33CC00;border:5px;margin:3px;border-radius:25px>");
          client.print("<center>");
          client.print("<form METHOD=get action=\"");

          client.println("\">");
          client.println("<input type=hidden name=click value=0>");
          client.println("<input type=submit value=\"GREEN\"></form>"); 
          client.print("<p></center></div>");
          
                    client.print("<hr>");
                             client.print("<hr>");
          
        //blue  
          client.print("<div style=width:960px;height:150px;padding:5px;background:#0000FF;border:5px;margin:3px;border-radius:25px>");
          client.print("<center>");
          client.print("<form METHOD=get action=\"");
 
          client.println("\">");
          client.println("<input type=hidden name=click value=1>");
          client.println("<input type=submit value=\"BLUE\"></form>"); 
          client.print("<p></center></div>");
          
                   client.print("<hr>");
                            client.print("<hr>");
          
        //orange
          client.print("<div style=width:960px;height:150px;padding:5px;background:#FF9933;border:5px;margin:3px;border-radius:25px>");
          client.print("<center>"); 
          client.print("<form METHOD=get action=\"");
 
          client.println("\">");
          client.println("<input type=hidden name=click value=2>");
          client.println("<input type=submit value=\"ORANGE\"></form>"); 
          client.print("<p></center></div>");  
          
                   client.print("<hr>");
                            client.print("<hr>");
          
          
        //purple
          client.print("<div style=width:960px;height:150px;padding:5px;background:#CC00FF;border:5px;margin:3px;border-radius:25px>");
          client.print("<center>"); 
          client.print("<form METHOD=get action=\"");

          client.println("\">");
          client.println("<input type=hidden name=click value=3>");
          client.println("<input type=submit value=\"PURPLE\"></form>"); 
          client.print("<p></center></div>");
          
                   client.print("<hr>");
                            client.print("<hr>");
                    
        //white
          client.print("<div style=width:960px;height:150px;padding:5px;background:#FFFFFF;border:5px;margin:3px;border-radius:25px>");
          client.print("<center>"); 
          client.print("<form METHOD=get action=\"");
 
          client.println("\">");
          client.println("<input type=hidden name=click value=5>");
          client.println("<input type=submit value=\"WHITE\"></form>"); 
          client.print("<p></center></div>");
          
                   client.print("<hr>");
                            client.print("<hr>");
          
        //rainbow
          client.print("<div style=width:960px;height:150px;padding:5px;background:#D8F5A7;border:5px;margin:3px;border-radius:25px>");
          client.print("<center>"); 
          client.print("<form METHOD=get action=\"");
 
          client.println("\">");
          client.println("<input type=hidden name=click value=6>");
          client.println("<input type=submit value=\"RAINBOW\"></form>"); 
          client.print("<p></center></div>");
          
                   client.print("<hr>");
                            client.print("<hr>");
          
          //rainbowcycle
          client.print("<div style=width:960px;height:150px;padding:5px;background:#8F00FF;border:5px;margin:3px;border-radius:25px>");
          client.print("<center>"); 
          client.print("<form METHOD=get action=\"");
 
          client.println("\">");
          client.println("<input type=hidden name=click value=7>");
          client.println("<input type=submit value=\"RAINBOW~CYCLE\"></form>"); 
          client.print("<p></center></div>");
          
                   client.print("<hr>");
                            client.print("<hr>");
                                     client.print("<hr>");
                                              client.print("<hr>");
          
        //off
          client.print("<div style=width:960px;height:150px;padding:5px;background:#000000;border:5px;margin:3px;border-radius:25px>");
          client.print("<center>"); 
          client.print("<form METHOD=get action=\"");

          client.println("\">");
          client.println("<input type=hidden name=click value=4>");
          client.println("<input type=submit value=\"OFF\"></form>"); 
          client.print("<p></center></div>");
          client.print("<div style=width:960px;background:white;border:0px;margin:3px;border-radius:25px></div>");
          
                   client.print("<hr>");
                            client.print("<hr>");
                                     client.print("<hr>");
                                              client.print("<hr>");
                                                       client.print("<hr>");
                                                       
         client.print("<p>jason t regina 2013.  peace.  _ <p>");
          
  //delay(30);  //maybe remove - changed from 300
          
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
           colorWipe(strip.Color(0, 0, 255), 0); // Blue
           break;
          }
          if(c == '2') {
           colorWipe(strip.Color(250, 40, 0), 0); // Orange
           break;
          }
          if(c == '3') {
           colorWipe(strip.Color(200, 0, 255), 0); // Purple
           break;
          }
           if(c == '4') {
            colorWipe(strip.Color(0, 0, 0), 0); // off 
           break;
        }
           if(c == '5') {
            colorWipe(strip.Color(224, 224, 224), 0); // white 
           break; 
           }
           if(c == '6') {
           rainbow(0); //rainbow
           delay(10);
           break;
           }
           if(c == '7') {
           rainbowCycle(0); //rainbowcycle
           delay(5);
           rainbowCycle(0);
           delay(5);
           rainbowCycle(0);
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
