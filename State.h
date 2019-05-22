//
// Created by onkar on 17/5/19.
//
#include <set>
using namespace std;

#ifndef LIVENESSVERIFICATION_STATE_H
#define LIVENESSVERIFICATION_STATE_H


class State {
public:
    set< pair<string,char> > incomingWrite, outgoingWrite, incomingRead, outgoingRead;

};


#endif //LIVENESSVERIFICATION_STATE_H
