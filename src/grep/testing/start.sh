for file in `echo '1 2 3' | xargs`
do
	for flag in `echo '-i -v -c -l -n' | xargs`
	do
		grep $flag yuy ./testing/$file > ./testing/test/yuy.$flag.$file.gnu
		./s21_grep $flag yuy ./testing/$file > ./testing/test/yuy.$flag.$file.s21
		grep $flag y.y ./testing/$file > ./testing/test/y.y.$flag.$file.gnu
		./s21_grep $flag y.y ./testing/$file > ./testing/test/y.y.$flag.$file.s21
		grep $flag b.b ./testing/$file > ./testing/test/b.b.$flag.$file.gnu
		./s21_grep $flag b.b ./testing/$file > ./testing/test/b.b.$flag.$file.s21
		grep $flag catch ./testing/$file > ./testing/test/catch.$flag.$file.gnu
		./s21_grep $flag catch ./testing/$file > ./testing/test/catch.$flag.$file.s21
		grep $flag me ./testing/$file > ./testing/test/me.$flag.$file.gnu
		./s21_grep $flag me ./testing/$file > ./testing/test/me.$flag.$file.s21
	done
done
grep -h me ./testing/1 ./testing/2 ./testing/3 > ./testing/test/h.123.gnu
grep -f ./testing/regex ./testing/1 ./testing/2 > ./testing/test/f.12.gnu
grep -e y.y -e b.b ./testing/1 ./testing/2 > ./testing/test/f.12.gnu
grep -iv y.y ./testing/1 ./testing/2 ./testing/3 > ./testing/test/iv.gnu
grep -on .E. ./testing/1 ./testing/2 ./testing/3 > ./testing/test/on.gnu
grep -s y.y ./testing/1 ./testing/12 ./testing/13 > ./testing/test/iv.gnu
grep -lc ... ./testing/1 ./testing/2 ./testing/3 > ./testing/test/lc.gnu
grep -ich ME ./testing/1 ./testing/2 ./testing/3 > ./testing/test/ich.gnu

./s21_grep -h me ./testing/1 ./testing/2 ./testing/3 > ./testing/test/h.123.s21
./s21_grep -f ./testing/regex ./testing/1 ./testing/2 > ./testing/test/f.12.s21
./s21_grep -e y.y -e b.b ./testing/1 ./testing/2 > ./testing/test/f.12.s21
./s21_grep -iv y.y ./testing/1 ./testing/2 ./testing/3 > ./testing/test/iv.s21
./s21_grep -on .E. ./testing/1 ./testing/2 ./testing/3 > ./testing/test/on.s21
./s21_grep -s y.y ./testing/1 ./testing/12 ./testing/13 > ./testing/test/iv.s21
./s21_grep -lc ... ./testing/1 ./testing/2 ./testing/3 > ./testing/test/lc.s21
./s21_grep -ich ME ./testing/1 ./testing/2 ./testing/3 > ./testing/test/ich.s21

for file in `echo '1 2 3' | xargs`
do
	for flag in `echo '-i -v -c -l -n' | xargs`
	do
		diff ./testing/test/yuy.$flag.$file.gnu ./testing/test/yuy.$flag.$file.s21 -qs | grep "differ"
		diff ./testing/test/y.y.$flag.$file.gnu ./testing/test/y.y.$flag.$file.s21 -qs | grep "differ"
		diff ./testing/test/b.b.$flag.$file.gnu ./testing/test/b.b.$flag.$file.s21 -qs | grep "differ"
		diff ./testing/test/catch.$flag.$file.gnu ./testing/test/catch.$flag.$file.s21 -qs | grep "differ"
		diff ./testing/test/me.$flag.$file.gnu ./testing/test/me.$flag.$file.s21 -qs | grep "differ"
	done
done

diff ./testing/test/h.123.gnu testing/test/h.123.s21 -qs | grep "differ"
diff ./testing/test/f.12.gnu testing/test/f.12.s21 -qs | grep "differ"
diff ./testing/test/f.12.gnu testing/test/f.12.s21 -qs | grep "differ"
diff ./testing/test/iv.gnu ./testing/test/iv.s21 -qs | grep "differ"
diff ./testing/test/on.gnu ./testing/test/on.s21 -qs | grep "differ"
diff ./testing/test/iv.gnu ./testing/test/iv.s21 -qs | grep "differ"
diff ./testing/test/lc.gnu ./testing/test/lc.s21 -qs | grep "differ"
diff ./testing/test/ich.gnu ./testing/test/ich.s21 -qs | grep "differ"
exit 0