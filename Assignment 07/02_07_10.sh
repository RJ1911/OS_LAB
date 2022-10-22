#! /bin/bash

# Assignment 7 : Question 10 . Read ‘n’ and generate a pattern given below.
#				1
#				1 2
#				1 2 3
#				1 2 3 4

# Execution Command : bash 02_07_10.sh

# Sample input :
# <enter n>
# Sample output :
# <generate pattern>

echo "Enter n : "
read rows
for((i=1; i<=rows; i++))
do
  for((j=1; j<=i; j++))
  do
    echo -n "$number "
    number=$((number + 1))
  done
  number=1
  echo
done
