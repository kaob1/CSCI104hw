#include <iostream>
#include <fstream>
#include <set>
#include <sstream>
#include <vector>
#include <iomanip>
#include <algorithm>
#include "product.h"
#include "db_parser.h"
#include "product_parser.h"
#include "util.h"
#include "mydatastore.h"

using namespace std;
struct ProdNameSorter {
    bool operator()(Product* p1, Product* p2) {
        return (p1->getName() < p2->getName());
    }
};
void displayProducts(vector<Product*>& hits);

int main(int argc, char* argv[])
{
    if(argc < 2) {
        cerr << "Please specify a database file" << endl;
        return 1;
    }

    /****************
     * Declare your derived DataStore object here replacing
     *  DataStore type to your derived type
     ****************/
    MyDataStore* ds=new MyDataStore();



    // Instantiate the individual section and product parsers we want
    ProductSectionParser* productSectionParser = new ProductSectionParser;
    productSectionParser->addProductParser(new ProductBookParser);
    productSectionParser->addProductParser(new ProductClothingParser);
    productSectionParser->addProductParser(new ProductMovieParser);
    UserSectionParser* userSectionParser = new UserSectionParser;

    // Instantiate the parser
    DBParser parser;
    parser.addSectionParser("products", productSectionParser);
    parser.addSectionParser("users", userSectionParser);

    // Now parse the database to populate the DataStore
    if( parser.parse(argv[1], (*ds)) ) {
        cerr << "Error parsing!" << endl;
        return 1;
    }

    cout << "=====================================" << endl;
    cout << "Menu: " << endl;
    cout << "  AND term term ...                  " << endl;
    cout << "  OR term term ...                   " << endl;
    cout << "  ADD username search_hit_number     " << endl;
    cout << "  VIEWCART username                  " << endl;
    cout << "  BUYCART username                   " << endl;
    cout << "  QUIT new_db_filename               " << endl;
    cout << "====================================" << endl;

    vector<Product*> hits;
    bool done = false;
    while(!done) {
        cout << "\nEnter command: " << endl;
        string line;
        getline(cin,line);
        stringstream ss(line);
        string cmd;
        if((ss >> cmd)) {
            if( cmd == "AND") {
                string term;
                vector<string> terms;
                while(ss >> term) {
                    term = convToLower(term);
                    terms.push_back(term);
                }
                hits = (*ds).search(terms, 0);
                displayProducts(hits);
            }
            else if ( cmd == "OR" ) {
                string term;
                vector<string> terms;
                while(ss >> term) {
                    term = convToLower(term);
                    terms.push_back(term);
                }
                hits = (*ds).search(terms, 1);
                displayProducts(hits);
            }
            else if ( cmd == "QUIT") {
                string filename;
                if(ss >> filename) {
                    ofstream ofile(filename.c_str());
                    (*ds).dump(ofile);
                    ofile.close();
                }
                done = true;
            }
	    /* Add support for other commands here */
            else if(cmd =="ADD"){
                string username;
                ss>>username;
                int hit;
                ss>>hit;
                username=convToLower(username);
                //if username is not in database or if hit is not valid
                //print error message
                if((*ds).customers.find(username)==(*ds).customers.end() || 
                        hit>(int)hits.size() || hit<=0){
                    cout<<"Invalid Request"<<endl;
                //else, add the corresponding product to the user shopping cart vector
                }else{
                    map<string,vector<Product*> >::iterator cartit;
                    cartit=(*ds).customers.find(username);
                    cartit->second.push_back(hits[hit-1]);
                }
            }else if(cmd =="VIEWCART"){
                string username;
                ss>>username;
                username=convToLower(username);
                //if username is not in database, print error message
                if((*ds).customers.find(username)==(*ds).customers.end()){
                    cout<<"Invalid Request"<<endl;
                //else, iterate through the user database and print out each product
                //in the user's shopping cart
                }else{
                    vector<Product*>temp;
                    map<string,vector<Product*> >::iterator it;
                    it=(*ds).customers.find(username);
                    temp=it->second;
                    int num=1;
                    for(vector<Product*>::iterator i=temp.begin();i!=temp.end();++i){
                        cout<<"Item "+to_string(num)<<endl;
                        cout<<(*i)->displayString()<<endl;
                        cout<<endl;
                        num++;
                    }
                }
            }else if(cmd =="BUYCART"){
                string username;
                ss>>username;
                username=convToLower(username);
                //if username is not in database, print error message
                if((*ds).customers.find(username)==(*ds).customers.end()){
                    cout<<"Invalid Request"<<endl;
                }else{
                    vector<Product*>temp2;
                    map<string,vector<Product*> >::iterator it2;
                    it2=(*ds).customers.find(username);
                    temp2=it2->second;
                    int index;
                    //iterate through a vector that contains all the users
                    //to find the vector index of the user 
                    //do this in order to access user information to check if
                    //the user can afford the product
                    for(int x=0;x<(int)(*ds).userdump.size();++x){
                        if((*ds).userdump[x]->getName()==username){
                            index=x;
                            break;
                        }
                    }
                    //iterate through user's shopping cart
                    for(vector<Product*>::iterator i=temp2.begin();i!=temp2.end();){
                        //if product is in stock and user can afford
                        //change user balance, product qty, and clear product from cart
                        if((*i)->getQty()>0 && ((*ds).userdump[index]->getBalance()>(*i)->getPrice())){
                            (*i)->subtractQty(1);
                            (*ds).userdump[index]->deductAmount((*i)->getPrice());
                            i=temp2.erase(i);
                        //else, skip the item
                        }else{
                            i++;
                        }
                    }
                }
            }else {
                cout << "Unknown command" << endl;
            }
        }
    }
    //call destructor to delete the new Objects created
    delete ds;
    return 0;
}

void displayProducts(vector<Product*>& hits)
{
    int resultNo = 1;
    if (hits.begin() == hits.end()) {
    	cout << "No results found!" << endl;
    	return;
    }
    std::sort(hits.begin(), hits.end(), ProdNameSorter());
    for(vector<Product*>::iterator it = hits.begin(); it != hits.end(); ++it) {
        cout << "Hit " << setw(3) << resultNo << endl;
        cout << (*it)->displayString() << endl;
        cout << endl;
        resultNo++;
    }
}
