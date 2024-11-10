for file in `echo '1 2' | xargs`
do
	for flag in `echo '-b --number-nonblank -e -n --number -s --squeeze-blank -t -v' | xargs`
	do
		# cat $flag $file > "./testing/$file.$flag.gnu"
		./s21_cat $flag ./testing/$file > "./testing/test/$file.$flag.s21"
		diff ./testing/test/$file.$flag.gnu ./testing/test/$file.$flag.s21
	done
	# cat -e -t $file > "./test/$file.-et.gnu"
	# cat -s -b $file > "./test/$file.-sb.gnu"
	# cat -b -n $file > "./test/$file.-bn.gnu"
	./s21_cat -e -t ./testing/$file > "./testing/test/$file.-et.s21"
	./s21_cat -s -b ./testing/$file > "./testing/test/$file.-sb.s21"
	./s21_cat -b -n ./testing/$file > "./testing/test/$file.-bn.s21"
	diff ./testing/test/$file.-et.gnu ./testing/test/$file.-et.s21
	diff ./testing/test/$file.-sb.gnu ./testing/test/$file.-sb.s21
	diff ./testing/test/$file.-bn.gnu ./testing/test/$file.-bn.s21
done

for flag in `echo '-b --number-nonblank -e -n --number -s --squeeze-blank -t -v' | xargs`
do
	# cat $flag 1 2 > "./test/12.$flag.gnu"
	./s21_cat $flag ./testing/1 ./testing/2 > "./testing/test/12.$flag.s21"
	diff ./testing/test/12.$flag.gnu ./testing/test/12.$flag.s21
done
