//@author Paul Miller-Schmidt


#include "Distribution.h"
using namespace std;

//DISTRIBUTION SELECTORS

/*Discrete Distribution choice
@brief - select from a discrete distribution
@param - a vector of the weights to select from and the number n numbers to pick.
@return - a vector of selected floating numbers.
*/
std::vector<int> choose_dd(std::vector<double> weights, int n) {
    // Setup the random bits
    std::random_device rd;
    std::mt19937 gen(rd());
    // Create the distribution with those weights
    std::discrete_distribution<> d(weights.begin(), weights.end());
    std::vector<int> res;
    for (int i=0;i<n;i++){
        res.push_back(d(gen));
    } 
    return res;
}

/*Choose a note using discrete distribution.
@brief - select a note from a vector of notes based on discrete distribution of weights.
@param - a vector of the weights to select from and a vector of notes to be selected.
@return - The selected note.
*/
Note chooseNote_dd(std::vector<Note> notes, std::vector<double> weights) {
    // Setup the random bits
    std::random_device rd;
    std::mt19937 gen(rd());
    // Create the distribution with those weights
    std::discrete_distribution<> d(weights.begin(), weights.end());
    return notes[d(gen)];
}


/*Normal Distribution choice
@brief - select from a normal distribution
@param - a mean, standard deviation and number n of numbers to choose.
@return - a vector of selected floating numbers.
*/
std::vector<double> choose_nd(double mean, double stdev, int n) {
    std::vector<double> res;
    std::random_device rd{};
    std::mt19937 gen{rd()};
    std::normal_distribution<> d{mean, stdev};
    for (int i=0;i<n;i++){
        res.push_back(round(d(gen)));
    }
    return res;
}

/*Uniform Distribution choice
@brief - select from a uniform distribution
@param - a min, max, number n of numbers to choose, and r for rounding precision.
@return - a vector of selected floating numbers.
*/
std::vector<double> choose_ud(double min, double max, int n, double r) {
    std::random_device rd; 
    std::mt19937 gen(rd()); 
    std::uniform_real_distribution<> d(min, max);
    std::vector<double> res;
    for (int i=0;i<n;i++) {
        res.push_back(round(d(gen) * (1.0*r)) / (1.0*r));
    }
    return res;
}

