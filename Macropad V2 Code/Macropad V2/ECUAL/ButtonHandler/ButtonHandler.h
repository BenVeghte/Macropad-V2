/*
 * ButtonHandler.h
 *
 *  Created on: 8/20/2022
 *      Author: Ben Veghte
*/
#ifndef $BUTTONHANDLER_H_
#define $BUTTONHANDLER_H_

typedef ButtonInfo {
    KeyOutput output;
    bool trigger_type; //0 = on release, 1 = on press
};

typedef KeyOutput { //Needs to be able to handle single character, string, key press combination or special function, can one of the datatypes in a struct point to a function

};

#endif /*$BUTTONHANDLER_H_*/
