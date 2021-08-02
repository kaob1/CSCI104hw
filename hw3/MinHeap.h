#include <vector>
#include <utility>
#include <iostream>
#include <string>

template <class T>
  class MinHeap {
     public:
     
       MinHeap (int d){
       /* Constructor that builds a d-ary Min Heap
          This should work for any d >= 2,
          but doesn't have to do anything for smaller d.*/

          //d must be >=2
          if(d<=1){
            throw "d has to be >=2.";
          }else{
            this->d=d;
          }
       }
       ~MinHeap (){}

       void add (T item, int priority){
         /* adds the item to the heap, with the given priority. */
        
        //create pair to store the item and priority
        //then store the pair in a vector
        //call trickleUp to reorder the vector.
            std::pair<T,int> adding;
            adding.first=item;
            adding.second=priority;
            heap.push_back(adding);
            int currIndex=heap.size()-1;
            int parentIndex=(currIndex-1)/d;
            trickleUp(parentIndex,currIndex);
       }

       const T & peek () const{
         /* returns the element with smallest priority.  
			Break ties however you wish.  
			Throws an exception if the heap is empty. */
        if(heap.empty()){
          throw "exception"; 
        }else{
          return heap[0].first;
        }
       }
       void remove (){
         /* removes the element with smallest priority.
			Break ties however you wish.
            Throws an exception if the heap is empty. */
          if(heap.empty()){
            throw "exception";
          }
          //if there's only one item, then just erase everything
          if(heap.size()==1){
            heap.clear();
          //else swap the first node with the last node.
          //delete the last node and call trickDown on the root node
          }else{
            std::pair<T, int> temp;
            temp.first=heap[0].first;
            temp.second=heap[0].second;
            heap[0]=heap[heap.size()-1];
            heap[heap.size()-1]=temp;
            typename std::vector< std::pair< T, int> >::iterator it;
            it=heap.end()-1;
            heap.erase(it);
            trickleDown(0);
          }
       }
       bool isEmpty (){
         /* returns true iff there are no elements on the heap. */
         if(heap.empty()){
           return true;
         }
         return false;
       }
       
      private:
      //d is the number of children in the heap
      //heap is the vector that I'm using for the heap.
      int d;
      std::vector< std::pair< T, int> >  heap;
      
      void trickleUp(int parent, int current){
        //do this until the parent is the root node, 
        //which would have no more parents to compare to.
        if(parent>=0){
          //swap if a child is smaller than its parent
          //do this recursively
          if(heap[current].second<heap[parent].second){
            std::pair<T, int> temp;
            temp.first=heap[current].first;
            temp.second=heap[current].second;
            heap[current]=heap[parent];
            heap[parent]=temp;
            trickleUp((parent-1)/d,parent);
          }
        }

      }
      
      void trickleDown(int index){
        //keep track of its leftmost child and rightmost child
        int leftChild=(d*index)+1;
        int rightChild=(d*index)+d;
        int min=index;
        //loop through all the middle children to compare the
        //priority and get the smallest one among all the children 
        //and the parent
        for(int x=leftChild;x<=rightChild;x++){
          if(x<(int)heap.size()){
            if(heap[x].second<heap[min].second){
              min=x;
            }
          }
        }
        //swap if the parent is not the smallest one
        //swap the parent with the smallest child
        //do this recursively
        if(min!=index){
          std::pair<T, int> temp;
          temp.first=heap[index].first;
          temp.second=heap[index].second;
          heap[index]=heap[min];
          heap[min]=temp;
          trickleDown(min);
        }
      }
  };

