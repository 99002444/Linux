# Library fine
![C/C++ CI](https://github.com/99002444/Linux/workflows/C/C++%20CI/badge.svg?branch=master)

The above files are used to implement sempahore, mutex and messge passing. When the name of the books are passed, the program calculates the fine for the next 4 days.
Sender.c is the common file which sends messages/ book name via message queue taking input from the user. 
In Mutex implementation mutex_reciever recieves the book names from the user through sender.c.
In semaphore implementation sem_recieve recieves the book name via message queue.

To run the file :
1. Mutex : 
  make all_mutex
2. Semaphore :
  make all_sem
