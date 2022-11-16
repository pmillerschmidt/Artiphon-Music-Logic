//@author Paul Miller-Schmidt
#include "ChordProgression.h"

ChordProgression::ChordProgression(void) {
    length = 0;
};

ChordProgression::ChordProgression(std::vector<Chord> cp) {
    for (Chord c : cp) {
        this->cp.push_back(c);
        this->length += c.get_length();
    };
};

ChordProgression::ChordProgression(std::vector<Chord> cp, float length) {
    for (Chord c : cp) {
        this->cp.push_back(c);
    };
    this->length = length;
};

void ChordProgression::add(Chord c) {
    this->cp.push_back(c);
};

//get chord based on time
Chord ChordProgression::get_chord_at(float time){
    float start_of_chord = 0;
    for (Chord c : get_cp()){
        if (start_of_chord <= time && time < start_of_chord+c.get_length()){return c;}
        else {start_of_chord += c.get_length();}
    };
    //if couldn't find, return null chord
    Chord null_chord;
    return null_chord;
};