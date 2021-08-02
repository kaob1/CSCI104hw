#include <iostream>
#include "ulliststr.h"
using namespace std;


int main(int argc, char* argv[])
{
  ULListStr testback;
  ULListStr testfront;

//PUSH_BACK when the list is empty
//should the only string: 1
cout<<"push_back() when list is empty: ";
testback.push_back("1");
cout<<testback.get(0)<<endl;

//normal push_back when adding to the end of array 
//without creating a new tail node.
//should print all strings: 1 to 10
cout<<"push_back() when there is space in the array: ";
testback.push_back("2");
testback.push_back("3");
testback.push_back("4");
testback.push_back("5");
testback.push_back("6");
testback.push_back("7");
testback.push_back("8");
testback.push_back("9");
testback.push_back("10");
for(int x=0;x<=9;x++){
  cout<<testback.get(x)<<" ";
}
cout<<endl;

//push_back when tail node is full, create a new tail node
//should print all strings: 1 to 11
cout<<"push_back() when tail node is full: ";
testback.push_back("11");
for(int x=0;x<=10;x++){
  cout<<testback.get(x)<<" ";
}
cout<<endl;

//size should be 11
cout<<"size is: "<<testback.size()<<endl;
cout<<endl;
//_____________________________________________________________

//POP_BACK
//when tail node only has 1 string
//should print the rest of the strings in prev node: 1 to 10
cout<<"pop_back() when tail node only has 1 string: ";
testback.pop_back();
for(int x=0;x<=9;x++){
  cout<<testback.get(x)<<" ";
}
cout<<endl;

//back() and front() tests
//back should print 10 
//front should print 1
cout<<"back(): "<<testback.back()<<endl;
cout<<"front(): "<<testback.front()<<endl;

//pop_back from a array with more than 1 string
//should print 1 since other strings are removed
cout<<"pop_back() when tail node has more than 1 string: ";
testback.pop_back();
testback.pop_back();
testback.pop_back();
testback.pop_back();
testback.pop_back();
testback.pop_back();
testback.pop_back();
testback.pop_back();
testback.pop_back();
cout<<testback.get(0)<<endl;


//pop_back the only string in the only Node
cout<<"After pop_back() the only string in the only Node, size becomes: ";
testback.pop_back();
cout<<testback.size()<<endl;
cout<<endl;
//______________________________________________________________


//PUSH_FRONT when list is empty
//should print the only string: 11
cout<<"push_front() when list is empty: ";
testfront.push_front("11");
cout<<testfront.get(0)<<endl;


//normal push_front when adding to the start of array 
//without creating a new head node.
//the loop should print out all strings: 2 to 11
cout<<"push_front() when there is space in the array: ";
testfront.push_front("10");
testfront.push_front("9");
testfront.push_front("8");
testfront.push_front("7");
testfront.push_front("6");
testfront.push_front("5");
testfront.push_front("4");
testfront.push_front("3");
testfront.push_front("2");
for(int x=0;x<=9;x++){
  cout<<testfront.get(x)<<" ";
}
cout<<endl;

//push_front when head node is full, create a new head node
// the loop should print out all the strings: 1 to 11
cout<<"push_front() when head node is full: ";
testfront.push_front("1");
for(int x=0;x<=10;x++){
  cout<<testfront.get(x)<<" ";
}
cout<<endl;

//size should be 11
cout<<"size is: "<<testfront.size()<<endl;

//_____________________________________________________________
cout<<endl;
//POP_FRONT
//when head node only has 1 string
//should print the rest of the strings in next node: 2 to 11
testfront.pop_front();
cout<<"pop_front() when head node only has 1 string: ";
for(int x=0;x<=9;x++){
  cout<<testfront.get(x)<<" ";
}
cout<<endl;

//back() and front() tests
//back should print 11 
//front should print 2
cout<<"back(): "<<testfront.back()<<endl;
cout<<"front(): "<<testfront.front()<<endl;

//pop_back from a array with more than 1 string
//should print 11 since other strings are removed
cout<<"pop_front() when array has more than 1 string: ";
testfront.pop_front();
testfront.pop_front();
testfront.pop_front();
testfront.pop_front();
testfront.pop_front();
testfront.pop_front();
testfront.pop_front();
testfront.pop_front();
testfront.pop_front();
cout<<testfront.get(0)<<endl;

//pop_front the only string in the only Node
testfront.pop_front();
cout<<"pop_front() the only string in the only Node, size becomes: "
<<testfront.size()<<endl;
//______________________________________________________________

//GETVALATLOC() test
  cout<<endl;
  cout<<"getValAtLoc() is tested through get(), which is implemented throughout the tests"<<endl;
}
