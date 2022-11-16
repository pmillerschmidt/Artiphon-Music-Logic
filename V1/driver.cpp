
/*
@author Paul Miller-Schmidt

Driver program for algorithmic musical generation. 
*/
#include <iostream>
#include <map>
#include <random>
#include <MidiFile.h>
#include "Generator.h"

using namespace std;
using namespace smf;

//Ticks per quarter note. MIDI default is 48. 
#define TPQ 120


//Major/Minor intervals
std::vector<int>MAJOR{0, 2, 4, 5, 7, 9, 11, 12, 14, 16, 17, 19, 21, 23};
std::vector<int>MINOR{0, 2, 3, 5, 7, 8, 10, 12, 14, 15, 17, 19, 20, 22};

/* note_on
@brief - add note on message to MIDI file. 
@param - MidiFile to add note to, the channel, and the parameters of the note. 
@return - void.
*/
void note_on(MidiFile *file, int channel, double time, int note, int velocity) {
    vector<uchar> midievent;     // temporary storage for MIDI events
    midievent.resize(3); 
    midievent[0] = 0x90; //note on
    midievent[1] = note;
    midievent[2] = velocity;
    file->addEvent(channel, time, midievent);
}
/* note_off
@brief - add note off message to MIDI file. 
@param - MidiFile to add note to, the channel, and the parameters of the note. 
@return - void.
*/
void note_off(MidiFile *file, int channel, double time, int note, int velocity) {
    vector<uchar> midievent;     // temporary storage for MIDI events
    midievent.resize(3);  
    midievent[0] = 0x80; //note off
    midievent[1] = note;
    midievent[2] = velocity;
    file->addEvent(channel, time, midievent);
}

/* add_note
@brief - adds note to file. 
@param - MidiFile and channel to add to, Note to be added and bpm of track. 
@return - void. 
*/
void add_note(MidiFile *file, int channel, Note note) {
    note_on(file, 1, note.get_time() * TPQ, note.get_tone(), note.get_vel());
    note_off(file, 1, (note.get_time() + note.get_len()) * TPQ, note.get_tone(), note.get_vel());

}

/* add_notes
@brief - adds a collection of notes to file. 
@param - MidiFile and channel to add to, notes to be added and bpm of track. 
@return - void. 
*/
void add_notes(MidiFile *file, int channel, std::vector<Note> notes) {
    for (Note note : notes) 
        add_note(file, channel, note);
}



int main(int argc, char** argv)
{
    
    //MIDI File Set-Up
    MidiFile outputfile;        // create an empty MIDI file with one track
   outputfile.absoluteTicks();  // time information stored as absolute time
                               // (will be converted to delta time when written)
   outputfile.addTrack(2);     // Add another two tracks to the MIDI file
   outputfile.setTicksPerQuarterNote(TPQ);

    //Set of notes
    Note c_note(60, 0, 1.0, 100); Note d_note(62, 0, 1.0, 100); Note e_note(64, 0, 1.0, 100);
    Note f_note(65, 0, 1.0, 100); Note g_note(67, 0, 1.0, 100); Note a_note(69, 0, 1.0, 100);
    Note b_note(71, 0, 1.0, 100); Note c2_note(72, 0, 1.0, 100); 
    std::vector<Note> notes{c_note, d_note, e_note, f_note, g_note, a_note, b_note, c2_note};
    //note weights - equally weights with edge toward C and G
    std::vector<double> note_weights{0.2, 0.1, 0.1, 0.1, 0.2, 0.1, 0.1, 0.1};

    //create random discrete distribution algorithm
    RandomDD rdd;
    rdd.set_choices(notes);
    rdd.set_weights(note_weights);
    // std::cout << a.next().get_tone() << "\n";

    //generator
    Generator g(16, 120, c_note, rdd);
    //generate notes
    std::cout << g.next().get_tone() << "\n";
    //add notes
    std::vector<Note> res = g.get();
    // add_notes(&outputfile, 1, res);
    // std::cout << res[0].get_tone() << "\n";



    //WRITE TO MIDI File
    outputfile.sortTracks();         // make sure data is in correct order
    outputfile.write("gen.mid"); // write Standard MIDI File twinkle.mid
    return 0;
}

