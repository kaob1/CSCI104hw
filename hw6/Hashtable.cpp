#include <iostream>
#include <string>
#include <time.h>
#include <math.h>
#include <cstdlib>
#include "Hashtable.h"

using namespace std;

Hashtable::Hashtable(bool d, unsigned int p){
    trackA=0;
    trackP=0;
    arrsize=arrayIndices[trackA];
    prime=doublehashingPrimes[trackP];
    probing =p;//determine which probing method to use
    numItems=0;
    srand(time(NULL));
    //debug mode off
    //true random
    if(d==false){
        for(int x=0;x<5;x++){
            rArray[x]=rand()%arrsize;
        }
    }else{
        //debug mode on,
        //psuedo random
        rArray[0]=983132572;
        rArray[1]=62337998;
        rArray[2]=552714139;
        rArray[3]=984953261;
        rArray[4]=261934300;
    }
    hashArray.resize(11,make_pair("",0));
}

Hashtable::~Hashtable(){
}

void Hashtable::add(string k){
    if(((double)(numItems)/arrsize)>0.5){//check load factor
        resize();
    }
    int index=hash(k);//use hash() to get the index to insert 

    //if empty...set it and update number of items in the hash table
    if(hashArray[index].first==""){
        hashArray[index].first=k;
        numItems++;
    }
    //else just increase the number of occurence
    hashArray[index].second++;
}

//return the number of occurence of the given string
int Hashtable::count(string k){
    return hashArray[hash(k)].second;
}

//output the entire hash table to an output file
ostream& Hashtable::reportAll (ostream & os) const{
    for(int x=0;x<arrsize;x++){
        if(hashArray[x].first!=""){
            os<<hashArray[x].first<<" "<<hashArray[x].second<<endl;
        }
    }
    return os;
}

void Hashtable::resize(){
    //create a temporary hashtable to store all the existing data
    vector<pair<string,int> > tempArray;
    tempArray.resize(arrsize);
    for(int x=0;x<arrsize;x++){
        tempArray[x].first=hashArray[x].first;
        tempArray[x].second=hashArray[x].second;
    }
    //get the next prime number in the arrays of primes
    trackA++;
    trackP++;
    arrsize=arrayIndices[trackA];
    prime=doublehashingPrimes[trackP];

    //resize the hash table
    hashArray.clear();
    hashArray.resize(arrsize,make_pair("",0));
    numItems=0;

    //go through the temporary hash table and 
    //call add() to rehash everything to the new hash table
    for(int x=0;x<(int)tempArray.size();x++){
        if(tempArray[x].first!=""){
            int tempOccur=tempArray[x].second;
            add(tempArray[x].first);
            int newIndex = hash(tempArray[x].first);
            hashArray[newIndex].second=tempOccur;
        }
    }    
}

//hash function using formula provided in the assignment instruction
int Hashtable::hash(string k)const{
    int len=k.size();
    long long wArray[]={0,0,0,0,0};
    long long tempSum=0;
    int z =4;

    //First translate each letter into a value between 0 and 25, where a=0, b=1, c=2, …, z=25.
    //for each group of 6 letters, use this: 26^5 a1 + 26^4 a2 + 26^3 a3 + 26^2 a4 + 26 a5 + a6
    for(int x=len-1;x>=len%6 && x>=0;x-=6, z--){
        tempSum=0;
        for(int y=5;y>=0;y--){
             tempSum+=(long long)((pow(26,y))*((int)k.at(x-y)-97));
        }
        wArray[z]=tempSum;
    }

    //the remainder when the number of letters is not divisible by 6
    for(int x=len%6-1;x>=0;x--){
        wArray[4-(len/6)]+=(long long)((pow(26,x))*((int)k.at(len%6-1-x)-97));
    }

    //(r1 w1 + r2 w2 + r3 w3 + r4 w4 + r5 w5) % m
    long long total=0;
    for(int x=0;x<5;x++){
        total+=(wArray[x]*(long long)rArray[x]);
    }
    int index= total%arrsize;

    //0 means that your Hashtable must use linear probing, 1 means quadratic probing, and 2 means double hashing.
    if(hashArray[index].first=="" || hashArray[index].first==k){//empty space or already exist
        return index;
    }else if(hashArray[index].first!=k && probing==0){//occupied, linear probing
        while(hashArray[index].first!="" && hashArray[index].first!=k){
            index=(index+1)%arrsize;
        }
        return index;
    }else if(hashArray[index].first!=k && probing==1){//occupied, quadratic probing
        int i=1;
        while(hashArray[index].first!="" && hashArray[index].first!=k){
            if(hashArray[(index+(i*i))%arrsize].first=="" || hashArray[(index+(i*i))%arrsize].first==k){
                return (index+(i*i))%arrsize;
            }
            i++;
        }
    }else if(hashArray[index].first!=k && probing==2){//double hashing; h(w) = p - ((w1+w2+w3+w4+w5) % p)
        long long sumofW=0;
        for(int x=0;x<5;x++){
            sumofW+=wArray[x];
        }
        int doublehashIndex = prime-(sumofW%prime);
        while(hashArray[index].first!="" && hashArray[index].first!=k){
            index+=doublehashIndex;
            index=index%arrsize;
        }
        return index;
    }
    return 0;
}