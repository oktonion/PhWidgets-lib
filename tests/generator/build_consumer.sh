mkdir ./tests/bin

build_ok=1
exclude_warn=""
COMPILER=QCC
coption="-DNDEBUG -DBUILDENV_qss"
objfiles=""

if [[ $COMPILER = *"clang"* ]]; then
  exclude_warn="-Wno-c++11-long-long -Wno-non-literal-null-conversion"
fi

mkdir ./tests/generator/artifacts/obj/
cp ./slib/AbWidgetsWrap.cpp ./tests/generator/artifacts/AbWidgetsWrap.cpp

for file in ./tests/generator/artifacts/*.c*; do
  filename=$(basename -- "$file")
  filename="${filename%.*}"
  echo "compiling artifact c++03 $filename"
  if ! $COMPILER -Vgcc_ntox86 -lang-c++ $coption -pedantic $exclude_warn $file -I./slib/PhWidgets/include/ -I./ -I./tests/generator/testsuit/resources/test_app/src/ -L./slib/PhWidgets/ -lphexlib -lphwidgets -lAp -lph -lm -c -o "./tests/generator/artifacts/obj/$filename.o"; then
    build_ok=0
  else
    objfiles="$objfiles ./tests/generator/artifacts/obj/$filename.o"
  fi
done

rm ./tests/generator/artifacts/AbWidgetsWrap.cpp

file="./tests/generator/consumer.cxx"
filename=$(basename -- "$file")
filename="${filename%.*}"
echo "compiling obj c++03 $filename"
if ! $COMPILER -Vgcc_ntox86 -lang-c++ $coption -pedantic $exclude_warn $file -I./slib/PhWidgets/include/ -I./ -L./slib/PhWidgets/ -lphexlib -lphwidgets -lAp -lph -lm -c -o "./tests/generator/artifacts/obj/$filename.o" ; then
  build_ok=0
else
  echo "compiling test c++03 $filename"
  objfiles="$objfiles ./tests/generator/artifacts/obj/$filename.o"
  if ! $COMPILER -Vgcc_ntox86 -lang-c++ $coption -pedantic $exclude_warn -o "./tests/bin/$filename" $objfiles -I./slib/PhWidgets/include/ -I./ -L./slib/PhWidgets/ -lphexlib -lphwidgets -lAp -lph -lm ; then
    build_ok=0
  else
    phabbind ./tests/bin/$filename tests/generator/testsuit/resources/test_app/wgt/Dialog0.wgtd tests/generator/testsuit/resources/test_app/wgt/Picture0.wgtp tests/generator/testsuit/resources/test_app/wgt/TEST_WINDOW.wgtw
  fi
fi

if [ $build_ok -eq 0 ]; then
  echo "consumer test build failed"
  exit 3 
fi