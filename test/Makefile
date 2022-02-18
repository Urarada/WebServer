test_valgrind.log: ./tThreads
	valgrind --leak-check=full --log-file=test_valgrind.log --num-callers=30 -s ./tThreads
tThreads: ./testThreads.cpp ../threads/threads.cpp
	g++ -pthread -g -o tThreads ./testThreads.cpp ../threads/threads.cpp
clean:
	rm test_valgrind.log tThreads
# -O0