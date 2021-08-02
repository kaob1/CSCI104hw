#include "util.h"
#include "product.h"
#include <iostream>
#include <sstream>
using namespace std;

class Clothing:public Product{
    public:
        Clothing(const string category, const string name,string clothesize,string clothebrand,double price, int qty);
        ~Clothing(){
        }
        set<string> keywords() const;
        bool isMatch(vector<string>& searchTerms) const;
        string displayString() const;
        void dump(ostream& os) const;
        string getsize();
        string getbrand();
    private:
        string size;
        string brand;
};