# Benchmarker
Automatic easy-to-use cross-platform header-only single-run or repetitive benchmarking class in C++.

I built this class for fast and easy-to-use benchmarking of anything that we want to benchmark in C++.

It supports singular benchmarking processes, where a single process is to be benchmarked only once, as well as repetitive benchmarking processes where a process is going to be run many times in a for loop, in order to be benchmarked many times and get the statistical data of its benchmarking.

**NOTE** that this class does not run the loop for you. You have to run the for loop yourself, because there might be lots of things you might want to do inside the for loop. This class is only used for doing benchmarking, keeping track of it, calculating its statistics and reporting it.

Further improvement to this class can be made by reporting more details about its benchmarking, etc.

This class is only one header, `Benchmarking.h`

The `main.cpp` file inside the `Benchmarker` directory includes an example of using this class, for singular and also repetitive benchmarking.

If you have Visual Studio installed on your Windows, you can just go ahead and run the solution file `Benchmarker.sln`. Otherwise, on other platforms, you can build a C++ console app using the `main.cpp` and `Benchmarker.h` files inside the `Benchmarker` directory.

Note that the identifiers used in the member functions of this class are `SEC`, `MILLISEC`, `MICROSEC`, and `NANOSEC`.

Author: Pouya P. Niaz;  `pniaz20@ku.edu.tr`

LICENSE: MIT License, see LICENSE.md for more info
