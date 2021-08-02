#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <cstring>
#include "avlbst.h"
#include <map>

using namespace std;

struct Rectangle
{
    int ID;
    int length;
    int height;
};

// Typedefs for you input and output map. Start with
// std::map but once the backtracking search algorithm is working
// try to use your AVL-tree map implementation by changing these
// typedef's
typedef AVLTree<const int, Rectangle> InputMapType;
typedef AVLTree<const int, std::pair<int, int> > OutputMapType;

// Allowed global variables: the dimensions of the grid
int n; // X-dim size
int m; // Y-dim size

// No other global variables are allowed

// A dummy operator << for Rectangles so the BST and AVL BST will
// compile with their printRoot() implementations
std::ostream& operator<<(std::ostream& os, const Rectangle& r)
{
    os << r.ID;
    return os;
}

// A dummy operator << for pairs so the BST and AVL BST will
// compile with their printRoot() implementations
template <typename T, typename U>
std::ostream& operator<<(std::ostream& os, const std::pair<T,U>& p)
{
    os << p.first << "," << p.second;
    return os;
}



void printSolution(std::ostream& os, InputMapType& input, OutputMapType& output)
{
    for (OutputMapType::iterator it = output.begin(); it != output.end(); ++it)
    {
        InputMapType::iterator rbit = input.find(it->first);
        os << it->first << " ";
        os << it->second.first << " ";
        os << it->second.second << " ";
        os << rbit->second.length << " ";
        os << rbit->second.height << endl;
    }
}

// Changes the grid entries to their opposite values for the
// rectangle r starting at x1,y1
void flip(int x1, int y1, const Rectangle& r, vector<vector<bool> >& grid)
{
    for (int x = x1; x < x1+r.length; x++)
    {
        for (int y = y1; y < y1+r.height; y++) grid[x][y] = !grid[x][y];
    }
}
// TODO: Write your backtracking search function here
bool isValid(InputMapType::iterator it, vector<vector<bool> > grid,int row,int col){
    for(int i=row;i<row+it->second.height;++i){
        for(int j=col;j<col+it->second.length;++j){
            if(grid[i][j]==true){
                return false;
            }
        }
    }
    return true;
}

bool solve(InputMapType::iterator it, InputMapType& input, OutputMapType& output,vector<vector<bool> > grid){
    //stops when iterator reaches the end
    if(it==input.end()){
        return true;
    }
    //traverse through the grid to see if there's 
    //another tile present in where we want to place the current tile
    for(int x=0;x<m-(it->second.height)+1;++x){
       for(int y=0;y<n-(it->second.length)+1;++y){
           //if placing the current tile does not overlap with any prexisting tile
           //place it here by marking grid to true and insert the coordinates into output
           if(isValid(it,grid,x,y)){
                for(int i=x;i<x+it->second.height;++i){
                    for(int j=y;j<y+it->second.length;++j){
                        grid[i][j]=true;
                    }
                }
                output.insert(pair<const int,pair<int,int> >(it->first,pair<int,int>(x,y)));
                InputMapType::iterator iter=it;
                //do this for the next tile recursively, if the next tile passes, return true
                if(solve(++iter,input,output,grid)){
                    return true;
                //if the next tile does not pass, make grid false
                }else{
                    for(int i=x;i<x+it->second.height;++i){
                        for(int j=y;j<y+it->second.length;++j){
                            grid[i][j]=false;
                        }
                    }
                }
           }
       }
   }
   //tile didn't fit the first time, try rotating it
   if(it->second.length!=it->second.height){
       int temp=it->second.length;
       it->second.length=it->second.height;
       it->second.height=temp;
       //try inserting it after rotating it
       //repeat the same as above
       for(int x=0;x<m-(it->second.height)+1;++x){
           for(int y=0;y<n-(it->second.length)+1;++y){
                if(isValid(it,grid,x,y)){
                    for(int i=x;i<x+it->second.height;++i){
                        for(int j=y;j<y+it->second.length;++j){
                            grid[i][j]=true;
                        }
                    }
                    output.insert(pair<const int,pair<int,int> >(it->first,pair<int,int>(x,y)));
                    InputMapType::iterator iter=it;
                    if(solve(++iter,input,output,grid)){
                        return true;
                    }else{
                        for(int i=x;i<x+it->second.height;++i){
                            for(int j=y;j<y+it->second.length;++j){
                                grid[i][j]=false;
                            }
                        }
                    }
                }
            }
        }
   }
   return false;
}

int main(int argc, char *argv[])
{
    if (argc < 3) {
        cout << "please specify an input and output file";
        return 0;
    }
    ifstream ifile(argv[1]);
    stringstream ss;
    string line;
    ofstream ofile(argv[2]);
    int x;
    getline(ifile, line);
    ss << line;
    ss >> n;
    ss >> m;
    ss >> x;

    InputMapType input;
    OutputMapType output;
    for (int i = 0; i < x; i++) {
        getline(ifile, line);
        stringstream ss2(line);
        Rectangle r;
        ss2 >> r.ID;
        ss2 >> r.length;
        ss2 >> r.height;
        input.insert(std::make_pair(r.ID, r));
    }
    ifile.close();
    vector<vector<bool> > grid;

    for (int i = 0; i < n; i++)
    {
        grid.push_back(vector<bool>(m, false));
    }
    InputMapType::iterator it = input.begin();
    bool solution_exists = false;
    
    // TODO:  Call your backtracking search function here
    if(solve(it,input,output,grid)){
        
        solution_exists=true;
    }
    
    if (!solution_exists) {
        ofile << "No solution found.";
    }
    else {
        printSolution(ofile, input, output);
    }
    ofile.close();
    return 0;
}