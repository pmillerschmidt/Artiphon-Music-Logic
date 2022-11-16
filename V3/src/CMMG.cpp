//@author Paul Miller-Schmidt

#include "CMMG.h"  


CMMG::CMMG() {
    set_length(0);
    set_bpm(0);
    this->chord_multiplier = 1;
    this->movement_hesitance = 1;
};


CMMG::CMMG(float length, float bpm, Section section){
    set_length(length);
    set_bpm(bpm);
    set_section(section);
    this->chord_multiplier = 1;
    this->movement_hesitance = 1;
};

CMMG::CMMG(float length, float bpm, Section section, MM mm){
    set_length(length);
    set_bpm(bpm);
    set_section(section);
    set_mm(mm);
    this->chord_multiplier = 1;
    this->movement_hesitance = 1;
};

CMMG::CMMG(float length, Section section, MM mm, float cm, float mh, float dm){
    set_length(length);
    set_bpm(120);
    set_section(section);
    set_mm(mm);
    this->chord_multiplier = cm;
    this->movement_hesitance = mh;
    this->downbeat_multiplier = dm;
};

// std::vector<Note> CMMG::run(int n){
//     Note null_note;
//     return {null_note};
// };

// n is the weight of the chord context
std::vector<Note> CMMG::run(int n){
    //get section information
    Section section = get_section();
    std::vector<float> rhythm = section.get_rhythm();
    ChordProgression cp = section.get_cp();
    MM curr_mm = get_mm();
    float desired_length = get_length();
    int downbeat_mask = 1;
 
    //initialize time
    float time = 0;
    
    //get initial chord
    Chord curr_chord = cp.get_chord_at(time);

    //input is the starting tone
    int curr_tone = n;

    //iterate through rhythm
    for (int i=0; i<section.get_rhythm().size(); i++){   
        // std::cout << time << "\n";
        //get current chord, if it is diff
        if (cp.get_chord_at(time).get_root().get_tone() != curr_chord.get_root().get_tone()){
            curr_chord = cp.get_chord_at(time);
            downbeat_mask = 1;
        }
        else {
            downbeat_mask = 0;
        }
    
        // std::cout << curr_chord.get_chord()[0].get_tone() << "\n";
        
        
        //add the note
        Note temp(curr_tone, rhythm[i], 100);
        add(temp);

        //increment time
        time += rhythm[i];
        // //if we have reached the number of bars, stop
        if (time >= 4*desired_length){break;}
        //pnd for this note - update current note
        PND temp_pnd = curr_mm.get_PND(curr_tone);
        
        temp_pnd.add_chord(curr_chord, this->chord_multiplier);
        temp_pnd.add_mask(curr_tone, this->movement_hesitance);
        temp_pnd.update(curr_chord.get_chord()[0].get_tone(), downbeat_mask*this->downbeat_multiplier);
        curr_tone = temp_pnd.choose();
    };
    return get();

};

// temp_pnd.add_chord(curr_chord, chord_multiplier);
        // PND temp_pnd = curr_mm.get_PND(curr_tone);

        // //add context: chord and mask 
        
        // temp_pnd.add_mask(curr_tone, movement_hesitance);
        // //choose the next tone
        // curr_tone = temp_pnd.choose();