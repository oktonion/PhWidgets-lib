mkdir ./tests/bin

echo "\023331;0m"
echo "\023333;4m"

build_ok=1
exclude_warn=""
COMPILER=QCC
testgroup="**"

if [[ $COMPILER = *"clang"* ]]; then
  exclude_warn="-Wno-c++11-long-long -Wno-non-literal-null-conversion"
fi

if [ "$1" == "debug" ]
	then
	coption=-g
	print "	Warning: DEBUG compile configuration!"
  testgroup=$2
elif [ "$1" == "clear" ]
  then
  rm -rf ./tests/bin
  exit
elif [ "$1" != "" ]
  then
  testgroup=$1
fi

for file in ./tests/$testgroup/*.cpp; do
  filename=$(basename -- "$file")
  filename="${filename%.*}"
  foldername=$(dirname -- "$file")
  foldername=$(basename -- "$foldername")
  echo "compiling test c++03 $foldername:$filename"
  if ! $COMPILER -Vgcc_ntox86 -lang-c++ $coption -pedantic $exclude_warn $file -I./slib/PhWidgets/include/ -I./ -L./slib/PhWidgets/ -lAp -lph -lm -lphexlib -lphwidgets -o "./tests/bin/$foldername:$filename"; then
    build_ok=0
  fi
done

if [ $build_ok -eq 0 ]; then
  echo "tests build failed"
  exit 3 
fi