#! /bin/bash

# Assignment 7 : Question 8 . Write a script for addition of two numbers for real numbers also.

# Execution Command : bash 02_07_8.sh

# Sample input :
# a = 7.1 b = 2.2
# Sample output :
# sum = 9.3

echo "Enter 1st no. : "
read a 
echo "Enter 2nd no. : "
read b
echo sum = `echo $a + $b | bc`
