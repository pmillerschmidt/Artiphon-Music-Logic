//@author Paul Miller-Schmidt
//Probablistic Note Distribution

#pragma once

#include <vector>
#include <map>
#include "Note.h"

class PND {

    public:
        //sets
        void set_tone_dist(std::map<int, float> td){this->tone_distribution = td;}

        //gets
        std::map<int, float> get_td(){return tone_distribution;}
        std::vector<int> get_tones();
        std::vector<float> get_probs();

        //add
        void add(int tone, float prob);

        //update - add prob to existing val
        void update(int tone, float prob);

        //Constructors
        PND();
        PND(std::map<int, float> td);
        PND(std::vector<int> tones, std::vector<float> probs);

        
        
    private:
        //map of tones and their probabilities 
        std::map<int, float> tone_distribution;


};