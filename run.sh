#!/bin/bash

for file in tests/validos/*; do 
	if ./bin/Compiler < $file | grep -q 'Fin.'; 
	then 
		echo "$file: PASSED"; 
	else 
		echo "$file: ERROR"; 
	fi; 
done

