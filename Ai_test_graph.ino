/*
 An example digital clock using a TFT LCD screen to show the time.
 Demonstrates use of the font printing routines. (Time updates but date does not.)

 It uses the time of compile/upload to set the time
 For a more accurate clock, it would be better to use the RTClib library.
 But this is just a demo...

 Make sure all the display driver and pin comnenctions are correct by
 editting the User_Setup.h file in the TFT_eSPI library folder.

 #########################################################################
 ###### DON'T FORGET TO UPDATE THE User_Setup.h FILE IN THE LIBRARY ######
 #########################################################################

 Based on clock sketch by Gilchrist 6/2/2014 1.0

A few colour codes:

code	color
0x0000	Black
0xFFFF	White
0xBDF7	Light Gray
0x7BEF	Dark Gray
0xF800	Red
0xFFE0	Yellow
0xFBE0	Orange
0x79E0	Brown
0x7E0	Green
0x7FF	Cyan
0x1F	Blue
0xF81F	Pink

 */
#include "Free_Fonts.h"
#include <TFT_eSPI.h> // Hardware-specific library
#include <SPI.h>

#define TFT_GREY 0x5AEB

TFT_eSPI tft = TFT_eSPI();       // Invoke custom library

String command;
String TIME = "";
String DATE ="";
String STATION;
String ARTIST;
String SONG;

float input1b = 0;
float input2b = 0;
float input3b = 0;
int scan1;
int scan2;
int scan3;


long lastMsg = 0;
char msg[50];
int value = 0;
char msg2[50];
char msg3[50];

unsigned int colour = 0;

void setup(void) {
  Serial.begin(9600);
  tft.init();
  tft.setRotation(1);
  tft.fillScreen(TFT_BLACK);

  tft.setTextSize(1);
  tft.setTextColor(TFT_YELLOW, TFT_BLACK);
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

void loop() {




   if(Serial.available())
   {
      char c = Serial.read();
    
      if (c == ')')
      {
       
        parseCommand(command);
        
        command="";
      }
      else
      {
       command += c;
       digitalWrite(BUILTIN_LED, HIGH); 
      }
  }


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
  tft.fillRect(20,12,280,40,TFT_BLACK);
    tft.setFreeFont(FSB24);
 tft.setTextColor(TFT_YELLOW, TFT_BLACK);tft.setCursor(75, 50);tft.setTextColor(TFT_YELLOW, TFT_BLACK);tft.print(Time);
   

}

void AI_date(String Date){
  tft.fillRect(20,62,280,40,TFT_BLACK);
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

void parseCommand(String com)
{
   
char test[5];
  String part1;
  String part2;
  
  part1 = com.substring(6, com.indexOf("("));
  
  Serial.println(part1);
  
  part2 = com.substring(com.indexOf("(")+1);
  Serial.println(part2);
  if (part1 == "1")
  {
    

    Serial.println("recieved 1");
    String raw_CMD;
    
  TIME= part2;
 AI_time(TIME);

    
    
    }
  if (part1== "2")
    {
  
    Serial.println("recieved 2");
    String raw_CMD;
    DATE= part2;
    AI_date(DATE);
    
    }
 if (part1 == "3")
    {
    
    Serial.println("recieved 3");
    String raw_CMD;
    AI_ready();
 
 
    
  }

 if (part1== "4")
    {
 
    Serial.println("recieved 4");
    String raw_CMD;
    AI_listen();

    }

 if (part1== "5")
    {
   
    Serial.println("recieved 5");
    String raw_CMD;
    STATION = part2;
    AI_station(STATION);

    }

 if (part1== "6")
    {
  
    Serial.println("recieved 6");
    String raw_CMD;
    ARTIST = part2;
    AI_META(ARTIST);

    }
 if (part1== "7")
    {
   ; 
    Serial.println("recieved 7");
    String raw_CMD;
    SONG = part2;
    AI_song(SONG);

    }
   if (part1== "8")
    {
    
    Serial.println("recieved 8");
    String raw_CMD;
    AI_standby();

    }

   if (part1== "9")
    {
    
    Serial.println("recieved 9");
    String raw_CMD;
    AI_finished();

    }

   if (part1== "10")
    {
    
    Serial.println("recieved 10");
    String raw_CMD;
    

    }

   if (part1== "11")
    {
    
    Serial.println("recieved 11");
    String raw_CMD;
    

    }

   if (part1== "12")
    {
    
    Serial.println("recieved 12");
    String raw_CMD;
    

    }

   if (part1== "13")
    {
    
    Serial.println("recieved 14");
    String raw_CMD;
    

    }
    
delay(100);
    }  

    void AI_finished(){
  tft.fillScreen(TFT_BLACK);
  AI_ready();
 
  
}
