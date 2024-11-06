//@author Paul Miller-Schmidt

#include "Rhythm.h"

Rhythm::Rhythm() {
    this->length = 0;
};

//length is in bars, rhythm is quarter notes
Rhythm::Rhythm(float length, std::vector<float>rhythm){
    this->length = length;
    this->rhythm = rhythm;
}