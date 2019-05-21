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
        for (auto & i : State.second.incomingRead) {
            cout<< "  " << i.first << " --?" << i.second << "--> " << State.first <<endl;
        }
        for (auto & i : State.second.incomingWrite) {
            cout<< "  " << i.first << " --!" << i.second << "--> " << State.first <<endl;
        }
        for (auto & i : State.second.outgoingRead) {
            cout<< "  " << State.first << " --?" << i.second << "--> " << i.first <<endl;
        }
        for (auto & i : State.second.outgoingWrite) {
            cout<< "  " << State.first << " --!" << i.second << "--> " << i.first <<endl;
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

set<int> Automata::getReachableStates() {
    set<int> ans,oldAns;
    set<char> lettersSeen;
    ans = initialStates;
    while( ans != oldAns ){
        oldAns = ans;
        for (int State : oldAns) {
            for (auto & i : States[State].outgoingWrite){
                lettersSeen.insert(i.second);
                ans.insert(i.first);
            }
        }
        for (int State : oldAns) {
            for (auto & i : States[State].outgoingRead){
                if( lettersSeen.find(i.second)!=lettersSeen.end() ){
                    ans.insert(i.first);
                }
            }
        }
    }
    return ans;
}

bool Automata::isLive() {
    set<int> reachable = getReachableStates();
    int m = reachable.size();
    set<int> allStates;
    for (auto & i : States){
        allStates.insert(i.first);
    }
    set<int> C[m+1], oldC[m+1];
    for (int i = 1; i < m+1; ++i) {
        C[i] = allStates;
    }
    while(true){
        for (int j = 1; j < m+1; ++j) {
            oldC[j]=C[j];
        }

        //C = intersection of post+_oldC and pre*_oldC
        set<int> R[m+1], oldR[m+1];
        int count = 1;
        for (auto & i : reachable){
            R[count].insert(i);
        }
        //Now we have R = ({s1},{s2}...{sm})
        {//Taking post once
            for (int i = 1; i < m+1; ++i) {
                oldR[i]=R[i];
            }

            set<char> lettersSeen;
            for (int k = 1; k < m+1; ++k) {
                for ( int i : oldR[k] ){
                    for ( auto & j : States[i].outgoingWrite){
                        if( oldR[k].find(j.first)!=oldR[k].end() ){
                            lettersSeen.insert(j.second);
                        }
                    }
                }
            }
            //lettersSeen is initialized now
            for (int k = 1; k < m+1; ++k) {
                for ( int i : oldR[k] ){
                    for (auto & j : States[i].outgoingWrite){
                        R[k].insert(j.first);
                    }
                    for (auto & j : States[i].outgoingRead){
                        if( lettersSeen.find(j.second)!=lettersSeen.end() ){
                            R[k].insert(j.first);
                        }
                    }
                }
            }
            //Now, R is post(OldR)

            for (int j = 1; j < m+1; ++j) {
                R[j].insert(oldR[j].begin(),oldR[j].end());
            }
            // R = R union oldR
        }
        while(true){
            for (int i = 1; i < m+1; ++i) {
                oldR[i]=R[i];
            }

            set<char> lettersSeen;
            for (int k = 1; k < m+1; ++k) {
                for ( int i : oldR[k] ){
                    for ( auto & j : States[i].outgoingWrite){
                        if( oldR[k].find(j.first)!=oldR[k].end() ){
                            lettersSeen.insert(j.second);
                        }
                    }
                }
            }
            //lettersSeen is initialized now
            for (int k = 1; k < m+1; ++k) {
                for ( int i : oldR[k] ){
                    for (auto & j : States[i].outgoingWrite){
                        R[k].insert(j.first);
                    }
                    for (auto & j : States[i].outgoingRead){
                        if( lettersSeen.find(j.second)!=lettersSeen.end() ){
                            R[k].insert(j.first);
                        }
                    }
                }
            }
            //Now, R is post(OldR)

            for (int j = 1; j < m+1; ++j) {
                R[j].insert(oldR[j].begin(),oldR[j].end());
            }
            // R = R union oldR


            for (int j = 1; j < m+1; ++j) {
                if(oldR[j]!=R[j]){
                    continue;
                }
            }
            break;
        }
        //TODO compute pre*
        //TODO C = post+ int pre*

        //Check if fixed point is reached
        for (int i = 1; i < m+1; ++i) {
            if (C[i] != oldC[i]){
                continue;
            }
        }
        break;
    }
    for (int k = 1; k < m+1; ++k) {
        if( !C[k].empty() ){
            return true;
        }
    }
    return false;
}
