# Operating Systems

This project is created to learn and practice `fork()` method, message queues and POSIX threads. In `input files` folder, there are 5 `.txt` input files. Each of them contains one million random integers, which C files will be using. 
When each one of the programs are executed, user will be asked to choose an N value between 1 and 5, which means how many files will be used. Then a k value between 0 and 1000. k value means k<sub>th</sub> biggest values from N files will be selected.

## fork
In `findtopk.c` file, values are found by creating child processes from a parent process. Every child accesses to one input file, sorts the numbers using bubble sort and returns the k<sub>th</sub> biggest number. All these numbers will be written to `output.txt`.

## Message Queues
Message queues operate in `findtopk_mqueue.c` file. Firstly a message queue is created using `mq_open` method. This queue can be used only for writing. Then, as in findtopk.c, N files are read, sorted and k<sub>th</sub> biggest value is found. This value is sent to message queue using `mq_send` method. After finishing the sending of N files, message queue is closed. A new queue is opened with same name but this time, only for reading. Queue is read N times, meaning N values from queue is read and written to `output.txt`.

## POSIX Threads
`findtopk_thread.c` is used for this part. A sturct is created to keep the information about threads. N threads are created in main function and directed to func function. In func, again, files are read, sorted and found the k<sub>th</sub> biggest number. After all of the threads are done, tehy are closed using `pthread_join` method. In the end, found numbers are written in `output.txt`.
