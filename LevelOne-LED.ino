#include "FastLED.h"

/*
	LevelOne-LED.ino

	Controls the color of 5 individual LED strips.
  Colors fade between the start and end color defined in the COLORS section
  Colors wait between for a random time between 5-8 seconds then start transitioning
  Colors transion over 2.55 seconds

	The circuit:
  * Input: None
	* Output: 5 LED Strips

	Created 2021
	By Taylor Scafe and Wesley Scafe

  https://github.com/robosheep95/LevelOne-LED-Arduino

*/

/* ABBREVIATIONS
FOOD = Food
WATR = Water
SHTR = Shelter
HLTH = Healthcare
ELEC = Electricity
*/

// PINS
const int FOOD_DATA_PIN = 7;
const int WATR_DATA_PIN = 5;
const int SHTR_DATA_PIN = 9;
const int HLTH_DATA_PIN = 2;
const int ELEC_DATA_PIN = 3;

// COLORS
const CHSV foodStart = CHSV(60,255,255);
const CHSV foodEnd = CHSV(96,224,184);
const CHSV watrStart = CHSV(127,255,255);
const CHSV watrEnd = CHSV(167,225,255);
const CHSV shtrStart = CHSV(33,255,255);
const CHSV shtrEnd = CHSV(39,166,255);
const CHSV hlthStart = CHSV(0,255,255);
const CHSV hlthEnd = CHSV(0,0,230);
const CHSV elecStart = CHSV(43,255,255);
const CHSV elecEnd = CHSV(43,10,255);

// COLOR TIMINGS
#define MAX_COLOR_WAIT 300

// GLOBAL VARIABLES
#define LED_TYPE WS2811
#define COLOR_ORDER GRB
#define NUM_LEDS 84
#define BRIGHTNESS 100

// STRIPS
CRGB leds[5][NUM_LEDS];

// DIRECTION STORAGE ARRAY
bool directionForward[] = {true, true, true, true, true};

// LED STATUS STORAGE ARRAYS
CHSV colorCurrent[] = {foodStart, watrStart, shtrStart, hlthStart, elecStart};
const CHSV colorStart[] = {foodStart, watrStart, shtrStart, hlthStart, elecStart};
const CHSV colorEnd[] = {foodEnd, watrEnd, shtrEnd, hlthEnd, elecEnd};
int colorWait[] = {1, 1, 1, 1, 1};
bool colorWaitStatus[] = {true, true, true, true, true};
uint8_t colorPosition[] = {0,0,0,0,0};

/**
 * @brief Initializes serial output, Initializes LED strips, sets the LED brightness
 */
void setup() {
  Serial.begin(115200);  // Allows serial monitor output (check baud rate)
  delay(3000); // 3 second delay for recovery
  FastLED.addLeds<LED_TYPE,FOOD_DATA_PIN,COLOR_ORDER>(leds[0], NUM_LEDS).setCorrection(TypicalLEDStrip);
  FastLED.addLeds<LED_TYPE,WATR_DATA_PIN,COLOR_ORDER>(leds[1], NUM_LEDS).setCorrection(TypicalLEDStrip);
  FastLED.addLeds<LED_TYPE,SHTR_DATA_PIN,COLOR_ORDER>(leds[2], NUM_LEDS).setCorrection(TypicalLEDStrip);
  FastLED.addLeds<LED_TYPE,HLTH_DATA_PIN,COLOR_ORDER>(leds[3], NUM_LEDS).setCorrection(TypicalLEDStrip);
  FastLED.addLeds<LED_TYPE,ELEC_DATA_PIN,COLOR_ORDER>(leds[4], NUM_LEDS).setCorrection(TypicalLEDStrip);

  FastLED.setBrightness(BRIGHTNESS);
  Serial.println("Setup done. \n");
}

/**
 * @brief For every LED strip, update the color of the led to the next color
 */
void loop()
{
  for (int i = 0; i < 5; i++)
  {
    tick(i);
    colorCurrent[i] = blend((directionForward[i] == true ? colorStart[i] : colorEnd[i]),
                            (directionForward[i] == true ? colorEnd[i] : colorStart[i]),
                            colorPosition[i], SHORTEST_HUES);
    fill_solid(leds[i], NUM_LEDS, colorCurrent[i]);
  }
  Serial.print(colorWait[1]);
  Serial.print("|");
  Serial.print(colorWaitStatus[1]);
  Serial.print("|");
  Serial.print(colorCurrent[1].h);
  Serial.print("|");
  Serial.print(colorCurrent[1].s);
  Serial.print("|");
  Serial.print(colorCurrent[1].v);
  Serial.print("|");
  Serial.println(colorPosition[1]);

  FastLED.show();
  FastLED.delay(10);
}

/**
 * @brief Increments the wait count if the LED strip is waiting;
 * increments the color position if transitioning;
 * calls reverse if the transition is complete.
 *
 * @param i the index of the LED strip being processed
 */
void tick(int i)
{
  colorWaitStatus[i] = colorWait[i] < MAX_COLOR_WAIT + 500;
  if (colorWaitStatus[i])
  {
    colorWait[i]++;
  }
  else
  {
    colorPosition[i]++;
  }
  if ((colorCurrent[i].h == (directionForward[i] == true ? colorEnd[i].h : colorStart[i].h)) &&
      (colorCurrent[i].s == (directionForward[i] == true ? colorEnd[i].s : colorStart[i].s)) &&
      (colorCurrent[i].v == (directionForward[i] == true ? colorEnd[i].v : colorStart[i].v)))
  {
    reverse(i);
  }
}

/**
 * @brief Reverses the LED color direction and sets the new wait period.
 *
 * @param i the index of the LED strip being processed
 */
void reverse(int i)
{
  colorWait[i] = random16(0, MAX_COLOR_WAIT);
  directionForward[i] = !directionForward[i];
  colorPosition[i] = 0;
}
