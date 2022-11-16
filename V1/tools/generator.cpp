#include <iostream>
#include <map>
#include <random>
#include <math.h> 
#include "MidiFile.h"
#include "VecMath.h"
#include "Note.h"
#include "MidiIO.h"

using namespace std;
using namespace smf;

//Major/Minor intervals
std::vector<int>MAJOR{0, 2, 4, 5, 7, 9, 11, 12, 14, 16, 17, 19, 21, 23};
std::vector<int>MINOR{0, 2, 3, 5, 7, 8, 10, 12, 14, 15, 17, 19, 20, 22};

//GENERATORS

//Chords
std::vector<int> gen_cp(std::vector<double> init, std::vector<std::vector<double>> MM, int n){
    std::vector<int> res;
    int curr = choose_dd(init, 1)[0];
    res.push_back(curr);
    for (int i=0;i<n-1; i++){
        curr = choose_dd(MM[curr], 1)[0];
        res.push_back(curr);
    }
    return res;
}

std::vector<std::vector<int>> gen_chords(int root, std::vector<int> mode, std::vector<int> cp){
    std::vector<std::vector<int>> res;
    for (int c : cp) {
        res.push_back({root + mode[c], root + mode[(c+2)], root + mode[(c+4)]});
    }
    return res;
}

//invert triad, take the top note 
void invert(std::vector<int> *chord){
    int max = 0;
    int index;

    for (int i=0;i<chord->size();i++) {
        if (chord->at(i) > max) {
            max = chord->at(i);
            index = i;
        }
    }
    chord->at(index) -= 12;
}


//RHYTHM GENERATION
//input: section length measured in quarter notes, minimum note length measured in quarter notes
void rh_gen(std::vector<double> *out, double secLen, double minLen) {
    
    if (secLen == minLen) {
        out->push_back(minLen);
    }
    else {
        //threshold between 0-1, if the minimum/section is > than the threshold, keep the note
        double thresh = choose_ud(0, 100, 1, 1)[0]/100.0;
        // std::cout << thresh << '\n';
        if (minLen/secLen > thresh) {
            out->push_back(secLen);
        }
        else {
            rh_gen(out, secLen / 2, minLen);
            rh_gen(out, secLen / 2, minLen);
        }
    }
}

// void gen_ABAB(std::vector<double> *out, std::vector<double> secLens, double minLen) {
//     std::vector<double> A;
//     std::vector<double> B;
//     rh_gen(A, secLens[0], minLen);
//     rh_gen(B, secLens[1], minLen);
//     bool is_A = true;
//     for (double sec : secLens)
//         if (is_A) rh_gen(A, sec, minLen);
//         else rh_gen(B, sec, minLen);


// }

int main(int argc, char** argv)
{
    
    //MIDI INFO
    MidiFile outputfile;        // create an empty MIDI file with one track
   outputfile.absoluteTicks();  // time information stored as absolute time
                               // (will be converted to delta time when written)
   outputfile.addTrack(2);     // Add another two tracks to the MIDI file
   vector<uchar> midievent;     // temporary storage for MIDI events
   midievent.resize(3);        // set the size of the array to 3 bytes
   int tpq = 120;              // default value in MIDI file is 48
   outputfile.setTicksPerQuarterNote(tpq);

    //How long of a loop do we want, four bar loop 
    int section_len = 16;

    //CHORDS
    //chord distributions for C Major scale, from 1 to 7, 1 5 most pop, then 3 4 6, then 2 7
    std::vector<double> chord_dist{4, 1, 2, 3, 4, 3, 2};
    //start on root
    std::vector<double> init{  1, 0, 0, 0, 0, 0, 0};
    //MM for chord progression
    std::vector<std::vector<double>> MM{
        {0, 0, 1, 2, 3, 2, 0}, 
        {0, 0, 0, 0, 1, 0, 0},
        {0, 0, 0, 1, 0, 1, 0}, 
        {0, 1, 0, 0, 1, 2, 0}, 
        {1, 0, 0, 1, 0, 1, 0}, 
        {1, 1, 0, 2, 1, 0, 0}, 
        {1, 0, 0, 0, 0, 0, 0},
        };

    //choose four chords
    // std::vector<int> cp = gen_cp(init, MM, 4);
    std::vector<int> cp{0, 5, 3, 4};
    std::vector<std::vector<int>> chords = gen_chords(48, MAJOR, cp);
    std::vector<int> chord_lens{4, 4, 4, 4};
    // for (std::vector<int> chord : chords)
    //     for (int note : chord)
    //         std::cout << " " << note << "\n";

    //MELODY
    // Scale distribution, C(60) to C(72)
    std::vector<double> scale_dist{1, 0, 1, 0, 1, 1, 0, 1, 0, 1, 0, 1, 1};
    std::vector<double> CM_dist{1, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 1};
    std::vector<double> Am_dist{1, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 1};
    std::vector<double> FM_dist{1, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 1};
    std::vector<double> GM_dist{0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0};
    std::vector<double> weights = sum_v(scale_dist, CM_dist);


    //generate melody rhythm
    std::vector<double> mrhythm;
    rh_gen(&mrhythm, section_len, 0.5);
    
    //generate melody 
    std::vector<int> melody = choose_dd(weights, mrhythm.size());
    add_constant_v(&melody, 72);
    melody.push_back(-1);

    //generate note lengths
    std::vector<double> note_lengths = choose_ud(0, 1, mrhythm.size(), 2);
    //generate melody velocities
    std::vector<double> velocities = choose_ud(50, 120, mrhythm.size(), 1);

    //print output
    for(double x : melody)
        std::cout << " " << x << "\n";


    //RHYTHM 


    //CHORD GENERATION
    int actiontime = 0;      // temporary storage for MIDI event time
    for (int i=0;i<chords.size();i++) {
        chord_on(&outputfile, 1, actiontime, chords[i], 100);
        actiontime += tpq*chord_lens[i];
        chord_off(&outputfile, 1, actiontime, chords[i], 100);
    }
    
//MELODY GENERATION
    int i=0;
    actiontime = 0;
//     while (melody[i] >= 0) {
//         //note on
//         note_on(&outputfile, 2, actiontime, 72, velocities[i]);
//         //increment time
//         actiontime += tpq * (mrhythm[i]);
//         //note_off
//         note_off(&outputfile, 2, actiontime, 72, velocities[i]);
//         i++;
//    }

    outputfile.sortTracks();         // make sure data is in correct order
    outputfile.write("gen.mid"); // write Standard MIDI File twinkle.mid
    return 0;
}