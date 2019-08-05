print " "
print "Making mkphgui"

binname=mkphgui
coption=-O3

print "> Compiling objects..."


g++ -Wall $coption -c ./src/config.cfg.c -o config
if [ "$1" == "debug" ]
	then
	coption=-g
	print "Warning: DEBUG compile configuration!"
fi

for i in $(find ./src/ -name "*.cpp"); do fname=$(basename $i); fname="${fname%.*}.o"; echo "Compile $fname"; g++ -Wall $coption -c $i -o $fname; done

print "> Making EXE-File..."

mkdir -p "old"
mv -f $binname "old/$binname"
g++ $coption -o $binname *.o config -L ./src/include/ -l Ap

print "> Deleting temporary objects..."

rm -r *.o

print "> Applying use msg..."

cp $binname ~$binname
~$binname -h > $binname.use
usemsg  $binname $binname.use

rm $binname.use
rm ~$binname

print "Done"
print " "
