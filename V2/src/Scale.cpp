//@author Paul Miller-Schmidt

#include "Scale.h"

Scale::Scale() {
    this->root = 0;
};

Scale::Scale(int root, std::vector<int> intervals) {
    this->root = root;
    this->intervals = intervals;
};