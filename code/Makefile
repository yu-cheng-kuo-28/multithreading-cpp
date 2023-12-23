singleThreaded: singleThreaded.cpp
	g++ -o singleThreaded singleThreaded.cpp

multithreaded_01: multithreaded_01.cpp
	g++ -o multithreaded_01 multithreaded_01.cpp -pthread

multithreaded_02: multithreaded_02.cpp
	g++ -o multithreaded_02 multithreaded_02.cpp -pthread

multithreaded_03: multithreaded_03.cpp
	g++ -o multithreaded_03 multithreaded_03.cpp -pthread
		
multithreaded_10: multithreaded_10.cpp
	g++ -o multithreaded_10 multithreaded_10.cpp -pthread

fetchTimeMultithreaded_01: fetchTimeMultithreaded_01.cpp
	g++ -o fetchTimeMultithreaded_01 fetchTimeMultithreaded_01.cpp -pthread -lcurl

fetchTimeMultithreaded_02: fetchTimeMultithreaded_02.cpp
	g++ -o fetchTimeMultithreaded_02 fetchTimeMultithreaded_02.cpp -pthread -lcurl

fetchTimeMultithreaded_03: fetchTimeMultithreaded_03.cpp
	g++ -o fetchTimeMultithreaded_03 fetchTimeMultithreaded_03.cpp -pthread -lcurl

clean:
	rm -f singleThreaded multithreaded_01 multithreaded_02 multithreaded_03 ultithreaded_10 fetchTimeMultithreaded_01 fetchTimeMultithreaded_02 fetchTimeMultithreaded_03
