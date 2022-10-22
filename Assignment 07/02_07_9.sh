#! /bin/bash
# Assignment 7 : Question 9 . Write a script to convert string lower to upper and upper to lower from a file.

# Execution Command : bash 02_07_9.sh

# Sample input :
# <input file name>
# Sample output :
# <updated file text>

# Function to get File
getFile(){
    # Reading txtFileName to convert it's content
    echo -n "Enter File Name:"
    read txtFileName
    # Checking if file exist
    if [ ! -f $txtFileName ]; then
        echo "File Name $txtFileName does not exists."
        exit 1
    fi
}

clear
  echo "1. Uppercase to Lowercase "
  echo "2. Lowercase to Uppercase"
  echo "3. Exit"
  echo -n "Enter your Choice(1-3):"
  read Ch

  case "$Ch" in
    1) 
      # Function Call to get File 
      getFile    
      # Converting to lower case if user chose 1     
      echo "Converting Upper-case to Lower-Case "
      tr '[A-Z]' '[a-z]' <$txtFileName
    ;;

    2)
      # Function Call to get File 
      getFile
      # Converting to upper case if user chose 2
      echo "Converting Lower-Case to Upper-Case "
      tr '[a-z]' '[A-Z]' <$txtFileName
    ;;
    

    *) # exiting for all other cases
        echo "Exiting..."
        exit
    ;;
  esac
