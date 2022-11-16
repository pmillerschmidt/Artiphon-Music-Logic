//@author Paul Miller-Schmidt

#pragma once
#include <vector>

class Scale {
    public:
        //sets
        void set_root(int root) {this->root = root;}
        void set_intervals(std::vector<int> intervals) {this->intervals = intervals;}

        //gets
        int get_root() {return root;}
        std::vector<int> get_intervals() {return intervals;}

        //constructors
        Scale();
        Scale(int root, std::vector<int> intervals);
    private:
        int root;
        std::vector<int> intervals;
};
