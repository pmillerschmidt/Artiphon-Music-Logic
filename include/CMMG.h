//@author Paul Miller-Schmidt
//Contextualized Markov Melody Generator 

#pragma once
#include <iostream>
#include "AbstractMelodyGenerator.h"
#include "MM.h"
#include "PND.h"
#include "ChordProgression.h"


//Markov matrix might be map of note and a PND, to get the next note
class CMMG : public AbstractMelodyGenerator{
        public:
                //constructors
                CMMG();
                CMMG(float length, float bpm, Section section);
                CMMG(float length, float bpm, Section section, MM mm);
                CMMG(float length, Section section, MM mm, float cm, float mh, float dm);

                //Arp run
                std::vector<Note> run(int n);

        private:
                float chord_multiplier;
                float movement_hesitance;
                float downbeat_multiplier;

};