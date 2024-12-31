#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

#define STRIP_PIN 6
#define MOTION_SENSOR_PIN 2  // Pin where the PIR sensor is connected
// Carters Comment: Pixel Brightness and pixel count are combined to produce current draw
// After testing, for a standard computer usb port using all 300 pixels, a maximum brightness of
// 15 is allowed before computer current regulations shut off the usb connection
#define PIXEL_COUNT 300
#define BRIGHTNESS 13


// NOTE: this has not been tested with battery packs, the maximum brightness of a the neopixel strip is 255
// to avoid burn out i do not recommend exceeding 200

// Adafruit Comment:
// Parameter 1 = number of pixels in strip
// Parameter 2 = Arduino pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
//   NEO_RGBW    Pixels are wired for RGBW bitstream (NeoPixel RGBW products)
Adafruit_NeoPixel strip = Adafruit_NeoPixel(PIXEL_COUNT, STRIP_PIN, NEO_GRB + NEO_KHZ800);

//RAINBOW COLOR DEFINITIONS
#define RED strip.Color(255, 0, 0)
#define ORANGE strip.Color(255, 165, 0)
#define YELLOW strip.Color(255, 255, 0)
#define GREEN strip.Color(0, 255, 0)
#define BLUE strip.Color(0, 0, 255)
#define INDIGO strip.Color(75, 0, 130)
#define VIOLET strip.Color(238, 130, 238)
#define WHITE strip.Color(255,255,255)

//BASIC COLOR DEFINTIONS
#define CYAN strip.Color(0, 255, 255)
#define MAGENTA strip.Color(255, 0, 255)
#define PURPLE strip.Color(128, 0, 128)
#define PINK strip.Color(255, 192, 203)
#define BROWN strip.Color(139, 69, 19)
#define LIGHT_BLUE strip.Color(173, 216, 230)
#define LIGHT_GREEN strip.Color(144, 238, 144)
#define LIGHT_YELLOW strip.Color(255, 255, 224)
#define LIGHT_PINK strip.Color(255, 182, 193)
#define GOLD strip.Color(255, 215, 0)
#define SILVER strip.Color(192, 192, 192)
#define TEAL strip.Color(0, 128, 128)
#define TAN strip.Color(210, 180, 140)

//OBSCURE COLOR DEFINITIONS
#define AMBER strip.Color(255, 191, 0)
#define PERIWINKLE strip.Color(204, 204, 255)
#define TURQUOISE strip.Color(64, 224, 208)
#define PEACHPUFF strip.Color(255, 218, 185)
#define MINTCREAM strip.Color(245, 255, 250)
#define FUCHSIA strip.Color(255, 0, 255)
#define CORAL strip.Color(255, 127, 80)
#define LAVENDERBLUSH strip.Color(255, 240, 245)
#define SLATEBLUE strip.Color(106, 90, 205)
#define PLUM strip.Color(221, 160, 221)
#define CHARTREUSE strip.Color(127, 255, 0)
#define WISTERIA strip.Color(201, 160, 220)
#define CARMINE strip.Color(150, 0, 24)
#define SEAFOAM strip.Color(83, 255, 196)
#define KHAKI strip.Color(240, 230, 140)
#define BURLYWOOD strip.Color(222, 184, 135)
#define OLIVE drab strip.Color(107, 142, 35)
#define MANGANITE strip.Color(227, 57, 83)

void setup() {
    // This is for Trinket 5V 16MHz, you can remove these three lines if you are not using a Trinket
    #if defined (__AVR_ATtiny85__)
        if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
        #endif
    // End of trinket special code
    Serial.begin(9600);
    // Set up the motion sensor pin as input
    pinMode(MOTION_SENSOR_PIN, INPUT);
    // put your setup code here, to run once:
    strip.begin();
    strip.setBrightness(BRIGHTNESS);
    strip.show(); // Initialize all pixels to 'off'
    }

void loop() {
    CheckForMotion();
}

void CheckForMotion() {
    // Read the value from the motion sensor
    int motionDetected = digitalRead(MOTION_SENSOR_PIN);
    
    if (motionDetected == HIGH) {
        // Print a message to the serial monitor
        Serial.println("Motion detected!");

        // Execute the Christmas lights sequence once after 200ms
        // christmasLights(200);

        // Execute the New Years lights sequence once after 200ms
        newYearsLights(400);
        

        // Wait to avoid immediate retriggering
        delay(10000);  // Adjust delay as needed (e.g., 10 seconds)
    }
}


// New Years themed lights
// Fill the dots one after the other with a color starting from the bottom
void newYearsLights(uint8_t wait) {
    // Check if motion is detected
    if (digitalRead(MOTION_SENSOR_PIN) == HIGH) {
        Serial.println("Motion detected!");

        // Step 1: Turn on the first ten lights with light blue color
        for (int i = 0; i < 10; i++) {
            strip.setPixelColor(i, LIGHT_BLUE); // Light Blue
        }
        strip.show();
        delay(3000); // Hold the lights on for 3 seconds

        // Step 2: Create a chasing effect
        for (int i = 10; i < strip.numPixels(); i++) {
            strip.setPixelColor(i, LIGHT_BLUE);        // Turn on the current light (light blue)
            strip.setPixelColor(i - 10, strip.Color(0, 0, 0));     // Turn off the oldest light
            strip.show();
            delay(wait); // Adjust speed of the chase effect
        }

        // Step 3: Turn off all lights
        for (int i = 0; i < strip.numPixels(); i++) {
            strip.setPixelColor(i, strip.Color(0, 0, 0)); // Turn off each light
            strip.show();
            delay(wait);
        }
    } else {
        Serial.println("No motion detected. Lights off.");
        strip.clear();
        strip.show(); // Ensure all lights are off
    }
}


// Fill the dots one after the other with a color starting from the bottom
void SetCascadingColorUpwards(uint32_t color, uint16_t pixelsToCountTo, uint8_t speedMs) {
    for(uint16_t i=0; i<pixelsToCountTo; i++) {
        strip.setPixelColor(i, color);
        if(i > 60) strip.setPixelColor((i-60), strip.Color(0,0,0));
        strip.show();
        delay(speedMs);
        }
}

// Fill the dots one after the other with a color starting from the Top
void SetCascadingColorDownwards(uint32_t color, uint16_t pixelsToCountTo, uint8_t speedMs) {
    for(uint16_t i=strip.numPixels(); i>=strip.numPixels() - pixelsToCountTo; i--)
    {
        strip.setPixelColor(i, color);
        strip.show();
        delay(speedMs);
        if(i == 0) break;
        }
}

// Turn off the entire strip
void SetStripOffBottomToTop(uint8_t speedMs){
    for(uint16_t i=0; i<strip.numPixels(); i++) {
        strip.setPixelColor(i, strip.Color(0,0,0));
        strip.show();
        delay(speedMs);
        }
}

// Turn off the entire strip
void SetStripOffTopToBottom(uint8_t speedMs){
    for(uint16_t i=strip.numPixels(); i>=0; i--)
    {
        strip.setPixelColor(i, strip.Color(0,0,0));
        strip.show();
        delay(speedMs);
        if(i == 0) break;
        }
}

// Slightly different, this makes the rainbow equally distributed throughout
void rainbowCycle(uint8_t wait) {
    uint16_t i, j;
    int num_cycles = 3;
    for(j=0; j<256*num_cycles; j++) { // 5 cycles of all colors on wheel
        for(i=0; i< strip.numPixels(); i++) {
            strip.setPixelColor(i, Wheel(((i * 256 / strip.numPixels()) + j) & 255));
            if(j == 0) strip.show();
            }
            strip.show();
            delay(wait);
            }
}

// Christmas themed lights
// Fill the dots one after the other with a color starting from the bottom
void christmasLights(uint8_t wait) {
    // Check if motion is detected
    if (digitalRead(PIR_PIN) == HIGH) {
        Serial.println("Motion detected!");

        // Step 1: Turn on the first ten lights, alternating red and green
        for (int i = 0; i < 10; i++) {
            if (i % 2 == 0) {
                strip.setPixelColor(i, strip.Color(255, 0, 0)); // Red
            } else {
                strip.setPixelColor(i, strip.Color(0, 255, 0)); // Green
            }
        }
        strip.show();
        delay(2000); // Hold the lights on for 2 seconds

        // Step 2: Create a chasing effect
        for (int i = 10; i < strip.numPixels(); i++) {
            strip.setPixelColor(i, strip.Color(255, 0, 0));        // Turn on the current light (red)
            strip.setPixelColor(i - 10, strip.Color(0, 0, 0));     // Turn off the oldest light
            strip.show();
            delay(wait); // Adjust speed of the chase effect
        }

        // Step 3: Turn off all lights
        for (int i = 0; i < strip.numPixels(); i++) {
            strip.setPixelColor(i, strip.Color(0, 0, 0)); // Turn off each light
            strip.show();
            delay(wait);
        }
    } else {
        Serial.println("No motion detected. Lights off.");
        strip.clear();
        strip.show(); // Ensure all lights are off
    }
}

//Theatre-style crawling lights with rainbow effect
void theaterChaseRainbow(uint8_t wait) {
  for (int j=0; j < 256; j++) {     // cycle all 256 colors in the wheel
    for (int q=0; q < 3; q++) {
        for (uint16_t i=0; i < strip.numPixels(); i=i+3) {
            strip.setPixelColor(i+q, Wheel( (i+j) % 255));    //turn every third pixel on
            }
            strip.show();
            
            delay(wait);
            
            for (uint16_t i=0; i < strip.numPixels(); i=i+3) {
                strip.setPixelColor(i+q, 0);        //turn every third pixel off
                }
    }
    }
}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
    WheelPos = 255 - WheelPos;
    if(WheelPos < 85) {
    return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
    }
    if(WheelPos < 170) {
    WheelPos -= 85;
    return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
    }
    WheelPos -= 170;
    return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
    }
