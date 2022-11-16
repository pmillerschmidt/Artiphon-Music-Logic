//@author Paul Miller-Schmidt

#pragma once
#include "Chord.h"
#include <vector>


class ChordProgression{
    public:
        //sets
        void set_cp(std::vector<Chord> cp){this->cp = cp;}
        void set_length(float length){this->length = length;}
        void add(Chord c);

        //gets
        std::vector<Chord> get_cp() {return cp;}
        float get_length() {return length;}

        //get chord based on time
        Chord get_chord_at(float time);

        //constructors
        ChordProgression(void);
        ChordProgression(std::vector<Chord> cp);
        ChordProgression(std::vector<Chord> cp, float length);

    private:
        std::vector<Chord> cp;
        float length;

};