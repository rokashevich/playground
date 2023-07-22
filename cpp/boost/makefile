all: asio_http.exe

asio_http.exe: asio_http.cpp
	g++ asio_http.cpp -I /usr/local/Cellar/boost/1.54.0/include -std=c++11 -lboost_system -o asio_http.exe

clean:
	rm asio_http.exe
