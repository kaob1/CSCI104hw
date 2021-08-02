#include <iostream>
#include <string>
#include <time.h>
#include <math.h>
#include <cstdlib>
#include <iostream>
#include <vector>
#include <utility>
#include <map>
#include <set>
#include <stack>
using namespace std;

int main(){
    vector<int> v(3,0);
    int i=0;
    int j=0;
    v[i++]=2;
    j ? j = v[j - 1] : i++;
    for(int x=0;x<v.size();x++){
        cout<<v[x]<<endl;
    }
    cout<<i<<endl;
    return 0;
}