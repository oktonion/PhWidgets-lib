mkdir ./tests/bin

build_ok=1
exclude_warn=""
COMPILER=qcc
cversion=""

if [[ $COMPILER = *"clang"* ]]; then
  exclude_warn="-Wno-c++11-long-long -Wno-non-literal-null-conversion"
fi

if [ "$1" == "debug" ]
	then
	coption=-g
	print "	Warning: DEBUG compile configuration!"
elif [ "$1" == "c++" ]
	then
	cversion="-Vgcc_ntox86_gpp -lstdc++"
	print " Compiling with c++ option"
fi

if [ "$2" == "debug" ]
	then
	coption=-g
	print "	Warning: DEBUG compile configuration!"
elif [ "$2" == "c++" ]
	then
	cversion="-Vgcc_ntox86_gpp -lstdc++"
	print " Compiling with c++ option"
fi

for file in ./tests/*.cpp; do
  filename=$(basename -- "$file")
  filename="${filename%.*}"
  echo "compiling test c++03 $filename"
  if ! $COMPILER $cversion -pedantic $exclude_warn $file -I./slib/PhWidgets/include/ -L./slib/PhWidgets/ -lm -lAp -lph -lfont -lm -lang-c++ -lphwidgets -o "./tests/bin/$filename"; then
    build_ok=0
  fi
done

if [ $build_ok -eq 0 ]; then
  echo "tests build failed"
  exit 3 
fi