#!/bin/bash
cat public_testcases/example00.stdin | ./a.out | sort | diff <(sort public_testcases/example00.stdout) -
cat public_testcases/example01.stdin | ./a.out | sort | diff <(sort public_testcases/example01.stdout) -
cat public_testcases/example02.stdin | ./a.out | sort | diff <(sort public_testcases/example02.stdout) -
cat public_testcases/example03.stdin | ./a.out | sort | diff <(sort public_testcases/example03.stdout) -
cat public_testcases/example04.stdin | ./a.out | sort | diff <(sort public_testcases/example04.stdout) -
cat public_testcases/example05.stdin | ./a.out | sort | diff <(sort public_testcases/example05.stdout) -
cat public_testcases/example06.stdin | ./a.out | sort | diff <(sort public_testcases/example06.stdout) -
cat public_testcases/example07.stdin | ./a.out | sort | diff <(sort public_testcases/example07.stdout) -
cat public_testcases/example08.stdin | ./a.out | sort | diff <(sort public_testcases/example08.stdout) -
cat public_testcases/example09.stdin | ./a.out | sort | diff <(sort public_testcases/example09.stdout) -
cat public_testcases/example10.stdin | ./a.out | sort | diff <(sort public_testcases/example10.stdout) -
cat public_testcases/example11.stdin | ./a.out | sort | diff <(sort public_testcases/example11.stdout) -
cat public_testcases/example12.stdin | ./a.out | sort | diff <(sort public_testcases/example12.stdout) -

cat more_testcases/example2001.stdin | ./a.out | sort | diff <(sort more_testcases/example2001.stdout) -
cat more_testcases/example2002.stdin | ./a.out | sort | diff <(sort more_testcases/example2002.stdout) -
cat more_testcases/example2003.stdin | ./a.out | sort | diff <(sort more_testcases/example2003.stdout) -
cat more_testcases/example2004.stdin | ./a.out | sort | diff <(sort more_testcases/example2004.stdout) -
cat more_testcases/example2005.stdin | ./a.out | sort | diff <(sort more_testcases/example2005.stdout) -

cat more_testcases/example5004.stdin | ./a.out | sort | diff <(sort more_testcases/example5004.stdout) -
cat more_testcases/example6004.stdin | ./a.out | sort | diff <(sort more_testcases/example6004.stdout) -
cat more_testcases/example7003.stdin | ./a.out | sort | diff <(sort more_testcases/example7003.stdout) -
cat more_testcases/example7004.stdin | ./a.out | sort | diff <(sort more_testcases/example7004.stdout) -
cat more_testcases/example7005.stdin | ./a.out | sort | diff <(sort more_testcases/example7005.stdout) -

