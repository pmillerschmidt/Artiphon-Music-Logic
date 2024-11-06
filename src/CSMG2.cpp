//@author Paul Miller-Schmidt

#include "CSMG2.h"  


CSMG2::CSMG2() {
    set_length(0);
    set_bpm(0);
    this->chord_multiplier = 1;
    this->movement_hesitance = 1;
};


CSMG2::CSMG2(float length, float bpm, Section section){
    set_length(length);
    set_bpm(bpm);
    set_section(section);
    this->chord_multiplier = 1;
    this->movement_hesitance = 1;
};

CSMG2::CSMG2(float length, float bpm, Section section, MM mm){
    set_length(length);
    set_bpm(bpm);
    set_section(section);
    set_mm(mm);
    this->chord_multiplier = 1;
    this->movement_hesitance = 1;
};

//rc should be less than one 
CSMG2::CSMG2(float length, Section section, MM mm, float cm, float mh, float ms, float dm, float rc){
    set_length(length);
    set_bpm(120);
    set_section(section);
    set_mm(mm);
    this->chord_multiplier = cm;
    this->movement_hesitance = mh;
    this->movement_spread = ms;
    this->downbeat_multiplier = dm;
    this->repitition_coefficient = rc;
};

//rc should be less than one 
CSMG2::CSMG2(float length, Section section, MM mm, std::vector<float> hp){
    set_length(length);
    set_bpm(120);
    set_section(section);
    set_mm(mm);
    //make sure it is five values
    assert(hp.size() == 5);
    this->chord_multiplier = hp[0];
    this->downbeat_multiplier = hp[1];
    this->movement_hesitance = hp[2];
    this->movement_spread = hp[3];
    this->repitition_coefficient = hp[4];
};


// n is the weight of the chord context
std::vector<Note> CSMG2::run(int n){
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
        // //if we have reached the number of bars, stop
        if (time >= 4*desired_length){break;}

        //get current chord, if it is diff
        if (cp.get_chord_at(time).get_root().get_tone() != curr_chord.get_root().get_tone()){
            curr_chord = cp.get_chord_at(time);
            downbeat_mask = 1;
        }else {downbeat_mask = 0;}
    
        // std::cout << time << "\n";
        // std::cout << curr_chord.get_root().get_tone() << "\n";
        //add the note
        Note temp(curr_tone, rhythm[i], 100);
        add(temp);

        
        //pnd for this note - update current note
        PND temp_pnd = curr_mm.get_PND(curr_tone);
        //normalize the distribution
        temp_pnd.normalize();
        //chord mask
        temp_pnd.mask_chord(curr_chord, chord_multiplier);
        //downbeat mask
        temp_pnd.mask_tone(curr_chord.get_root().get_tone(), downbeat_mask*downbeat_multiplier);
        //movement mask
        temp_pnd.add_mask(curr_tone, movement_spread, movement_hesitance);
        //repitition mask
        temp_pnd.mask_tone(curr_tone, repitition_coefficient);
        curr_tone = temp_pnd.choose();

        //increment time
        time += rhythm[i];
        
    };
    return get();

};
