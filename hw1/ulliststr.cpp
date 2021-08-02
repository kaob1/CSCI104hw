#include <cstddef>
#include <stdexcept>
#include <iostream>
#include "ulliststr.h"

ULListStr::ULListStr()
{
  head_ = NULL;
  tail_ = NULL;
  size_ = 0;
}

ULListStr::~ULListStr()
{
  clear();
}

bool ULListStr::empty() const
{
  return size_ == 0;
}

size_t ULListStr::size() const
{
  return size_;
}

//___________________________________________________
void ULListStr::push_back(const std::string& val){
  //when the ULList is empty, adding the first Item
  if(empty()){
    Item* add=new Item(); 
    head_=add;
    tail_=add;
    size_++;
    add->val[0]=val;
    add->last++;    
  
  //when the tail node is full, create a new tail node
  }else if(tail_->last==sizeof(tail_->val)/sizeof(tail_->val[0])){
    Item* add=new Item();
    tail_->next=add;
    add->prev=tail_;
    tail_=add;
    size_++;
    add->val[0]=val;
    add->last++;

  //when the tail node is not full, add to the end of tail
  }else{
    tail_->val[tail_->last]=val;
    tail_->last++;
    size_++;
  }
}

void ULListStr::pop_back(){
  //if only 1 Node and 1 string
  if(tail_->last - tail_->first==1 && size_==1){
    Item* x = tail_;
    delete x; 
    tail_ = NULL;
    head_ = NULL;
  }
  //if tail node only 1 string
  else if(tail_->last==1){
    tail_=tail_->prev;
    delete tail_->next;
    tail_->next=NULL;
    size_--;
  }
  //everything else...
  //array having more than 1 string
  else{
    tail_->last=tail_->last-1;
    size_--;
  }
}

void ULListStr::push_front(const std::string& val){
  //when the ULList is empty, adding the first Item
  if(empty()){
    Item* add=new Item();
    head_=add; 
    tail_=add;
    size_++;
    add->val[0]=val;
    add->last++;

  //When head is not empty, create a new head node 
  //and add to the end of the new head node
  }else if(head_->first==0){
    Item* add=new Item();
    add->next=head_;
    head_->prev=add;
    add->prev=NULL;
    head_=add;
    size_++;
    add->val[sizeof(add->val)/sizeof(add->val[0])-1]=val;
    add->last=sizeof(add->val)/sizeof(add->val[0]);
    add->first=sizeof(add->val)/sizeof(add->val[0])-1;
  
  //when head node is not full, add to the start of head
  }else{
    head_->first--;
    head_->val[head_->first]=val;
    size_++;
  }
}

void ULListStr::pop_front(){
  //if only 1 Node and 1 string
  if(head_->last-head_->first == 1 && size_==1){
    Item* x=head_;
    delete x; 
    tail_=NULL;
    head_=NULL;
  }
  //if head node only 1 string
  else if(head_->first==sizeof(head_->val)/sizeof(head_->val[0])-1){
    head_=head_->next;
    delete head_->prev;
    head_->prev=NULL;
    size_--;
  }
  //everything else...
  //array having more than 1 string
  else{
    head_->first=head_->first+1;
    size_--;
  }
}

std::string const & ULListStr::back() const{
  return tail_->val[tail_->last-1];
}

std::string const & ULListStr::front() const{
  return head_->val[head_->first];
}

std::string* ULListStr::getValAtLoc(size_t loc) const{
  //if loc is out of bounds return NULL
  if(loc>=size_ || loc<0){
    return NULL;
  }

  //loop through each array in each node to find for the string at loc
  size_t temp=head_->first;
  size_t iter=0;
  Item* temphead=head_;
  while(iter!=loc){
    iter++;
    temp++;
    if(temp==temphead->last){
      temphead=temphead->next;
      temp=0;
    }
  }
  return &temphead->val[temp];
}

//________________________________________________________
void ULListStr::set(size_t loc, const std::string& val)
{
  std::string* ptr = getValAtLoc(loc);
  if(ptr == NULL){
    throw std::invalid_argument("Bad location");
  }
  *ptr = val;
}

std::string& ULListStr::get(size_t loc)
{
  std::string* ptr = getValAtLoc(loc);
  if(ptr == NULL){
    throw std::invalid_argument("Bad location");
  }
  return *ptr;
}

std::string const & ULListStr::get(size_t loc) const
{
  std::string* ptr = getValAtLoc(loc);
  if(ptr == NULL){
    throw std::invalid_argument("Bad location");
  }
  return *ptr;
}

void ULListStr::clear()
{
  while(head_ != NULL){
    Item *temp = head_->next;
    delete head_;
    head_ = temp;
  }
  tail_ = NULL;
  size_ = 0;
}
