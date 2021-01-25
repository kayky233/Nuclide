

#!/bin/bash

file_b=""
outcome="lalaspec.dat"
for file_mac in `ls testmac/*.mac`; do  
	myrid $file_mac
    file_b="${file_mac:8:5}.dat"
   mv ${outcome} "$file_b"
	echo ${file_mac:8:5}
done 
