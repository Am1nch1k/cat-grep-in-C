for file in `echo '1 2 3' | xargs`
do
	for flag in `echo '-i -v -c -l -n' | xargs`
	do
		alias test='./s21_grep $flag yuy ./testing/$file > /dev/null'
		leaks -q --atExit -- test 2>/dev/null &
		alias test='./s21_grep $flag y.y ./testing/$file > /dev/null'
		leaks -q --atExit -- test 2>/dev/null &
		alias test='./s21_grep $flag b.b ./testing/$file > /dev/null'
		leaks -q --atExit -- test 2>/dev/null &
		alias test='./s21_grep $flag catch ./testing/$file > /dev/null'
		leaks -q --atExit -- test 2>/dev/null &
		alias test='./s21_grep $flag me ./testing/$file > /dev/null'
		leaks -q --atExit -- test 2>/dev/null
	done
done

alias test='./s21_grep -h me ./testing/1 ./testing/2 ./testing/3'
leaks -q --atExit -- test 2>/dev/null &
alias test='./s21_grep -f ./testing/regex ./testing/1 ./testing/2'
leaks -q --atExit -- test 2>/dev/null &
alias test='./s21_grep -e y.y -e b.b ./testing/1 ./testing/2'
leaks -q --atExit -- test 2>/dev/null &
alias test='./s21_grep -iv y.y ./testing/1 ./testing/2 ./testing/3'
leaks -q --atExit -- test 2>/dev/null &
alias test='./s21_grep -on .E. ./testing/1 ./testing/2 ./testing/3'
leaks -q --atExit -- test 2>/dev/null &
alias test='./s21_grep -s y.y ./testing/1 ./testing/12 ./testing/13'
leaks -q --atExit -- test 2>/dev/null
alias test='./s21_grep -lc ... ./testing/1 ./testing/2 ./testing/3'
leaks -q --atExit -- test 2>/dev/null
alias test='./s21_grep -ich ME ./testing/1 ./testing/2 ./testing/3'
leaks -q --atExit -- test 2>/dev/null