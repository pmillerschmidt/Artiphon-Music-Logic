//@author Paul Miller-Schmidt

/*
NOTE CLASS
@brief - Note is the most basic element to be generated. It is the material that is 
fed into the generators to produce musical data. The Note is also used for simple 
MIDI IO interactions. We can easily add notes to a MIDI file by parsing its data.

@param - A note in our case is made up of a tone, a length, a velocity and a time. 
All of these all self-explanatory, except time, which is the time in the MIDI file 
the note is supposed to be. For example, a note with a time 0, should be placed at
the beginning of the MIDI file. 
*/

class Note {

    public:
        /* set functions
        @brief - simple set functions for various elements of Note.
        @param - the variable to be set.
        @return - void
        */
        void set_values(int, double, double, double);
        void set_tone(int tone) {this->tone = tone;}
        void set_len(double len) {this->length = len;}
        void set_vel(double vel) {this->velocity = vel;}
        void set_time(double time) {this->time = time;}

        /* get functions
        @brief - get functions for variables of Note. 
        @param - NULL
        @return - said variable. 
        */
        int get_tone() {return tone;}
        double get_len() {return length;}
        double get_vel() {return velocity;}
        double get_time() {return time;}

        /* constructors
        @brief - constructors for Note with no variables or all variables.
        */
        Note(); 
        Note(int note, double time, double length, double vel);

    private:
        //Variables
        int tone;
        double time;
        double length;
        double velocity;
};


/*
Note constructor - with variables
@brief - constructor for a Note with all parameters.
@param - tone, time, length, and velocity definitions. 
@return - a Note object.
*/

Note::Note(int tone, double time, double length, double vel) {
    this->tone = tone;
    this->time = time;
    this->length = length;
    this->velocity = vel;
};

/*
Note constructor - no variables
@brief - constructor for a Note with all parameters.
@param - NULL
@return - a Note object with all values set to 0.
*/
Note::Note(void) {
    time = 0;
    tone = 0;
    length = 0;
    velocity = 0;
};

/*set function
@brief - set values for note
@param - tone, time, length, and velocity definitions. 
@return -void
*/
void Note::set_values(int tone, double time, double length, double velocity) {
    this->tone = tone;
    this->time = time;
    this->length = length;
    this->velocity = velocity;
};