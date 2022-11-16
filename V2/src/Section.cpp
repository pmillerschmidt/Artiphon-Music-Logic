//@author Paul Miller-Schmidt

#include "Section.h"


Section::Section() {

};

Section::Section(Scale scale, std::vector<float> rhythm, ChordProgression cp){
    this->scale = scale;
    this->rhythm = rhythm;
    this->cp = cp;
};