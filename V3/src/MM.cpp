// @author Paul Miller-Schmidt

#include "MM.h"

//constructors
MM::MM() {
    //do nothing
    this->root = 60;
    this->octaves = 0;
};

MM::MM(int root, std::map<int, PND> mm){
    this->mm = mm;
    this->root = root;
    this->octaves = mm.size() / 12 + 1;
};

MM::MM(int root, std::vector<int> tones, std::vector<PND> pnds){
    //make sure they are the same length
    assert(tones.size() == pnds.size());

    this->root = root;
    this->octaves = tones.size() / 12 + 1;

    for (int i=0; i<tones.size(); i++){
        mm[tones[i]] = pnds[i];
    };
};

// //constructor using root and how many octaves
// MM::MM(int root, int octaves){
//     this->root = root;
//     this->octaves = octaves;

//     for (int i = root; i<root+12*octaves; i++){
//         MM[i] = 0;
//     };
// };

//get tones
std::vector<int> MM::get_tones(){
    std::vector<int> tones;
        for(auto const& imap: mm)
            tones.push_back(imap.first);
    return tones;
};

//get pnds
std::vector<PND> MM::get_PNDs(){
    std::vector<PND> pnds;
        for(auto const& imap: mm)
            pnds.push_back(imap.second);
    return pnds;
};

//get pnd for tone
PND MM::get_PND(int tone){
    return mm[tone];
};

//add element ot MM
void MM::add(int tone, PND pnd){
    this->mm[tone] = pnd;
};

void MM::update(int first_tone, int second_tone, float prob) {
    //if the entry doesn't exist
    if (mm.find(first_tone) == mm.end()){
        PND temp;
        temp.add(second_tone, prob);
        add(first_tone, temp);
    }
    else{mm[first_tone].update(second_tone, prob);}
}

void MM::update_line(std::vector<int> line){
    for (int i=1; i<line.size(); i++){
        update(line[i-1], line[i], 1);
    }
}


int MM::next(int tone){
    return get_PND(tone).choose();
}
