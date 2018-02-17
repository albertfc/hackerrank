#!/bin/bash
for i in $(seq 2 16)
do

	echo -n "template<"
	for j in $(seq 1 $((i-1)))
	do
		echo -n "bool b$j, "
	done
	echo "bool b$i>"

	echo -n "struct Reversed_binary_value<1,"
	for j in $(seq 1 $((i-1)))
	do
		echo -n "b$j, "
	done
	echo "b$i>{"


	echo "	int operator()() {"

	echo -n "		struct Reversed_binary_value<"
	for j in $(seq 1 $((i-1)))
	do
		echo -n "b$j, "
	done
	echo "b$i> bb;"

	echo "		return $((2**$i)) + bb();"
	echo "	}"
	echo "};"
	echo
done

