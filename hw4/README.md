floorplan.cpp uses recursive backtracking to place X tiles into a N by M board without overlapping or going out of bounds. The file takes in an input.txt for the input and an output.txt to print the solution.

bst.h implements a binary search tree. It contains functions to perform the basic operations of a binary search tree, such as insert, remove, check if it's balanced. It also contains several helper functions to help perform these tasks.

avlbst.h implements an AVL tree by building on top of bst.h. I changed up the insert and remove functions to override the ones in bst.h since an AVL tree should be balanced after inserting and removing nodes. I also included helper functions rotateright and rotateleft to help perform zigzig and zigzag to balance the tree.