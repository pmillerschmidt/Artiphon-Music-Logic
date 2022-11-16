//@author Paul Miller-Schmidt

#pragma once
#include "Note.h"
#include <vector>

class Chord {
    public:
        //sets
        void set_length(float length) {this->length = length;}
        void set_chord(std::vector<Note> chord) {this->chord = chord;}
        void set_values(std::vector<Note> chord, float length);
        void add(Note note);

        //gets
        float get_length() {return length;}
        std::vector<Note> get_chord() {return chord;}
        Note get_root();
        std::vector<int> get_tones();

        //constructor - root goes first when defining a chord
        Chord(void);
        Chord(std::vector<Note> chord, float length);
        Chord(std::vector<int>, float length);



    private:
        std::vector<Note> chord;
        float length;

};