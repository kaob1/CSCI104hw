#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>
#include <cctype>
#include <ctime>
#include "Hashtable.h"
#include "avlbst.h"

using namespace std;

int main(int argc, char* argv[]){
    if(argc<6){
        cout<<"Please specify input.txt, output.txt, x, d, and r"<<endl;
    }
    //pass in user inputs
    int x=stoi(argv[3]);
    int d=stoi(argv[4]);
    int r=stoi(argv[5]);
    ifstream myfile(argv[1]);
    string line;
    string words;
    vector<string> inserting;

    //store all the words into a vector first
    while(getline(myfile,line)){
        stringstream ss(line);
        while(ss>>words){
        //strip punctuations and numbers and convert to lower case
            transform(words.begin(), words.end(), words.begin(), ::tolower);
            for(int i=0;i<(int)words.size();i++){
                if(ispunct(words[i]) || isdigit(words[i])){
                    words.erase(words.begin()+i);
                    i--;
                }
            }
            inserting.push_back(words);
        }
    }
    myfile.close();

    //setup the timer and the output file format
    clock_t start;
    double duration;
    ofstream ofile(argv[2]);
    ofile<<"Storing with: ";
    if(x==3){
        ofile<<"AVLTree"<<endl;
    }else{
        ofile<<"Hash Table."<<endl;
        if(x==0){
            ofile<<"Using Linear Probing."<<endl;
        }else if(x==1){
            ofile<<"Using Quadratic Probing."<<endl;
        }else if(x==2){
            ofile<<"Using Double Hashing."<<endl;
        }
        if(d==0){
            ofile<<"Debug mode off."<<endl;
        }else{
            ofile<<"Debug mode on."<<endl;
        }
    }
    ofile<<"Run for "<<r<<" time(s)"<<endl;

    //start timing
    start=clock();

    //use avl tree if x=3
    if(x==3){
        //run for r times
        for(int i=0;i<r;i++){
            AVLTree<string,int> avl;
            for(int y=0;y<(int)inserting.size();y++){
                if(inserting[y]!=""){
                    avl.insert(make_pair(inserting[y],1));
                }
            }
        }
        ofile<<"No content outputted when using AVLTree.\nUse print() in the program to print content to the console."<<endl;
    }else{
        //use hash table with debug mode off
        //add every word into the hashtable then output
        if(d==0){
            for(int i=0;i<r;i++){
                Hashtable hash(false,x);
                for(int y=0;y<(int)inserting.size();y++){
                    if(inserting[y]!=""){
                        hash.add(inserting[y]);
                    }
                }
                if(i==0){
                    hash.reportAll(ofile);
                }
            }
        }else{
            //use hashtable with debug mode on
            for(int i=0;i<r;i++){
                Hashtable hash(true,x);
                for(int y=0;y<(int)inserting.size();y++){
                    if(inserting[y]!=""){
                        hash.add(inserting[y]);
                    }
                }
                if(i==0){
                    hash.reportAll(ofile);
                }
            }
        }
    }

    //calculate time then output
    duration = ( clock() - start ) / (double) CLOCKS_PER_SEC;
    ofile<<"Time for inserting/updating "<<duration/r<<endl;
    return 0;
}