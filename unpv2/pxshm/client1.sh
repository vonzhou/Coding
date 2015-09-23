#!/bin/bash

for  i in 1 2 3
do
    #echo 'vonzhou'
    ./client1 /shm1 /sem1 1000 &
done

