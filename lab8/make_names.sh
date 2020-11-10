#!/bin/bash

echo $1

~plank/bin/LINUX/random_names $1 > temp_names.txt

i=1
while [ $i -le $1 ];
do
    name=$(head -n $i temp_names.txt | tail -n 1)
    
    age=$RANDOM
    let "age %= 100"
    let "age += 1"
    
    gender=$RANDOM
    let "gender %= 2"
    if [ $gender -eq 0 ]
    then
        gender='M'
    else
        gender='F'
    fi
    
    echo $name
    printf "%d %c\n" $age $gender
    let "i += 1"
done

rm temp_names.txt
