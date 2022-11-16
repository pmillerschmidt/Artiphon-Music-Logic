//@author Paul Miller-Schmidt
//Markov Matrix 

#pragma once

#include <vector>
#include <map>
#include "PND.h"
#include "Distribution.h"

class MM {

    public:
        //sets
        void set_MM(std::map<int, PND> mm){this->mm = mm;}

        //gets
        std::map<int, PND> get_mm(){return mm;}
        std::vector<int> get_tones();
        std::vector<PND> get_PNDs();
        PND get_PND(int tone);

        //add element and add scale
        void add(int tone, PND pnd);
        void update(int first_tone, int second_tone, float prob);
        //update with melody line
        void update_line(std::vector<int> line);

        //get next 
        int next(int tone);

        //Constructors
        MM();
        MM(int root, std::map<int, PND> mm);
        MM(int root, std::vector<int> tones, std::vector<PND> pnds);
        // MM(int root, int octaves);
        
        
    private:
        //map of tones and their probabilities 
        std::map<int, PND> mm;
        int root;
        int octaves;


};