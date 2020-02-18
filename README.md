# Fibonacci Client-Server

A simple client-server application using Flask (python) as server and Qt as client. Also it calculate the elements using dynamic programming.

**Client**
- Implemented with Qt (*C++*)
- Very simple UI without style-sheets
	- [Main Window HeaderFile](https://github.com/HadiFazelinia/SC-FlaskQt/blob/master/FibonacciClient/win_main.h)
	- [Main Window CodeFile](https://github.com/HadiFazelinia/SC-FlaskQt/blob/master/FibonacciClient/win_main.cpp)

**Server**
- Implemented with Flask framework (*Python*)
- Calculate the element in `O(log n)` using power of a specific matrix
	- [Server CodeFile](https://github.com/HadiFazelinia/SC-FlaskQt/blob/master/server.py)

