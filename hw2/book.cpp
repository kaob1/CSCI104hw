#include "book.h"
#include "util.h"
#include <sstream>
using namespace std;

Book::Book(const string category,const string name,string authorname,string isbnnumber,double price,int qty)
                    :Product(category,name,price,qty){
    author=authorname;
    isbn=isbnnumber;
}

set<string> Book::keywords() const{
    //book product can be searched by its name, isbn, or author
    //find the union of all three
    set<string> namekey;
    set<string> isbnkey;
    set<string> authorkey;
    set<string> unionNameAuthor;
    set<string> finalkey;
    namekey=parseStringToWords(name_);
    isbnkey.insert(isbn);
    authorkey=parseStringToWords(author);
    unionNameAuthor=setUnion(namekey,authorkey);
    finalkey=setUnion(unionNameAuthor,isbnkey);
    
    return finalkey;
}

bool Book::isMatch(vector<string>& searchTerms) const{
    return Product::isMatch(searchTerms);
}

string Book::displayString() const{
    //following the format of the assignment instructions
    //to be displayed in terminal
    stringstream s;
    s<<name_<<"\n"<<"Author: "<<author<<" "<<"ISBN: "
        <<isbn<<"\n"<<price_<<" "<<qty_<<" left.";
    string display=s.str();
    return display;
}

void Book::dump(ostream& os) const{
    //to be displayed in an output file
    os << category_ << "\n" << name_ << "\n" << price_
        <<"\n" << qty_ <<"\n"<<isbn<<"\n"<<author<< endl;
}

string Book::getisbn(){
    return isbn;
}

string Book::getauthor(){
    return author;
}