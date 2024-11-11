#!/bin/bash

# -----------------------------------------------
# Name        : Samudra Roy
# Roll No     : 002211001114
# Assignment  : 8 (Shell Script Programming)
# Filename    : 114_8.sh
# Description : This script performs various tasks including creating directories, moving files,
#               counting files, and displaying patterns as per assignment requirements.
# Compilation & Execution : bash 114_8.sh
# Input       : Choice options from the menu
# Output      : Outputs include directory creation, file lists, date display, file counts, sums, etc.
# -----------------------------------------------

# Function to display the menu
display_menu() {
    echo "Choose an option:"
    echo "1. Create 'All My Cprogs Files' directory in home"
    echo "2. Move all .c files to the created directory"
    echo "3. Show list of files in current directory"
    echo "4. Show current working directory"
    echo "5. Display date in dd:mm:yy format"
    echo "6. Count number of files in home directory"
    echo "7. Create a file listing all .c files in home"
    echo "8. Add two numbers (supports real numbers)"
    echo "9. Convert text file contents from lower to upper and vice versa"
    echo "10. Generate a pattern based on provided 'n'"
    echo "11. Exit"
}

# Menu-driven approach
while true; do
    display_menu
    read -p "Enter your choice: " choice

    case $choice in
        1)
            mkdir -p "$HOME/All My Cprogs Files" || echo "Error: Directory creation failed."
            echo "Directory 'All My Cprogs Files' created in home directory."
            ;;
        
       2)
            # Check if there are any .c files in the current directory
            if ls *.c 1> /dev/null 2>&1; then
                mv *.c "$HOME/All My Cprogs Files" 2>/dev/null || echo "Error: Move failed."
                echo "Moved all .c files to '$HOME/All My Cprogs Files'."
            else
                echo "No .c files found in the current directory."
            fi
            ;;        
        3)
            echo "Files in the current directory:"
            ls
            ;;
        
        4)
            echo "Current working directory:"
            pwd
            ;;
        
        5)
            echo "Date in dd:mm:yy format:"
            date +"%d:%m:%y"
            ;;
        
        6)
            echo "Number of files in the home directory:"
            find "$HOME" -type f | wc -l
            ;;
        
        7)
            find "$HOME" -name "*.c" > "$HOME/list_of_c_files.txt"
            echo "List of .c files saved in $HOME/list_of_c_files.txt"
            ;;
        
        8)
            read -p "Enter first number: " num1
            read -p "Enter second number: " num2
            sum=$(echo "$num1 + $num2" | bc)
            echo "Sum of $num1 and $num2 is: $sum"
            ;;
        
        9)
            read -p "Enter filename for case conversion: " filename
            if [ -f "$filename" ]; then
                tr 'a-zA-Z' 'A-Za-z' < "$filename" > "${filename}_converted"
                echo "Converted content saved to ${filename}_converted"
            else
                echo "File does not exist."
            fi
            ;;
        
        10)
            read -p "Enter the value of 'n' for pattern generation: " n
            for (( i=1; i<=n; i++ )); do
                for (( j=1; j<=i; j++ )); do
                    echo -n "$j "
                done
                echo
            done
            ;;
        
        11)
            echo "Exiting the script."
            break
            ;;
        
        *)
            echo "Invalid choice. Please try again."
            ;;
    esac

    echo # Blank line for readability
done

