#include "clothing.h"
#include "util.h"
using namespace std;

Clothing::Clothing(const string category, const string name, string clothesize, string clothebrand,
                                    double price, int qty):Product(category,name,price,qty){
    
    size=clothesize;
    brand=clothebrand;
}
set<string> Clothing::keywords() const{
    //clothing can be searched by its name or brand
    //find the union of those two
    set<string> namekey;
    set<string> brandkey;
    set<string> unionNameBrand;
    namekey=parseStringToWords(name_);
    brandkey=parseStringToWords(brand);
    unionNameBrand=setUnion(namekey,brandkey);
    
    return unionNameBrand;
}
bool Clothing::isMatch(vector<string>& searchTerms) const{
    return Product::isMatch(searchTerms);
}
string Clothing::displayString() const{
    //to be displayed in terminal
    stringstream s;
    s<<name_<<"\n"<<"Size: "<<size<<" "<<"Brand: "
        <<brand<<"\n"<<price_<<" "<<qty_<<" left.";
    string display=s.str();

    return display;
}
void Clothing::dump(ostream& os) const{
    //to be displayed in output file
    os << category_ << "\n" << name_ << "\n" << price_
        <<"\n" << qty_ <<"\n"<<size<<"\n"<<brand<< endl;
}
string Clothing::getsize(){
    return size;
}
string Clothing::getbrand(){
    return brand;
}