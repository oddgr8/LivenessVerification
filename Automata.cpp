//
// Created by onkar on 17/5/19.
//

#include "Automata.h"
#include <utility>
#include <iostream>
using namespace std;


void Automata::addInitialState(int id) {
    if( States.find(id)==States.end() ){
        States.emplace(id,State());
    }
    initialStates.insert(id);
}

void Automata::addFinalState(int id) {
    if( States.find(id)==States.end() ){
        States.emplace(id,State());
    }
    finalStates.insert(id);
}

void Automata::addWriteTransition(int src, int dst, char letter) {
    States[src].outgoingWrite.insert(make_pair(dst, letter));
    States[dst].incomingWrite.insert(make_pair(src, letter));
}

void Automata::addReadTransition(int src, int dst, char letter) {
    States[src].outgoingRead.insert(make_pair(dst, letter));
    States[dst].incomingRead.insert(make_pair(src, letter));
}

bool Automata::deleteReadTransition(int src, int dst, char letter) {
    if( States.find(src)==States.end() || States.find(dst)==States.end() ){
        return false;
    }
    States[src].outgoingRead.erase(make_pair(dst, letter));
    States[dst].incomingRead.erase(make_pair(src, letter));
    return true;
}

bool Automata::deleteWriteTransition(int src, int dst, char letter) {
    if( States.find(src)==States.end() || States.find(dst)==States.end() ){
        return false;
    }
    States[src].outgoingWrite.erase(make_pair(dst, letter));
    States[dst].incomingWrite.erase(make_pair(src, letter));
    return true;
}

bool Automata::deleteState(int id) {
    if( States.find(id)==States.end() ){
        return false;
    }
    for (auto it = States[id].outgoingWrite.begin();  it != States[id].outgoingWrite.end(); it++) {
        States[it->first].incomingWrite.erase(make_pair(id,it->second));
    }
    for (auto it = States[id].outgoingRead.begin();  it != States[id].outgoingRead.end(); it++) {
        States[it->first].incomingRead.erase(make_pair(id,it->second));
    }
    for (auto it = States[id].incomingWrite.begin();  it != States[id].incomingWrite.end(); it++) {
        States[it->first].outgoingWrite.erase(make_pair(id,it->second));
    }
    for (auto it = States[id].incomingRead.begin();  it != States[id].incomingRead.end(); it++) {
        States[it->first].outgoingRead.erase(make_pair(id,it->second));
    }
    States.erase(id);
    return true;
}

void Automata::print() {

    cout<<"Initial States are :"<<endl;
    for (int initialState : initialStates) {
        cout<< "  " << initialState <<endl;
    }
    cout<<"Final States are :"<<endl;
    for (int finalState : finalStates) {
        cout<< "  " << finalState <<endl;
    }
    for (auto & State : States) {
        cout<<"State "<< State.first <<":"<<endl;
        for (auto i = State.second.incomingRead.begin(); i != State.second.incomingRead.end(); ++i) {
            cout<< "  " << i->first << " --?" << i->second << "--> " << State.first <<endl;
        }
        for (auto i = State.second.incomingWrite.begin(); i != State.second.incomingWrite.end(); ++i) {
            cout<< "  " << i->first << " --!" << i->second << "--> " << State.first <<endl;
        }
        for (auto i = State.second.outgoingRead.begin(); i != State.second.outgoingRead.end(); ++i) {
            cout<< "  " << State.first << " --?" << i->second << "--> " << i->first <<endl;
        }
        for (auto i = State.second.outgoingWrite.begin(); i != State.second.outgoingWrite.end(); ++i) {
            cout<< "  " << State.first << " --!" << i->second << "--> " << i->first <<endl;
        }
    }

    cout<<"Print done"<<endl;
}

set<int> Automata::getInitialStates() {
    return initialStates;
}

set<int> Automata::getFinalStates() {
    return finalStates;
}

State Automata::getState(int id) {
    return States[id];
}
