//@author Paul Miller-Schmidt

#include "Note.h"
#include "Distribution.h"
#include "VecMath.h"

/* Algorithm Object 
@brief - Algorithm is fed into a generator and used to produce musical material. 
Each algorithm has initial and current states and generates next states based on 
the particular algorithm. 
@param - Initial and current states.
@return - an algorithm object.
*/
class Algorithm {

    private: 
        //variables
        Note init_state;
        Note curr_state;

    public:
        /* set functions
        @brief - simple set functions for various elements of Algorithm.
        @param - the variable to be set.
        @return - void
        */
        void set_init(Note init) {init_state = init;}
        void set_curr(Note curr) {curr_state = curr;}

        /* get functions
        @brief - get functions for variables of Algorithm.
        @param - NULL
        @return - said variable. 

        The most basic next just gets the current state. 
        */
        Note get_state() {return curr_state;}
        Note next() {return curr_state;}

        /* constructors
        @brief - constructors for Note with no variables or all variables.
        */
        Algorithm(void);
        Algorithm(Note init_state);
};

//Constructor - no varibles
Algorithm::Algorithm(void) {
};
//Constructor - with init, sets both init and curr to init.
Algorithm::Algorithm(Note init) {
    init_state = init;
    curr_state = init;
};

/*Random Discrete Distribution Algoritm
@brief - A random discrete distribution algorithm to chose Note parameters randomly
from a discrete distrubution. 
*/
class RandomDD : public Algorithm {
    public: 
        //sets
        void set_choices(std::vector<Note> choices) {this->choices = choices;}
        void set_weights(std::vector<double> weights) {this->weights = weights;}
        //gets
        std::vector<Note> get_choices() {return choices;}
        std::vector<double> get_weights() {return weights;}
        //next algo
        Note next();

    private:
        std::vector<Note> choices;
        std::vector<double> weights;
};

Note RandomDD::next() {
    //get the note
    Note curr = chooseNote_dd(choices, weights);
    //set the note as the state
    set_curr(curr);
    //return current note
    return curr;
};

