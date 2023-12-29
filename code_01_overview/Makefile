1_singleThreaded: 1_singleThreaded.cpp
	g++ -o 1_singleThreaded 1_singleThreaded.cpp

2_multithreaded_01: 2_multithreaded_01.cpp
	g++ -o 2_multithreaded_01 2_multithreaded_01.cpp -pthread

3_multithreaded_02: 3_multithreaded_02.cpp
	g++ -o 3_multithreaded_02 3_multithreaded_02.cpp -pthread

4_multithreaded_03: 4_multithreaded_03.cpp
	g++ -o 4_multithreaded_03 4_multithreaded_03.cpp -pthread

5_fetchTimeMultithreaded_01: 5_fetchTimeMultithreaded_01.cpp
	g++ -o 5_fetchTimeMultithreaded_01 5_fetchTimeMultithreaded_01.cpp -pthread -lcurl

clean:
	rm -f 1_singleThreaded multithreaded_01 multithreaded_02 multithreaded_03  fetchTimeMultithreaded_01
