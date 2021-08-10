#include <Wire.h>
#include <Adafruit_MLX90614.h>
Adafruit_MLX90614 mlx = Adafruit_MLX90614();

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH1106.h>
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
// Declaration for an SH1106 display connected to I2C (SDA, SCL pins)
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SH1106 display(OLED_RESET);

#define BAO_COI (7)

void setup() {
  Serial.begin(9600);
  
  mlx.begin();
  
  display.begin(SH1106_SWITCHCAPVCC, 0x3C);
  
  pinMode(BAO_COI, OUTPUT);
}
void loop() {

  
  float nhiet_do;
  float nhiet_do_chuan;
  nhiet_do = mlx.readObjectTempC();
  nhiet_do_chuan = (nhiet_do + 2.6);
  if(nhiet_do_chuan >= 37.8){
    digitalWrite(BAO_COI, HIGH);
    }
  else {
    digitalWrite(BAO_COI, LOW);
    }
    
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(40, 10);
  display.print("SCANNING");
  display.setCursor(20, 30);
  display.setTextSize(3);
  display.print(nhiet_do_chuan);
  display.display();
  display.clearDisplay();  
  delay(500);
  //Serial.println(nhiet_do_chuan);
}
