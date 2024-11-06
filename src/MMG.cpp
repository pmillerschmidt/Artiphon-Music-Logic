//@author Paul Miller-Schmidt

#include "MMG.h"


MMG::MMG() {
    set_length(0);
    set_bpm(0);
};


MMG::MMG(float length, float bpm, Section section){
    set_length(length);
    set_bpm(bpm);
    set_section(section);
};

MMG::MMG(float length, float bpm, Section section, MM mm){
    set_length(length);
    set_bpm(bpm);
    set_section(section);
    set_mm(mm);
};

//n in the weight of the chord context
std::vector<Note> MMG::run(int n){
    //get section information
    Section section = get_section();
    std::vector<float> rhythm = section.get_rhythm();
    ChordProgression cp = section.get_cp();
    MM curr_mm = get_mm();
 
    //initialize time
    float time = 0;
    Chord curr_chord = cp.get_chord_at(0);
    //curr tone is the root of first chord
    int curr_tone = curr_chord.get_root().get_tone();

    //iterate through rhythm
    for (int i=0; i<section.get_rhythm().size(); i++){   
        //add the note
        Note temp(curr_tone, rhythm[i], 100);
        add(temp);
        curr_tone = curr_mm.get_PND(curr_tone).choose();
        //increment time
        time += rhythm[i];
    };
    return get();

};