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
#include "Note.h"

/*
Note constructor - no variables
@brief - constructor for a Note with all parameters.
@param - NULL
@return - a Note object with all values set to 0.
*/
Note::Note(void) {
    tone = 0;
    length = 0;
    velocity = 0;
};

/*
Note constructor - with variables
@brief - constructor for a Note with all parameters.
@param - tone, time, length, and velocity definitions. 
@return - a Note object.
*/

Note::Note(int tone, float length, int vel) {
    this->tone = tone;
    this->length = length;
    this->velocity = vel;
};


/*set function
@brief - set values for note
@param - tone, time, length, and velocity definitions. 
@return -void
*/
void Note::set_values(int tone, float length, int velocity) {
    this->tone = tone;
    this->length = length;
    this->velocity = velocity;
};