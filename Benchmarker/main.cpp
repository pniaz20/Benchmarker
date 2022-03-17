#include "Benchmarker.h"
#include <stdio.h>
#include <chrono>
#include <thread>

using namespace std;


// some random function. This is the process that is going to be benchmarked.
void Foo() {
    static unsigned long count = 1;
    static size_t numDigits = 1;
    static const size_t textSize = 21;
    static size_t lineSize = 21;
    this_thread::sleep_for(chrono::milliseconds(10));
    printf_s("We are counting at : %d", count);
    numDigits = floorl(log10l((long double)count)) + 1;
    lineSize = numDigits + textSize;
    for (size_t i = 0; i < lineSize; i++) {
        printf_s("\b");
    }
    count++;
}


int main()
{
    cout << "Hello World!\n";
    
    
    /*************************************
    * Performing a singular benchmarking without repetition
    **************************************/
    
    Benchmarker bench1;
    bench1.begin();
    Foo();
    bench1.terminate();
    cout << endl;

    cout.precision(20);
    cout << "Single benchmarking suration was (in microseconds): " << fixed << bench1.getSingleDur(MICROSEC) << endl;

    bench1.report();

    /*************************************
    * Performing a repetitive benchmarking with a high number of repetitions
    **************************************/
    
    cout << endl << "Press Enter to commence benchmarking ...\n";
    cin.get();

    // Defining number of repetitions for the benchmarking
    unsigned numRepetitions = 1000;

    // This is how you write a loop for a repetitive process that is to be benchmarked
    Benchmarker bench2(numRepetitions);
    bench2.begin(); // Run this immediately before the loop in which the benchmarked function will be run many times.
    for (unsigned i = 0;i < numRepetitions;i++) {

        // some code
        
        // Benchmarking ---------------------
        bench2.tic();
        Foo();
        bench2.toc();
        // ----------------------------------

        // some other code
    }
    bench2.terminate(); // Run this immediately after the loop in which the benchmarked function will has been run many tikmes.


    cout << endl;
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

}

