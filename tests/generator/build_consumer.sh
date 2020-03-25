mkdir ./tests/bin

build_ok=1
exclude_warn=""
COMPILER=qcc

if [[ $COMPILER = *"clang"* ]]; then
  exclude_warn="-Wno-c++11-long-long -Wno-non-literal-null-conversion"
fi

file="./tests/generator/consumer.cxx"
filename=$(basename -- "$file")
filename="${filename%.*}"
echo "compiling test c++03 $filename"
if ! $COMPILER -Vgcc_ntox86 -lang-c++ $coption -pedantic $exclude_warn $file -I./slib/PhWidgets/include/ -I./ -L./slib/PhWidgets/ -lAp -lph -lm -lphexlib -lphwidgets -o "./tests/bin/$filename"; then
build_ok=0
fi

if [ $build_ok -eq 0 ]; then
  echo "tests build failed"
  exit 3 
fi