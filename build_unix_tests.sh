mkdir ./tests/bin

build_ok=1
exclude_warn=""
build_libs="-lrt"
testgroup=$1

if [[ $testgroup = "" ]]; then
	print "Error: test group is not specified!"
  exit 13
fi

$COMPILER -v

if [[ $COMPILER = *"clang"* ]]; then
  exclude_warn="-Wno-c++11-long-long -Wno-non-literal-null-conversion"
else
  exclude_warn="-Wno-long-long"
fi

case "$(uname -s)" in

   Darwin)
     echo 'Mac OS X'
     build_libs="-lpthread"
     ;;

   Linux)
     echo 'Linux'
     build_libs="-lrt -lpthread"
     ;;

   CYGWIN*|MINGW32*|MSYS*)
     echo 'MS Windows'
     exit 13
     ;;

   # Add here more strings to compare
   # See correspondence table at the bottom of this answer

   *)
     echo 'other OS' 
     exit 13
     ;;
esac

if [[ $COMPILER = *"g++-4."* ]]; then
  echo "c++03 option is not supported"
elif [[ $COMPILER = *"g++-3."* ]]; then
  echo "c++03 option is not supported"
else
  for file in ./tests/$testgroup/*.cpp; do
    filename=$(basename -- "$file")
    filename="${filename%.*}"
    foldername=$(dirname -- "$file")
    foldername=$(basename -- "$foldername")
    echo "$(date): compiling test c++03 $foldername:$filename"
    if ! $COMPILER -std=c++03 -pedantic $exclude_warn $file -I./src/ $build_libs -o "./tests/bin/$foldername:$filename"; then
      build_ok=0
    fi
  done
fi

if [ $build_ok -eq 0 ]; then
  echo "tests build failed"
  exit 3
fi

for file in ./tests/$testgroup/*.cpp; do
  filename=$(basename -- "$file")
  filename="${filename%.*}"
  foldername=$(dirname -- "$file")
  foldername=$(basename -- "$foldername")
  echo "$(date): compiling test c++98 $foldername:$filename"
  if ! $COMPILER -std=c++98 -pedantic $exclude_warn $file -I./src/ $build_libs -o "./tests/bin/$foldername:$filename"; then
    build_ok=0
  fi
done

if [ $build_ok -eq 0 ]; then
  echo "tests build failed for c++98"
  exit 98
fi