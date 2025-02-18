#!/bin/bash

echo -n > memory_test.log

cat public_testcases/example00.stdin | valgrind ./a.out >> memory_test.log 2>&1
cat public_testcases/example01.stdin | valgrind ./a.out >> memory_test.log 2>&1
cat public_testcases/example02.stdin | valgrind ./a.out >> memory_test.log 2>&1
cat public_testcases/example03.stdin | valgrind ./a.out >> memory_test.log 2>&1
cat public_testcases/example04.stdin | valgrind ./a.out >> memory_test.log 2>&1
cat public_testcases/example05.stdin | valgrind ./a.out >> memory_test.log 2>&1
cat public_testcases/example06.stdin | valgrind ./a.out >> memory_test.log 2>&1
cat public_testcases/example07.stdin | valgrind ./a.out >> memory_test.log 2>&1
cat public_testcases/example08.stdin | valgrind ./a.out >> memory_test.log 2>&1
cat public_testcases/example09.stdin | valgrind ./a.out >> memory_test.log 2>&1
#cat public_testcases/example10.stdin | valgrind ./a.out > out
#cat public_testcases/example11.stdin | valgrind ./a.out > out
#cat public_testcases/example12.stdin | valgrind ./a.out > out

cat more_testcases/example2001.stdin | valgrind ./a.out >> memory_test.log 2>&1
cat more_testcases/example2002.stdin | valgrind ./a.out >> memory_test.log 2>&1
cat more_testcases/example2003.stdin | valgrind ./a.out >> memory_test.log 2>&1
cat more_testcases/example2004.stdin | valgrind ./a.out >> memory_test.log 2>&1
cat more_testcases/example2005.stdin | valgrind ./a.out >> memory_test.log 2>&1

cat more_testcases/example5004.stdin | valgrind ./a.out >> memory_test.log 2>&1
cat more_testcases/example6004.stdin | valgrind ./a.out >> memory_test.log 2>&1
cat more_testcases/example7003.stdin | valgrind ./a.out >> memory_test.log 2>&1
cat more_testcases/example7004.stdin | valgrind ./a.out >> memory_test.log 2>&1
cat more_testcases/example7005.stdin | valgrind ./a.out >> memory_test.log 2>&1

grep "ERROR SUMMARY" memory_test.log
grep "total heap usage" memory_test.log
