// @author Paul Miller-Schmidt

#include "PND.h"


//constructors
PND::PND() {
    //do nothing
    this->root = 60;
    this->octaves = 0;
};

PND::PND(int root, std::map<int, float> td){
    this->tone_distribution = td;
    this->root = root;
    this->octaves = td.size() / 12 + 1;
};

PND::PND(int root, std::vector<int> tones, std::vector<float> probs){
    //make sure they are the same length
    assert(tones.size() == probs.size());

    this->root = root;
    this->octaves = tones.size() / 12 + 1;

    for (int i=0; i<tones.size(); i++){
        tone_distribution[tones[i]] = probs[i];
    };
};

//constructor using root and how many octaves
PND::PND(int root, int octaves){
    this->root = root;
    this->octaves = octaves;

    for (int i = root; i<root+12*octaves; i++){
        tone_distribution[i] = 0;
    };
};

//get tones
std::vector<int> PND::get_tones(){
    std::vector<int> tones;
        for(auto const& imap: tone_distribution)
            tones.push_back(imap.first);
    return tones;
};

//get probs
std::vector<float> PND::get_probs(){
    std::vector<float> probs;
        for(auto const& imap: tone_distribution)
            probs.push_back(imap.second);
    return probs;
};

//add element ot PND
void PND::add(int tone, float prob){
    this->tone_distribution[tone] = prob;
};

//update PND element
void PND::update(int tone, float prob) {
    this->tone_distribution[tone] += prob;
};

//add scale
void PND::apply_scale(std::vector<int> scale){
    //iterate through all octaves
    for (int i=0; i<octaves; i++){
        for (auto &degree : scale){
            //increment the td
            tone_distribution[root + degree + 12*i]++;
        };
    };
};

//add a chord
// void PND::add_chord(Chord chord, float chord_weight) {
//     std::vector<int> tones = chord.get_tones();
//     //reduce into intervals
//     for (int i=0; i<tones.size(); i++){
//         tones[i] = (tones[i] - root) % 12;
//     };
//     //sort the tones and get unique
//     sort( tones.begin(), tones.end() );
//     tones.erase( unique( tones.begin(), tones.end() ), tones.end() );
    
//     //iterate through all octaves
//     for (int i=0; i<octaves; i++){
//         for (auto &degree : tones){
//             //increment the td
//             tone_distribution[root + degree + 12*i] += chord_weight;
//         };
//     };
// };

void PND::add_chord(Chord chord, float chord_weight) {
    std::vector<int> tones = chord.get_tones();

    for (int i=0; i<tones.size(); i++){
        tone_distribution[tones[i]] += chord_weight;
    };
};


//subtract a chord
void PND::subtract_chord(Chord chord, float chord_weight) {
    std::vector<int> tones = chord.get_tones();
    //reduce into intervals
    for (int i=0; i<tones.size(); i++){
        tones[i] = (tones[i] - root) % 12;
    };
    //sort the tones and get unique
    sort( tones.begin(), tones.end() );
    tones.erase( unique( tones.begin(), tones.end() ), tones.end() );
    
    //iterate through all octaves
    for (int i=0; i<octaves; i++){
        for (auto &degree : tones){
            //increment the td
            tone_distribution[root + degree + 12*i] -= chord_weight;
        };
    }; 
};

//add a mask - want everything an octave away or more to be shrunk
//center is the center of mask, spread is how far do i want to mask to effect and intensity 
//is how powerful the mask is 
//intensity is the height basically and spread is the width
void PND::add_mask(int center, float spread, float intensity){
    for (auto i = tone_distribution.begin(); i != tone_distribution.end(); i++){
        //add 10 - difference between notes and center
        //ex: note 67, note 60 would have a 
        float mask = intensity - (((intensity - 1) / spread) * (float) abs(i->first - center));
        i->second *= mask;
        normalize();
    };
};

//add mask for addition
void PND::add_mask(int center, float intensity){
    for (auto i = tone_distribution.begin(); i != tone_distribution.end(); i++){
        //add 10 - difference between notes and center
        //ex: note 67, note 60 would have a 
        float mask = intensity - (float) abs(i->first - center);
        i->second += (mask > 0) ? mask : 0;
    };
};

//normalize a vector
void PND::normalize(){
    std::vector<float> probs = get_probs();
    auto max = *std::max_element(std::begin(probs), std::end(probs));
    for (auto i = tone_distribution.begin(); i != tone_distribution.end(); i++){
        //add one, so minimum isn't completely erased
        i->second = i->second / max;
    }
};

//chord mask 
void PND::mask_chord(Chord chord, float multiplier) {
    std::vector<int> tones = chord.get_tones();
    //if there are chord tones, multiply them in, octave up and octave down
    for (int tone : tones){
        for (int i= -1; i<2; i++){
            if (tone_distribution.find(tone + 12*i) != tone_distribution.end()){
                tone_distribution[tone + 12*i] *= multiplier;}
        };
    };
    normalize();
};

//tone mask
void PND::mask_tone(int tone, float multiplier) {
    tone_distribution[tone] *= multiplier;
    normalize();
};

int PND::choose() {
    //get the tones and probabilities
    std::vector<int> tones = get_tones();
    std::vector<float> probs = get_probs();

    return choose_int_dd(tones, probs);

};