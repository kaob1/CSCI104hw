#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
using namespace std;
int countries;
int rows;
int cols;
vector<vector<char> > ogmap;
vector<vector<int> >colormap;
map<char,int>combinedmap;
bool isValid(int row,int col);
void getAnswer();
bool color(int row,int col);
void printColoredMap();
void printMap();

//print out the content of the map to get the color of each country
void getAnswer(){
    for(map<char,int>::iterator it=combinedmap.begin();it!=combinedmap.end();it++){
        cout<<it->first<<" "<<it->second<<endl;
    }
}

//using recursion and backtracking to find the color of each country
bool color(int row,int col){
    //return true when reach the end of map
    if(row>rows-1){
        return true;
    }
    //when it reaches the rightmost column,
    //start at the leftmost column of the next row
    if(col>cols-1){
        return color(row+1,0);
    }
    //for each country, try each of the 4 colors
    //use isValid to check whether each color works or not
    //do the same for the next index
    for(int x=1;x<=4;x++){
        colormap[row][col]=x;
        if(isValid(row,col)){
            if(color(row,col+1)){
                //insert the country and its color into combined map
                //use combined map to print out the answer in getAnswer()
                combinedmap.insert(pair<char,int>(ogmap[row][col],colormap[row][col]));
                return true;
            }
        }
    }
    colormap[row][col]=0;
    return false;
}

//print out the inputted map
void printMap(){
    for(int x=0;x<(int)ogmap.size();x++){
        for(int y=0;y<(int)ogmap[x].size();y++){
            cout<<ogmap[x][y];
        }
        cout<<endl;
    }
}

//check whether each color assignment is valid
bool isValid(int row,int col){
    char temp=ogmap[row][col];
    char temp2=colormap[row][col];
    //first row
    if(row==0){
        //top left corner
        if(col==0){
            if((temp!=ogmap[row+1][col] && temp2==colormap[row+1][col]) ){
                return false;
            }
            if((temp!=ogmap[row][col+1] && temp2==colormap[row][col+1]) ){
                return false;
            }
        //the rest of first row
        }else{
            if((temp!=ogmap[row+1][col] && temp2==colormap[row+1][col]) ){
                return false;
            }
            if((temp!=ogmap[row][col+1] && temp2==colormap[row][col+1]) ){
                return false;
            }
            if((temp!=ogmap[row][col-1] && temp2==colormap[row][col-1]) ){
                return false;
            }
        }
    }
    //last row
    else if(row==rows-1){
        //bottom left corner
        if(col==0){
            if((temp!=ogmap[row-1][col] && temp2==colormap[row-1][col]) ){
                return false;
            }
            if((temp!=ogmap[row][col+1] && temp2==colormap[row][col+1]) ){
                return false;
            }
        //rest of last row
        }else{
            if((temp!=ogmap[row-1][col] && temp2==colormap[row-1][col]) ){
                return false;
            }
            if((temp!=ogmap[row][col+1] && temp2==colormap[row][col+1]) ){
                return false;
            }
            if((temp!=ogmap[row][col-1] && temp2==colormap[row][col-1]) ){
                return false;
            }
        }
    }
    //first column
    else if(col==0){
        if((temp!=ogmap[row-1][col] && temp2==colormap[row-1][col]) ){
            return false;
        }
        if((temp!=ogmap[row][col+1] && temp2==colormap[row][col+1]) ){
            return false;
        }
        if((temp!=ogmap[row+1][col] && temp2==colormap[row+1][col]) ){
            return false;
        }
    }
    //last column
    else if(col==cols-1){
        //top right corner
        if(row==0){
            if((temp!=ogmap[row+1][col] && temp2==colormap[row+1][col]) ){
                return false;
            }
            if((temp!=ogmap[row][col-1] && temp2==colormap[row][col-1]) ){
                return false;
            }
        //bottom right corner
        }else if(row==rows-1){
            if((temp!=ogmap[row-1][col] && temp2==colormap[row-1][col])){
                return false;
            }
            if((temp!=ogmap[row][col-1] && temp2==colormap[row][col-1]) ){
                return false;
            }
        }else{
            if((temp!=ogmap[row+1][col] && temp2==colormap[row+1][col]) ){
                return false;
            }
            if((temp!=ogmap[row-1][col] && temp2==colormap[row-1][col]) ){
                return false;
            }
            if((temp!=ogmap[row][col-1] && temp2==colormap[row][col-1]) ){
                return false;
            }
        }
    //for indices that are not on the borders of the map
    //check all four sides: top, down, left, right   
    }else{
        if((temp!=ogmap[row+1][col] && temp2==colormap[row+1][col]) ){
            return false;
        }
        if((temp!=ogmap[row-1][col] && temp2==colormap[row-1][col]) ){
            return false;
        }
        if((temp!=ogmap[row][col+1] && temp2==colormap[row][col+1]) ){
            return false;
        }
        if((temp!=ogmap[row][col-1] && temp2==colormap[row][col-1])){
            return false;
        }
    }
    //if a nearby index is the same country, make sure they are the same color
    if(col!=0 && temp==ogmap[row][col-1]&& temp2!=colormap[row][col-1]){
            return false;
    }
    if(row!=0 && temp==ogmap[row-1][col]&& temp2!=colormap[row-1][col]){
            return false;
    }
  return true;
}

//print out the colored map
void printColoredMap(){
    for(int x=0;x<(int)colormap.size();x++){
        for(int y=0;y<(int)colormap[x].size();y++){
            cout<<colormap[x][y];
        }
        cout<<endl;
    }
}

int main(int argc, char* argv[]){
    ifstream myfile(argv[1]);
    
    //get the inputs from txt file
    myfile>>countries;
    myfile>>rows;
    myfile>>cols;
    string trash;
    getline(myfile,trash);

    //create the map
    for(int x=0;x<rows;x++){
        string temp;
        getline(myfile,temp);
        vector<char>v;
        for(int y=0;y<cols;y++){
            v.push_back(temp[y]);
        }
        ogmap.push_back(v);
    }
    myfile.close();
    
    //create an empty colormap with rows x cols
    for(int x=0;x<rows;x++){
        vector<int>i;
        for(int y=0;y<cols;y++){
            i.push_back(0);
        }
        colormap.push_back(i);
    }
    
    color(0,0);
    getAnswer();

    return 0;
}
