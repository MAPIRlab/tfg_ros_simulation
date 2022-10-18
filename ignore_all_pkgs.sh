# Creates a COLCON_IGNORE empty file in all subfolders
shopt -s globstar
for d in */; do 
	touch -- "$d/COLCON_IGNORE"; 
done
