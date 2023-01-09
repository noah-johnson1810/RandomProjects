/**************************************************************************//**
 * @file
 * @brief Tech Values Calculator
 *
 * @mainpage Program 1 - Tech Values Calculator
 *
 * @section course_section Course Section
 *
 * @authors Noah Johnson
 *
 * @date September 27, 2020
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
 * @details The program gets input for all the user's technology in their
 * dorm room. It then displays the worth of the objects in an ordered manner
 * (accounting for depreciation on the user's computer). The program assumes 
 * the worth of a Nintendo, PlayStation, XBox, console game, and other disks,
 * but receives user input for all other values. 
 *
 * @section compile_section Compiling and Usage
 *
 * @par Compiling Instructions:
 *      None
 *
 * @par Usage:
 * @verbatim
 * c:\> prog1.exe
 * d:\> c:\bin\prog1.exe
 * @endverbatim
 *
 * @section todo_bugs_modification_section Todo, Bugs, and Modifications
 *
 * @par Modifications and Development Timeline:
 * @verbatim
 * https://gitlab.mcs.sdsmt.edu/7507264/csc150f20programs
 * @endverbatim
 *****************************************************************************/


#define _USE_MATH_DEFINES
#include <iostream>
#include <string>
#include <cmath>
#include <iomanip>
using namespace std;

// The value of an XBox is $250.00
const double XBOX_VALUE = 250.00;
// The value of a PlayStation is $400.00
const double PS_VALUE = 400.00;
// The value of a Nintendo is $300.00
const double NINTENDO_VALUE = 300.00;
// The value of a console game is $35.00
const double CONSOLE_GAME_VALUE = 35.00;
// The value of a disk is $25.00
const double DISK_VALUE = 25.00;


/********************************************************************//**
* @author Noah Johnson
* @par get input for the user's name, computer value, computer age, phone
* value, printer value, which game consoles the user has, and the number of 
* disks and games the user has. It then outputs the ratio of games to disks,
* the total number of games and disks, the total number of consoles, the "other
* tech" subtotal (phone value + printer value), the games/disks subtotal, the 
* computer subtotal (after calculating for 20% loss of value per year), the
* consoles subtotal, and the total tech value. The XBox is assumed to be worth
* $250, the PlayStation is assumed to be worth $400, a Nintendo switch is
* assumed to be worth $300, a disk is assumed to be worth $25, and a game disk
* is assumed to be worth $35. 
* @returns 0 program runs successfully
********************************************************************* **/


int main ( )
{

	string user_name; // contains the user's name
	double initial_computer_value; // value of user's computer when purchased
	int computer_age; // age of the user's computer
	double phone_value; // value of user's phone when purchased
	int printer_value; // value of user's printer
	char xbox_user_input; // char used to determine if user owns xbox
	char ps_user_input; // char used to determine if user owns playstation
	char nintendo_user_input; // char used to determine if user owns nintendo
	int num_console_games; // the number of console games the user owns
	int num_disks; // the number of disks the user owns
	double games_disks_ratio; // the ratio of games to disks the user owns
	int games_disks_total; // the total number of games and disks the user owns
	int num_consoles = 0; // the number of consoles the user owns
	double other_tech_worth; // the total value of the user's printer and phone
	double games_disks_worth; // the otal value of the user's disks and games
	double computer_worth; // the final value of the user's computer
	double consoles_subtotal = 0; // the total worth of the user's consoles 
	double tech_worth; /* the total worth of the user's tech that uses 
					   electricity, so, the phone, printer, 
					   consoles, and computer */


	// set the precision to display 2 digits after the decimal
	cout << fixed << setprecision ( 2 );

	// output welcome statement
	cout << "Welcome to the Dorm Room Tech Calculator!" << endl;

	// get user input for user's name
	cout << endl << "Please enter your name: ";
	cin >> user_name; 
	
	// get user input for computer value
	cout << "Please enter the value of your computer when purchased: ";
	cin >> initial_computer_value; 

	// get user input for computer age
	cout << "Please enter the age of your computer: ";
	cin >> computer_age; 

	// get user input for phone value
	cout << "Please enter the value of your phone: ";
	cin >> phone_value; 

	// get user input for printer value
	cout << "Please enter the value of your printer: "; 
	cin >> printer_value; 

	// get user input to add xbox or not 
	cout << "Do you have a XBox (y to add): ";
	cin >> xbox_user_input; 

	// add XBOX_VALUE to consoles_subtotal and 1 to num_consoles 
	// if user inputs 'y'
	if ( xbox_user_input == 'y' ) 
	{
		consoles_subtotal = ( consoles_subtotal + XBOX_VALUE );
		num_consoles = num_consoles + 1;
	}

	// get user input to add playstation or not
	cout << "Do you have a PlayStation (y to add): "; 
	cin >> ps_user_input; 

	// add PS_VALUE to consoles_subtotal and 1 to num_consoles 
	// if user inputs 'y'
	if ( ps_user_input == 'y' )
	{
		consoles_subtotal = consoles_subtotal + PS_VALUE;
		num_consoles = num_consoles + 1;
	}

	// get user input to add nintendo or not
	cout << "Do you have a Nintendo (y to add): ";
	cin >> nintendo_user_input; 

	// add NINTENDO_VALUE to consoles_subtotal and 1 to num_consoles 
	// if user inputs 'y'
	if ( nintendo_user_input == 'y' )
	{
		consoles_subtotal = consoles_subtotal + NINTENDO_VALUE;
		num_consoles = num_consoles + 1;
	}

	// get user input for number of console games
	cout << "Please enter the total number of console games: ";
	cin >> num_console_games; 

	// get user input for number of other disks
	cout << "Please enter the number of other computer or dvd disks: ";
	cin >> num_disks; 

	//calculate the ratio between user's games and disks
	games_disks_ratio = 
		( static_cast < double > ( num_console_games ) ) / num_disks; 

	// output new line
	cout << endl; 

	// display user's name, followed by "..."
	cout << user_name << "..." << endl; 

	//output ratio of console games to disks
	cout << "You have " << games_disks_ratio << " ratio of games to disks.";
	cout << endl;
	
	// calculate total number of console games and discs
	games_disks_total = num_console_games + num_disks;

	// output number of console games and discs
	cout << "You have " << games_disks_total << " games and disks." << endl;

	// output number of consoles
	cout << "You have " << num_consoles << " consoles." << endl;

	// set the fill character to '.'
	cout << setfill('.');

	//calculate other tech worth
	other_tech_worth = printer_value + phone_value;

	// output other tech subtotal
	cout << setw ( 30 ) << left << "Other tech subtotal:" << "$";
	cout << other_tech_worth << endl;

	// calculate games & disks worth
	games_disks_worth = ( num_disks * DISK_VALUE ) + 
		( num_console_games * CONSOLE_GAME_VALUE );

	// output games & disks worth
	cout << setw ( 30 ) << left << "Games\\disks subtotal:" << "$";
	cout << games_disks_worth << endl;

	// calculate computer worth
	computer_worth = ( initial_computer_value * 
		( pow ( 0.8, static_cast < double > ( computer_age ) ) ) );

	// output computer worth
	cout << setw ( 30 ) << left << "Computer subtotal:" << "$";
	cout << computer_worth << endl;

	// OUTPUT: consoles subtotal...
	cout << setw ( 30 ) << left << "Consoles subtotal:" << "$";
	cout << consoles_subtotal << endl;

	// newline containing the '-' character
	cout << setfill ('-');
	cout << setw ( 60 ) << left << "-" << endl;

	// calculate total worth of tech
	tech_worth = computer_worth + consoles_subtotal + printer_value
		+ phone_value;

	// output total worth of tech
	cout << "The estimated tech worth in your room is $";
	cout << tech_worth << endl;

	// output new line
	cout << endl;

	// output closing statement
	cout << "Thank you for using the calculator!" << endl;

	return 0;

}