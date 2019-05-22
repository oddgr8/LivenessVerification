//
// Created by onkar on 17/5/19.
//
#include "Automata.cpp"
#include <string>
#include <iostream>
using namespace std;

int main(){
    Automata A;
    char input[100];
    bool atInitial = true,firstInput =true, foundFinalState = false;
    while(cin.getline(input,100)){
        string s(input);
        if(s=="input_over"){
            break;
        }
        if(s.find(',')==string::npos){
            if(atInitial){
                A.addInitialState(s);
            }
            else{
                A.addFinalState(s);
                foundFinalState = true;
            }
        }
        else{
            atInitial = false;
            int c = s.find(','), t = s.find("->");
            string src = s.substr(c+1,t-c-1);
            string dst = s.substr(t+2);
            if(s[0]=='!'){
                A.addWriteTransition(src, dst, s[1]);
            }
            else if(s[0]=='?'){
                A.addReadTransition(src, dst, s[1]);
            }
            if(firstInput){
                A.addInitialState(src);
            }
        }
        firstInput = false;
    }
    if(!foundFinalState){
        A.makeAllStatesFinal();
    }

    A.print();
    cout<<"Reachable States are :";
    for ( auto & State : A.getReachableStates()){
        cout<<State<<" ";
    }
    cout<<endl;

//    int ds;//Delete States
//    cin>>ds;
//    for (int i = 0; i < ds; ++i) {
//        int s;
//        cin>>s;
//        A.deleteState(s);
//    }
//    A.print();
//
//    int drt,dwt;//Delete Transitions
//    cin>>drt>>dwt;
//    for (int j = 0; j < drt; ++j) {
//        int src, dst;
//        cin>>src>>dst;
//        char letter;
//        cin>>letter;
//        A.deleteReadTransition(src, dst, letter);
//    }
//    for (int j = 0; j < dwt; ++j) {
//        int src, dst;
//        cin>>src>>dst;
//        char letter;
//        cin>>letter;
//        A.deleteWriteTransition(src, dst, letter);
//    }
//    A.print();

    cout<<"Is A Live?";
    if(A.isLive()){
        cout<<"Yes"<<endl;
    }
    else{
        cout<<"No"<<endl;
    }
    return 0;
}
