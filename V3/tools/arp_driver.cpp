
/*
@author Paul Miller-Schmidt

Driver program for algorithmic musical generation. 
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


    Note c_sharp_note(61, 4, 100); Note d_sharp_note(63, 4, 100); Note e_note(64, 4, 100);
    Note f_sharp_note(66, 4, 100); Note g_sharp_note(68, 4, 100); Note a_note(69, 4, 100);
    Note b_note(71, 4, 100); Note c_sharp2_note(73, 4, 100); Note d_sharp2_note(75, 4, 100); 
    Note e2_note(76, 4, 100); Note f_sharp2_note(78, 4, 100); Note g_sharp2_note(80, 4, 100); 
    Note a2_note(81, 4, 100); Note b2_note(83, 4, 100); Note c_sharp3_note(85, 4, 100); 


    // std::vector<Note> notes{c_note, d_note, e_note, f_note, g_note, a_note, b_note, c2_note};
    std::vector<Note> c_sharp_minor{c_sharp_note, e_note, g_sharp_note, c_sharp2_note, e2_note, g_sharp2_note};
    std::vector<Note> a_major{a_note, c_sharp2_note, e2_note, g_sharp2_note, a2_note, c_sharp3_note};
    std::vector<Note> f_sharp_minor{f_sharp_note, a_note, c_sharp2_note, f_sharp2_note, a2_note, c_sharp3_note};
    std::vector<Note> g_sharp_minor{g_sharp_note, b_note, d_sharp2_note, f_sharp2_note, g_sharp2_note, b2_note};
    Chord c_sharp(c_sharp_minor, 4);
    Chord a(a_major, 4);
    Chord f_sharp(f_sharp_minor, 4);
    Chord g_sharp(g_sharp_minor, 4);
    ChordProgression verse_prog({c_sharp, a, f_sharp, g_sharp});

    //make rhythm and progression and the verse section
    // std::vector<float> verse_rhythm{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
    // std::vector<float> verse_rhythm{0.5, 0.25, 0.25, 0.5, 0.25, 0.25, 1, 0.5, 0.5, 
    //                                 0.5, 0.25, 0.25, 0.5, 0.25, 0.25, 1, 0.5, 0.5, 
    //                                 0.5, 0.25, 0.25, 0.5, 0.25, 0.25, 1, 0.5, 0.5, 
    //                                 0.5, 0.25, 0.25, 0.5, 0.25, 0.25, 1, 0.5, 0.5};
    std::vector<float> verse_rhythm{1.0/3.0, 1.0/3.0, 1.0/3.0, 1.0/3.0, 1.0/3.0, 1.0/3.0, 1.0/3.0, 1.0/3.0, 1.0/3.0, 1.0/3.0, 1.0/3.0, 1.0/3.0,
                                    1.0/3.0, 1.0/3.0, 1.0/3.0, 1.0/3.0, 1.0/3.0, 1.0/3.0, 1.0/3.0, 1.0/3.0, 1.0/3.0, 1.0/3.0, 1.0/3.0, 1.0/3.0,
                                    1.0/3.0, 1.0/3.0, 1.0/3.0, 1.0/3.0, 1.0/3.0, 1.0/3.0, 1.0/3.0, 1.0/3.0, 1.0/3.0, 1.0/3.0, 1.0/3.0, 1.0/3.0,
                                    1.0/3.0, 1.0/3.0, 1.0/3.0, 1.0/3.0, 1.0/3.0, 1.0/3.0, 1.0/3.0, 1.0/3.0, 1.0/3.0, 1.0/3.0, 1.0/3.0, 1.0/3.0};
    
    Section verse(49, 'M', verse_rhythm, verse_prog);
    // Section verse;
    // add_progression(&outputfile, 1, verse_prog, 0);

    //generate melody 
    Arpeggiator verse_generator(4, 120, verse);
    std::vector<Note> verse_melody = verse_generator.run(1);
    add_consecutive_notes(&outputfile, 2, verse_melody, 0);
    
    //print chord
    std::cout << verse.get_key() << "\n";




    //WRITE TO MIDI File
    outputfile.sortTracks();         // make sure data is in correct order
    outputfile.write("arp_out.mid"); // write Standard MIDI File twinkle.mid
    return 0;
}
