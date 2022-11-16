//@author Paul Miller-Schmidt

#pragma once
#include <vector>

//Length is measured in bars, rhythm is measured in quarter notes
class Rhythm {
    public:
        //sets
        void set_length(float length) {this->length = length;}
        void set_rhythm(std::vector<float> rhythm) {this->rhythm = rhythm;}

        //gets 
        float get_length() {return length;}
        std::vector<float> get_rhythm() {return rhythm;}

        //constructors
        Rhythm();
        Rhythm(float length, std::vector<float> rhythm);

    private: 
        float length;
        std::vector<float> rhythm;
};