
outlocation="./slib"
libname="PhWidgets"
libfullname="Photon Widgets"


echo "\023331;0m"
echo "\023333;4m"

print $(basename $0)
print " "
print "Export $libfullname library"

print_usage(){
	print " "
	print "Usage: $(basename $0) <destination project directory>"
}

get_phab_prjct_name(){
	if [ -f "$1/$(basename $1).ldb" ]; then
		if [ -f "$1/abapp.dfn" ]; then
			echo "$(basename $1)";
		fi
	fi
	
	echo ""
}

get_full_dir(){
	echo "$( cd "$( dirname "$1" )" && pwd)/$(basename "$1")"
}

if [ ! $1 ]; then
	print_usage;
	exit
fi

destination=$(get_full_dir $1)

if [ ! -d "$destination" ]; then
	print "$destination is not a valid directory"
	print_usage;
	exit
fi

if [ ! -d "$outlocation" ]; then
	print "Make library first"
	exit
fi
	
if [ $(basename $destination) == "src" ]; then
	destination=$(dirname $destination);
fi

prjctname=$(get_phab_prjct_name $destination)

if [ prjctname == "" ]; then
	destination=$(get_full_dir $1)
	print " "
	print "> Copy library to folder $destination"
	cp -r "$outlocation/" "$destination"
else
	print " "
	print "> Copy library to project $prjctname ($destination)"
	cp -r "$outlocation/." "$destination/src/"
	print "Done <"
	
	print " "
	print "> Make links to $libname library"
	cd "$destination/src/$libname/" && "./.linklib.sh"
fi


print "Done <"
print " "
