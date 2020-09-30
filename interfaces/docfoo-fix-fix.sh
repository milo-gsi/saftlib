for i in Types.texi docfoo-fix.*.texi
do
	sed -i '/^@node Top/d' $i
done