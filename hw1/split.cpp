/*
CSCI 104: Homework 1 Problem 1

Write a recursive function to split a sorted singly-linked
list into two sorted linked lists, where one has the even 
numbers and the other contains the odd numbers. Students 
will receive no credit for non-recursive solutions. 
To test your program write a separate .cpp file and #include
split.h.  **Do NOT add main() to this file**.  When you submit
the function below should be the only one in this file.
*/

#include "split.h"
#include <iostream>
#include <fstream>
#include <cstddef>
using namespace std;
/* Add a prototype for a helper function here if you need */
Node*& addtoend(Node*& head, Node*& adding);

void split(Node*& in, Node*& odds, Node*& evens)
{
  //if linked list is empty, no need to split
  if(in==NULL){
    return;
  }

  //node is odd
  else if(in->value % 2 != 0){
    
    //if the odds linked list is empty
    if(odds == NULL){
      Node* oddhead=new Node(0,NULL);
      oddhead->value = in->value;
      oddhead->next=NULL;
      odds=oddhead;

    //when odds linked list is not empty
    //call addtoend() to append the node
    }else{
      Node* temp=new Node(0,NULL);
      temp->value=in->value;
      addtoend(odds,temp);
    }
  }

  //node is even
  else{

    //if the evens linked list is empty 
    if(evens == NULL){
      Node* evenhead=new Node(0,NULL);
      evenhead->value=in->value;
      evenhead->next=NULL;
      evens=evenhead;
    }

    //when evens linked list is not empy
    //call addtoend() to append the node
    else {
      Node* temp=new Node(0,NULL);
      temp->value=in->value;
      addtoend(evens,temp);
    }
  }

  //recursively call split() to go through the entire linked list
  split(in->next, odds, evens);
  in=NULL;
}

/* If you needed a helper function, write it here */
//helper function to execute the actual steps to
//add a value(adding) to a linked list with head node (head)
Node*& addtoend(Node*& head, Node*& adding){
  //if head node is empty, "adding" becomes the head
  if(head==NULL){
    return adding;
  
  //recursively add "adding" to the end of the linked list
  }else{
    head->next=addtoend(head->next,adding);
  }
  return head;
}
