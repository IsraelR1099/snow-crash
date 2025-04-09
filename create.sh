#!/bin/bash

for i in $(seq -w 0 14); do
	dir="level$i"
	echo "Creating $dir structure..."

	mkdir -p "$dir/resources"
	touch "$dir/resources/README.md"
	touch "$dir/flag"
done

echo "All levels created."
