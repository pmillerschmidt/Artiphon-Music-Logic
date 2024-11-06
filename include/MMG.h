//@author Paul Miller-Schmidt
//Markov Melody Generator 

#pragma once
#include "AbstractMelodyGenerator.h"
#include "MM.h"
#include "PND.h"


//Markov matrix might be map of note and a PND, to get the next note
class MMG : public AbstractMelodyGenerator{
        public:
        //constructors
        MMG();
        MMG(float length, float bpm, Section section);
        MMG(float length, float bpm, Section section, MM mm);

        //Arp run
        std::vector<Note> run(int n);

};