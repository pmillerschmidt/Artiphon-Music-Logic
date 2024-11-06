//@author Paul Miller-Schmidt

#pragma once
#include "AbstractMelodyGenerator.h"

class Arpeggiator : public AbstractMelodyGenerator {

    public:
        //constructors
        Arpeggiator();
        Arpeggiator(float length, float bpm, Section section);

        //Arp run
        std::vector<Note> run(int n);

};