mkdir ./tests/bin

build_ok=1
exclude_warn=""
COMPILER=QCC

if [[ $COMPILER = *"clang"* ]]; then
  exclude_warn="-Wno-c++11-long-long -Wno-non-literal-null-conversion"
fi

mkdir ./tests/generator/artifacts/obj/
cp ./slib/AbWidgetsWrap.cpp ./tests/generator/artifacts/AbWidgetsWrap.cpp

for file in ./tests/generator/artifacts/*.c*; do
  filename=$(basename -- "$file")
  filename="${filename%.*}"
  echo "compiling artifact c++03 $filename"
  if ! $COMPILER -Vgcc_ntox86 -lang-c++ $coption -pedantic $exclude_warn $file -I./slib/PhWidgets/include/ -I./ -I./tests/generator/testsuit/resources/test_app/src/ -L./slib/PhWidgets/ -lAp -lph -lm -lphexlib -lphwidgets -c -o "./tests/generator/artifacts/obj/$filename.o"; then
    build_ok=0
  fi
done

rm ./tests/generator/artifacts/AbWidgetsWrap.cpp

if [ $build_ok -eq 0 ]; then
  echo "artifacts lib build failed"
  exit 4
fi

cd ./tests/generator/artifacts/obj/

if ar rsc "./libartifacts.a" *.o; then
  echo "artifacts library packed"
  cd ./../../../../
  if ranlib "./tests/generator/artifacts/obj/libartifacts.a"; then
    echo "artifacts library done"
  else
    echo "artifacts lib build failed"
    exit 5
  fi
else
  echo "artifacts lib archive failed"
  exit 5
fi

file="./tests/generator/consumer.cxx"
filename=$(basename -- "$file")
filename="${filename%.*}"
echo "compiling test c++03 $filename"
if ! $COMPILER -Vgcc_ntox86 -lang-c++ $coption -pedantic $exclude_warn $file -I./slib/PhWidgets/include/ -I./ -L./tests/generator/artifacts/obj/ -L./slib/PhWidgets/  -lAp -lph -lm -lphexlib -lphwidgets -lartifacts -o "./tests/bin/$filename"; then
  build_ok=0
else
  phabbind ./tests/bin/$filename tests/generator/testsuit/resources/test_app/wgt/Dialog0.wgtd tests/generator/testsuit/resources/test_app/wgt/Picture0.wgtp tests/generator/testsuit/resources/test_app/wgt/TEST_WINDOW.wgtw
fi

if [ $build_ok -eq 0 ]; then
  echo "consumer test build failed"
  exit 3 
fi