#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <utility>
using namespace std;

//calculate the probability of each fruit using bayes theorem
//return a string of the name of the most likely fruit
string probability(map<string, vector<string> > database,vector<string> adj, map<string,pair<int,double> > m,int n){
    double numerator=0.0;
    double denominator=0.0;
    for(map<string,pair<int,double> >::iterator it=m.begin();it!=m.end();++it){//going through the diff kinds of fruit
        //set the numerator to P(of the fruit we're testing) ex. P(banana)
        //# of occurence over total # of fruits
        numerator=((double)it->second.first/(double)n);
        //set the denominator to P(not the fruit we're testing) ex. P(not banana)
        //complement of the numerator.
        denominator=((double)1-numerator);

        for(int x=0;x<(int)(adj.size());x++){//going through the adjectives
            double occ=1;//set to 1 because of laplacian smoothing
            double occNot=1;//set to 1 because of laplacian smoothing

            //go through the set of adjectives in the training set to look for matches 
            for(map<string,vector<string> >::iterator itt=database.begin();itt!=database.end();++itt){
                for(int y=0;y<(int)(itt->second.size());++y){
                    //if the adjective is describing the fruit we're testing, occurence++
                    if(itt->first==it->first && itt->second.at(y)==adj[x]){
                        occ++;
                    }
                    //if the adjective is describing any of the fruits we're not testing, 
                    //occurenceOfNot++
                    if(itt->first!=it->first && itt->second.at(y)==adj[x]){
                        occNot++;
                    }
                }
            }
            //multiply the numerator by the probability of this adjective matching the fruit
            //the probability of this adjective matching the fruit is:
            //occurence of same adjective same fruit divided by occurence of fruit
            //+1 because of laplacian smoothing
            //same concept but opposite for denominator
            numerator*=(occ/(it->second.first+1));
            denominator*=(occNot/(n-it->second.first+1));
        }
        //update the total probability 
        it->second.second=numerator/(numerator+denominator);
    }

    //loop through the map of fruits to find the one with the highest probability
    string highest=m.begin()->first;
    for(map<string,pair<int,double> >::iterator it =m.begin();it!=m.end();it++ ){
        if(it->second.second>m.at(highest).second){
            highest=it->first;
        }
    }
    return highest; 
}
int main(int argc, char* argv[]){
    if(argc<4){
        cout<<"please specify train.txt, classify.txt, and output.txt";
    }
    //get the inputs from txt file
    ifstream myfile(argv[1]);
    string line;
    stringstream ss;
    getline(myfile,line);
    ss<<line;
    int n;
    ss>>n;

    //diffFruit is a map(fruit name, pair of (# of occurence of the fruit, double for probability))
    //database is a map(fruit name, vector of all the adj for that fruit)
    map<string, vector<string> > database;
    map<string,pair<int,double> > diffFruit;
    
    //storing the training set into database and diffFruit
    for(int x=0;x<n;x++){
        vector<string>v1;
        getline(myfile,line);
        stringstream ss2(line);
        string databaseKey;
        ss2>>databaseKey;
        string databaseVector;
        while(ss2>>databaseVector){
            v1.push_back(databaseVector);
        }
        if(database.find(databaseKey)!=database.end()){//if the fruit already exist in database
            while(!v1.empty()){
                database.at(databaseKey).push_back(v1[v1.size()-1]);
                v1.pop_back();
            }
        }else{//else add the fruit and its adj's
            database.insert(pair<string,vector<string> >(databaseKey,v1));
        }
        if(diffFruit.find(databaseKey)!=diffFruit.end()){//if fruit already exist in diffFruit
            diffFruit.at(databaseKey).first++;
        }else{
            diffFruit.insert(pair<string,pair<int,double> >(databaseKey,pair<int,double>(1,0.0)));    
        }
    }
        myfile.close();
      
    //read classify.txt
    ifstream classify(argv[2]);
    stringstream ss3;
    getline(classify,line);
    ss3<<line;
    int sizeOfClassify;
    ss3>>sizeOfClassify;
    
    vector<vector<string> > adj;
    string solution;
    ofstream ofile(argv[3]);
    //store the adjectives in classify.txt into a vector of vector called "adj"
    for(int x=0;x<sizeOfClassify;x++){
        vector<string>v1;
        getline(classify,line);
        stringstream ss2(line);
        string temp;
        while(ss2>>temp){
            v1.push_back(temp);
        }
        adj.push_back(v1);

        //call probability to calculate the probability and get the fruit with the highest probability
        string answer=probability(database, v1,diffFruit,n);
        //output the answer
        ofile<<answer<<endl;
    }
    classify.close();
    ofile.close();
    return 0;
}
