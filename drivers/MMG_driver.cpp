
/*
@author Paul Miller-Schmidt

Driver program for algorithmic musical generation using PMG.
*/
#include <iostream>
#include <random>
#include <MidiFile.h>

//My files
#include "Note.h"
#include "Chord.h"
#include "ChordProgression.h"
#include "VecMath.h"
#include "Section.h"
#include "Distribution.h"
#include "AbstractMelodyGenerator.h"
#include "Arpeggiator.h"
#include "PND.h"
#include "MM.h"
#include "MMG.h"

using namespace std;
using namespace smf;

//Ticks per quarter note. MIDI default is 48. 
#define TPQ 120


// //Major/Minor intervals
// std::vector<int>MAJOR{0, 2, 4, 5, 7, 9, 11, 12};
// std::vector<int>MINOR{0, 2, 3, 5, 7, 8, 10, 12};


/* note_on
@brief - add note on message to MIDI file. 
@param - MidiFile to add note to, the channel, and the parameters of the note. 
@return - void.
*/
void note_on(MidiFile *file, int channel, float time, int note, char velocity) {
    vector<uchar> midievent;     // temporary storage for MIDI events
    midievent.resize(3); 
    midievent[0] = 0x90; //note on
    midievent[1] = note;
    midievent[2] = velocity;
    file->addEvent(channel, time, midievent);
};
/* note_off
@brief - add note off message to MIDI file. 
@param - MidiFile to add note to, the channel, and the parameters of the note. 
@return - void.
*/
void note_off(MidiFile *file, int channel, float time, int note, char velocity) {
    vector<uchar> midievent;     // temporary storage for MIDI events
    midievent.resize(3);  
    midievent[0] = 0x80; //note off
    midievent[1] = note;
    midievent[2] = velocity;
    file->addEvent(channel, time, midievent);
};

/* add_note
@brief - adds note to file. 
@param - MidiFile and channel to add to, Note to be added and bpm of track. 
@return - void. 
*/
void add_note(MidiFile *file, int channel, Note note, float time) {
    note_on(file, 1, time * TPQ, note.get_tone(), note.get_vel());
    note_off(file, 1, (time + note.get_length()) * TPQ, note.get_tone(), note.get_vel());

};

/* add_notes
@brief - adds a collection of notes to file. 
@param - MidiFile and channel to add to, notes to be added and bpm of track. 
@return - void. 
*/
void add_notes(MidiFile *file, int channel, std::vector<Note> notes, float time) {
    for (Note note : notes) 
        add_note(file, channel, note, time);
};

/* add_notes consecutively 
@brief - adds a collection of notes to file. 
@param - MidiFile and channel to add to, notes to be added and bpm of track. 
@return - void. 
*/
void add_consecutive_notes(MidiFile *file, int channel, std::vector<Note> notes, float init_time) {
    float time = init_time;
    for (Note note : notes) {
        add_note(file, channel, note, time);
        time += note.get_length();
    };
};

/*add progression 
@brief - add entire chord progression, consecutively.
*/
void add_progression(MidiFile *file, int channel, ChordProgression cp, float init_time) {
    float time = init_time;
    for (Chord c : cp.get_cp()) {
        add_notes(file, channel, c.get_chord(), time);
        time += c.get_length();
    };
};

int main(int argc, char** argv)
{
    
    //MIDI File Set-Up
    MidiFile outputfile;        // create an empty MIDI file with one track
    outputfile.absoluteTicks();  // time information stored as absolute time
                               // (will be converted to delta time when written)
    outputfile.addTrack(2);     // Add another two tracks to the MIDI file
    outputfile.setTicksPerQuarterNote(TPQ);


    // //Set of notes
    Note c_note(60, 4, 100); Note d_note(62, 4, 100); Note e_note(64, 4, 100);
    Note f_note(65, 4, 100); Note g_note(67, 4, 100); Note a_note(69, 4, 100);
    Note b_note(71, 4, 100); Note c2_note(72, 4, 100); Note d2_note(74, 4, 100); 
    Note e2_note(76, 4, 100); Note f2_note(77, 4, 100); Note g2_note(79, 4, 100); 
    Note a2_note(81, 4, 100); Note b2_note(83, 4, 100); Note c3_note(84, 4, 100); 


    // std::vector<Note> notes{c_note, d_note, e_note, f_note, g_note, a_note, b_note, c2_note};
    std::vector<Note> c_major{c_note, e_note, g_note};
    std::vector<Note> f_major{f_note, a_note, c2_note};
    std::vector<Note> a_major{a_note, c2_note, e2_note};
    std::vector<Note> g_major{g_note, b_note, d2_note};
    Chord c(c_major, 4);
    Chord g(g_major, 4);
    Chord f(f_major, 4);
    Chord a(a_major, 4);
    ChordProgression verse_prog({c, g, a, f});

    //make rhythm and progression and the verse section // std::vector<float> verse_rhythm{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
    std::vector<float> verse_rhythm{0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 1,
                                    0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 1, 
                                    0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 1, 
                                    0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 1};
    
    Section verse(48, 'M', verse_rhythm, verse_prog);
    // Section verse;
    // add_progression(&outputfile, 1, verse_prog, 0);
    

    std::vector<int> major{0, 2, 4, 5, 7, 9, 11};
    std::vector<int> minor{0, 2, 3, 5, 7, 8, 10};

    //MM - SET UP 
    std::vector<int> tones{60, 62, 64, 65, 67, 69, 71};
    PND c_pnd(60, tones, {0, 0, 1, 1, 3, 2, 0});
    PND d_pnd(60, tones, {0, 0, 0, 2, 1, 3, 1});
    PND e_pnd(60, tones, {1, 0, 0, 0, 3, 1, 2});
    PND f_pnd(60, tones, {1, 1, 0, 0, 0, 3, 2});
    PND g_pnd(60, tones, {2, 3, 1, 0, 0, 0, 1});
    PND a_pnd(60, tones, {2, 0, 2, 1, 1, 0, 0});
    PND b_pnd(60, tones, {0, 2, 1, 1, 2, 0, 0});

    //make an MM
    MM verse_mm(60, tones, {c_pnd, d_pnd, e_pnd, f_pnd, g_pnd, a_pnd, b_pnd});
    
    // std::cout << verse_mm.next(67) << "\n";

    //MMG
    MMG verse_gen(4, 120, verse, verse_mm);
    std::vector<Note> verse_melody = verse_gen.run(10);
    //print chord
    // std::cout << probs[0] << "\n";
    add_consecutive_notes(&outputfile, 2, verse_melody, 0);
    

    //WRITE TO MIDI File
    outputfile.sortTracks();         // make sure data is in correct order
    outputfile.write("MMG_out.mid"); // write Standard MIDI File twinkle.mid
    return 0;
}
