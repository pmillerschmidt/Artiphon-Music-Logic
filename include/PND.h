//@author Paul Miller-Schmidt
//Probablistic Note Distribution

#pragma once

#include <vector>
#include <map>
#include <cstdlib>
#include "Note.h"
#include "Chord.h"
#include "Distribution.h"


class PND {

    public:
        //sets
        void set_tone_dist(std::map<int, float> td){this->tone_distribution = td;}

        //gets
        std::map<int, float> get_td(){return tone_distribution;}
        std::vector<int> get_tones();
        std::vector<float> get_probs();

        //add element and add scale
        void add(int tone, float prob);
        void apply_scale(std::vector<int> scale);
        void add_chord(Chord chord, float chord_weight);
        void subtract_chord(Chord chord, float chord_weight);
        void add_mask(int center, float intensity);
        void add_mask(int center, float spread, float intensity);
        
        //normalize 
        void normalize();
        //new mask function
        void mask_chord(Chord chord, float multiplier);
        void mask_tone(int tone, float multiplier);

        //update - add prob to existing val
        void update(int tone, float prob);

        //choose
        int choose();

        //Constructors
        PND();
        PND(int root, std::map<int, float> td);
        PND(int root, std::vector<int> tones, std::vector<float> probs);
        PND(int root, int octaves);
        
        
    private:
        //map of tones and their probabilities 
        std::map<int, float> tone_distribution;
        int root;
        int octaves;


};