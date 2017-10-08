for i in $(find ./ -name "lib*.a"); do
	
	linkpath="../../x86/o/$(basename $i)";
	rm "$linkpath";
	link "$i" "$linkpath";
	
	linkpath="../../x86/o-g/$(basename $i)";
	rm "$linkpath";
	link "$i" "$linkpath";
done
