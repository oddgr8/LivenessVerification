//
// Created by onkar on 17/5/19.
//

#include "Automata.h"
#include <utility>
#include <algorithm>
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
    bool flag = false;
    for (int i : reachable){
        if(finalStates.find(i)!=finalStates.end()){
            flag = true;
            break;
        }
    }

    if(!flag){
        return false;
    }

    int m = reachable.size() + 1;
    set<int> allStates;
    for (auto & i : States){
        allStates.insert(i.first);
    }
    set<int> C[m];
    set<int> oldC[m];
    for (int i = 1; i < m; ++i) {
        C[i] = allStates;
    }
    while(true){
        for (int j = 1; j < m; ++j) {
            oldC[j]=C[j];
        }

        //C = intersection of post+_oldC and pre*_oldC
        set<int> R[m], oldR[m], S[m], oldS[m];//R is used for computing post. S is used for computing pre
        int count = 1;
        for (int i : reachable){
            if( oldC[count].find(i)!=oldC[count].end() ){
                R[count].insert(i);
                S[count].insert(i);
            }
            count++;
        }
        //Now we have R,S = ({s1},{s2}...{sm})
        {//Taking post once
            for (int i = 1; i < m; ++i) {
                oldR[i]=R[i];
                R[i].clear();
            }

            set<char> lettersSeen;
            for (int k = 1; k < m; ++k) {
                for ( int i : oldR[k] ){
                    for ( auto & j : States[i].outgoingWrite){
                        if( oldR[k].find(j.first)!=oldR[k].end() ){
                            lettersSeen.insert(j.second);
                        }
                    }
                }
            }
            //lettersSeen is initialized now
            for (int k = 1; k < m; ++k) {
                for ( int i : oldR[k] ){
                    for (auto & j : States[i].outgoingWrite){
                        if( C[k].find(j.first)!=C[k].end() ){
                            R[k].insert(j.first);
                        }
                    }
                    for (auto & j : States[i].outgoingRead){
                        if( lettersSeen.find(j.second)!=lettersSeen.end() ){
                            R[k].insert(j.first);
                        }
                    }
                }
            }
            //Now, R = post(OldR)

        }
        while(true){//computing post*(post(X))
            for (int i = 1; i < m; ++i) {
                oldR[i]=R[i];
            }

            set<char> lettersSeen;
            for (int k = 1; k < m; ++k) {
                for ( int i : oldR[k] ){
                    for ( auto & j : States[i].outgoingWrite){
                        if( oldR[k].find(j.first)!=oldR[k].end() ){
                            lettersSeen.insert(j.second);
                        }
                    }
                }
            }
            //lettersSeen is initialized now
            for (int k = 1; k < m; ++k) {
                for ( int i : oldR[k] ){
                    for (auto & j : States[i].outgoingWrite){
                        if( C[k].find(j.first)!=C[k].end() ){
                            R[k].insert(j.first);
                        }
                    }
                    for (auto & j : States[i].outgoingRead){
                        if( lettersSeen.find(j.second)!=lettersSeen.end() ){
                            R[k].insert(j.first);
                        }
                    }
                }
            }
            //Now, R = R union post(OldR)


            bool notequal = false;
            for (int j = 1; j < m; ++j) {
                for ( int l : R[j] ){
                    if( oldR[j].find(l)==oldR[j].end() ){
                        notequal = true;
                        break;
                    }
                }
                if(notequal){
                    break;
                }
            }
            if(!notequal){
                break;
            }
        }

        while(true){//computing pre* of X
            for (int i = 1; i < m; ++i){
                oldS[i]=S[i];
            }

            set<char> lettersSeen;
            for (int k = 1; k < m; ++k) {
                for ( int i : oldS[k] ){
                    for ( auto & j : States[i].outgoingWrite){
                        if( oldS[k].find(j.first)!=oldS[k].end() ){
                            lettersSeen.insert(j.second);
                        }
                    }
                }
            }
            //lettersSeen is initialized now
            for (int k = 1; k < m; ++k) {
                for (int i : oldS[k]){
                    for ( auto & j : States[i].incomingWrite){
                        if( C[k].find(j.first)!=C[k].end() ){
                            S[k].insert(j.first);
                        }
                    }
                    for (auto & j : States[i].incomingRead){
                        if( lettersSeen.find(j.second)!=lettersSeen.end() ){
                            S[k].insert(j.first);
                        }
                    }
                }
            }
            //Now S is S union pre(oldS)

            bool notequal = false;
            for (int j = 1; j< m; j++){
                for ( int l : S[j] ){
                    if( oldS[j].find(l)==oldS[j].end() ){
                        notequal = true;
                    }
                }
                if (notequal){
                    break;
                }
            }
            if(!notequal){
                break;
            }
        }
        //R is post+
        //S is pre*
        for (int l = 1; l < m; ++l) {
            C[l].clear();
            for (int i : R[l]){
                if( S[l].find(i)!=S[l].end() ){
                    C[l].insert(i);
                }
            }
        }

        //Check if fixed point is reached
        bool notequal = false;
        for (int i = 1; i < m; ++i) {
            for( int l : oldC[i]){
                if(C[i].find(l) == C[i].end()){
                    notequal = true;
                }
            }
            if (notequal){
                break;
            }
        }
        if(!notequal){
            break;
        }
    }
    for (int k = 1; k < m; ++k) {
        if( !C[k].empty() ){
            return true;
        }
    }
    return false;
}
