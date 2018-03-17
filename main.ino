#include <FastLED.h>


// NeoPixelBrightness
// This example will cycle brightness from high to low of
// three pixels colored Red, Green, Blue.
// This demonstrates the use of the NeoPixelBrightnessBus
// with integrated brightness support
//
// There is serial output of the current state so you can
// confirm and follow along
//



#include <NeoPixelBrightnessBus.h> // instead of NeoPixelBus.h

const uint16_t PixelCount = 64; // this example assumes 3 pixels, making it smaller will cause a failure

#define colorSaturation 75 // saturation of color constants

RgbColor red(colorSaturation, 0, 0);
RgbColor green(0, colorSaturation, 0);
RgbColor blue(0, 0, colorSaturation);
  
uint16_t bright = 0;
// Make sure to provide the correct color order feature
// for your NeoPixels
NeoPixelBrightnessBus<NeoRgbFeature, NeoEsp8266Dma800KbpsMethod> strip(PixelCount);

// you loose the original color the lower the dim value used
// here due to quantization
const uint8_t c_MinBrightness = 8;
const uint8_t c_MaxBrightness = 128;

NeoTopology <RowMajorAlternatingLayout> topo(8,8);

int8_t direction; // current direction of dimming
uint16_t t;

void setup()
{
  Serial.begin(115200);
  while (!Serial); // wait for serial attach

  Serial.println();
  Serial.println("Initializing...");
  Serial.flush();

  // this resets all the neopixels to an off state
  strip.Begin();
  strip.Show();

  direction = -1; // default to dim first

  Serial.println();
  Serial.println("Running...");

  
  // set our three original colors
  for (int x = 0; x < 8; x++) {
    for (int y = 0; y < 8; y++) {
      bright = inoise16 (x, y, t);
      strip.SetPixelColor(topo.Map(x, y), RgbColor(bright/512,0,0));      
    }
  }
  strip.Show();
}


void loop(){  
  // set our three original colors
  if(t+100 > millis()){
    for (int x = 0; x < 8; x++) {
      for (int y = 0; y < 8; y++) {
        bright = inoise16(x*2048, y*2048, t*5)/512;
        strip.SetPixelColor(topo.Map(x, y), RgbColor(bright,0,0));
        Serial.println(bright);      
      }
    }
    strip.Show();
    t = millis();
  }
}
