#! /bin/bash
while true; do
	echo 
	echo "1. Create Employee Record"
	echo "2. Delete Employee Record"
	echo "3. Search Employee Record"
	echo "4. Display Employee Details"
	echo "5. Sort Records"
	echo "6. List All Records"
	echo "7. Exit"
	read -p "Enter your choice (1-7): " choice

	case $choice in
		1)
			read -p "Enter Employee name: " name
			read -p "Enter Employee number: " num
			read -p "Enter Enployee contact: " contact
			if grep -q "^.* $num .*$" employee_records.txt; then
				echo "Employee number $num already exists"
			else
				echo "$name $num $contact" >> employee_records.txt
				echo "Record Saved successfully!"
			fi
			;;

		2)
			read -p "Enter the employe number: " number
			grep -v "^.* $number .*$" employee_records.txt > temp.txt
			mv temp.txt employee_records.txt
			echo "Employee Deleted successfully"
			;;


		3)
			read -p "Enter the employee number: " number
			echo "Found employee record: "
			grep "^.* $number .*$" employee_records.txt
			;;

		4)
			read -p "Enter the employee number: " number
                        grep "^.* $number .*$" employee_records.txt
                        ;;

		5)
			sort -nk2,2 employee_records.txt > temp.txt
			mv temp.txt employee_records.txt
			echo "Records sorted successfully!"
			;;

		6)
			echo 
			echo "List of employee records available: "
			cat employee_records.txt
			;;

		7)
			exit 0
			;;

		*)
			echo "Invalid choice"
			;;

	esac
done
