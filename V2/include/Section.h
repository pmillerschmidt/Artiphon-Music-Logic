//@author Paul Miller-Schmidt

#pragma once
#include "ChordProgression.h"
#include "Scale.h"

class Section {
    public:
        //sets
        void set_rhythm(std::vector<float> rhythm){this->rhythm = rhythm;}
        void set_cp(ChordProgression cp){this->cp = cp;}
        void set_scale(Scale scale){this->scale = scale;}

        //gets
        std::vector<float> get_rhythm(){return rhythm;}
        ChordProgression get_cp(){return cp;}
        // int get_root(){return scale.get_root();}
        Scale get_scale(){return scale;}

        //constructors
        Section();
        Section(Scale scale, std::vector<float> rhythm, ChordProgression cp);
        
    private:
        std::vector<float> rhythm;
        ChordProgression cp;
        Scale scale;

};