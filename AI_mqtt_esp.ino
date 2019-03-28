#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <Arduino.h>
#include <XPT2046.h>
#include <SPI.h>
#include <TFT_eSPI.h> // Hardware-specific library
#include "Free_Fonts.h"
#include "day.h"
#include "night.h"
#define TEXT "aA MWyz~12" // Text that will be printed on screen in any font
TFT_eSPI tft = TFT_eSPI();       // Invoke custom library

#define TFT_GREY 0x5AEB

// http://www.barth-dev.de/online/rgb565-color-picker/
#define LTBLUE    0xB6DF
#define LTTEAL    0xBF5F
#define LTGREEN         0xBFF7
#define LTCYAN    0xC7FF
#define LTRED           0xFD34
#define LTMAGENTA       0xFD5F
#define LTYELLOW        0xFFF8
#define LTORANGE        0xFE73
#define LTPINK          0xFDDF
#define LTPURPLE  0xCCFF
#define LTGREY          0xE71C

#define BLUE            0x001F
#define TEAL    0x0438
#define GREEN           0x07E0
#define CYAN          0x07FF
#define RED           0xF800
#define MAGENTA       0xF81F
#define YELLOW        0xFFE0
#define ORANGE        0xFD20
#define PINK          0xF81F
#define PURPLE    0x801F
#define GREY        0xC618
#define WHITE         0xFFFF
#define BLACK         0x0000

#define DKBLUE        0x000D
#define DKTEAL    0x020C
#define DKGREEN       0x03E0
#define DKCYAN        0x03EF
#define DKRED         0x6000
#define DKMAGENTA       0x8008
#define DKYELLOW        0x8400
#define DKORANGE        0x8200
#define DKPINK          0x9009
#define DKPURPLE      0x4010
#define DKGREY        0x4A49
XPT2046 touch(/*cs=*/ 4, /*irq=*/ 5);

 
String FORECAST = ""; 
String ICON = "sunny"; 
String TIME = "";
String DATE ="";
String STATION;
String ARTIST;
String SONG;

char copy[50];

String input1 ="/ai/onlight";
String input2 ="/ai/offlight";
String input3 ="/ai/time";
String input4 ="/ai/date";
String input5 ="/ai/clear";
String input6 ="/ai/station";
String input7 ="/ai/artist";
String input8 ="/ai/song";
String input9 ="/ai/standby";
String input10 ="/ai/icon";
String input11 ="/ai/forecast";

// Update these with values suitable for your network.

const char* ssid = "IOT";
const char* password = "";
const char* mqtt_server = "192.168.168.150";

WiFiClient espClient;
PubSubClient client(espClient);
long lastMsg = 0;
char msg[50];
int value = 0;


void setup() {
   Serial.begin(115200);
  tft.init();
  tft.fillScreen(BLACK);

  tft.setRotation(3);
 MyCroft();
  ;
pinMode(BUILTIN_LED, OUTPUT);     // Initialize the BUILTIN_LED pin as an output
tft.setFreeFont(TT1);
  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
 
}

void setup_wifi() {

  delay(10);
  // We start by connecting to a WiFi network
  Serial.println();
  tft.setCursor(0, 0);
  tft.setTextColor(CYAN);// tft.setTextSize(3);
  tft.println("Connecting to ");
  tft.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  tft.setCursor(0, 30);
  tft.setTextColor(BLUE);// tft.setTextSize(3);
  tft.println("IP address: ");
  tft.println(WiFi.localIP());
  
  
}

void callback(char* topic, byte* payload, unsigned int length) {
  
   if (input1 == topic){
     AI_listen();
 
}

//##############################  
if (input2 == topic){
  AI_ready();

} 

//##############################
 if (input3 == topic){
  TIME = "";

  for (int i=0;i<length;i++) {
     TIME +=  ((char)payload[i]);
  }
AI_time(TIME);
  
  }
  
  //##############################
if (input4 == topic){
 DATE = "";
  for (int i=0;i<length;i++) {
     DATE +=  ((char)payload[i]);  
  }
  AI_date(DATE);
} 

//##############################
if (input5 == topic){

   AI_finished();
} 

//##############################
if (input6 == topic){
  STATION = "";
  for (int i=0;i<length;i++) {
     STATION +=  ((char)payload[i]);  
  }
  AI_station(STATION);
} 

//##############################
if (input7 == topic){
ARTIST = "";
  for (int i=0;i<length;i++) {
     ARTIST +=  ((char)payload[i]);  
  }
  AI_META(ARTIST);
} 

//##############################
if (input8 == topic){
SONG = "";
  for (int i=0;i<length;i++) {
     SONG +=  ((char)payload[i]);  
  }
  AI_song(SONG);
} 

//##############################
if (input9 == topic){

  AI_standby();
} 

//##############################
if (input10 == topic){
ICON = "";
  for (int i=0;i<length;i++) {
     ICON +=  ((char)payload[i]);  
  }
 // int ICON_len = ICON.length() + 1; 
 // char char_array[ICON_len];
 // str.toCharArray(char_array, ICON_len);
 // const unsigned char* str;
 // str = (const unsigned char *)str.c_str();

 //tft.drawXBitmap(20, 20, snow, weatherWidth, weatherHeight, TFT_WHITE);
  //drawIcon(ICON,  (tft.width() -  weatherWidth)/2 - 50, (tft.height() -  weatherHeight)/2, weatherWidth,  weatherHeight);
} 

//##############################

if (input11 == topic){
 FORECAST = "";
  for (int i=0;i<length;i++) {
     FORECAST +=  ((char)payload[i]);  
  }
  
} 
//##############################

}

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    tft.setCursor(0, 50);
   tft.setTextColor(RED); //tft.setTextSize(3);
   tft.println("Attempting MQTT ...");
    // Attempt to connect
    if (client.connect("ESP8266Client")) {
     tft.setTextColor(GREEN);// tft.setTextSize(3);
     tft.println("connected");
      
      // Once connected, publish an announcement...
      client.publish("outTopic", "hello world");
      // ... and resubscribe
  
      client.subscribe("/ai/#");

      
      delay(3000);
      tft.fillScreen(BLACK);
      AI_finished();
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}
void loop(void) {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();
  

}


void AI_song(String Song){
    tft.setFreeFont(FSS9);
   tft.setTextColor(TFT_YELLOW, TFT_BLACK);tft.setCursor(20, 190);tft.setTextColor(TFT_BLUE, TFT_BLACK);tft.print(Song);
}

void AI_station(String Station){
  tft.fillRect(15,105,294,35,TFT_BLACK);
    tft.setFreeFont(FSB18);
  tft.setTextColor(TFT_YELLOW, TFT_BLACK);tft.setCursor(20, 130);tft.setTextColor(TFT_RED, TFT_BLACK);tft.print(Station);
  
}

void  AI_META(String Artist){
  tft.fillRect(15,140,294,80,TFT_BLACK);
    tft.setFreeFont(FSS12);
  tft.setTextColor(TFT_YELLOW, TFT_BLACK);tft.setCursor(20, 160);tft.setTextColor(TFT_GREEN, TFT_BLACK);tft.print(Artist);
}

void AI_time(String Time){
  tft.fillRect(70,12,230,40,TFT_BLACK);
    tft.setFreeFont(FSB24);
 tft.setTextColor(TFT_YELLOW, TFT_BLACK);tft.setCursor(70, 50);tft.setTextColor(TFT_YELLOW, TFT_BLACK);tft.print(Time);
   

}

void AI_date(String Date){
  tft.fillRect(70,62,230,40,TFT_BLACK);
  tft.setFreeFont(FSB18);
  tft.setTextColor(TFT_YELLOW, TFT_BLACK);tft.setCursor(75, 90);tft.setTextColor(TFT_YELLOW, TFT_BLACK);tft.print(Date); 
}

void AI_ready(){
  

tft.drawRoundRect(0,0,320,240,20,TFT_CYAN);
tft.drawRoundRect(1,1,318,238,20,TFT_CYAN);
tft.drawRoundRect(2,2,316,236,20,TFT_CYAN);
tft.drawRoundRect(3,3,314,234,20,TFT_CYAN);
tft.drawRoundRect(4,4,312,232,20,TFT_CYAN);
tft.drawRoundRect(5,5,310,230,20,TFT_CYAN);
tft.drawRoundRect(6,6,308,228,20,TFT_CYAN);
tft.drawRoundRect(7,7,306,226,20,TFT_CYAN);
tft.drawRoundRect(8,8,304,224,20,TFT_CYAN);
tft.drawRoundRect(9,9,302,222,20,TFT_CYAN);
tft.drawRoundRect(10,10,300,220,20,TFT_CYAN);
}

void AI_listen(){
tft.drawRoundRect(0,0,320,240,20,TFT_GREEN);
tft.drawRoundRect(1,1,318,238,20,TFT_GREEN);
tft.drawRoundRect(2,2,316,236,20,TFT_GREEN);
tft.drawRoundRect(3,3,314,234,20,TFT_GREEN);
tft.drawRoundRect(4,4,312,232,20,TFT_GREEN);
tft.drawRoundRect(5,5,310,230,20,TFT_GREEN);
tft.drawRoundRect(6,6,308,228,20,TFT_GREEN);
tft.drawRoundRect(7,7,306,226,20,TFT_GREEN);
tft.drawRoundRect(8,8,304,224,20,TFT_GREEN);
tft.drawRoundRect(9,9,302,222,20,TFT_GREEN);
tft.drawRoundRect(10,10,300,220,20,TFT_GREEN);

}



void AI_standby(){
    tft.setFreeFont(FSB24);
tft.setTextColor(TFT_YELLOW, TFT_BLACK);tft.setCursor(30, 160);tft.setTextColor(TFT_GREEN, TFT_BLACK);tft.print("Please Wait");
}


void AI_finished(){
  tft.fillScreen(TFT_BLACK);
  AI_ready();
 
    }
    
 void MyCroft(){
  tft.setFreeFont(FSB24);
tft.setCursor(30, 115);tft.setTextColor(TFT_GREEN, TFT_BLACK);tft.print(" MYCROFT");
tft.drawRoundRect(0,0,320,240,20,TFT_RED);
tft.drawRoundRect(1,1,318,238,20,TFT_RED);
tft.drawRoundRect(2,2,316,236,20,TFT_RED);
tft.drawRoundRect(3,3,314,234,20,TFT_RED);
tft.drawRoundRect(4,4,312,232,20,TFT_RED);
tft.drawRoundRect(5,5,310,230,20,TFT_RED);
tft.drawRoundRect(6,6,308,228,20,TFT_RED);
tft.drawRoundRect(7,7,306,226,20,TFT_RED);
tft.drawRoundRect(8,8,304,224,20,TFT_RED);
tft.drawRoundRect(9,9,302,222,20,TFT_RED);
tft.drawRoundRect(10,10,300,220,20,TFT_RED);
   
 }

//====================================================================================
// This is the function to draw the icon stored as an array in program memory (FLASH)
//====================================================================================

// To speed up rendering we use a 64 pixel buffer
#define BUFF_SIZE 64

// Draw array "icon" of defined width and height at coordinate x,y
// Maximum icon size is 255x255 pixels to avoid integer overflow

void drawIcon(String icon, int16_t x, int16_t y, uint16_t width, uint16_t height) {

  uint16_t  pix_buffer[BUFF_SIZE];   // Pixel buffer (16 bits per pixel)

  // Set up a window the right size to stream pixels into
  tft.setWindow(x, y, x + width - 1, y + height - 1);

  // Work out the number whole buffers to send
  uint16_t nb = ((uint16_t)height * width) / BUFF_SIZE;

  // Fill and send "nb" buffers to TFT
  for (int i = 0; i < nb; i++) {
    for (int j = 0; j < BUFF_SIZE; j++) {
      pix_buffer[j] = pgm_read_word(&icon[i * BUFF_SIZE + j]);
    }
    tft.pushColors(pix_buffer, BUFF_SIZE);
  }

  // Work out number of pixels not yet sent
  uint16_t np = ((uint16_t)height * width) % BUFF_SIZE;

  // Send any partial buffer left over
  if (np) {
    for (int i = 0; i < np; i++) pix_buffer[i] = pgm_read_word(&icon[nb * BUFF_SIZE + i]);
    tft.pushColors(pix_buffer, np);
  }
}

