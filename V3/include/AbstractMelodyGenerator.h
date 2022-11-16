//@author Paul Miller-Schmidt

#pragma once
#include <vector>
#include <math.h> 
#include "VecMath.h"
#include "Note.h"
#include "Section.h"
#include "PND.h"
#include "MM.h"

/*Melody Generator class
@brief - Generator objects to generate musical material. 
@param - Composed of hyperparameters (length, bpm), a vector of Notes for output, 
and a section that it is generating over.
@return - notes to be played.
*/

class AbstractMelodyGenerator {
    
  public:
        /* set functions
        @brief - simple set functions for variables of Generator.
        @param - the variable to be set.
        @return - void
        */
        void set_length(float length) {this->length = length;}
        void set_bpm(float bpm) {this->bpm = bpm;}
        void set_section(Section section){this->section = section;}
        void set_pnd(PND pnd){this->pnd = pnd;}
        void set_mm(MM mm){this->mm = mm;}

        /* get functions
        @brief - get functions for variables of Generator.
        @param - NULL
        @return - said variable. 
        */
        float get_length() {return length;}
        float get_bpm() {return bpm;}
        Section get_section(){return section;}
        PND get_pnd(){return pnd;}
        MM get_mm(){return mm;}

        
        /*get output
        @brief - gets the output vector. 
        @param - NULL
        @return - output vector.
        */
        std::vector<Note> get() {return this->out;}

        //Do something functions - described in src
        void add(Note note);
        void clear();
        Note next();
        virtual std::vector<Note> run(int n) = 0;

        /* constructors
        @brief - constructors for Note with no variables or all variables.
        */
        AbstractMelodyGenerator();
        AbstractMelodyGenerator(float length, float bpm, Section section);
        AbstractMelodyGenerator(float length, float bpm, Section section, PND pnd);
        AbstractMelodyGenerator(float length, float bpm, Section section, MM mm);

    private:
        //Variables 
        float length;
        float bpm;
        Section section;
        PND pnd;
        MM mm;
        std::vector<Note> out;
};
