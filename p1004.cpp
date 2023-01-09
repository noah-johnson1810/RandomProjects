/**************************************************************************//**
 * @file
 * @brief Additive Sequence Generator
 *
 * @mainpage Lab 06a - Additive Number Sequence
 *
 * @section course_section Course Section
 *
 * @authors Noah Johnson
 *
 * @date October 2, 2020
 *
 * @par Instructor:
 *         Qiao, de Castro, Bergevin
 *
 * @par Course:
 *         CSC 150 - Section MT2 - 3:00-5:00 PM
 *
 * @par Location:
 *         Zoom
 *
 * @section program_section Program Information
 *
 * @details This program uses two terms (entered by the user) to create a 
 * sequence where each term is calculated by adding the previous two terms.
 * The program then outputs the sequence a number of times (specificed by the
 * user). 
 *
 * @section compile_section Compiling and Usage
 *
 * @par Compiling Instructions:
 *      None
 *
 * @par Usage:
   @verbatim
   c:\> p1004.exe
   d:\> c:\bin\p1004.exe
   @endverbatim
 *
 * @section todo_bugs_modification_section Todo, Bugs, and Modifications
 *
 *
 * @par Modifications and Development Timeline:
   @verbatim
   https://gitlab.mcs.sdsmt.edu/7507264/csc150f20work
   @endverbatim
 *
 *****************************************************************************/


#include <iostream>
using namespace std;

void output_sequence ( int num_a, int num_b, int num_terms );

/********************************************************************//**
* @author Noah Johnson
* @par Main gets user input for the first two numbers. Then, it gets user input
* for the number of terms to display (after the second term). Finally, it uses
* the output_sequence function to display the correct number of iterations of
* the sequence.
* @returns 0 program runs successfully
********************************************************************* **/


int main ( )
{
	int num_a;
	int num_b;
	int num_terms;

	// get user input for first term
	cout << "Enter first term: ";
	cin >> num_a;
	// get user input for second term
	cout << "Enter second term: ";
	cin >> num_b;
	// get user input for number of terms
	cout << "Enter number of terms to follow: ";
	cin >> num_terms;
	// output the word "sequence" 
	cout << "Sequence:" << endl;
	// output the sequence the desired number of times
	output_sequence ( num_a, num_b, num_terms );

}

/********************************************************************//**
* @author Noah Johnson
* @par output_sequence() displays the first two terms that the user entered as
* the first two values in the sequence. Then, it displays a sequence where each
* digit is found by adding the previous two digits. It runs the number of times
* that the user enters, plus 2 for the first 2 terms.
* @returns 0 program runs successfully
********************************************************************* **/

void output_sequence ( int num_a, int num_b, int num_terms )
{
	int num_c;
	// display the first two digits as entered by the user
	cout << num_a << endl;
	cout << num_b << endl;
	// display the sum of the previous two numbers as the next number
	for ( int i = 1; i <= num_terms; i++ )
	{
		num_c = num_a + num_b;
		cout << num_c << endl;
		num_a = num_b;
		num_b = num_c;
	}
	
}
