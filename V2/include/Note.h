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

#pragma once

class Note {

    public:
        /* set functions
        @brief - simple set functions for various elements of Note.
        @param - the variable to be set.
        @return - void
        */
        void set_values(int tone, float len, int vel);
        void set_tone(int tone) {this->tone = tone;}
        void set_length(float len) {this->length = len;}
        void set_vel(float vel) {this->velocity = vel;}

        /* get functions
        @brief - get functions for variables of Note. 
        @param - NULL
        @return - said variable. 
        */
        int get_tone() {return tone;}
        float get_length() {return length;}
        float get_vel() {return velocity;}

        /* constructors
        @brief - constructors for Note with no variables or all variables.
        */
        Note(); 
        Note(int note, float length, int vel);

    private:
        //Variables
        int tone;
        float length;
        int velocity;
};


