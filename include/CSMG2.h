//@author Paul Miller-Schmidt
//Contextualized Markov Melody Generator 

#pragma once
#include <iostream>
#include "AbstractMelodyGenerator.h"
#include "MM.h"
#include "PND.h"
#include "ChordProgression.h"


//Markov matrix might be map of note and a PND, to get the next note
class CSMG2 : public AbstractMelodyGenerator{
        public:
                //constructors
                CSMG2();
                CSMG2(float length, float bpm, Section section);
                CSMG2(float length, float bpm, Section section, MM mm);
                CSMG2(float length, Section section, MM mm, float cm, float mh, float ms, float dm, float rc);
                CSMG2(float length, Section section, MM mm, std::vector<float> hp);

                //Arp run
                std::vector<Note> run(int n);

        private:
                float chord_multiplier;
                float downbeat_multiplier;
                float movement_hesitance;
                float movement_spread;
                float repitition_coefficient;

};