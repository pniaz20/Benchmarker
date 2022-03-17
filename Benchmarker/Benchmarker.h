/**
* Copyright (c) 2022 Pouya P. Niaz
* https://github.com/pniaz20/Benchmarker
* This github repository is shared under the MIT license.
*/

#pragma once

#include <iostream>
#include <iomanip>
#include <vector>
#include <chrono>

using namespace std;

#define SEC 0
#define MILLISEC 1
#define MICROSEC 2
#define NANOSEC 3


class Benchmarker {
public:
	/**
	Default constructor for Benchmarker class. It by default implies a singular benchmarking process, without looped repetition.
	*/
	Benchmarker() :
		start(std::chrono::system_clock::now()),
		stop(std::chrono::system_clock::now()),
		startTotal(std::chrono::system_clock::now()),
		stopTotal(std::chrono::system_clock::now()),
		dur(0),
		durt(0.0),
		avgt(0.0),
		mint(100000.0),
		maxt(0.0),
		numRepetitions(1),
		isActive(false),
		isSingle(true),
		isTic(false),
		isToc(true),
		tempDurSec(0.0) {
		cout << "Benchmarker constructed by default with number of repetitions of 1.\n";
	};


	/**
	* Constructor for Benchmarking class. The input is number of repetitions of the loop for benchmarking.
	* Note that this class does not automatically run a for loop, you have to do it yourself.
	* Also note that this class does not undersand whether or not your for loop will also run the same number of times as the specified count.
	* @param unsigned long numrept: number of repetitions you will employ in the for loop.
	*/
	Benchmarker(unsigned long numrepts) :
		start(std::chrono::system_clock::now()),
		stop(std::chrono::system_clock::now()),
		startTotal(std::chrono::system_clock::now()),
		stopTotal(std::chrono::system_clock::now()),
		dur(0),
		durt(0.0),
		avgt(0.0),
		mint(100000.0),
		maxt(0.0),
		numRepetitions(numrepts),
		isActive(false),
		isSingle(false),
		isTic(false),
		isToc(true),
		tempDurSec(0.0)
	{
		std::cout << "Benchmarker constructed with number of repetitions of " << numRepetitions << " ." << endl;
	};



	/**
	Starts the benchmarking clock for the current benchmarking instance, within the loop.
	Note that if the number of repetitions is more than 1 (singular benchmarking) then
	begin() must be called immediately before the for loop, in order to initiate the benchmarking process.
	Similar to the tic function of matlab.
	*/
	void tic() {
		if (isTic) {
			cout << "ERROR in tic(): it has already been called before.\n";
			exit(0);
		}
		if (!isToc) {
			cout << "ERROR in tic(): toc() has not been called yet.\n";
			exit(0);
		}
		if (!isSingle && !isActive) {
			cout << "ERROR in tic(): begin() has not been called yet. It must be called immediately before the loop.\n";
			exit(0);
		}
		isTic = true;
		isToc = false;
		start = std::chrono::system_clock::now();
	};



	/**
	Stops the benchmarking clock for the current benchmarking instance, within the for loop.
	Note that tic() must be called before this function, inside the for loop of repetitions.
	Also note that this function does not terminate benchmarking, it simply stamps the time passed since tic() for the current loop.
	*/
	void toc() {
		if (!isTic) {
			cout << "ERROR in toc(): tic() has not been called yet.\n";
			exit(0);
		}
		if (!isSingle && !isActive) {
			cout << "ERROR in toc(): terminate() has already been called, or begin() has not yet been called.\n";
			exit(0);
		}
		isToc = true;
		isTic = false;
		stop = std::chrono::system_clock::now();
		dur = stop - start;
		tempDurSec = dur.count();
		avgt += tempDurSec;
		if (tempDurSec < mint)
			mint = tempDurSec;
		if (maxt < tempDurSec)
			maxt = tempDurSec;
	};



	/**
	Initiates the benchmarking process. This method must be called immediately before the for loop that runs the repetitions.
	For singular benchmarking processes (number of repetitions = 1), this function is the same as tic().
	*/
	void begin() {
		if (isActive) {
			cout << "ERROR in begin(): it has already been called.\n";
			exit(0);
		}
		if (isTic) {
			cout << "ERROR in begin(): tic() has already been called.\n";
			exit(0);
		}
		isActive = true;
		isTic = false;
		isToc = true;
		if (isSingle) {
			tic();
			startTotal = start;
		}
		else {
			startTotal = std::chrono::system_clock::now();
		}
	};



	/**
	Terminates the benchmarking process. This method must be called immediately after the for loop that runs the repetitions.
	For singular benchmarking processes (number of repetitions = 1), this function is the same as toc().
	*/
	void terminate() {
		if (!isActive) {
			cout << "ERROR in terminate(): it has already been called, or begin() has not been called.\n";
			exit(0);
		}
		if (isSingle) {
			toc();
			stopTotal = stop;
			durt = tempDurSec;
		}
		else {
			stopTotal = std::chrono::system_clock::now();
			avgt = avgt / numRepetitions;
			dur = stopTotal - startTotal;
			durt = dur.count();
		}
		isToc = true;
		isActive = false;
		isTic = false;
	};




	/**
	* Get the duration of the singular benchmarking process, after it is complete.
	* Note that this function does not work for repetitive benchmarking processes (number of repetitions > 1).
	* @param unit of measurement: SEC, MILLISEC, MICROSEC, NANOSEC. Default is SEC.
	* @return duration, in the spcified units
	*/
	double getSingleDur(int ident = SEC) {
		if (isActive) {
			cout << "ERROR in getSingleDur(): terminate() or toc() has not been called yet.\n";
			exit(0);
		}
		return durt * coeff[ident];
	};




	/**
	* Get the durations of the repetitive benchmarking process, after it is complete.
	* the output will have the format {minimum, average, maximum, total} where min, avg and max are for whatever was being benchmarked
	* between tic() and toc() in the for loop, and total is the entire duration of the for loop itself, i.e. the whole duration of the
	* benchmarking process.
	* Note that this function must only be called after terminate() has been called and benchmarking has finished.
	* @param unit of measurement: SEC, MILLISEC, MICROSEC, NANOSEC. Default is SEC.
	* @return vector<double>(4) durations, in the format {min, avg, max, total}.
	*/
	vector<double> getDurations(int ident = SEC) {
		if (isActive) {
			cout << "ERROR in getDurations(): terminate() or toc() has not been called yet.\n";
			exit(0);
		}
		if (isSingle) {
			cout << "ERROR in getDurations(): function not supported when there is only one repetition (singular benchmarking).\n";
			exit(0);
		}
		vector<double> durs;
		durs.push_back(mint * coeff[ident]);
		durs.push_back(avgt * coeff[ident]);
		durs.push_back(maxt * coeff[ident]);
		durs.push_back(durt * coeff[ident]);
		return durs;
	};



	/**
	Pretty-prints all the attributes of the Benchmarking class instance object.
	*/
	void print() {
		cout.precision(20);
		cout << endl;
		cout << "Variables of Benchmarker object are:" << endl;
		cout << "    numRepetitions =   " << numRepetitions << endl;
		cout << "    durt =             " << fixed << durt << endl;
		cout << "    avgt =             " << fixed << avgt << endl;
		cout << "    mint =             " << fixed << mint << endl;
		cout << "    maxt =             " << fixed << maxt << endl;
		cout << "    tempDurSec =       " << fixed << tempDurSec << endl;
		cout << "    isActive =         " << isActive << endl;
		cout << "    isSingle =         " << isSingle << endl;
		cout << "    isTic =            " << isTic << endl;
		cout << "    isToc =            " << isToc << endl;
	};



	/**
	* Reports the results of benchmarking after they are finishd, in a pretty way.
	* @param unit of measurement: SEC, MILLISEC, MICROSEC, NANOSEC. Default is SEC.
	*/
	void report(int ident = SEC) {
		cout.precision(20);
		cout << endl;
		cout << "-----------------------------------------------------------------------------------" << endl;
		cout << "Benchmarking finished with " << numRepetitions << " trials.\n";
		cout << "Results are (in " << coeffStr[ident] << " ):\n";
		cout << "Minimum:    " << fixed << mint * coeff[ident] << endl;
		cout << "Average:    " << fixed << avgt * coeff[ident] << endl;
		cout << "Maximum:    " << fixed << maxt * coeff[ident] << endl;
		cout << endl;
		cout << "This entire bechmarking process took  " << fixed << durt << " seconds." << endl;
		cout << "-----------------------------------------------------------------------------------" << endl;
	};



	/**
	* Sets the number of repetitions after they are done. Useful when numbr of repetitions is not known apriori.
	* Note that this function should be called directly before terminate(). Otherwise it makes no sense.
	* @param unsigned long numrept: Number of repetitions
	*/
	void setNumRepetitions(unsigned long numrept) {
		numRepetitions = numrept;
	};

private:

	unsigned long numRepetitions;

	const long double thousand = 1000.0;
	const long double million = 1000.0 * 1000.0;
	const long double billion = 1000.0 * 1000.0 * 1000.0;
	const long double coeff[4] = { 1.0, thousand, million, billion };
	const char* coeffStr[4] = { "seconds","milliseconds","microseconds","nanoseconds" };

	std::chrono::system_clock::time_point start;
	std::chrono::system_clock::time_point stop;
	std::chrono::system_clock::time_point startTotal;
	std::chrono::system_clock::time_point stopTotal;
	std::chrono::duration<double> dur;

	double durt;
	double avgt;
	double mint;
	double maxt;

	double tempDurSec;

	bool isActive;
	bool isSingle;
	bool isTic;
	bool isToc;

};
