all: proj4.x

proj4.x: proj4_driver.cpp
	g++ -std=c++11 -o proj4.x proj4_driver.cpp

run: proj4.x
	./proj4.x

clean:
	rm -f proj4.x
