#include "product.h"
#include "util.h"
#include <iostream>
#include <sstream>
using namespace std;

class Book : public Product{
    public:
        Book(const string category,const string name,string authorname ,string isbnnumber,double price,int qty);
        ~Book(){
        }
        set<string> keywords() const;
        bool isMatch(vector<string>& searchTerms) const;
        string displayString() const;
        void dump(ostream& os) const;
        string getisbn();
        string getauthor();
    private:
        string isbn;
        string author;
};