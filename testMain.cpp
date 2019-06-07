//
// Created by onkar on 17/5/19.
//
#include "Automata.cpp"
#include "SymAutomata.cpp"
#include <string>
#include <iostream>
#include <ctime>
using namespace std;

int main(){
    bdd_init(1000,1000);
    bdd_setvarnum(5);
    bdd x = bdd_ithvar(0);
    bdd_printtable(x);



//    Automata A;
//    char input[100];
//    bool atInitial = true,firstInput =true, foundFinalState = false;
//    while(cin.getline(input,100)){
//        string s(input);
//        if(s=="input_over"){
//            break;
//        }
//        if(s.find(',')==string::npos){
//            if(atInitial){
//                A.addInitialState(s);
//            }
//            else{
//                A.addFinalState(s);
//                foundFinalState = true;
//            }
//        }
//        else{
//            atInitial = false;
//            int c = s.find(','), t = s.find("->");
//            string src = s.substr(c+1,t-c-1);
//            string dst = s.substr(t+2);
//            if(s[0]=='!'){
//                A.addWriteTransition(src, dst, s[1]);
//            }
//            else if(s[0]=='?'){
//                A.addReadTransition(src, dst, s[1]);
//            }
//            if(firstInput){
//                A.addInitialState(src);
//            }
//        }
//        firstInput = false;
//    }
//    if(!foundFinalState){
//        A.makeAllStatesFinal();
//    }
//
////    A.print();
////    cout<<"Reachable States are :";
////    for ( auto & State : A.getReachableStates()){
////        cout<<State<<" ";
////    }
////    cout<<endl;
//    A.printSize();
//
//    time_t time1,time2;
//    time(&time1);
//    cout<<"Is A Live?";
//    if(A.isLive()){
//        cout<<"Yes"<<endl;
//    }
//    else{
//        cout<<"No"<<endl;
//    }
//    time(&time2);
//    cout<<"Time required to verify Liveness: "<<difftime(time2, time1)<<" seconds"<<endl<<endl;




    return 0;
}
