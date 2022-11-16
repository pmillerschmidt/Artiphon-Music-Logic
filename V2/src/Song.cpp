//@author Paul Miller-Schmidt

#include "Song.h"

Song::Song() {

};

Song::Song(std::vector<Section> sections) {
    this->sections = sections;
};

void Song::add(Section section) {
    this->sections.push_back(section);
};