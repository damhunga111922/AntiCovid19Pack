#include <Wire.h>
#include <Adafruit_MLX90614.h>
Adafruit_MLX90614 mlx = Adafruit_MLX90614();
float nhietdo;

#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH1106.h>
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
// Declaration for an SH1106 display connected to I2C (SDA, SCL pins)
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SH1106 display(OLED_RESET);

#define LOGO_HEIGHT   16
#define LOGO_WIDTH    16
static const unsigned char PROGMEM logo_bmp[] =
{ B00000000, B11000000,
  B00000001, B11000000,
  B00000001, B11000000,
  B00000011, B11100000,
  B11110011, B11100000,
  B11111110, B11111000,
  B01111110, B11111111,
  B00110011, B10011111,
  B00011111, B11111100,
  B00001101, B01110000,
  B00011011, B10100000,
  B00111111, B11100000,
  B00111111, B11110000,
  B01111100, B11110000,
  B01110000, B01110000,
  B00000000, B00110000 };

void setup() {
  Serial.begin(115200);
  mlx.begin();
  display.begin(SH1106_SWITCHCAPVCC, 0x3C);
  pinMode(2, OUTPUT);
  pinMode(13, INPUT);
  pinMode(12, OUTPUT);
  //pinMode(14, INPUT);
}
bool checkVC()
{
   int vatcan = abs(digitalRead(13) - 1);
   digitalWrite(12, vatcan);
   return(abs(digitalRead(13) - 1));
}
float Temp()
{
  float nhietdochuan;
  nhietdo = mlx.readObjectTempC();
  nhietdochuan = (nhietdo + 2.8);
  return(nhietdochuan);
  //delay(2000);
}

void OLED(float data)
{
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(40, 10);
  display.print("NHIET DO");
  display.setTextSize(3);
  display.setCursor(20, 26);
  display.print(data);
  display.display();
  display.clearDisplay();
  Serial.println(data);
  
  if (data >= 38.00)
  { 
   digitalWrite(2, HIGH);
   delay(2000);
   digitalWrite(2, LOW);
  }
  else
  {
   digitalWrite(2, LOW);
  }
  delay(2000);
}

void loop() 
{   
  if (checkVC())
  {
    OLED(Temp());
  }
}
