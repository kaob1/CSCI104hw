#ifndef RBBST_H
#define RBBST_H

#include <iostream>
#include <exception>
#include <cstdlib>
#include <algorithm>
#include "bst.h"

struct KeyError { };

/**
* A special kind of node for an AVL tree, which adds the height as a data member, plus
* other additional helper functions. You do NOT need to implement any functionality or
* add additional data members or helper functions.
*/
template <typename Key, typename Value>
class AVLNode : public Node<Key, Value>
{
public:
    // Constructor/destructor.
    AVLNode(const Key& key, const Value& value, AVLNode<Key, Value>* parent);
    virtual ~AVLNode();

    // Getter/setter for the node's height.
    int getHeight () const;
    void setHeight (int height);

    // Getters for parent, left, and right. These need to be redefined since they
    // return pointers to AVLNodes - not plain Nodes. See the Node class in bst.h
    // for more information.
    virtual AVLNode<Key, Value>* getParent() const override;
    virtual AVLNode<Key, Value>* getLeft() const override;
    virtual AVLNode<Key, Value>* getRight() const override;

protected:
    int height_;
};

/*
  -------------------------------------------------
  Begin implementations for the AVLNode class.
  -------------------------------------------------
*/

/**
* An explicit constructor to initialize the elements by calling the base class constructor and setting
* the color to red since every new node will be red when it is first inserted.
*/
template<class Key, class Value>
AVLNode<Key, Value>::AVLNode(const Key& key, const Value& value, AVLNode<Key, Value> *parent) :
    Node<Key, Value>(key, value, parent), height_(1)
{

}

/**
* A destructor which does nothing.
*/
template<class Key, class Value>
AVLNode<Key, Value>::~AVLNode()
{

}

/**
* A getter for the height of a AVLNode.
*/
template<class Key, class Value>
int AVLNode<Key, Value>::getHeight() const
{
    return height_;
}

/**
* A setter for the height of a AVLNode.
*/
template<class Key, class Value>
void AVLNode<Key, Value>::setHeight(int height)
{
    height_ = height;
}

/**
* An overridden function for getting the parent since a static_cast is necessary to make sure
* that our node is a AVLNode.
*/
template<class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getParent() const
{
    return static_cast<AVLNode<Key, Value>*>(this->parent_);
}

/**
* Overridden for the same reasons as above.
*/
template<class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getLeft() const
{
    return static_cast<AVLNode<Key, Value>*>(this->left_);
}

/**
* Overridden for the same reasons as above.
*/
template<class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getRight() const
{
    return static_cast<AVLNode<Key, Value>*>(this->right_);

}


/*
  -----------------------------------------------
  End implementations for the AVLNode class.
  -----------------------------------------------
*/


template <class Key, class Value>
class AVLTree : public BinarySearchTree<Key, Value>
{
public:
    virtual void insert (const std::pair<const Key, Value> &new_item); // TODO
    virtual void remove(const Key& key);  // TODO
protected:
    virtual void nodeSwap( AVLNode<Key,Value>* n1, AVLNode<Key,Value>* n2);

    // Add helper functions here
    void rotateLeft ( AVLNode<Key,Value>* n);
    void rotateRight ( AVLNode<Key,Value>* n);
    void removeFix(AVLNode<Key,Value>* n);
    
};

//same as insert in bst.h, but balance the tree after inserting
template<class Key, class Value>
void AVLTree<Key, Value>::insert (const std::pair<const Key, Value> &new_item)
{
    //use a trailing node to keep track of where to insert 
    //the new node when the traversing node becomes null
    AVLNode<Key,Value>* adding=new AVLNode<Key,Value>(new_item.first,new_item.second,NULL);
    AVLNode<Key,Value>*trailer=NULL;
    AVLNode<Key,Value>*temp=static_cast<AVLNode<Key,Value>*>(this->root_);
    //if tree is empty
    if(this->root_==NULL){
        this->root_=adding;
        this->root_->setLeft(NULL);
        this->root_->setRight(NULL);
    }else{
        //traverse to the leaf node
        while(temp!=NULL){
            trailer=temp;
            //if the key already exists, increase the value by 1
            if(new_item.first==temp->getKey()){
                temp->setValue(temp->getValue()+1);
                return;
            }
            if(new_item.first > temp->getKey()){
                temp=temp->getRight();
            }else{
                temp=temp->getLeft();
            }
        }
        //insert the node and set its parent and children
        if(new_item.first < trailer->getKey()){
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
    //if adding to root or second node in the tree, tree must be balanced
    //if adding to non root,
    //balance the tree if it is not balanced
    if(this->root_!=adding){
        AVLNode<Key,Value>* p =adding->getParent();
        AVLNode<Key,Value>* g =p->getParent();
        if(g!=NULL && !BinarySearchTree<Key,Value>::isBalanced()){
            //BALANCE IT
            if(g->getLeft()==p && p->getLeft()==adding){
                //zigzig
                rotateRight(g);
            }else if(g->getRight()==p && p->getRight()==adding){
                //zigzig
                rotateLeft(g);
            }else if(g->getRight()==p && p->getLeft()==adding){
                //zigzag
                rotateRight(p);
                rotateLeft(g);
            }else if(g->getLeft()==p && p->getRight()==adding){
                //zigzag
                rotateLeft(p);
                rotateRight(g);
            }
        }
    }
}
template<class Key, class Value>
void AVLTree<Key, Value>::rotateRight ( AVLNode<Key,Value>* n)
{
    //top is the node that will be the parent after rotating
    //extra is the subtree of top that will have no parent, so 
    //add them to the left child of n since n will have no left child
    AVLNode<Key,Value>* top = n->getLeft();
    AVLNode<Key,Value>* extra=top->getRight();
    AVLNode<Key,Value>* parentOfN=n->getParent();
    n->setLeft(extra);
    if(extra!=NULL){
        extra->setParent(n);
    }
    top->setRight(n);
    n->setParent(top);
    //if n was originally the root, make top the new root
    if(this->root_==n){
        this->root_=top;
        top->setParent(NULL);
    }else{
        //rearrange the pointers to parent and children
        if(parentOfN!=NULL && parentOfN->getLeft()==n){
            parentOfN->setLeft(top);
            top->setParent(parentOfN);
        }else if(parentOfN!=NULL && parentOfN->getRight()==n){
            parentOfN->setRight(top);
            top->setParent(parentOfN);
        }
    }
}
template<class Key, class Value>
void AVLTree<Key, Value>::rotateLeft ( AVLNode<Key,Value>* n)
{
    //same as rotateRight but just opposite direction
    AVLNode<Key,Value>* top = n->getRight();
    AVLNode<Key,Value>* extra=top->getLeft();
    AVLNode<Key,Value>* parentOfN=n->getParent();
    n->setRight(extra);
    if(extra!=NULL){
        extra->setParent(n);
    }
    top->setLeft(n);
    n->setParent(top);
    if(this->root_==n){
        this->root_=top;
        top->setParent(NULL);
    }else{
        if(parentOfN!=NULL && parentOfN->getLeft()==n){
            parentOfN->setLeft(top);
            top->setParent(parentOfN);
        }else if(parentOfN!=NULL && parentOfN->getRight()==n){
            parentOfN->setRight(top);
            top->setParent(parentOfN);
        }
    }
}

//same as bst.h remove, but balance the tree after removing
template<class Key, class Value>
void AVLTree<Key, Value>:: remove(const Key& key)
{
    //if tree is empty, don't do anything
    if(this->root_==NULL){
        return;
    }
    Node<Key,Value>* d = BinarySearchTree<Key,Value>::internalFind(key);
    AVLNode<Key,Value>* deleting=static_cast<AVLNode<Key,Value>*>(d);
    AVLNode<Key,Value>* parentOfDeleting=NULL;
    //deleting root; don't need to update parent
    if(this->root_==deleting){
        //need to handle: no child, left child, right child, 2 children;
        if(deleting->getLeft()==NULL && deleting->getRight()==NULL){
            //no child
            delete deleting;
            this->root_=NULL;
        }else if(deleting->getRight()==NULL && deleting->getLeft()!=NULL){
            //left child
            deleting->getLeft()->setParent(NULL);
            this->root_=deleting->getLeft();
            delete deleting;
        }else if(deleting->getRight()!=NULL && deleting->getLeft()==NULL){
            //right child
            deleting->getRight()->setParent(NULL);
            this->root_=deleting->getRight();
            delete deleting;
        }else if(deleting->getRight()!=NULL && deleting->getLeft()!=NULL){
            //2 children
            //swap with predecessor
            Node<Key,Value>* pre=BinarySearchTree<Key,Value>::predecessor(deleting);
            AVLNode<Key,Value>* pred=static_cast<AVLNode<Key,Value>*>(pre);
            nodeSwap(deleting,pred);
            parentOfDeleting=deleting->getParent();
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
        if(deleting->getRight()!=NULL && deleting->getLeft()!=NULL){
            //2 children
            Node<Key,Value>* pre=BinarySearchTree<Key,Value>::predecessor(deleting);
            AVLNode<Key,Value>* pred=static_cast<AVLNode<Key,Value>*>(pre);
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
    //helper function to balance the tree
    removeFix(parentOfDeleting);
}
template<class Key, class Value>
void AVLTree<Key, Value>:: removeFix(AVLNode<Key,Value>* n){
    //if tree is empty, do nothing
    if(n==NULL){
        return;
    }
    //if tree is already balanced, do nothing
    if(BinarySearchTree<Key,Value>::isBalanced()){
        return;
    }
    //case 1: n is out of balance
    if(!BinarySearchTree<Key,Value>::balanceHelper(n)){
        //c = taller child of n
        //g = taller child of c
        //if both children of c are the same height, choose g that 
        //would allow us to use zigzig instead of zigzag
        AVLNode<Key,Value>* c;
        AVLNode<Key,Value>* g;
        if(BinarySearchTree<Key,Value>::heightofTree(n->getLeft())>
           BinarySearchTree<Key,Value>::heightofTree(n->getRight()) ){
            c = n->getLeft();
        }else{
            c = n->getRight();
        }
        if(BinarySearchTree<Key,Value>::heightofTree(c->getLeft())==
           BinarySearchTree<Key,Value>::heightofTree(c->getRight()) ){
            if(c==n->getLeft()){
                g=c->getLeft();
            }else{
                g=c->getRight();
            }
        }else if(BinarySearchTree<Key,Value>::heightofTree(c->getLeft())>
           BinarySearchTree<Key,Value>::heightofTree(c->getRight()) ){
            g=c->getLeft();
        }else{
            g=c->getRight();
        }
        //case 1.1: zigzig
        //just like in insert
        if(n->getLeft()==c && c->getLeft()==g){
            rotateRight(n);
            n->setHeight(BinarySearchTree<Key,Value>::heightofTree(n));
            c->setHeight(BinarySearchTree<Key,Value>::heightofTree(c));
            removeFix(n->getParent());
        }else if(n->getRight()==c && c->getRight()==g){
            rotateLeft(n);
            n->setHeight(BinarySearchTree<Key,Value>::heightofTree(n));
            c->setHeight(BinarySearchTree<Key,Value>::heightofTree(c));
            removeFix(n->getParent());
        }
        //case 1.2:zigzag
        if(n->getLeft()==c && c->getRight()==g){
            rotateLeft(c);
            rotateRight(n);
            n->setHeight(BinarySearchTree<Key,Value>::heightofTree(n));
            c->setHeight(BinarySearchTree<Key,Value>::heightofTree(c));
            g->setHeight(BinarySearchTree<Key,Value>::heightofTree(g));
            removeFix(n->getParent());
        }else if(n->getRight()==c && c->getLeft()==g){
            rotateRight(c);
            rotateLeft(n);
            n->setHeight(BinarySearchTree<Key,Value>::heightofTree(n));
            c->setHeight(BinarySearchTree<Key,Value>::heightofTree(c));
            g->setHeight(BinarySearchTree<Key,Value>::heightofTree(g));
            removeFix(n->getParent());
        }
    }
    //do this recursively up the ancestor chain
    removeFix(n->getParent());
}
template<class Key, class Value>
void AVLTree<Key, Value>::nodeSwap( AVLNode<Key,Value>* n1, AVLNode<Key,Value>* n2)
{
    BinarySearchTree<Key, Value>::nodeSwap(n1, n2);
    int tempH = n1->getHeight();
    n1->setHeight(n2->getHeight());
    n2->setHeight(tempH);
}


#endif
