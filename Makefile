.DEFAULT_GOAL := test

test: perf_testO0 perf_testO3 perf_testO0ggdb perf_testO3ggdb
	./perf_testO0
	./perf_testO3
	./perf_testO0ggdb
	./perf_testO3ggdb

perf_testO3: perf_test.cpp
	g++ -O3 $< -o $@ -DFLAGS="-O3"

perf_testO0: perf_test.cpp
	g++ -O0 $< -o $@ -DFLAGS="-O0"

perf_testO3ggdb: perf_test.cpp
	g++ -ggdb -O3 $< -o $@ -DFLAGS="-O3 -ggdb"

perf_testO0ggdb: perf_test.cpp
	g++ -ggdb -O0 $< -o $@ -DFLAGS="-O0 -ggdb"

clean:
	rm -f perf_testO0 perf_testO3 perf_testO0ggdb perf_testO3ggdb

