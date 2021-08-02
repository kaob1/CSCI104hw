#ifndef BST_H
#define BST_H

#include <iostream>
#include <exception>
#include <cstdlib>
#include <utility>

/**
 * A templated class for a Node in a search tree.
 * The getters for parent/left/right are virtual so
 * that they can be overridden for future kinds of
 * search trees, such as Red Black trees, Splay trees,
 * and AVL trees.
 */
template <typename Key, typename Value>
class Node
{
public:
    Node(const Key& key, const Value& value, Node<Key, Value>* parent);
    virtual ~Node();

    const std::pair<const Key, Value>& getItem() const;
    std::pair<const Key, Value>& getItem();
    const Key& getKey() const;
    const Value& getValue() const;
    Value& getValue();

    virtual Node<Key, Value>* getParent() const;
    virtual Node<Key, Value>* getLeft() const;
    virtual Node<Key, Value>* getRight() const;

    void setParent(Node<Key, Value>* parent);
    void setLeft(Node<Key, Value>* left);
    void setRight(Node<Key, Value>* right);
    void setValue(const Value &value);

protected:
    std::pair<const Key, Value> item_;
    Node<Key, Value>* parent_;
    Node<Key, Value>* left_;
    Node<Key, Value>* right_;
};

/*
  -----------------------------------------
  Begin implementations for the Node class.
  -----------------------------------------
*/

/**
* Explicit constructor for a node.
*/
template<typename Key, typename Value>
Node<Key, Value>::Node(const Key& key, const Value& value, Node<Key, Value>* parent) :
    item_(key, value),
    parent_(parent),
    left_(NULL),
    right_(NULL)
{

}

/**
* Destructor, which does not need to do anything since the pointers inside of a node
* are only used as references to existing nodes. The nodes pointed to by parent/left/right
* are freed within the deleteAll() helper method in the BinarySearchTree.
*/
template<typename Key, typename Value>
Node<Key, Value>::~Node()
{
    
}

/**
* A const getter for the item.
*/
template<typename Key, typename Value>
const std::pair<const Key, Value>& Node<Key, Value>::getItem() const
{
    return item_;
}

/**
* A non-const getter for the item.
*/
template<typename Key, typename Value>
std::pair<const Key, Value>& Node<Key, Value>::getItem()
{
    return item_;
}

/**
* A const getter for the key.
*/
template<typename Key, typename Value>
const Key& Node<Key, Value>::getKey() const
{
    return item_.first;
}

/**
* A const getter for the value.
*/
template<typename Key, typename Value>
const Value& Node<Key, Value>::getValue() const
{
    return item_.second;
}

/**
* A non-const getter for the value.
*/
template<typename Key, typename Value>
Value& Node<Key, Value>::getValue()
{
    return item_.second;
}

/**
* An implementation of the virtual function for retreiving the parent.
*/
template<typename Key, typename Value>
Node<Key, Value>* Node<Key, Value>::getParent() const
{
    return parent_;
}

/**
* An implementation of the virtual function for retreiving the left child.
*/
template<typename Key, typename Value>
Node<Key, Value>* Node<Key, Value>::getLeft() const
{
    return left_;
}

/**
* An implementation of the virtual function for retreiving the right child.
*/
template<typename Key, typename Value>
Node<Key, Value>* Node<Key, Value>::getRight() const
{
    return right_;
}

/**
* A setter for setting the parent of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setParent(Node<Key, Value>* parent)
{
    parent_ = parent;
}

/**
* A setter for setting the left child of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setLeft(Node<Key, Value>* left)
{
    left_ = left;
}

/**
* A setter for setting the right child of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setRight(Node<Key, Value>* right)
{
    right_ = right;
}

/**
* A setter for the value of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setValue(const Value& value)
{
    item_.second = value;
}

/*
  ---------------------------------------
  End implementations for the Node class.
  ---------------------------------------
*/

/**
* A templated unbalanced binary search tree.
*/
template <typename Key, typename Value>
class BinarySearchTree
{
public:
    BinarySearchTree(); //TODO
    virtual ~BinarySearchTree(); //TODO
    virtual void insert(const std::pair<const Key, Value>& keyValuePair); //TODO
    virtual void remove(const Key& key); //TODO
    void clear(); //TODO
    bool isBalanced() const; //TODO
    void print() const;
    bool empty() const;
public:
    /**
    * An internal iterator class for traversing the contents of the BST.
    */
    class iterator  // TODO
    {
    public:
        iterator();

        std::pair<const Key,Value>& operator*() const;
        std::pair<const Key,Value>* operator->() const;

        bool operator==(const iterator& rhs) const;
        bool operator!=(const iterator& rhs) const;

        iterator& operator++();

    protected:
        friend class BinarySearchTree<Key, Value>;
        iterator(Node<Key,Value>* ptr);
        Node<Key, Value> *current_;
    };

public:
    iterator begin() const;
    iterator end() const;
    iterator find(const Key& key) const;

protected:
    // Mandatory helper functions
    Node<Key, Value>* internalFind(const Key& k) const; // TODO
    Node<Key, Value> *getSmallestNode() const;  // TODO
    static Node<Key, Value>* predecessor(Node<Key, Value>* current); // TODO
    // Note:  static means these functions don't have a "this" pointer
    //        and instead just use the input argument.

    // Provided helper functions
    virtual void printRoot (Node<Key, Value> *r) const;
    virtual void nodeSwap( Node<Key,Value>* n1, Node<Key,Value>* n2) ;

    // Add helper functions here
    void clearHelper(Node<Key,Value>* n);
    bool balanceHelper(Node<Key,Value>* n) const;
    int heightofTree(Node<Key,Value>* n) const;
protected:
    Node<Key, Value>* root_;
    // You should not need other data members
};

/*
--------------------------------------------------------------
Begin implementations for the BinarySearchTree::iterator class.
---------------------------------------------------------------
*/

/**
* Explicit constructor that initializes an iterator with a given node pointer.
*/
template<class Key, class Value>
BinarySearchTree<Key, Value>::iterator::iterator(Node<Key,Value> *ptr)
{
    // TODO
    current_=ptr;
}

/**
* A default constructor that initializes the iterator to NULL.
*/
template<class Key, class Value>
BinarySearchTree<Key, Value>::iterator::iterator() 
{
    // TODO
    current_=NULL;

}

/**
* Provides access to the item.
*/
template<class Key, class Value>
std::pair<const Key,Value> &
BinarySearchTree<Key, Value>::iterator::operator*() const
{
    return current_->getItem();
}

/**
* Provides access to the address of the item.
*/
template<class Key, class Value>
std::pair<const Key,Value> *
BinarySearchTree<Key, Value>::iterator::operator->() const
{
    return &(current_->getItem());
}

/**
* Checks if 'this' iterator's internals have the same value
* as 'rhs'
*/
template<class Key, class Value>
bool
BinarySearchTree<Key, Value>::iterator::operator==(
    const BinarySearchTree<Key, Value>::iterator& rhs) const
{
    // TODO
    return current_==rhs.current_;
}

/**
* Checks if 'this' iterator's internals have a different value
* as 'rhs'
*/
template<class Key, class Value>
bool
BinarySearchTree<Key, Value>::iterator::operator!=(
    const BinarySearchTree<Key, Value>::iterator& rhs) const
{
    return current_!=rhs.current_;
}


/**
* Advances the iterator's location using an in-order sequencing
*/
template<class Key, class Value>
typename BinarySearchTree<Key, Value>::iterator&
BinarySearchTree<Key, Value>::iterator::operator++()
{
    if(current_->getRight()!=NULL){
        current_ = current_->getRight();
    		while(current_->getLeft()!=NULL){
    			current_ = current_->getLeft();
    		}
    		return *this;
    }else{
        while(current_->getParent()!=NULL){
            if(current_->getParent()->getLeft()!=current_){
                current_ = current_->getParent();
            }else{
                current_ = current_->getParent();
                return *this;
            }   
        }
        current_ = NULL;
        return *this;
    }
}


/*
-------------------------------------------------------------
End implementations for the BinarySearchTree::iterator class.
-------------------------------------------------------------
*/

/*
-----------------------------------------------------
Begin implementations for the BinarySearchTree class.
-----------------------------------------------------
*/

/**
* Default constructor for a BinarySearchTree, which sets the root to NULL.
*/
template<class Key, class Value>
BinarySearchTree<Key, Value>::BinarySearchTree()
{
    root_=NULL;
}

template<typename Key, typename Value>
BinarySearchTree<Key, Value>::~BinarySearchTree()
{
    clear();
}

/**
 * Returns true if tree is empty
*/
template<class Key, class Value>
bool BinarySearchTree<Key, Value>::empty() const
{
    return root_ == NULL;
}

template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::print() const
{
    printRoot(root_);
    std::cout << "\n";
}

/**
* Returns an iterator to the "smallest" item in the tree
*/
template<class Key, class Value>
typename BinarySearchTree<Key, Value>::iterator
BinarySearchTree<Key, Value>::begin() const
{
    BinarySearchTree<Key, Value>::iterator begin(getSmallestNode());
    return begin;
}

/**
* Returns an iterator whose value means INVALID
*/
template<class Key, class Value>
typename BinarySearchTree<Key, Value>::iterator
BinarySearchTree<Key, Value>::end() const
{
    BinarySearchTree<Key, Value>::iterator end(NULL);
    return end;
}

/**
* Returns an iterator to the item with the given key, k
* or the end iterator if k does not exist in the tree
*/
template<class Key, class Value>
typename BinarySearchTree<Key, Value>::iterator
BinarySearchTree<Key, Value>::find(const Key & k) const
{
    Node<Key, Value> *curr = internalFind(k);
    BinarySearchTree<Key, Value>::iterator it(curr);
    return it;
}

/**
* An insert method to insert into a Binary Search Tree.
* The tree will not remain balanced when inserting.
*/
template<class Key, class Value>
void BinarySearchTree<Key, Value>::insert(const std::pair<const Key, Value> &keyValuePair)
{
    //use a trailing node to keep track of where to insert 
    //the new node when the traversing node becomes null
    Node<Key,Value>* adding=new Node<Key,Value>(keyValuePair.first,keyValuePair.second,NULL);
    Node<Key,Value>*trailer=NULL;
    Node<Key,Value>*temp=root_;
    //if tree is empty
    if(root_==NULL){
        root_=adding;
        root_->setLeft(NULL);
        root_->setRight(NULL);
    }else{
        //traverse to the leaf node
        while(temp!=NULL){
            trailer=temp;
            //if the key already exists, update the value by replacing
            if(keyValuePair.first==temp->getKey()){
                temp->setValue(keyValuePair.second);
                return;
            }
            if(keyValuePair.first > temp->getKey()){
                temp=temp->getRight();
            }else{
                temp=temp->getLeft();
            }
        }
        //insert the node and set its parent and children
        if(keyValuePair.first < trailer->getKey()){
            trailer->setLeft(adding);
            adding->setParent(trailer);
            adding->setLeft(NULL);
            adding->setRight(NULL);
        }else{
            trailer->setRight(adding);
            adding->setParent(trailer);
            adding->setLeft(NULL);
            adding->setRight(NULL);
        }
    }
}

/**
* A remove method to remove a specific key from a Binary Search Tree.
* The tree may not remain balanced after removal.
*/
template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::remove(const Key& key)
{
    //if tree is empty, don't do anything
    if(root_==NULL){
        return;
    }
    Node<Key,Value>* deleting = internalFind(key);
    //deleting root; don't need to update parent
    if(root_==deleting){
        //need to handle: no child, left child, right child, 2 children;
        if(deleting->getLeft()==NULL && deleting->getRight()==NULL){
            //no child
            delete deleting;
            root_=NULL;
        }else if(deleting->getRight()==NULL && deleting->getLeft()!=NULL){
            //left child
            deleting->getLeft()->setParent(NULL);
            root_=deleting->getLeft();
            delete deleting;
        }else if(deleting->getRight()!=NULL && deleting->getLeft()==NULL){
            //right child
            deleting->getRight()->setParent(NULL);
            root_=deleting->getRight();
            delete deleting;
        }else if(deleting->getRight()!=NULL && deleting->getLeft()!=NULL){
            //2 children
            //swap with predecessor
            Node<Key,Value>* pred=predecessor(deleting);
            nodeSwap(deleting,pred);
            Node<Key,Value>* parentOfDeleting=deleting->getParent();
            //after swapping, deleting can have 0 or left child
            if(deleting->getLeft()==NULL){
                if(parentOfDeleting->getLeft()==deleting){
                    parentOfDeleting->setLeft(NULL);
                    delete deleting;
                }else{
                    parentOfDeleting->setRight(NULL);
                    delete deleting;
                }
            }else{
                //has left child
                if(parentOfDeleting->getLeft()==deleting){
                    parentOfDeleting->setLeft(deleting->getLeft());
                    deleting->getLeft()->setParent(parentOfDeleting);
                    delete deleting;
                }else{
                    parentOfDeleting->setRight(deleting->getLeft());
                    deleting->getLeft()->setParent(parentOfDeleting);
                    delete deleting;
                }
            }
        }
    }else{
        //deleting a non root; need to keep track of parent of deleting
        Node<Key,Value>* parentOfDeleting=deleting->getParent();
        if(deleting->getRight()!=NULL && deleting->getLeft()!=NULL){
            //2 children
            Node<Key,Value>* pred=predecessor(deleting);
            nodeSwap(deleting,pred);
            //after swapping, deleting can have 0 or left child
            if(deleting->getLeft()==NULL){
                if(parentOfDeleting->getLeft()==deleting){
                    parentOfDeleting->setLeft(NULL);
                    delete deleting;
                }else{
                    parentOfDeleting->setRight(NULL);
                    delete deleting;
                }
            }else{
                //has left child
                if(parentOfDeleting->getLeft()==deleting){
                    parentOfDeleting->setLeft(deleting->getLeft());
                    deleting->getLeft()->setParent(parentOfDeleting);
                    delete deleting;
                }else{
                    parentOfDeleting->setRight(deleting->getLeft());
                    deleting->getLeft()->setParent(parentOfDeleting);
                    delete deleting;
                }
            }
        }else{
            //non root with 0 or 1 child
            if(deleting->getLeft()==NULL && deleting->getRight()==NULL){
                if(parentOfDeleting->getLeft()==deleting){
                    parentOfDeleting->setLeft(NULL);
                    delete deleting;
                }else{
                    parentOfDeleting->setRight(NULL);
                    delete deleting;
                }
            }else if(deleting->getLeft()!=NULL && deleting->getRight()==NULL){
                if(parentOfDeleting->getRight()==deleting){
                //right child of the parent
                    parentOfDeleting->setRight(deleting->getLeft());            
                    deleting->getLeft()->setParent(parentOfDeleting);
                }else{
                //left child of the parent
                    parentOfDeleting->setLeft(deleting->getLeft());
                    deleting->getLeft()->setParent(parentOfDeleting);
                }
                delete deleting;
            }else if(deleting->getLeft()==NULL && deleting->getRight()!=NULL){
                if(parentOfDeleting->getRight()==deleting){
                //right child of the parent
                    parentOfDeleting->setRight(deleting->getRight());
                    deleting->getRight()->setParent(parentOfDeleting);
                }else{
                //left child of the parent
                    parentOfDeleting->setLeft(deleting->getRight());
                    deleting->getRight()->setParent(parentOfDeleting);
                }
                delete deleting;
            }
        }
    }
}

template<class Key, class Value>
Node<Key, Value>* 
BinarySearchTree<Key, Value>::predecessor(Node<Key, Value>* current)
{
    //only need to get the predecessor for when a node has 2 children
    //since the only time we call predecssor is to nodeswap when 
    //when removing a node with 2 children.
    Node<Key,Value>* temp=current;
    //get rightmost leaf node of the left child.
    if(temp->getLeft()!=NULL){
        temp=temp->getLeft();
        while(temp->getRight()!=NULL){
            temp=temp->getRight();
        }
    }
    return temp;
}

/**
* A method to remove all contents of the tree and
* reset the values in the tree for use again.
*/
template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::clear()
{
    clearHelper(root_);
    root_=NULL;
}

template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::clearHelper(Node<Key,Value>* n){
    if(n==NULL){
        return;
    }else{
        clearHelper(n->getLeft());
        clearHelper(n->getRight());
        delete n;
    }
}

/**
* A helper function to find the smallest node in the tree.
*/
template<typename Key, typename Value>
Node<Key, Value>*
BinarySearchTree<Key, Value>::getSmallestNode() const
{
    //get the leftmost leaf node
    Node<Key,Value>* temp=root_;
    while (temp!=NULL && temp->getLeft() != NULL){
        temp = temp->getLeft();
    }
    return temp;
}

/**
* Helper function to find a node with given key, k and
* return a pointer to it or NULL if no item with that key
* exists
*/
template<typename Key, typename Value>
Node<Key, Value>* BinarySearchTree<Key, Value>::internalFind(const Key& key) const
{
    //traverse through the tree to find the node with the given key
    Node<Key,Value>* temp=root_;
    if(temp==NULL){
        return NULL;
    }
    while(temp!=NULL){
        if(temp->getKey()==key){
            return temp;
        }
        if(temp->getKey()>key ){
            temp=temp->getLeft();
        }else if(temp->getKey()<key){
            temp=temp->getRight();
        }
    }
    return NULL;
}

/**
 * Return true iff the BST is balanced.
 */
template<typename Key, typename Value>
bool BinarySearchTree<Key, Value>::isBalanced() const
{
    return balanceHelper(root_);
}

template<typename Key, typename Value>
bool BinarySearchTree<Key, Value>::balanceHelper(Node<Key,Value>* n) const
{
    int leftside;
    int rightside;
    //true if tree is empty
    if(n==NULL){
        return true;
    }
    //get the height of the left subtree and the right subtree
    leftside=heightofTree(n->getLeft());
    rightside=heightofTree(n->getRight());
    //if the difference is 0 or 1, and if every subtree is balanced
    //return true
    if(abs(leftside-rightside)<=1 && balanceHelper(n->getLeft()) 
        && balanceHelper(n->getRight())){
            return true;
    }
    return false;
}

template<typename Key, typename Value>
int BinarySearchTree<Key, Value>::heightofTree(Node<Key,Value>* n) const
{
    //get the height by returning the tallest height between the 2 children
    if(n==NULL){
        return 0;
    }
    return std::max(heightofTree(n->getLeft()),heightofTree(n->getRight()))+1;
}

template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::nodeSwap( Node<Key,Value>* n1, Node<Key,Value>* n2)
{
    if((n1 == n2) || (n1 == NULL) || (n2 == NULL) ) {
        return;
    }
    Node<Key, Value>* n1p = n1->getParent();
    Node<Key, Value>* n1r = n1->getRight();
    Node<Key, Value>* n1lt = n1->getLeft();
    bool n1isLeft = false;
    if(n1p != NULL && (n1 == n1p->getLeft())) n1isLeft = true;
    Node<Key, Value>* n2p = n2->getParent();
    Node<Key, Value>* n2r = n2->getRight();
    Node<Key, Value>* n2lt = n2->getLeft();
    bool n2isLeft = false;
    if(n2p != NULL && (n2 == n2p->getLeft())) n2isLeft = true;


    Node<Key, Value>* temp;
    temp = n1->getParent();
    n1->setParent(n2->getParent());
    n2->setParent(temp);

    temp = n1->getLeft();
    n1->setLeft(n2->getLeft());
    n2->setLeft(temp);

    temp = n1->getRight();
    n1->setRight(n2->getRight());
    n2->setRight(temp);

    if( (n1r != NULL && n1r == n2) ) {
        n2->setRight(n1);
        n1->setParent(n2);
    }
    else if( n2r != NULL && n2r == n1) {
        n1->setRight(n2);
        n2->setParent(n1);

    }
    else if( n1lt != NULL && n1lt == n2) {
        n2->setLeft(n1);
        n1->setParent(n2);

    }
    else if( n2lt != NULL && n2lt == n1) {
        n1->setLeft(n2);
        n2->setParent(n1);

    }


    if(n1p != NULL && n1p != n2) {
        if(n1isLeft) n1p->setLeft(n2);
        else n1p->setRight(n2);
    }
    if(n1r != NULL && n1r != n2) {
        n1r->setParent(n2);
    }
    if(n1lt != NULL && n1lt != n2) {
        n1lt->setParent(n2);
    }

    if(n2p != NULL && n2p != n1) {
        if(n2isLeft) n2p->setLeft(n1);
        else n2p->setRight(n1);
    }
    if(n2r != NULL && n2r != n1) {
        n2r->setParent(n1);
    }
    if(n2lt != NULL && n2lt != n1) {
        n2lt->setParent(n1);
    }


    if(this->root_ == n1) {
        this->root_ = n2;
    }
    else if(this->root_ == n2) {
        this->root_ = n1;
    }

}

/**
 * Lastly, we are providing you with a print function,
   BinarySearchTree::printRoot().
   Just call it with a node to start printing at, e.g:
   this->printRoot(this->root_) // or any other node pointer

   It will print up to 5 levels of the tree rooted at the passed node,
   in ASCII graphics format.
   We hope it will make debugging easier!
  */

// include print function (in its own file because it's fairly long)
#include "print_bst.h"

/*
---------------------------------------------------
End implementations for the BinarySearchTree class.
---------------------------------------------------
*/

#endif
