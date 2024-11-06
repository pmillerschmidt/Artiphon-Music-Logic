//@author Paul Miller-Schmidt


#include "AbstractMelodyGenerator.h"

AbstractMelodyGenerator::AbstractMelodyGenerator(){
    this->length = 0;
    this->bpm = 0;
};

AbstractMelodyGenerator::AbstractMelodyGenerator(float length, float bpm, Section section){
    this->length = length;
    this->bpm = bpm;
    this->section = section;
};

AbstractMelodyGenerator::AbstractMelodyGenerator(float length, float bpm, Section section, PND pnd){
    this->length = length;
    this->bpm = bpm;
    this->section = section;
    this->pnd = pnd;
};

//for MM
AbstractMelodyGenerator::AbstractMelodyGenerator(float length, float bpm, Section section, MM mm){
    this->length = length;
    this->bpm = bpm;
    this->section = section;
    this->mm = mm;
};


/*add note 
@brief - adds a note to the output vector.
@param - note to be added. 
@return - void.
*/
void AbstractMelodyGenerator::add(Note note){
    this->out.push_back(note);
};

  /*clear 
@brief - clears the output vector.
@param - NULL
@return - void.
*/
void AbstractMelodyGenerator::clear() {
    this->out.clear();
};

// //Abstract run, plays root note based on rhythm 
// std::vector<Note> AbstractMelodyGenerator::run() {
//     //iterate through rhythm, adding root as we go
//     for (int i=0; i<section.get_rhythm().size(); i++){
//         Note temp(section.get_root(), section.get_rhythm()[i], 100);
//         add(temp);
//     };

//     return out;
// };
