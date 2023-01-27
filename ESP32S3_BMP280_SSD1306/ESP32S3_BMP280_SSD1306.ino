
#include <Arduino.h>

#include <Wire.h>

#include "oled.h"
#include "bmp280.h"

// DON'T USE LEDs ANYMORE
#define LEDA 10
#define LEDB 11



void u8g2_prepare_ascii(void) {
  u8g2.setFont(u8g2_font_6x10_tf);
  u8g2.setFontRefHeightExtendedText();
  u8g2.setDrawColor(1);
  u8g2.setFontPosTop();
  u8g2.setFontDirection(0);
}

void u8g2_box_frame(uint8_t a) {
  u8g2.drawStr(0, 0, "drawBox");
  u8g2.drawBox(5, 10, 20, 10);
  u8g2.drawBox(1 + a, 15, 30, 7);
  // u8g2.drawStr(0, 30, "drawFrame");
  // u8g2.drawFrame(5, 10 + 30, 20, 10);
  // u8g2.drawFrame(10 + a, 15 + 30, 30, 7);
}

void u8g2_disc_circle(uint8_t a) {
  u8g2.drawStr(0, 0, "drawDisc");
  u8g2.drawDisc(10, 18, 9);
  u8g2.drawDisc(24 + a, 16, 7);
  // u8g2.drawStr( 0, 30, "drawCircle");
  // u8g2.drawCircle(10, 18 + 30, 9);
  // u8g2.drawCircle(24 + a, 16 + 30, 7);
}

void u8g2_r_frame(uint8_t a) {
  u8g2.drawStr( 0, 0, "drawRFrame/Box");
  u8g2.drawRFrame(5, 10, 40, 30, a + 1);
  u8g2.drawRBox(50, 10, 25, 40, a + 1);
}

void u8g2_string(uint8_t a) {
  u8g2.setFontDirection(0);
  u8g2.drawStr(30 + a, 31, " 0");
  u8g2.setFontDirection(1);
  u8g2.drawStr(30, 31 + a, " 90");
  u8g2.setFontDirection(2);
  u8g2.drawStr(30 - a, 31, " 180");
  u8g2.setFontDirection(3);
  u8g2.drawStr(30, 31 - a, " 270");
}

void u8g2_line(uint8_t a) {
  u8g2.drawStr( 0, 0, "drawLine");
  u8g2.drawLine(7 + a, 10, 40, 55);
  u8g2.drawLine(7 + a * 2, 10, 60, 55);
  u8g2.drawLine(7 + a * 3, 10, 80, 55);
  u8g2.drawLine(7 + a * 4, 10, 100, 55);
}

void u8g2_triangle(uint8_t a) {
  uint16_t offset = a;
  u8g2.drawStr( 0, 0, "drawTriangle");
  u8g2.drawTriangle(14, 7, 45, 30, 10, 40);
  u8g2.drawTriangle(14 + offset, 7 - offset, 45 + offset, 30 - offset, 57 + offset, 10 - offset);
  u8g2.drawTriangle(57 + offset * 2, 10, 45 + offset * 2, 30, 86 + offset * 2, 53);
  u8g2.drawTriangle(10 + offset, 40 + offset, 45 + offset, 30 + offset, 86 + offset, 53 + offset);
}

void u8g2_ascii_1() {
  char s[2] = " ";
  uint8_t x, y;
  u8g2.drawStr( 0, 0, "ASCII page 1");
  for ( y = 0; y < 6; y++ ) {
    for ( x = 0; x < 16; x++ ) {
      s[0] = y * 16 + x + 32;
      u8g2.drawStr(x * 7, y * 10 + 10, s);
    }
  }
}

void u8g2_ascii_2() {
  char s[2] = " ";
  uint8_t x, y;
  u8g2.drawStr( 0, 0, "ASCII page 2");
  for ( y = 0; y < 6; y++ ) {
    for ( x = 0; x < 16; x++ ) {
      s[0] = y * 16 + x + 160;
      u8g2.drawStr(x * 7, y * 10 + 10, s);
    }
  }
}

void u8g2_temperature() {
  char buf[128];
  snprintf(buf, 128, "%.2f°C", temperature);
  u8g2.setFont(u8g2_font_unifont_t_chinese2);
  u8g2.enableUTF8Print();
  // u8g2.setFont(u8g2_font_unifont_t_symbols);
  u8g2.setFontPosTop();
  // u8g2.enableUTF8Print();
  // u8g2.setFont(u8g2_font_unifont_t_chinese2);
  // u8g2.setFont(u8g2_font_wqy12_t_gb2312b);
  u8g2.setFont(u8g2_font_wqy16_t_gb2312b);
  // u8g2.setFont(u8g2_font_wqy14_t_gb2312b);
  u8g2.drawUTF8(0, 0, "温度°C");
  u8g2.drawUTF8(0, 0 + 16, buf);
  u8g2.setFont(u8g2_font_unifont_t_symbols);
  //u8g2.drawUTF8(33, 15, "°C");
  //u8g2.drawUTF8(0, 15, "℃");

  // u8g2.disableUTF8Print();
  u8g2_prepare_ascii();

  delay(1000);
}
void u8g2_pressure() {
  char buf[128];
  snprintf(buf, 128, "%.2f", pressure);
  u8g2.setFont(u8g2_font_unifont_t_chinese2);
  u8g2.enableUTF8Print();
  // u8g2.setFont(u8g2_font_unifont_t_symbols);
  u8g2.setFontPosTop();
  // u8g2.enableUTF8Print();
  // u8g2.setFont(u8g2_font_unifont_t_chinese2);
  // u8g2.setFont(u8g2_font_wqy12_t_gb2312b);
  u8g2.setFont(u8g2_font_wqy16_t_gb2312b);
  // u8g2.setFont(u8g2_font_wqy14_t_gb2312b);
  u8g2.drawUTF8(0, 0, "气压Pa");
  u8g2.drawUTF8(0, 0 + 16, buf);

  delay(1000);
}

void u8g2_altitude() {
  char buf[128];
  snprintf(buf, 128, "%.2f", altitude);
  u8g2.enableUTF8Print();
  // u8g2.setFont(u8g2_font_unifont_t_symbols);
  u8g2.setFontPosTop();
  // u8g2.setFont(u8g2_font_wqy12_t_gb2312b);
  u8g2.setFont(u8g2_font_wqy16_t_gb2312b);
  // u8g2.setFont(u8g2_font_wqy14_t_gb2312b);
  u8g2.drawUTF8(0, 0, "海拔 米");
  u8g2.drawUTF8(0, 0 + 16, buf);
  delay(1000);
}

#define cross_width 24
#define cross_height 24
static const unsigned char cross_bits[] U8X8_PROGMEM  = {
  0x00, 0x18, 0x00, 0x00, 0x24, 0x00, 0x00, 0x24, 0x00, 0x00, 0x42, 0x00,
  0x00, 0x42, 0x00, 0x00, 0x42, 0x00, 0x00, 0x81, 0x00, 0x00, 0x81, 0x00,
  0xC0, 0x00, 0x03, 0x38, 0x3C, 0x1C, 0x06, 0x42, 0x60, 0x01, 0x42, 0x80,
  0x01, 0x42, 0x80, 0x06, 0x42, 0x60, 0x38, 0x3C, 0x1C, 0xC0, 0x00, 0x03,
  0x00, 0x81, 0x00, 0x00, 0x81, 0x00, 0x00, 0x42, 0x00, 0x00, 0x42, 0x00,
  0x00, 0x42, 0x00, 0x00, 0x24, 0x00, 0x00, 0x24, 0x00, 0x00, 0x18, 0x00,
};

#define cross_fill_width 24
#define cross_fill_height 24
static const unsigned char cross_fill_bits[] U8X8_PROGMEM  = {
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x00, 0x18, 0x64, 0x00, 0x26,
  0x84, 0x00, 0x21, 0x08, 0x81, 0x10, 0x08, 0x42, 0x10, 0x10, 0x3C, 0x08,
  0x20, 0x00, 0x04, 0x40, 0x00, 0x02, 0x80, 0x00, 0x01, 0x80, 0x18, 0x01,
  0x80, 0x18, 0x01, 0x80, 0x00, 0x01, 0x40, 0x00, 0x02, 0x20, 0x00, 0x04,
  0x10, 0x3C, 0x08, 0x08, 0x42, 0x10, 0x08, 0x81, 0x10, 0x84, 0x00, 0x21,
  0x64, 0x00, 0x26, 0x18, 0x00, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};

#define cross_block_width 14
#define cross_block_height 14
static const unsigned char cross_block_bits[] U8X8_PROGMEM  = {
  0xFF, 0x3F, 0x01, 0x20, 0x01, 0x20, 0x01, 0x20, 0x01, 0x20, 0x01, 0x20,
  0xC1, 0x20, 0xC1, 0x20, 0x01, 0x20, 0x01, 0x20, 0x01, 0x20, 0x01, 0x20,
  0x01, 0x20, 0xFF, 0x3F,
};

void u8g2_bitmap_overlay(uint8_t a) {
  uint8_t frame_size = 28;

  u8g2.drawStr(0, 0, "Bitmap overlay");

  u8g2.drawStr(0, frame_size + 12, "Solid / transparent");
  u8g2.setBitmapMode(false /* solid */);
  u8g2.drawFrame(0, 10, frame_size, frame_size);
  u8g2.drawXBMP(2, 12, cross_width, cross_height, cross_bits);
  if (a & 4)
    u8g2.drawXBMP(7, 17, cross_block_width, cross_block_height, cross_block_bits);

  u8g2.setBitmapMode(true /* transparent*/);
  u8g2.drawFrame(frame_size + 5, 10, frame_size, frame_size);
  u8g2.drawXBMP(frame_size + 7, 12, cross_width, cross_height, cross_bits);
  if (a & 4)
    u8g2.drawXBMP(frame_size + 12, 17, cross_block_width, cross_block_height, cross_block_bits);
}

void u8g2_bitmap_modes(uint8_t transparent) {
  const uint8_t frame_size = 24;

  u8g2.drawBox(0, frame_size * 0.5, frame_size * 5, frame_size);
  u8g2.drawStr(frame_size * 0.5, 50, "Black");
  u8g2.drawStr(frame_size * 2, 50, "White");
  u8g2.drawStr(frame_size * 3.5, 50, "XOR");

  if (!transparent) {
    u8g2.setBitmapMode(false /* solid */);
    u8g2.drawStr(0, 0, "Solid bitmap");
  } else {
    u8g2.setBitmapMode(true /* transparent*/);
    u8g2.drawStr(0, 0, "Transparent bitmap");
  }
  u8g2.setDrawColor(0);// Black
  u8g2.drawXBMP(frame_size * 0.5, 24, cross_width, cross_height, cross_bits);
  u8g2.setDrawColor(1); // White
  u8g2.drawXBMP(frame_size * 2, 24, cross_width, cross_height, cross_bits);
  u8g2.setDrawColor(2); // XOR
  u8g2.drawXBMP(frame_size * 3.5, 24, cross_width, cross_height, cross_bits);
}

uint8_t draw_state = 0;

void draw_frame(void) {
  u8g2_prepare_ascii();
  switch (draw_state >> 3) {
    case 0:
    case 1: u8g2_temperature(); break;
    case 2:
    case 3: u8g2_pressure(); break;
    case 4:
    case 5: u8g2_altitude(); break;
    case 6:
    case 7: u8g2_temperature(); break;
    case 8:
    case 9: u8g2_pressure(); break;
    case 10:
    case 11: u8g2_altitude(); break;
  }
}


void setup(void) {
  Serial.begin(115200);

  // TWO LEDS
  //  pinMode(LEDA, OUTPUT);
  //  pinMode(LEDB, OUTPUT);
  //  digitalWrite(LEDA, LOW);
  //  digitalWrite(LEDB, LOW);
  bmp280_pins_setup();
  oled_pins_setup();

  delay(10);

  bmp280_init();

  u8g2.begin();
  u8g2.setContrast(10);
}

long bmp280_last_update_time = 0;

void loop(void) {
  auto t = millis();
  if (t > bmp280_last_update_time + 1000) {
    bmp280_force_measure();
    bmp280_last_update_time = t;
  }
  // picture loop
  u8g2.clearBuffer();
  draw_frame();
  u8g2.sendBuffer();

  // increase the state
  draw_state++;
  if ( draw_state >= 12 * 8 ) {
    draw_state = 0;
  }

  // deley between each page
  delay(100);

}
