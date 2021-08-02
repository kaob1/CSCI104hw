#include "util.h"
#include "datastore.h"
#include <map>
#include <vector>
#include <set>
#include <utility>
#include "product.h"
#include <string>
#include"user.h"
using namespace std;

class MyDataStore : public DataStore{
    public:
        ~MyDataStore();
        void addProduct(Product* p);
        void addUser(User* u);
        vector<Product*> search(vector<string>& terms, int type);
        void dump(ostream& ofile);
    //using a product's keywords as the key for the map
    //each keyword matches to a set of Products that can be searched 
    //by that keyword.
    map<string,set<Product*> > database;

    //using a user's name as the string keyword for the map
    //each keyword matches to the user's shopping cart
    map<string,vector<Product*> >customers;

    //a vector of all the products added to the database
    //makes it easier to output every product into an output file
    vector<Product*>productdump;

    //a vector that contains all the users in the database
    //use this to access invdividual user information
    vector<User*>userdump;
};