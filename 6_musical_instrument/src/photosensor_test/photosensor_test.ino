#include <Control_Surface.h>

#define NUM_BEAMS 1
#define BEAM_HIGH 4095
#define BEAM_ACTIVATION_THRESHOLD 3500

BluetoothMIDI_Interface midi;

using namespace MIDI_Notes;

void readPins();
void printBeamActives();

int beams[] = { 33 };  
bool beam_actives[] = { false };

void setup() {
  Control_Surface.begin();
  Serial.begin(9600);

  for(int i = 0; i < NUM_BEAMS; i++) {
    pinMode(beams[i], INPUT);
  }
}

void loop() {
  readPins();

  // Send note 42 with velocity 127 on channel 1
  MIDI.sendNoteOn(42, 127, 1);

  delay(50);

  
//  printBeamActives();
}

void readPins() {
  int value = BEAM_HIGH;
  for (int i = 0; i < NUM_BEAMS; i++) {
    value = analogRead(beams[i]);
    if (value > BEAM_ACTIVATION_THRESHOLD) {
      beam_actives[i] = true;
    } else {
      beam_actives[i] = false;
    }
  }
}

void loadScale() {
  for(int i = 0; i < NUM_BEAMS; i++) {
    
  }
}

void printBeamActives() {
  Serial.print("[");
  for (int i = 0; i < NUM_BEAMS; i++) {
    Serial.print(beam_actives[i]);
    Serial.print(", ");
  }
  Serial.println("]");
}
