# Benchmarker
Automatic easy-to-use header-only single-run or repetitive benchmarking class in C++

## Usage

I built this class for fast and easy-to-use benchmarking of anything that we want to benchmark in C++.

It supports singular benchmarking processes, where a single process is to be benchmarked only once, as well as repetitive benchmarking processes where a process is going to be run many times in a for loop, in order to be benchmarked many times and get the statistical data of its benchmarking.

NOTE that this class does not run the loop for you. You have to run the for loop yourself, because there might be lots of things you might want to do inside the for loop. This class is only used for doing benchmarking, keeping track of it, calculating its statistics and reporting it.

Further improvement to this class can be made by reporting more details about its benchmarking, etc.

This class is only one header, `Benchmarking.h`. There is no cpp file to run whatsoever.

The `Benchmarking.cpp` file inside the solution folder includes an example of using this class, for singular and also repetitive benchmarking.

### Singular benchmarking Example

```c++
#include "Benchmarker.h"
#include <Windows.h>

using namespace std;

// some function
void Foo() {
    Sleep(1);
}

int main()
{
    Benchmarker bench1;
    bench1.begin();
    Foo();
    bench1.terminate();
	// one way of reporting it:
    cout.precision(20);
    cout << "Single benchmarking suration was: " << fixed << bench1.getSingleDur(MICROSEC) << endl;
    // another way of reporting it:
    bench1.report();
    
    return 0;
}
```

Output:

```
Benchmarker constructed by default with number of repetitions of 1.
Single benchmarking suration was: 14602.69999999999890860636

-----------------------------------------------------------------------------------
Benchmarking finished with 1 trials.
Results are (in seconds ):
Minimum:    0.01460269999999999971
Average:    0.01460269999999999971
Maximum:    0.01460269999999999971

This entire bechmarking process took  0.01460269999999999971 seconds.
-----------------------------------------------------------------------------------
```

Note that the identifiers used in the value-returning member functions of this class are `SEC`,`MILLISEC`,`MICROSEC`, and `NANOSEC`.

### Repetitive benchmarking example

```c++
#include "Benchmarker.h"
#include <Windows.h>

using namespace std;

// some function
void Foo() {
    Sleep(1);
}

int main()
{
    // Defining number of repetitions for the benchmarking
    unsigned numRepetitions = 1000;

    Benchmarker bench2(numRepetitions);
    bench2.begin();
    for (unsigned i = 0;i < numRepetitions;i++) {

        // some code
        
        // Benchmarking ---------------------
        bench2.tic();
        Foo();
        bench2.toc();
        // ----------------------------------

        // some other code
    }
    bench2.terminate();

    cout << endl << "Running getDurations() ...\n";
    vector<double> results = bench2.getDurations(MICROSEC);

    cout << "Acquired variables are:\n";
    cout << "Min: " << fixed << results[0] << endl;
    cout << "Avg: " << fixed << results[1] << endl;
    cout << "Max: " << fixed << results[2] << endl;
    cout << "Tot: " << fixed << results[3] << endl;

    cout << endl << "Running report() ...\n";
    bench2.report(MICROSEC);

    cout << endl << "Running print() ...\n";
    bench2.print();
	
    return 0;
}
```

Output:

```
Benchmarker constructed with number of repetitions of 1000 .

Running getDurations() ...
Acquired variables are:
Min: 3827.19999999999981810106
Avg: 15482.96300000000519503374
Max: 16351.89999999999963620212
Tot: 15485417.90000000037252902985

Running report() ...

-----------------------------------------------------------------------------------
Benchmarking finished with 1000 trials.
Results are (in microseconds ):
Minimum:    3827.19999999999981810106
Average:    15482.96300000000519503374
Maximum:    16351.89999999999963620212

This entire bechmarking process took  15.48541789999999984673 seconds.
-----------------------------------------------------------------------------------

Running print() ...

Variables of Benchmarker object are:
    numRepetitions =   1000
    durt =             15.48541789999999984673
    avgt =             0.01548296300000000583
    mint =             0.00382719999999999979
    maxt =             0.01635189999999999907
    tempDurSec =       0.01601910000000000139
    isActive =         0
    isSingle =         0
    isTic =            0
    isToc =            1
```

(C) Copyright Pouya Pourakbarian Niaz

LICENSE: MIT License, see LICENSE.md for more info
