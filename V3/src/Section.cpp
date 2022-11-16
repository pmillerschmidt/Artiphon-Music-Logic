//@author Paul Miller-Schmidt

#include "Section.h"


Section::Section() {
    this->key = 0;
};

Section::Section(std::vector<float> rhythm, ChordProgression cp){
    this->key = 0;
    this->mode = 'm';
    this->rhythm = rhythm;
    this->cp = cp;
    
};

Section::Section(int key, char mode, std::vector<float> rhythm, ChordProgression cp){
    this->key = key;
    this->mode = mode;
    this->rhythm = rhythm;
    this->cp = cp;
    
};