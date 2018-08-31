
binname=libphwidgets.a
outlocation="./slib"
libname="PhWidgets"
libfullname="Photon Widgets"


echo "\023331;0m"
echo "\023333;4m"

print $(basename $0)
print " "
print "Making $libfullname library"

coption=-O3
compiler=qcc

print " "
print "> Compiling objects..."


if [ "$1" == "debug" ]
	then
	coption=-g
	print "	Warning: DEBUG compile configuration!"
fi

compilefail=0

for i in $(find ./src/ -name "*.cpp"); do 
	fname=$(basename $i); 
	fname="${fname%.*}.o"; 

	while [ -f $fname ]; do 
		fname="~$fname"; 
	done
	
	print "	Compile $fname"; 
	$compiler -lang-c++ -Wall $coption -c $i -o $fname; 
	
	if [ $? -ne 0 ]; then
		compilefail=2;
	fi
	
	
done

if [ $compilefail == 1 ]; then
	print "	Compiled with warnings";
	compilefail=0;
fi

print "Done <"


if [ $compilefail == 0 ]; then
	
	print " "
	print "> Making lib-file..."

	if [ -d "$outlocation" ]; then
		if [ -d "./old" ]; then
			rm -r "./old"
		fi
		
		mkdir -p "./old"
		mv "$outlocation" "./old"
	fi

	mkdir -p "$outlocation"
	mkdir -p "$outlocation/$libname"


	if(ar rsc "$outlocation/$libname/$binname" *.o)
	then
		print "	Static library packed"
		
		if(ranlib "$outlocation/$libname/$binname")
		then
			hcount=0;
			for i in $(find ./src/ -name "*.h*"); do
				hdir=$(dirname $i);
				hdir=$(echo $hdir | sed -e "s/.\/src/.\/slib\/$libname\/include/g");
				
				mkdir -p  $hdir;
				cp -f $i $hdir;
				
				hcount=$((hcount+1));
			done
			
			cp "./etc/AbWidgetsWrap.cpp" "$outlocation/"
			cp "./etc/.linklib.sh" "$outlocation/$libname/"
			chmod a+rwx "$outlocation/$libname/.linklib.sh"
			
			print "	$hcount headers included"
			print "	Static library created"
			print "	Success!"
			print "Done <"
		else
			rm -r "$outlocation"
			print "	Can't run static library"
			print "Fail <"
			echo "Press enter to continue..."
			read
		fi
		
	else
		rm -r "$outlocation"
		print "	Can't pack static library"
		print "Fail <"
		echo "Press enter to continue..."
		read
	fi
else
	print "Some errors in compilation"
	print "Fail <"
	echo "Press enter to continue..."
	read
fi

 

print " "
print "> Deleting temporary objects..."

rm -r *.o

print "Done <"
print " "
