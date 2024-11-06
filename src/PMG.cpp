//@author Paul Miller-Schmidt

#include "PMG.h"

PMG::PMG() {
    set_length(0);
    set_bpm(0);
};


PMG::PMG(float length, float bpm, Section section){
    set_length(length);
    set_bpm(bpm);
    set_section(section);
};

PMG::PMG(float length, float bpm, Section section, PND pnd){
    set_length(length);
    set_bpm(bpm);
    set_section(section);
    set_pnd(pnd);
};

std::vector<Note> PMG::run(int n){
    //get section information
    Section section = get_section();
    std::vector<float> rhythm = section.get_rhythm();
    ChordProgression cp = section.get_cp();
    PND curr_pnd = get_pnd();
 
    //initialize time
    float time = 0;
    
    //get initial chord
    Chord curr_chord = cp.get_chord_at(time);
    //add chord to pnd
    curr_pnd.add_chord(curr_chord, 2);
    //iterate through rhythm
    for (int i=0; i<section.get_rhythm().size(); i++){
        
        //if its a new chord (DOING NEW ROOT, MIGHT NOT WORK), get the new chord
        if (cp.get_chord_at(time).get_root().get_tone() != curr_chord.get_root().get_tone()){
            //take away previous chord from PND
            curr_pnd.subtract_chord(curr_chord, 2);
            curr_chord = cp.get_chord_at(time);
            //add new chord to PND
            curr_pnd.add_chord(curr_chord, 2);
        };
        
        //get the chosen note from the PND
        int chosen_tone = curr_pnd.choose();
        Note temp(chosen_tone, rhythm[i], 100);
        add(temp);
        //increment times
        time += rhythm[i];
    };
    return get();
};