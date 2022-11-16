//@author Paul Miller-Schmidt
#include "Chord.h"

Chord::Chord(void) {
    length = 0;
};

Chord::Chord(std::vector<Note> chord, float length) {
    this->chord = chord;
    this->length = length;
};

// Chord::Chord(std::vector<int> tones, float length, unsigned char vel) {
//     for(int i=0; i<tones.size(); i++) {
//         Note temp = Note(tones[i], 0, length, vel);
//         this->chord.push_back(temp);
//     }
//     this->length = length;
// };

void Chord::set_values(std::vector<Note> chord, float length) {
    this->chord = chord;
    this->length = length;
};

void Chord::add(Note note) {
    chord.push_back(note);
}

Note Chord::get_root() {
    //if there is a chord, get the root
    if (this->chord.size() != 0){
        return this->chord.at(0);
    };
    Note null_note;
    return null_note;
    
};

std::vector<int> Chord::get_tones(){
    std::vector<int> res;
    for (Note n : this->chord)  
        res.push_back(n.get_tone());
    return res;
};

