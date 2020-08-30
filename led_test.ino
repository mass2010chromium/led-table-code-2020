// Screen dimensions
#include <FastLED.h>
#define NUM_LEDS 150
#define NUM_LEDS_USABLE 129
#define DATA_PIN 6
#define NUM_ROWS 4
#define NUM_COLS 30

// Color definitions
#define ILLINI_ORANGE CRGB(232, 74, 39)
#define ILLINI_BLUE CRGB(19, 41, 75)
#define IBM_BLUE CRGB(84, 149, 229)


// Abstracting away the fact that the LED strip is looped back on itself.
CRGB leds[NUM_LEDS];

// Allow write to out of bounds to simplify animation routines.
void ledSet(int r, int c, CRGB color) {
  if (r < 0 || r >= NUM_ROWS || c < 0 || c >= NUM_COLS) return;
  int offset = r * 33;
  if (r % 2) {
    offset += 29;
    leds[offset-c] = color;
  }
  else {
    leds[offset+c] = color;
  }
}

void columnSet(int col, CRGB color) {
  for (int i = 0; i < NUM_ROWS; ++i) {
    ledSet(i, col, color);
  }
}

void rowRangeSet(int row, int start, int end, CRGB color) {
  for (int i = start; i < end; ++i) {
    ledSet(row, i, color);
  }
}

void ledClear() {
  for (int i = 0; i < NUM_LEDS; ++i) {
    leds[i] = CRGB::Black;
  }
}

void setup() {
  // put your setup code here, to run once:
  FastLED.addLeds<WS2812, DATA_PIN, GRB>(leds, NUM_LEDS_USABLE);
}


// Put pattern we want to play in here!
// TODO add sensors or shiz to allow pattern selection
void loop() {
  pattern_IBM_scroll();
  for (int i = 0; i < 4; ++i) {
    pattern_ILLINI_scroll();
  }
}


/* 
 * !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
 *
 *   Patterns go below!
 *
 *     Note, my setup is super lame so
 *       if your pattern has too many on LEDs
 *       for too long, my arduino will brown out.
 *
 * !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
 */

void pattern_IBM_scroll() {
  for (int i = -30; i < 30; ++i) {
    pattern_eye(i);
    pattern_bee(i+10);
    pattern_M(i+23, IBM_BLUE);
    FastLED.show();
    ledClear();
    delay(100);
  }
}

void pattern_ILLINI_scroll() {
  for (int i = -30; i < 30; ++i) {
    pattern_I(i, ILLINI_ORANGE);
    pattern_L(i+10, ILLINI_BLUE);
    pattern_L(i+21, ILLINI_ORANGE);
    FastLED.show();
    ledClear();
    delay(100);
  }
  for (int i = -30; i < 30; ++i) {
    pattern_I(i, ILLINI_BLUE);
    pattern_N(i+11, ILLINI_ORANGE);
    pattern_I(i+24, ILLINI_BLUE);
    FastLED.show();
    ledClear();
    delay(100);
  }
}

void pattern_eye(int col) {
  const CRGB EYE_ORANGE = CRGB(221, 106, 0);
  const CRGB EYE_WHITE = CRGB(255, 255, 255);
  rowRangeSet(0, col+1, col+8, EYE_ORANGE);
  rowRangeSet(1, col+3, col+6, EYE_WHITE);
  rowRangeSet(2, col, col+3, EYE_WHITE);
  rowRangeSet(2, col+6, col+9, EYE_WHITE);
  rowRangeSet(3, col+3, col+6, EYE_WHITE);
}

void pattern_bee(int col) {
  const CRGB BEE_GREEN = CRGB(44, 142, 43);
  const CRGB BEE_PINK = CRGB(244, 182, 195);
  const CRGB BEE_YELLOW = CRGB(241, 181, 0);
  rowRangeSet(3, col, col+3, BEE_GREEN);
  rowRangeSet(3, col+4, col+8, BEE_YELLOW);
  rowRangeSet(3, col+9, col+12, BEE_GREEN);
  rowRangeSet(2, col+1, col+4, BEE_GREEN);
  rowRangeSet(2, col+8, col+11, BEE_GREEN);
  rowRangeSet(1, col+4, col+8, BEE_YELLOW);
  rowRangeSet(0, col+4, col+5, BEE_PINK);
  rowRangeSet(0, col+7, col+8, BEE_PINK);
  
}

void pattern_I(int col, CRGB color) {
  columnSet(col+2, color);
  columnSet(col+3, color);
  columnSet(col+4, color);
  ledSet(0, col, color);
  ledSet(0, col+1, color);
  ledSet(3, col, color);
  ledSet(3, col+1, color);
  ledSet(0, col+5, color);
  ledSet(3, col+5, color);
  ledSet(0, col+6, color);
  ledSet(3, col+6, color);
}

void pattern_L(int col, CRGB color) {
  columnSet(col, color);
  columnSet(col+1, color);
  columnSet(col+2, color);
  rowRangeSet(3, col+3, col+7, color);
}

void pattern_N(int col, CRGB color) {
  columnSet(col, color);
  columnSet(col+1, color);
  rowRangeSet(1, col+2, col+4, color);
  rowRangeSet(2, col+4, col+6, color);
  columnSet(col+6, color);
  columnSet(col+7, color);
}

void pattern_M(int col, CRGB color) {
  columnSet(col, color);
  columnSet(col+1, color);
  rowRangeSet(1, col+2, col+4, color);
  rowRangeSet(2, col+3, col+6, color);
  rowRangeSet(1, col+5, col+7, color);
  columnSet(col+7, color);
  columnSet(col+8, color);
}

void pattern_17() {
  CRGB color1 = CRGB::Red;
  columnSet(5, color1);
  columnSet(6, color1);
  columnSet(7, color1);
  
  CRGB color2 = CRGB::Blue;
  rowRangeSet(0, 14, 20, color2);
  rowRangeSet(1, 17, 19, color2);
  rowRangeSet(2, 16, 18, color2);
  rowRangeSet(3, 15, 17, color2);
  FastLED.show();
  delay(10);
}

void pattern2() {
  for (int i = 0; i < 30; ++i) {
    ledSet(0, i, CRGB::Red);
    ledSet(1, i, CRGB::Green);
    ledSet(2, i, CRGB::Blue);
    ledSet(3, i, CRGB::Yellow);
    FastLED.show();
    delay(10);
    ledSet(0, i, CRGB::Black);
    ledSet(1, i, CRGB::Black);
    ledSet(2, i, CRGB::Black);
    ledSet(3, i, CRGB::Black);
  }
}

void pattern1() {
  for (int i = 0; i < 30; ++i) {
    leds[i] = CRGB::Red;
    leds[i+33] = CRGB::Green;
    leds[i+66] = CRGB::Blue;
    leds[i+99] = CRGB::Yellow;
    FastLED.show();
    delay(10);
    leds[i] = CRGB::Black;
    leds[i+33] = CRGB::Black;
    leds[i+66] = CRGB::Black;
    leds[i+99] = CRGB::Black;
  }
}
