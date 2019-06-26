#include "main.h"
extern enum control_systerm system_s;
uint16_t R_RED, R_GREEN, R_BLUE, Y_RED, Y_GREEN, Y_BLUE, G_RED, G_GREEN, G_BLUE;
uint16_t r, g, b, c;
extern enum pick_mode_e mode;
extern int i;
Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_700MS, TCS34725_GAIN_16X);//color sensors
int color_range(uint16_t r, uint16_t b)
{
  int i;
  if (r > b) 
  {
    i = r - b;
    return i;
  }
  if (r <= b) 
  {
    i = b - r;
    return i;
  }
}
void slider_rgb_r()
{
  R_RED     =  177;
  R_GREEN   =   59;
  R_BLUE    =   53;
}
void slider_rgb_y()
{
  Y_RED    =  255;
  Y_GREEN  =  255;
  Y_BLUE   =  100;
}
void slider_rgb_g()
{
  G_RED    =   52;
  G_GREEN  =   96;
  G_BLUE   =   57;
}
void slider_rgb()
{
  slider_rgb_g();
  slider_rgb_y();
  slider_rgb_r();
}
void get_color()
{
  r = tcs.read16(TCS34725_RDATAL) / 255;
  g = tcs.read16(TCS34725_GDATAL) / 255;
  b = tcs.read16(TCS34725_BDATAL) / 255;
  r = constrain(r, 0, 255);
  b = constrain(b, 0, 255);
  g = constrain(g, 0, 255);
  Serial.print("r:"); Serial.println(r);
  Serial.print("b:"); Serial.println(b);
  Serial.print("g:");  Serial.println(g);

  if (color_range(G_RED, r) <= 10 && color_range(G_GREEN, g) <= 10 && color_range(G_BLUE, b) <= 10)
  {
    mode = GREEN_MODE;
    G_LED;
    Serial.println("Green");
  }
  else if (color_range(Y_RED, r) <= 10 && color_range(Y_GREEN, g) <= 10 && color_range(Y_BLUE, b) <= 10 )
  {
    mode = YELLOW_MODE;
    B_LED;
    Serial.println("Yellow");
  }
  else if (color_range(R_RED, r) <= 10 && color_range(R_GREEN, g) <= 10 && color_range(R_BLUE, b) <= 10)
  {
    mode = RED_MODE;
    R_LED;
    Serial.println("RED");
  }
  else {
    mode = NOTHING_MODE;
    LED_OFF;
  }
}
