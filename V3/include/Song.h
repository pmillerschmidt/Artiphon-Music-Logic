//@author Paul Miller-Schmidt

#pragma once
#include "Section.h"
#include <vector>

class Song {
    public:
        //sets
        void set_sections(std::vector<Section> sections) {this->sections = sections;}
        void add(Section section);

        //gets
        std::vector<Section> get_sections() {return sections;}

        //constructors
        Song();
        Song(std::vector<Section> sections);
    private:
        std::vector<Section> sections;

};