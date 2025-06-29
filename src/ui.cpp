#include "ui.h"
#include <Arduino.h>




int medQue = 2000;
int hardQue = 900;
int easyQue = 900;
int totalQue = 3600;

#define gnFont &FreeMonoBold12pt7b
#define arcFont &FreeMonoBold9pt7b
#define testCol TFT_BLACK







#define green 0x6e28
#define arcGrey 0xa554
#define easyCol 0x063f
#define mediumCol 0xffc0
#define hardCol 0xf980

// TFT object is declared as extern in ui.h and defined in main.cpp

void draw_screen(String user) {
   tft.fillScreen(TFT_BLACK);
   tft.setTextColor(TFT_WHITE);
   tft.setFreeFont(&Orbitron_Light_24);
   tft.setTextDatum(ML_DATUM);
   tft.drawString(user, 10, 10);
   tft.setFreeFont(NULL);

   tft.setTextColor(green);
   tft.setFreeFont(gnFont);
   tft.setTextDatum(ML_DATUM);
   tft.drawString("Rank: ",10, 55);
   tft.drawString("Rating: ",10,80);
   tft.drawString("Subm's: ",10,105);
   tft.setTextDatum(MC_DATUM);
   tft.setFreeFont(arcFont);
   tft.drawString("Solved",250,130);
   tft.setTextColor(easyCol);
   tft.drawString("Easy",62,215);
   tft.setTextColor(mediumCol);
   tft.drawString("Medium",160,215);
   tft.setTextColor(hardCol);
   tft.drawString("Hard",258,215);
   tft.setFreeFont(NULL);


   


}

void rank(int rank,int rating){
   tft.setTextColor(green);
   tft.setFreeFont(gnFont);
   tft.setTextDatum(ML_DATUM);
   tft.fillRect(78,48,110,18,testCol);
   tft.drawString(String(rank),80, 55);
   tft.fillRect(105,73,98,18,testCol);
   tft.drawString(String(rating),105,80);
   
   tft.setFreeFont(NULL);

}

void wifiFailed(String ssid){
    tft.fillRect(0,0,320,240,TFT_BLACK);
    tft.setTextColor(TFT_RED);
    tft.setFreeFont(arcFont);
    tft.setTextDatum(MC_DATUM);
    String str = "UNABLE TO CONNECT TO: ";
    //str += ssid;
    tft.drawString(str,160,120);
    tft.drawString(ssid,160,140);
    tft.setFreeFont(NULL);

}

void connectingWifi(String ssid){
    tft.fillRect(0,0,320,240,TFT_WHITE);
    tft.setTextColor(0x04df);
    tft.setFreeFont(&FreeSerifItalic18pt7b);
    tft.setTextDatum(MC_DATUM);
    tft.drawString("Connecting...",160,80);
    String str = "SSID: ";
    str += ssid;
    tft.setFreeFont(&FreeSerifBold12pt7b);
    tft.drawString(str,160,120);
    tft.setFreeFont(NULL);
}

void httpsError(){
    tft.fillScreen(TFT_WHITE);
    tft.setTextColor(0xfb80);
    tft.setFreeFont(&FreeSerifBold12pt7b);
    tft.setTextDatum(MC_DATUM);
    tft.drawString("HTTPS Error...",160,90);
    tft.setFreeFont(NULL);
}
    
void userNotFound(String user){
    tft.fillScreen(TFT_WHITE);
    tft.setTextColor(0xfb80);
    tft.setFreeFont(&FreeSerifBold12pt7b);
    tft.setTextDatum(MC_DATUM);
    tft.drawString(user,160,90);
    tft.setFreeFont(&FreeSerifItalic18pt7b);
    tft.drawString("User Not Found...",160,120);
    tft.setFreeFont(NULL);
}


void totalArc(int total,int submissions) {
    tft.fillRect(250 - 30, 88 - 20, 60, 40, TFT_BLACK);
    if (total < 0) total = 0;
    if (total > totalQue) total = totalQue;
    int startAngle = 45;
    int sweep = 270; // Arc covers 270 degrees
    int endAngle = startAngle + (sweep * total) / totalQue;
    tft.setTextColor(green);
    tft.setFreeFont(gnFont);
    tft.setTextDatum(ML_DATUM);
    tft.fillRect(105,98,90,18,testCol);
    tft.drawString(String(submissions),105,105);
    tft.setTextDatum(MC_DATUM);
    tft.drawString(String(total), 250, 88);
    tft.setFreeFont(NULL);
    tft.drawSmoothArc(250, 88, 45, 40, 45, 315, arcGrey, TFT_BLACK, true);
    tft.drawSmoothArc(250, 88, 45, 40, startAngle, endAngle, green, TFT_BLACK, true);
}


void easyArc(int easy) {
    if (easy < 0) easy = 0;
    if (easy > easyQue) easy = easyQue;
    int startAngle = 45;
    int sweep = 270;
    int endAngle = startAngle + (sweep * easy) / easyQue;
    tft.setTextColor(easyCol);
    tft.setFreeFont(gnFont);
    tft.setTextDatum(MC_DATUM);
    tft.fillRect(62  - 30, 184 - 15, 60, 30, TFT_BLACK);
    tft.drawString(String(easy), 62, 184);
    tft.setFreeFont(NULL);
    tft.drawSmoothArc(62, 184, 32, 34, 45, 315, arcGrey, TFT_BLACK, true);
    tft.drawSmoothArc(62, 184, 32, 34, startAngle, endAngle, easyCol, TFT_BLACK, true);
}

void mediumArc(int medium) {
    if (medium < 0) medium = 0;
    if (medium > medQue) medium = medQue;
    int startAngle = 45;
    int sweep = 270;
    int endAngle = startAngle + (sweep * medium) / medQue;
    tft.setTextColor(mediumCol);
    tft.setFreeFont(gnFont);
    tft.setTextDatum(MC_DATUM);
    tft.fillRect(160 - 30, 184 - 15, 60, 30, TFT_BLACK);
    tft.drawString(String(medium), 160, 184);
    tft.setFreeFont(NULL);
    tft.drawSmoothArc(160, 184, 32, 34, 45, 315, arcGrey, TFT_BLACK, true);
    tft.drawSmoothArc(160, 184, 32, 34, startAngle, endAngle, mediumCol, TFT_BLACK, true);
}

void hardArc(int hard) {
    if (hard < 0) hard = 0;
    if (hard > hardQue) hard = hardQue;
    int startAngle = 45;
    int sweep = 270;
    int endAngle = startAngle + (sweep * hard) / hardQue;
    tft.setTextColor(hardCol);
    tft.setFreeFont(gnFont);
    tft.setTextDatum(MC_DATUM);
    tft.fillRect(258 - 30, 184 - 15, 60, 30, TFT_BLACK);
    tft.drawString(String(hard), 258, 184);
    tft.setFreeFont(NULL);
    tft.drawSmoothArc(258, 184, 32, 34, 45, 315, arcGrey, TFT_BLACK, true);
    tft.drawSmoothArc(258, 184, 32, 34, startAngle, endAngle, hardCol, TFT_BLACK, true);
}