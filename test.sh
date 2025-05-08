#!/bin/bash

function test() {
	for i in $(find $1 -type f -name "*.cub"); do
		echo -e "\u001b[33mexecuting test: $i\033[0m"
		#valgrind --leak-check=full --show-leak-kinds=all --track-fds=yes ./cub3D $i
		./cub3D $i
		echo "exit status = $?"
		sleep 1
	done
}

echo -e "\u001b[32mTesting for invalid cases now...\033[0m"
sleep 1
test cubfiles/invalid

echo "Press enter for next test"
read
clear
echo -e "\u001b[32mTesting for valid cases now...\033[0m"
sleep 1
test cubfiles/valid

