#!/bin/bash

while true; do
    echo "File & Directory Manager"
    echo "1.Create File"
    echo "2.Create Directory"
    echo "3.Delete File/Directory"
    echo "4.List Directory Contents"
    echo "5.Move/Rename File or Directory"
    echo "6.Exit"
    read -p "Choose an option [1-6]: " choice
    echo ""

    case $choice in
        1)
            read -p "Enter file name to create: " file
            if [ -z "$file" ]; then
                echo "Error: File name cannot be empty."
            elif touch "$file" 2>/dev/null; then
                echo "File '$file' created."
            else
                echo "Failed to create file '$file'. Check permissions or path."
            fi
            ;;

        2)
            read -p "Enter directory name to create: " dir
            if [ -z "$dir" ]; then
                echo "Error: Directory name cannot be empty."
            elif mkdir -p "$dir" 2>/dev/null; then
                echo "Directory '$dir' created."
            else
                echo "Failed to create directory '$dir'. Check permissions or path."
            fi
            ;;

        3)
            read -p "Enter file or directory name to delete: " target
            if [ -z "$target" ]; then
                echo "Error: Target name cannot be empty."
            elif [ ! -e "$target" ]; then
                echo "'$target' does not exist."
            else
                read -p "Are you sure you want to delete '$target'? [y/N]: " confirm
                if [[ "$confirm" =~ ^[yY]$ ]]; then
                    if rm -r "$target" 2>/dev/null; then
                        echo "'$target' deleted."
                    else
                        echo "Failed to delete '$target'. Check permissions."
                    fi
                else
                    echo "Deletion cancelled."
                fi
            fi
            ;;

        4)
            read -p "Enter directory to list (leave empty for current): " list_dir
            list_dir=${list_dir:-.}  # Default to current directory if empty
            if [ ! -d "$list_dir" ]; then
                echo "Error: '$list_dir' is not a directory or does not exist."
            else
                ls -lah "$list_dir"
            fi
            ;;

        5)
            read -p "Enter current name: " src
            read -p "Enter new name: " dst
            if [ -z "$src" ] || [ -z "$dst" ]; then
                echo "Error: Source and destination names cannot be empty."
            elif mv "$src" "$dst" 2>/dev/null; then
                echo "Renamed/moved '$src' to '$dst'."
            else
                echo "Failed to rename/move '$src' to '$dst'. Check if source exists or permissions."
            fi
            ;;

        6)
            echo "Exiting. Goodbye!"
            break
            ;;

        *)
            echo "Invalid option. Please choose 1-6."
            ;;
    esac
    echo ""
done
