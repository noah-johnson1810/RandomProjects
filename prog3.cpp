/**************************************************************************//**
 * @file
 * @brief Accept or Reject the Lot
 *
 * @mainpage Program 3 - Accept or Reject the Lot
 *
 * @section course_section Course Section
 *
 * @authors Noah Johnson
 *
 * @date November 22, 2020
 *
 * @par Instructor:
 *         Daniel de Castro
 *
 * @par Course:
 *         CSC 150 - Section MT2 - 3:00-5:00 PM
 *
 * @par Location:
 *         Zoom
 *
 * @section program_section Program Information
 *
 * @details This program analyzes an input file for five attributes - Incoming
 * voltage, current, antenna gain, MT24, and MT5. The input files can have up 
 * to 100 rows. If the standard deviation of the IV attribute is greater than 
 * the max voltage variation, the median of the current is greater than the max
 * current median, the A standard deviation is greater than the max gain 
 * variation, or the percentage of 0's in MT24 or MT5 exceeds the max 
 * percentage, then the lot will be rejected. The program also creates and 
 * output file which contains the lot ID, the statistics for each attribute, 
 * whether each attribute passes the tests, and whether the let should be 
 * accepted or rejected. 
 * 
 *
 * @section compile_section Compiling and Usage
 *
 * @par Compiling Instructions:
 *      None
 *
 * @par Usage:
 * @verbatim
 * c:\> prog3.exe
 * d:\> c:\bin\prog3.exe
 * @endverbatim
 *
 * @section todo_bugs_modification_section Todo, Bugs, and Modifications
 *
 * @par Modifications and Development Timeline:
 * @verbatim
 * https://gitlab.mcs.sdsmt.edu/7507264/csc150f20programs
 * @endverbatim
 *****************************************************************************/

// include & using statements
#include <iostream>
#include <fstream>
#include <cmath>
#include <iomanip>
#include <cstdlib>
#include <cstring>
using namespace std;

// constant declarations
const double MAX_VOLTAGE_VARIATION = 0.2; 
const double MAX_CURRENT_MEDIAN = 3.6; 
const double MAX_GAIN_VARIATION = 1.5; 
const double MAX_PERCENTAGE = 1.0; // 1%

// required functions
int read_measurements ( double data[ ][5], int& lot_id, char filename[ ],
	ifstream &fin, ofstream &fout );
double calc_A_stdev ( double data[ ][5], int length );
double calc_G_stdev ( double data[ ][5], int length );
double calc_median ( double data[ ][5], int length );
double calc_percentage ( double data[ ][5], int length, int column );
bool calc_pass_fail ( double output_stats[ ], double data[ ][5],
	int pass_array[ ], int length );
void create_report ( char filename[ ], double output_stats[ ], bool pass,
	int pass_array[ ], int lot_id, ofstream &fout );
void swap ( double &a, double &b );


/** ***************************************************************************
 * @author N. Johnson
 *
 * @par Description: this function begins by setting the output precision to 4. 
 * Then, it gets the input file name from the command line. Next, it checks the
 * number of arguments used to call the program. If there are an incorrect 
 * number of arguments, the program will stop. Next, it calls each function 
 * to get and analyze data from the input file. Then it calls create_report 
 * to create the output file. Finally, it closes all open files. 
 *
 * @param[in] argc - number of argments 
 * @param[in, out] argv - input file name
 *
 * @returns 0 - successful program execution
 & @returns -1 - failed file opening
 *****************************************************************************/

int main ( int argc, char* argv[ ] )
{
	
	double input_data[101][5]; // two-dimensional array to hold the input data
	double output_stats[5]; // one-dimensional array holding results to output
	int pass_array[5]; // holds the pass/fail for each test
	int length = 0;	// number of items being tested
	bool result; // whether the data passes or not 
	// name of the file. "report_" will be prepended on the output file name
	char inputname[100] = ""; // holds the file input name
	int lot_id; // holds the lot id number
	ifstream fin; // input file stream
	ofstream fout; // output file stream

	// set file output precision to 4
	fout << fixed << showpoint << setprecision ( 4 );

	// get input file name from the command line
	strncpy_s ( inputname, argv[1], 80 );

	if ( argc != 2 ) // check number of arguments
	{
		cout << endl << "Usage: prog3.exe <input file name>" << endl;
		return 1; // program fail
	}
    // get info from input file
	length = read_measurements( input_data, lot_id, inputname, fin, fout );
	// if opening the file failed, end the program
	if ( length == -1 )
	{
		return -1;
	}
	// call calc_A_stdev and assign return value to output_stats[0]
	output_stats[0] = calc_A_stdev ( input_data, length );
	// call calc_median and assign return value to output_stats[1]
	output_stats[1] = calc_median ( input_data, length );
	// call calc_G_stdev and assign return value to output_stats[2]
	output_stats[2] = calc_G_stdev ( input_data, length );
	// call calc_percentage for column 3 and return value to output_stats[3]
	output_stats[3] = calc_percentage ( input_data, length, 3 );
	// call calc_percentage for column 4 and return value to output_stats[4]
	output_stats[4] = calc_percentage ( input_data, length, 4 );
	// call calc_pass_fail and return value to result
	result = calc_pass_fail ( output_stats, input_data, pass_array, length );
	// call create_report to create output file
	create_report ( inputname, output_stats, result, pass_array, lot_id, 
		fout );
	// close all files before ending program
	fin.close ( );
	fout.close ( );

	return 0; // 0 indicates successful program execution
}


/** ***************************************************************************
 * @author N. Johnson
 *
 * @par Description: this function reads the measurements of the input file. 
 * First, it opens the file and checks to confirm that it is open. If it does
 * not open correctly, it will output a message to indicate that. It then reads
 * in the lot ID, and fills the array "data" with the measurements from the 
 * file. It also records and returns the length (the number of rows in the 
 * file). 
 * 
 * @param[in, out] data - array holding the input file information
 * @param[in, out] lot_id - int holding the lot ID
 * @param[in, out] filename - char array containing the file name
 * @param[in, out] fin - ifstream for opening the input file
 * @param[in, out] fout - ofstream for outputting data
 *
 * @returns length - the number of rows in the file
 *****************************************************************************/

int read_measurements ( double data[ ][5], int& lot_id, char filename[ ], 
	ifstream &fin, ofstream &fout )
{
	int i = 0; // used in while loop
	int length = 0; // number of rows in the array

	fin.open ( filename ); // open the file
	if ( !fin )  // check if the file is open
	{
		cout << "Could not open file " << filename << "." << endl;
		return -1; // fail
	}
	// read in header information from input file (lot number)
	fin >> lot_id;
	// read and return the measurements from the input file 
	while ( i < 100 && !fin.eof() ) 
	{
		for ( int j = 0; j < 5; j++ )
		{
			fin >> data[i][j]; // read info into data[ ][ ]
		}
		i++;
	}
	if ( i == 100 ) // if the loop runs 100 times, the length is 100
	{
		length = 100;
	}
	else
	{
		length = i - 1; // otherwise, the length is i minus the final increment
	}

	return length; // return the length
}


/** ***************************************************************************
 * @author N. Johnson
 *
 * @par Description: This function calculates the arithmetic standard deviation
 * over a specified column of an array. It finds the total of all the numbers
 * in the column, then divides that by the length to find the average. Then,
 * it sums each data point minus the mean value, raised to the power of 2. 
 * Finally, it divides that result by the length and takes the square root,
 * returning the arithmetic standard deviation to be used over the IV column
 * of the data array. 
 *
 * @param[in, out] data - array holding the input file information
 * @param[in] length - number of rows in the array
 *
 * @returns a_stdev - arithmetic standard deviation of the column
 *****************************************************************************/

double calc_A_stdev ( double data[ ] [5], int length )
{
	double a_stdev = 0; // holds arithmetic standard deviation
	double total = 0; // holds the sum of all values in the column
	double average; // holds the average of all values in the column
	double sum = 0; // holds the sum in the third step

	// first, find the mean of the data
	// calculate the total of all the rows
	for ( int i = 0; i < length; i++ )
	{
		total += data[i][0];
	}

	// the average is the total divided by the length
	average = total / length;

	// sum each data point minus the mean value, raised to the power of 2
	for ( int i = 0; i < length; i++ )
	{
		sum += pow ( ( data[i][0] - average ), 2.0 );
	}

	// take that result, divide by the length, and take the square root
	a_stdev = pow ( ( (double) sum / length ), ( 1.0 / 2 ) );


	return a_stdev; // return the arithmetic standard deviation
}


/** ***************************************************************************
 * @author N. Johnson
 *
 * @par Description: this function calculates the geometric standard deviation
 * over a specified column of an array. First, it finds the value of
 * all the values in the column multiplied together. Then, it calculates the 
 * geometric mean by taking the multiplied values to root of 1 / length. Then, 
 * for each data point, it divides by the mean, takes the log base 10 of that 
 * result, and squares it. It add all the results, divides by n, takes the 
 * square root, and calculates 10 to the result’s power. This is the geometric
 * standard deviation, which the function returns.
 *
 * @param[in, out] data - array holding the input file information
 * @param[in] length - the number of rows in the array
 *
 * @returns g_stdev - the geometric standard deviation of the column
 *****************************************************************************/

double calc_G_stdev ( double data[ ][5], int length )
{
	double g_stdev; // holds the geometric standard deviation
	double g_mean; // holds the geometric mean
	double added_results = 0; // holds the added results in step 3
	double multiplied_values = data[0][2]; // holds the multiplied values
	double exponent; // the power to raise 10 to at the end
	// first, multiply all the values together
	for ( int i = 1; i < length; i++ )
	{
		multiplied_values *= data[i][2];
	}
	// the geometric mean is the multiplied values to the 1/length root
	g_mean = pow ( multiplied_values, ( 1.0 / length ) );
	/* for each data point, divide by the mean, take the log base 10 of that
	result, and squares it */
	for ( int i = 0; i < length; i++ )
	{
		added_results += pow ( ( log10 ( data[i][2] / g_mean ) ), 2 );
	}
	// assign "exponent" the value of the square root of added_results / length
	exponent = pow ( ( added_results / length ), 1.0 / 2 );
	// raise 10 to the power of exponent
	g_stdev = pow ( 10, exponent );

	return g_stdev; // return that value
}


/** ***************************************************************************
 * @author N. Johnson
 *
 * @par Description: this function calculates the median of the array. First,
 * it sorts the column. Then, if the length is an even number, the median is
 * in position length / 2. Otherwise, if it's an odd number, the median value
 * is in position of the length - one divided by two, plus the length + 1 
 * divided by two, all over two. The function then returns that median value. 
 *
 * @param[in, out] data - array holding the input file information
 * @param[in] length - the number of rows in the array
 *
 * @returns median - the median value over the specified column
 *****************************************************************************/

double calc_median ( double data[ ][5], int length )
{
	double median; // holds the median value over the specified column
	// first, sort the column
	for ( int i = 0; i < length - 1; i++ )
	{
		for ( int j = 0; j < ( length - 1 - i ); j++ )
		{
			if ( data[j][1] > data[j + 1][1] )
			{
				swap ( data[j][1], data[j + 1][1] ); // calls swap for integers
			}
		}
	}
	if ( length % 2 == 0 )	// if the length is an even number
	{
		median = data[( length / 2 )][1];
	}
	else if ( length % 2 == 1 ) // if the length is an odd number
	{
		median = data[( ( ( length - 1 ) / 2 ) + ( ( length + 1 ) / 2 ) ) / 2]
			[1];
	}
	return median; // return the median value
}


/** ***************************************************************************
 * @author N. Johnson
 *
 * @par Description: this function calculates the percentage of 0's (failed 
 * items) over the specified column of the array. It adds the total number of 
 * 0's, then divides by the length to calculate the percentage. The function
 * returns the percentage. 
 *
 * @param[in, out] data - array holding the input file information
 * @param[in] length - the number of rows in the array
 * @param[in] column - the column in the array over which to perform the 
 *	calculation
 *
 * @returns percentage - the percentage of 0's over the specified column
 *****************************************************************************/

double calc_percentage ( double data[ ][5], int length, int column )
{
	double percentage;
	int num_zeros = 0;
	// calculate the number of failed items over the specified column
	for ( int i = 0; i < length; i++ ) // go through each element of the column
	{
		if ( data[i][column] == 0 ) // if the number is 0
		{
			num_zeros++; // add one to the number of 0's
		}
	}
	// take that number and divide by the length
	percentage = num_zeros / (double) length;
	// finally, multiply by 100 to get the percentage
	percentage = percentage * 100;

	return percentage; // return that value
}


/** ***************************************************************************
 * @author N. Johnson
 *
 * @par Description: this function calculates which columns pass and fail the
 * requirements. It starts with a bool named "result" as true, runs each test,
 * and if any test fails, the bool is switched to false. The bool is then
 * returned. 
 *
 * @param[in, out] output_stats - array holding the stats calculated earlier
 * @param[in, out] data - array holding the input file information
 * @param[in, out] pass_arary - holds which tests passed and which failed
 * @param[in] length - the number of rows in the array
 *
 * @returns result - whether or not the lot should be accepted
 *****************************************************************************/

bool calc_pass_fail ( double output_stats[ ], double data[ ][5], 
	int pass_array[ ], int length )
{
	bool result = true; /* returning true means no attributes caused a 
	rejection and the lot should be accecpted */
	// determine if any attributes caused a lot to be rejected

	for ( int i = 0; i < 5; i++ ) // set each item in pass_array to 1
	{
		pass_array[i] = 1;
	}
	// if the standard deviation of IV is greater than max voltage variation
	if ( output_stats[0] > MAX_VOLTAGE_VARIATION )
	{
		pass_array[0] = 0;
		result = false; // set the bool to fail
	}
	// if the median of c is greater than max current median
	if ( output_stats[1] > MAX_CURRENT_MEDIAN )
	{
		pass_array[1] = 0;
		result = false; // set the bool to fail
	}
	// if the standard deviation of A is greater than the max gain variation
	if ( output_stats[2] > MAX_GAIN_VARIATION ) 
	{
		pass_array[2] = 0;
		result = false; // set the bool to fail
	}
	// if the percentage of 0's of mt24 exceed max percentage
	if ( output_stats[3] > MAX_PERCENTAGE )
	{
		pass_array[3] = 0;
		result = false; // set the bool to fail
	}
	// if the percentage of 0's of mt5 exceed max percentage
	if ( output_stats[4] > MAX_PERCENTAGE )
	{
		pass_array[4] = 0;
		result = false; // set the bool to fail
	}

	return result; // return whether or not the lot should be accepted
	
}


/** ***************************************************************************
 * @author N. Johnson
 *
 * @par Description: this function creates a report file for the calculations
 * completed in the other functions. First, it creates the output file name
 * by prepending "report" to the beginning of the input file name. Then, it 
 * checks to see if the output file is open. If it is, it outputs the lot id,
 * all the calculation results, and whether or not the lot should be accepted.
 *
 * @param[in, out] filename - char array holding the name of the input file
 * @param[in, out] output_stats - array holding the results of the calculations
 * @param[in] pass - bool containing whether or not the lot should be accepted
 * @param[in, out] pass_array[ ] - array containing pass results for each test
 * @param[in] lot_id - lot ID number
 * @param[in, out] fout - output filestream to create report file
 *
 * @returns void
 *****************************************************************************/

void create_report ( char filename[ ], double output_stats[ ], bool pass, 
	int pass_array[ ], int lot_id, ofstream &fout )
{
	char outputname[40] = "report_"; // holds the output name of the file


	strncat_s ( outputname, filename, 35 ); // create output file name
	fout.open ( outputname ); // open output file for writing
	if ( !fout ) // check to see if output file is open
	{
		fout << "Could not open file " << outputname << endl;
		return;
	}
	fout << "Lot ID: " << lot_id << endl; // output lot ID
	fout << endl;
	// output standard deviation of IV
	fout << setw ( 30 ) << left << "Standard Deviation of IV: ";
	fout << setw ( 11 ) << left << output_stats[0] << " ";
	if ( pass_array[0] == 0 )
	{
		fout << "Fail" << endl;
	}
	else if ( pass_array[0] == 1 )
	{
		fout << "Pass" << endl;
	}
	// output median of C
	fout << setw ( 30 ) << left << "Median of C: ";
	fout << setw ( 11 ) << left << output_stats[1] << " ";
	if ( pass_array[1] == 0 )
	{
		fout << "Fail" << endl;
	}
	else if ( pass_array[1] == 1 )
	{
		fout << "Pass" << endl;
	}
	// output standard deviation of A
	fout << setw ( 30 ) << left << "Standard Deviation of A: ";
	fout << setw ( 11 ) << left << output_stats[2] << " ";
	if ( pass_array[2] == 0 )
	{
		fout << "Fail" << endl;
	}
	else if ( pass_array[2] == 1 )
	{
		fout << "Pass" << endl;
	}
	// output percentage of failed MT24
	fout << setw ( 30 ) << left << "Percentage of failed MT24: ";
	fout << setw ( 11 ) << left << output_stats[3] << " ";
	if ( pass_array[3] == 0 )
	{
		fout << "Fail" << endl;
	}
	else if ( pass_array[3] == 1 )
	{
		fout << "Pass" << endl;
	}
	// output percentage of failed MT5
	fout << setw ( 30 ) << left << "Percentage of failed MT5: ";
	fout << setw ( 11 ) << left << output_stats[4] << " ";
	if ( pass_array[4] == 0 )
	{
		fout << "Fail" << endl;
	}
	else if ( pass_array[4] == 1 )
	{
		fout << "Pass" << endl;
	}
	// if the lot should be rejected, print reject
	if ( pass == false )
	{
		fout << endl << "Action: Reject" << endl;
	}
	// otherwise print accept
	else if ( pass == true )
	{
		fout << endl << "Action: Accept" << endl;
	}
	return;
}


/** ***************************************************************************
 * @author N. Johnson
 *
 * @par Description: this short function swaps two numbers. It uses a 
 * temporary variable to hold the value of a, then assigns a to b, then 
 * assigns b to the temp. It returns void.
 *
 * @param[in, out] a - first input number
 * @param[in, out] b - second input number
 *
 * @returns void
 *****************************************************************************/

void swap ( double &a, double &b )
{
	double temp; // temporary variable used in swap

	temp = a; // assign temp to the initial value of a
	a = b; // assign a to the intial value of b
	b = temp; // assign b to the inital value of a

	return; // returns void
}