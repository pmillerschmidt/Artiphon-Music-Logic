//@author Paul Miller-Schmidt
//Probabalistic Melody Generator 

#include "PMG.h"

PMG::PMG() {
    set_length(0);
    set_bpm(0);
};

PMG::PMG(float length, float bpm, Section section){
    set_length(length);
    set_bpm(bpm);
    set_section(section);
};


std::vector<Note> PMG::run(int n) {
    

};