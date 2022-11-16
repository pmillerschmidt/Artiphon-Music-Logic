// @author Paul Miller-Schmidt

#include "PND.h"

//constructors
PND::PND() {
    //do nothing
};

PND::PND(std::map<int, float> td){
    this->tone_distribution = td;
};

PND::PND(std::vector<int> tones, std::vector<float> probs){
    //make sure they are the same length
    assert(tones.size() == probs.size());

    for (int i=0; i<tones.size(); i++){
        tone_distribution[tones[i]] = probs[i];
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
            probs.push_back(imap.first);
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

