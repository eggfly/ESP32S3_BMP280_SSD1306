#pragma once


#include <U8g2lib.h>

#define SSD1306_GND 13
#define SSD1306_VCC 14
#define SSD1306_SCL 15
#define SSD1306_SDA 16


// Frame buffer
//U8G2_SSD1306_64X32_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);
//U8G2_SSD1306_64X32_1F_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE); // THIS IS OK!

// Page Buffer
//U8G2_SSD1306_64X32_NONAME_1_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE); -> 297053, 14316
//U8G2_SSD1306_64X32_1F_1_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);

/*
  6330,7: class U8G2_SSD1306_64X32_1F_1_HW_I2C : public U8G2 { Flash 297053, RAM 14316 // page buffer
  6336,7: class U8G2_SSD1306_64X32_1F_1_2ND_HW_I2C : public U8G2 { -> Not Available // page buffer
  6366,7: class U8G2_SSD1306_64X32_1F_2_HW_I2C : public U8G2 { Flash 297053, RAM 14380
  6372,7: class U8G2_SSD1306_64X32_1F_2_2ND_HW_I2C : public U8G2 { -> Not Available
  6384,7: class U8G2_SSD1306_64X32_NONAME_F_HW_I2C : public U8G2 { -> Flash 297053, RAM 14508
  6390,7: class U8G2_SSD1306_64X32_NONAME_F_2ND_HW_I2C : public U8G2 { -> Not Available
  6402,7: class U8G2_SSD1306_64X32_1F_F_HW_I2C : public U8G2 { THIS IS OK! -> Flash 297053, RAM 14508
  6408,7: class U8G2_SSD1306_64X32_1F_F_2ND_HW_I2C : public U8G2 { -> Not Available
*/

U8G2_SSD1306_64X32_1F_F_HW_I2C u8g2(U8G2_R0, U8X8_PIN_NONE, /* clock=*/ SSD1306_SCL, /* data=*/ SSD1306_SDA);


void oled_pins_setup() {
  pinMode(SSD1306_VCC, OUTPUT);
  pinMode(SSD1306_GND, OUTPUT);
  digitalWrite(SSD1306_VCC, HIGH);
  digitalWrite(SSD1306_GND, LOW);
}
