#include <Adafruit_NeoPixel.h>

//Input PINs
#define FLOW_SENSOR_PIN 7 // digital input
#define PRESSURE_SENSOR_PIN A2 // analog input
//Output PINs
#define WATER_PUMP_PIN 2 // digital output
#define GLASS_STRIP_PIN 3 // digital output
#define SPEAKER_PIN 4 // digital output
#define BOTTLE_STRIP_PIN 5 // digital output

//LED strips
#define BOTTLE_STRIP_COUNT 11
#define GLASS_STRIP_COUNT 12
#define LED_BRIGHTNESS 100

Adafruit_NeoPixel bottleStrip(BOTTLE_STRIP_COUNT, BOTTLE_STRIP_PIN, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel glassStrip(GLASS_STRIP_COUNT, GLASS_STRIP_PIN, NEO_GRB + NEO_KHZ800);

volatile double waterFlow;

#define PIN 2
void setup() {
  pinMode(FLOW_SENSOR_PIN, INPUT);
  pinMode(PRESSURE_SENSOR_PIN, INPUT);
  pinMode(SPEAKER_PIN, OUTPUT);
  pinMode(WATER_PUMP_PIN, OUTPUT);
  pinMode(BOTTLE_STRIP_PIN, OUTPUT);
  pinMode(GLASS_STRIP_PIN, OUTPUT);
  bottleStrip.begin(); // INITIALIZE NeoPixel strip object (REQUIRED)
  bottleStrip.show(); // Turn OFF all pixels ASAP
  bottleStrip.setBrightness(LED_BRIGHTNESS); // Set BRIGHTNESS to about 1/5 (max = 255)
  glassStrip.begin(); // INITIALIZE NeoPixel strip object (REQUIRED)
  glassStrip.show(); // Turn OFF all pixels ASAP
  glassStrip.setBrightness(LED_BRIGHTNESS); // Set BRIGHTNESS to about 1/5 (max = 255)
  Serial.begin(9600);
  waterFlow = 0;
  delay(10000);
}

void blink(Adafruit_NeoPixel &strip, uint32_t color){
  strip.clear();
  for(int i = 0;  i < strip.numPixels(); i++){
    strip.setPixelColor(i, color);
  }
  strip.show();
  delay(1000);
  strip.clear();
  strip.show();
}

void pulse() {  // measure the quantity of square waves
  waterFlow += 1.0 / 5880.0; // 5880 is the number of Pulses required for one liter
}

void loop() {
  Serial.println("Lautsprecher...");
  delay(1000);
  tone(SPEAKER_PIN, 300, 1000);
  delay(2000);

  Serial.println("Bottle LED...");
  delay(1000);
  blink(bottleStrip, bottleStrip.Color(255, 0, 0));
  delay(2000);

  Serial.println("Glass LED...");
  delay(1000);
  blink(glassStrip, glassStrip.Color(255, 0, 0));
  delay(2000);

  Serial.println("Wasserpumpe...");
  delay(1000);
  digitalWrite(WATER_PUMP_PIN, HIGH);
  delay(1000);
  digitalWrite(WATER_PUMP_PIN, LOW);
  delay(2000);

  Serial.println("Flow Sensor...");
  delay(1000);
  attachInterrupt(digitalPinToInterrupt(FLOW_SENSOR_PIN), pulse, RISING);
  for(int i = 0; i < 10; i++){
    Serial.println(waterFlow);
    delay(200);
  }
  detachInterrupt(digitalPinToInterrupt(FLOW_SENSOR_PIN)) ; // flow sensor stops measuring
  delay(2000);

  Serial.println("Drucksensor...");
  delay(1000);
  for(int i = 0; i < 10; i++){
    Serial.println(analogRead(PRESSURE_SENSOR_PIN));
    delay(200);
  }
  delay(2000);  
}
