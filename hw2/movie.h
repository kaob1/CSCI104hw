#include "product.h"
#include "util.h"
using namespace std;

class Movie:public Product{
    public:
        Movie(const string category, const string name,double price, 
                            int qty, string genretype, string ratingscore);
        ~Movie(){}
        set<string> keywords() const;
        bool isMatch(vector<string>& searchTerms) const;
        string displayString() const;
        void dump(ostream& os) const;
        string getgenre();
        string getrating();
    private:
        string genre;
        string rating;
};