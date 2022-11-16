//@author Paul Miller-Schmidt
//Probabalistic Melody Generator 

#pragma once
#include "AbstractMelodyGenerator.h"
#include "Distribution.h"
#include "PND.h"


class PMG : public AbstractMelodyGenerator {
    public:
        //constructors
        PMG();
        PMG(float length, float bpm, Section section);
        PMG(float length, float bpm, Section section, PND pnd);

        //Arp run
        std::vector<Note> run(int n);

};
