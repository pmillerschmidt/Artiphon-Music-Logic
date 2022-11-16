//@author Paul Miller-Schmidt

#include "Arpeggiator.h"

Arpeggiator::Arpeggiator() {
    set_length(0);
    set_bpm(0);
};

Arpeggiator::Arpeggiator(float length, float bpm, Section section){
    set_length(length);
    set_bpm(bpm);
    set_section(section);
};


//Abstract run, plays root note based on rhythm 
std::vector<Note> Arpeggiator::run(int n) {
    
    //get section information
    Section section = get_section();
    std::vector<float> rhythm = section.get_rhythm();
    ChordProgression cp = section.get_cp();
    
    //initialize time
    float time = 0;

    
    //get initial chord
    Chord curr_chord = cp.get_chord_at(time);
    //up for poisitive direciton, down for negative
    // int degree = (n == 1) ? 0 : curr_chord.get_chord().size() - 1;
    int degree = 0;
    //iterate through rhythm
    for (int i=0; i<section.get_rhythm().size(); i++){
        
        // //if its a new chord (DOING NEW ROOT, MIGHT NOT WORK), get the new chord and reset counter
        // if (cp.get_chord_at(time).get_root().get_tone() != curr_chord.get_root().get_tone()){
        //     curr_chord = cp.get_chord_at(time);
        //     degree = (n == 1) ? 0 : curr_chord.get_chord().size() - 1;
        // };
        curr_chord = cp.get_chord_at(time);
        
        //get the current note and add it 
        Note curr_note = curr_chord.get_chord()[degree++ % curr_chord.get_chord().size()];
        // degree += n;
        Note temp(curr_note.get_tone(), rhythm[i], 100);
        add(temp);
        //increment times
        time += rhythm[i];
    };

    return get();
};