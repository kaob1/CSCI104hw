In Hashtable.h and Hashtable.cpp, I created a hashtable data structure that stores a pair of string and int. The hash function I was given is described on the course website: https://bytes.usc.edu/cs104/homework/hw6/programming/. For probing, the program uses linear, quadratic, and double hashing probing methods depending on user input. 

Counting.cpp uses Hashtable.cpp and avltree.cpp that I created for hw4 to store all the different words in the input file using either hash table or AVL tree. It takes in 5 parameters: input.txt, output.txt, x, d, and r. Input.txt contains all the words that we want to store. X is the user input that determines the probing method that is used for the hashtable. When x=0, the hash table uses linear probing; when x=1, it uses quadratic probing; when x=2, it uses double hashing. When x=3, we store the words in an AVL tree as stated before. D is used to toggle debug mode for hash tables. When d=0, debug mode is off, meaning that the hash function is compeletly random. When d=1, debug mode is on, meaning that the has function will have the same result for the same strings every time. R is used to determine the number of times to run the program. This makes it easier for us to compare the times for each probing method when the input size is too small.

These are the results that I got for different input sizes...
Input size: 30
Linear Probing: 0.000454
Quadratic Probing: 0.000532667
Double Hashing: 0.00048
AVL TRee: 5.9e-05

Input size: 300
Linear Probing: 0.00323733
Quadratic Probing: 0.00354867
Double Hashing: 0.00355267
AVL TRee: 0.00067

Input size: 3000
Linear Probing: 0.0150617
Quadratic Probing: 0.0162467
Double Hashing: 0.015898
AVL TRee: 0.0145667

Input size: 30000
Linear Probing: 0.090797
Quadratic Probing: 0.096778
Double Hashing: 0.098707
AVL TRee: 0.465383

Overall, AVL tree is faster when input sizes are relatively low. However, as input size increases, hash table becomes faster than AVL tree. I'm surprised to see that linear probing, quadratic probing, and double hashing are about the same speed. I expected linear probing to be the slowest because there would be a huge cluster of data, making it slower to probe for empty indices. That might only be obvious when the input size gets to hundreds of thousands.


