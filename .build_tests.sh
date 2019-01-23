mkdir ./tests/bin

echo "\023331;0m"
echo "\023333;4m"

build_ok=1
exclude_warn=""
COMPILER=qcc

if [[ $COMPILER = *"clang"* ]]; then
  exclude_warn="-Wno-c++11-long-long -Wno-non-literal-null-conversion"
fi

if [ "$1" == "debug" ]
	then
	coption=-g
	print "	Warning: DEBUG compile configuration!"
fi

for file in ./tests/*.cpp; do
  filename=$(basename -- "$file")
  filename="${filename%.*}"
  echo "compiling test c++03 $filename"
  if ! $COMPILER -Vgcc_ntox86 -lang-c++ $coption -pedantic $exclude_warn $file -I./slib/PhWidgets/include/ -L./slib/PhWidgets/ -lAp -lph -lm -lphwidgets -o "./tests/bin/$filename"; then
    build_ok=0
  fi
done

if [ $build_ok -eq 0 ]; then
  echo "tests build failed"
  exit 3 
fi