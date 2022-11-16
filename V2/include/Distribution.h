//@author Paul Miller-Schmidt

#include <vector>
#include <math.h> 
#include <random>
#include "Note.h"
//DISTRIBUTION SELECTORS

/*Discrete Distribution choice
@brief - select from a discrete distribution
@param - a vector of the weights to select from and the number n numbers to pick.
@return - a vector of selected floating numbers.
*/
std::vector<int> choose_dd(std::vector<double> weights, int n);

/*Choose a note using discrete distribution.
@brief - select a note from a vector of notes based on discrete distribution of weights.
@param - a vector of the weights to select from and a vector of notes to be selected.
@return - The selected note.
*/
Note chooseNote_dd(std::vector<Note> notes, std::vector<double> weights);


/*Normal Distribution choice
@brief - select from a normal distribution
@param - a mean, standard deviation and number n of numbers to choose.
@return - a vector of selected floating numbers.
*/
std::vector<double> choose_nd(double mean, double stdev, int n);

/*Uniform Distribution choice
@brief - select from a uniform distribution
@param - a min, max, number n of numbers to choose, and r for rounding precision.
@return - a vector of selected floating numbers.
*/
std::vector<double> choose_ud(double min, double max, int n, double r);

