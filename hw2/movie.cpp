#include "movie.h"
#include <sstream>
using namespace std;

Movie::Movie(const string category, const string name, double price,
                int qty, string genretype, string ratingscore):Product(category,name,price,qty){
    genre=genretype;
    rating=ratingscore;
}
set<string> Movie::keywords() const{
    //Movie can be searched by its name or genre
    //find the union of those two
    set<string> namekey;
    set<string> genrekey;
    set<string> unionNameGenre;
    namekey=parseStringToWords(name_);
    genrekey=parseStringToWords(genre);
    unionNameGenre=setUnion(namekey,genrekey);
    
    return unionNameGenre;
}
bool Movie::isMatch(vector<string>& searchTerms) const{
    return Product::isMatch(searchTerms);
}
string Movie::displayString() const{
    //to be displayed in terminal
    stringstream s;
    s<<name_<<"\n"<<"Genre: "<<genre<<" "<<"Rating: "
        <<rating<<"\n"<<price_<<" "<<qty_<<" left.";
    string display=s.str();

    return display;
}
void Movie::dump(ostream& os) const{
    //to be displayed in output file
    os << category_ << "\n" << name_ << "\n" << price_
        <<"\n" << qty_ <<"\n"<<genre<<"\n"<<rating<< endl;
}
string Movie::getgenre(){
    return genre;
}
string Movie::getrating(){
    return rating;
}