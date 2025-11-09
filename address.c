#!/bin/bash
file="add.txt"

while true
do
    echo "-----------------------------------------------------"
    echo "---------------Address Book--------------------------"
    echo "-----------------------------------------------------"
    echo "1) create an address book"
    echo "2) view an address book"
    echo "3) insert a record"
    echo "4) delete a record"
    echo "5) modify a record"
    echo "6) exit"
    echo -n "Enter your choice"
    read choice

    case $choice in

        1) 
            echo " creating an address book"
            >>$file
            echo "Address book created"
            ;;
        2)
            if [ -s $file ]; then
                echo "------------Address book ----------"
                cat $file
            else
                echo "Address book is empty"
            fi
            ;;

        3)
            echo "Insert a record"
            echo "Enter a name"
            read name
            echo "Enter phone number"
            read phone
            echo "Enter email address"
            read email
            echo "$name | $phone | $email">> $file
            echo "record inserted successfully"
            ;;
        4)
            echo "Enter the name to delete" 
            read name
            if grep -q "^$name" $file; then
                grep -v "^$name" $file > temp && mv temp $file
                echo "record deleted"
            else
                echo "No record found"
            fi
            ;;
        5)
            echo "Enter the name to modify"
            read name
            if grep -q "^$name" $file; then
                grep -v "^$name" $file > temp && mv temp $file
                echo "Enter a name"
                read newname
                echo "Enter phone number"
                read newphone
                echo "Enter email address"
                read newemail
                echo "$newname | $newphone | $newemail">> $file

            else
                echo "No record found"
            fi
            ;;
        6)
            echo " Exiting goodbye"
            exit
            ;;
        *)
            echo "Invalid input"
            ;;
    esac
done

    


