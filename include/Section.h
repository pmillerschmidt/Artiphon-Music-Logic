//@author Paul Miller-Schmidt

#pragma once
#include "ChordProgression.h"
#include <vector>

class Section {
    public:
        //sets
        void set_rhythm(std::vector<float> rhythm){this->rhythm = rhythm;}
        void set_cp(ChordProgression cp){this->cp = cp;}
        void set_key(int key){this->key = key;}
        void set_mode(char m){this->mode = m;}

        //gets
        std::vector<float> get_rhythm(){return rhythm;}
        ChordProgression get_cp(){return cp;}
        int get_key(){return key;}
        char get_mode(){return mode;}

        //constructors
        Section();
        Section(std::vector<float> rhythm, ChordProgression cp);
        Section(int key, char mode, std::vector<float> rhythm, ChordProgression cp);
        
    private:
        int key;
        char mode;
        std::vector<float> rhythm;
        ChordProgression cp;

};