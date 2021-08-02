#include "mydatastore.h"
#include<iostream>
#include<sstream>
using namespace std;
MyDataStore::~MyDataStore(){
    for(int x=0;x<(int)productdump.size();x++){
        delete productdump[x];
    }
    for(int x=0;x<(int)userdump.size();x++){
        delete userdump[x];
    }
}

void MyDataStore::addProduct(Product* p){
    //add the product to the vector that contains all products
    productdump.push_back(p);

    //find the keywords of the product and store them into a set of strings
    set<string>keys;
    keys= p->keywords();

    //iterate through the set of keywords
    set<Product*> productlist;
    for(set<string>::iterator it = keys.begin();it!=keys.end();++it){    
        //if the keyword does not already exist in the database,
        //create a new key and add the product to the corresponding set.
        if(database.find(*it)==database.end()){
            productlist.insert(p);
            database.insert(make_pair(*it,productlist));
        
        //else, insert the product into its corresponding set
        }else{
            map<string,set<Product*> >::iterator itmap = database.find(*it);
            itmap->second.insert(p);
        }
    }
}

void MyDataStore::addUser(User* u){
    //add the user to a vector that contains all user
    userdump.push_back(u);

    //add the user to a map that uses the user's name as key
    //and contains a vector as the user's shoppingcart
    vector<Product*> shoppingcart;
    string name=u->getName();
    name=convToLower(name);
    customers.insert(make_pair(name,shoppingcart));
}

vector<Product*> MyDataStore:: search(vector<string>& terms, int type){
    set<string> temp;
    set<Product*> listofproducts;
    vector<set <Product*> > vectorofsets;
    //convert terms from vector to set since we're going to search by
    //setIntersection and setUnion. The parameters of those functions are sets
    for(vector<string>::iterator it=terms.begin();it!=terms.end();++it){
        temp.insert(*it);
    }
    //create a vector that contains sets.
    //each set contains all the products that can be searched with keyword(terms)
    for(set<string>::iterator iter = temp.begin();iter!=temp.end();++iter){
        if(database.find(*iter)!=database.end()){
            set<Product*> productsethead = database.find(*iter)->second;
            vectorofsets.push_back(productsethead);
        }
    }
    listofproducts=vectorofsets[0];
    //perform AND search on all the sets.
    if(type==0){
        
        for(vector<set <Product*> >::iterator vectorit=vectorofsets.begin()+1;
            vectorit!=vectorofsets.end();++vectorit){
            listofproducts=setIntersection(listofproducts,*vectorit);
        }
    //perform OR search on all the sets
    }else if(type==1){
        for(vector<set <Product*> >::iterator vectorit=vectorofsets.begin()+1;
            vectorit!=vectorofsets.end();++vectorit){
            listofproducts=setUnion(listofproducts,*vectorit);
        }
    }
    //convert from set to vector since this function returns vector
    vector<Product*>settovector;
    for(set<Product*>::iterator setit=listofproducts.begin();setit!=listofproducts.end();++setit){
        settovector.push_back(*setit);
    }
    return settovector;
}

void MyDataStore::dump(ostream& ofile){
    //to be displayed in an output file
    ofile<<"<products>"<<"\n";
    for(int x =0;x<(int)productdump.size();++x){
        productdump[x]->dump(ofile);
    }
    ofile<<"</product>"<<"\n";
    ofile<<"<users>"<<"\n";
    for(int i=0;i<(int)userdump.size();++i){
        userdump[i]->dump(ofile);
    }
    ofile<<"</users>";

}