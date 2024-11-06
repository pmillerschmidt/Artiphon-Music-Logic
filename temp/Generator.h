//@author Paul Miller-Schmidt

#include <vector>
#include <math.h> 
#include "Algorithm.h"

/*Generator class
@brief - Generator objects to generate musical material. 
@param - Composed of hyperparameters (length, bpm), a vector of Notes for output, 
and an Algorithm for generation. 
@return - Generator object
*/
class Generator {

    public:
        /* set functions
        @brief - simple set functions for variables of Generator.
        @param - the variable to be set.
        @return - void
        */
        void set_length(double length) {this->length = length;}
        void set_bpm(double bpm) {this->bpm = bpm;}

        /* get functions
        @brief - get functions for variables of Generator.
        @param - NULL
        @return - said variable. 
        */
        double get_length() {return length;}
        double get_bpm() {return bpm;}
        // Algorithm get_algorithm() {return algorithm;}

        
        /*get output
        @brief - gets the output vector. 
        @param - NULL
        @return - output vector.
        */
        std::vector<Note> get() {return this->out;}

        //Next - describeed below
        Note next();
        void fill();

        /*add note 
        @brief - adds a note to the output vector.
        @param - note to be added. 
        @return - void.
        */
        void add(Note note) {out.push_back(note);}
        /*clear 
        @brief - clears the output vector.
        @param - NULL
        @return - void.
        */
        void clear() {out.clear();}
        /* constructors
        @brief - constructors for Note with no variables or all variables.
        */
        Generator();
        Generator(double length, double bpm, Note init, Algorithm algo);

    private:
        //Variables 
        double length;
        double bpm;
        Note init_state;
        std::vector<Note> out;
        Algorithm algorithm;
};

//Constructor - no varibles
Generator::Generator(void) {
    this->length = 0;
    this->bpm = 120;
};

//Constructor - with varibles
Generator::Generator(double length, double bpm, Note init, Algorithm algo) {
    this->length = length;
    this->bpm = bpm;
    //set init state
    this->init_state = init;
    //initialize algorithm
    this->algorithm = algo;
    this->algorithm.set_init(init);
    this->algorithm.set_curr(init);

};

/*next 
@brief - gets next element based on parameters and algorithm. Base algorithm
is simple repitition. 
@param - NULL
@return - the next note in the sequence. 
*/
Note Generator::next() {
    //add the note and return it
    Note next = algorithm.next();
    out.push_back(next);
    return next;
}

// void Generator::fill() {
//     double filled = 0;
//     Note next;
//     while (filled < this->get_length()) {
//         next = this->next();
//         this->add(next);
//         filled += next.get_len();
//     };

// }



// class MelodyGenerator : private Generator {

//     public:

//     private:

// };
