#ifndef DISPLAY_H
#define DISPLAY_H

#include <Arduino.h>
#include <SSD1306Wire.h>
#include <OLEDDisplayUi.h>

class OLED_Display
{
protected:
    // Pin for Connected I2SC Oled Display, change based on your connection
    int Pin_SDC = D2;                     // Pin For oled Display
    int Pin_SDA = D1;                     // Pin For Oled Display
    const int I2C_DISPLAY_ADDRESS = 0x3c; // Update based on your OLED Device

    //Display
    SSD1306Wire *display; //(HomeServer::I2C_DISPLAY_ADDRESS, HomeServer::SDA_Pin, SDC_Pin);
    OLEDDisplayUi *ui;    //(&display);

public:
    OLED_Display(int sdc, int sda);
    ~OLED_Display();

    void setPins(int sdc, int sda);
    void InitDisplay();

    void DrawProgress(OLEDDisplay *display, int percentage, String label);
    void UpdateData(OLEDDisplay *display);
    
};

#endif

//TODO: Move to CPP File
void OLED_Display::UpdateData(OLEDDisplay *display){}
    
void OLED_Display::DrawProgress(OLEDDisplay *display, int percentage, String label)
{
    //TODO:
}

OLED_Display::~OLED_Display()
{
    free(ui);
    free(display);
}
OLED_Display::OLED_Display(int sdc, int sda)
{
    Pin_SDA = sda;
    Pin_SDC = sdc;
    display = new SSD1306Wire(I2C_DISPLAY_ADDRESS, Pin_SDA, Pin_SDC);
    ui = new OLEDDisplayUi(display);
}

void OLED_Display::setPins(int sdc, int sda)
{
    Pin_SDA = sda;
    Pin_SDC = sdc;
}

void OLED_Display::InitDisplay()
{
}