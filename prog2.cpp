/**************************************************************************//**
 * @file
 * @brief Game of College Life
 *
 * @mainpage Program 2 - Game of College Life
 *
 * @section course_section Course Section
 *
 * @authors Noah Johnson
 *
 * @date October 25, 2020
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
 * @details The program is a miniature version of the Game of Life board game.
 * It allows one player to spin a wheel to move through a board, landing on
 * squares to gain or lose "money" from their balance, pass paydays, and 
 * acquire other status updates like getting a dog or cat. It also has a bank
 * function, which can be visited at any time, to borrow from the bank, or 
 * pay back loans. Additionally, a player can choose to bet on a wheel once
 * per turn. When the player passes the end of the game board or quits, a win 
 * or loss message is output depending on whether or not the user's final 
 * balance is positive. 
 *
 * @section compile_section Compiling and Usage
 *
 * @par Compiling Instructions:
 *      None
 *
 * @par Usage:
 * @verbatim
 * c:\> prog2.exe
 * d:\> c:\bin\prog2.exe
 * @endverbatim
 *
 * @section todo_bugs_modification_section Todo, Bugs, and Modifications
 *
 * @par Modifications and Development Timeline:
 * @verbatim
 * https://gitlab.mcs.sdsmt.edu/7507264/csc150f20programs
 * @endverbatim
 *****************************************************************************/


// #include statements
#include <iostream>
#include <string>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <iomanip>
using namespace std;


// function definitions
void auto_borrow ( int player_info [ ] );
void bank_menu ( int player_info [ ] );
void bet_on_wheel ( int player_info [ ] );
void check_for_payday ( int player_info [ ], int square_each_turn [ ] );
void end_game ( string player_name, int player_info [ ] );
string initialization ( int player_info [ ] );
int main_menu ( string player_name, int player_info [ ] );
void move ( int player_info [ ] );
void payday ( int player_info [ ] );
void print_game_board ( int square );
int spin ( );
void square0_11 ( int player_info [ ] );
void square12_23 ( int player_info [ ] );
void square24_34 ( int player_info [ ] );
void square_events ( int player_info [ ] );


/** ***********************************************************************
* @author N. Johnson
*
* @par Description:
* Main begins by running initialization() to get the user's basic info
* such as starting sallary and mode choice, and returns the player's name.
* Then, it executes main_menu() until the player either passes the end
* of the game board, or selects 0 from the main menu to quit. Once either
* situation happens, it calls end_game() to calculate and output the final
* results for the player. The player's information is stored in an array
* named player_info[11], which is organized as follows:
* player_info[ ] contains the player's information in the following order:
* player_info[0] = current funds
* player_info[1] = current debt
* player_info[2] = seed choice
* player_info[3] = sallary
* player_info[4] = current square
* player_info[5] = mode choice
* player_info[6] = number of dogs
* player_info[7] = number of cats
* player_info[8] = number of paydays crossed on the current turn
* player_info[9] = number of current turn 
* player_info[10] = number of bets on wheel on current turn 
*
* @returns 0 - program ran successfully
*
******************************************************************************/

int main ( )
{
	int end_trigger = 0; // end the program when main_menu returns -1
	string player_name; // holds the player's name
	int player_info [ 11 ] = { 1000 }; // player starts with $1,000
	int square_each_turn [ 50 ]; // stores the history of the players' squares 

	player_info [ 4 ] = -1; // player starts off the board

	/* run initialization() and assign player_name to its return*/
	player_name = initialization ( player_info );

	while ( player_info [ 4 ] < 35 && end_trigger != -1 )
	{
		player_info [ 9 ]++; // add 1 to the current turn
		// run main_menu(...), checking if it returns -1 (user selects '0')
		end_trigger = main_menu ( player_name, player_info );
		// apply paydays after each turn
		check_for_payday ( player_info, square_each_turn );
	}

	end_game ( player_name, player_info ); /* once the player selects 0 or
	reaches the end of the board, call end_game(...)*/

	return 0;
}


/** ***************************************************************************
 * @author N. Johnson
 *
 * @par Description:
 * Checks if the user's balance is below 0, then borrows from the bank in
 * $2000 increments until the balance is above 0.
 *
 * @param[in, out] player_info - array to hold the player's information
 *
 * @returns void
 *****************************************************************************/

void auto_borrow ( int player_info [ ] )
{
	int num_borrows = 0; // number of times the 2000 is borrowed

	// automatically borrow from the bank if balance goes below 0
	while ( player_info [ 0 ] < 0 )
	{
		player_info [ 0 ] += 2000;
		player_info [ 1 ] += 2000;
		num_borrows++;
		cout << "You borrowed $" << num_borrows * 2000 << ".00 from the bank"
			<< endl;
	}

	return;
}


/** ***************************************************************************
 * @author N. Johnson
 *
 * @par Description:
 * The bank option for the user. As long as the user doesn't input 0, it will
 * allow them to borrow or pay multiples of 2000 from/to the bank. If the user
 * tries to enter a number that is not a multiple of 2000, it will output 
 * "Invalid amount. Need multiple of $2,000" and ask for user input again. 
 *
 * @param[in, out] player_info - array holding the player's information
 *
 * @returns void
 *****************************************************************************/

void bank_menu ( int player_info [ ] )
{
	int user_borrow_choice; // holds the player's borrow amount
	int user_menu_choice = 1; // holds the player's menu selection
	int user_pay_choice; // holds the player's pay amount

	while ( user_menu_choice != 0 ) // show bank_menu until user opts to quit
	{
		cout << endl << "Welcome to your bank" << endl;
		cout << setw ( 8 ) << " "; // formatting for the next line
		cout << "Your current funds are: $" << player_info [ 0 ]
			<< ".00" << endl;
		cout << setw ( 8 ) << " "; // formatting for the next line
		cout << "Your current debt is: $" << player_info [ 1 ]
			<< ".00" << endl;
		cout << endl << "1) Borrow\n2) Pay\n0) Exit" << endl;
		cout << endl << "Enter your choice: ";
		cin >> user_menu_choice; // get user input for the menu

		// if the user enters 1, they want to borrow from the bank
		if ( user_menu_choice == 1 )
		{
			cout << "Enter value to borrow or 0 to exit (multiple of $2,000): ";
			cin >> user_borrow_choice; /* once the user has chosen to borrow,
			get the amount that they want to borrow */

			while ( user_borrow_choice % 2000 != 0 ) // if not multiple of 2000
			{
				cout << "Invalid amount. Need multiple of $2,000." << endl;
				cout << "Enter value to borrow or 0 to exit "
					<< "(multiple of $2,000): ";
				cin >> user_borrow_choice; // get user input again
			}

			if ( user_borrow_choice == 0 )
			{
				return; // quit bank_menu if the user enters 0
			}

			else
			{
				// add the user's borrow choice to both their funds and debt
				player_info [ 0 ] += user_borrow_choice;
				player_info [ 1 ] += user_borrow_choice;
			}

		}

		// if the user enters 2, they want to pay back debt
		if ( user_menu_choice == 2 )
		{
			cout << "Enter value to pay or 0 to exit (multiple of $2,000): ";
			cin >> user_pay_choice; // amount of debt the user wants to pay

			while ( user_pay_choice % 2000 != 0 ) // if not a multiple of 2000
			{
				cout << "Invalid amount. Need multiple of $2,000." << endl;
				cout << "Enter value to pay or 0 to exit "
					<< "(multiple of $2,000): ";
				cin >> user_pay_choice; // get user input again
			}

			if ( user_pay_choice == 0 )
			{
				return; // quit bank_menu if the user enters 0
			}

			else
			{
				// subtract the amount they want to pay from funds and debt
				player_info [ 0 ] -= user_pay_choice;
				player_info [ 1 ] -= user_pay_choice;
			}

		}

	}

	return;
}


/** ***************************************************************************
 * @author N. Johnson
 *
 * @par Description:
 * Once per turn, the user can choose to bet on a wheel. The wheel will spin a
 * random number from 1 to 6, and the user can pay $1,000 to pick to numbers. 
 * If the wheel lands on one of their numbers, they get $10,000. If the user 
 * tries to use this option more than once per turn, it will output "Extra bet 
 * not allowed in this turn."
 *
 * @param[in, out] player_info - array holding the player's information
 *
 * @returns void
 *****************************************************************************/

void bet_on_wheel ( int player_info [ ] )
{
	int bet_1; // the user's first bet
	int bet_2; // the user's second bet
	int result; // result of the spin

	if ( player_info[10] == 0 ) /* player_info[10] starts at 0, but will be 
		incremented after the first use of bet_on_wheel(...) */
	{
		cout << "You are betting against the wheel" << endl;
		cout << "Your bet is $1,000, you need to choose 2 numbers from 1 to 6."
			<< endl;
		cout << "Choose number 1: ";
		cin >> bet_1; // get user input for bet 1
		cout << "Choose number 2: ";
		cin >> bet_2; // get user input for bet 2
		result = ( rand ( ) % 6 ) + 1; /* the result of the spin is a random
		number between 1 and 6 */
		cout << "You spin the wheel and get a " << result << endl;
		
		if ( bet_1 == result || bet_2 == result ) // if one bet is correct
		{
			cout << "YOU WIN! You receive $10,000" << endl;
			player_info [ 0 ] += 10000;
		}
		
		else // if neither bet is correct
		{
			cout << "You lost your bet." << endl;
			player_info [ 0 ] -= 1000;
		}
		player_info [ 10 ]++; /* increment player_info [ 10 ] to prevent 
		another spin of the wheel this turn */

	}

	else // if player_info[10] isn't 0, they've already taken a bet this turn
	{
		cout << "Extra bet not allowed in this turn." << endl;
	}

	return;
}


/** ***************************************************************************
 * @author N. Johnson
 *
 * @par Description:
 * After the player has moved each turn, this function will check to see how
 * many (if any) paydays have been crossed. It will then apply the appropriate
 * reward to the player, outputting the necessary information.
 *
 * @param[in, out] player_info - array holding the player's information
 * @param[in] square_each_turn - array holding the history of the player's
 * squares that they've landed on each turn
 *
 * @returns void
 *****************************************************************************/

void check_for_payday ( int player_info [ ], int square_each_turn [ ] )
{
	square_each_turn [ player_info [ 9 ] ] = player_info [ 4 ];

	// check if player's location last turn was before 6, and is now past 6 
	if ( square_each_turn [ player_info [ 9 ] - 1 ] < 6 
		&& square_each_turn [ player_info [ 9 ] ] >= 6 )
	{
		player_info [ 8 ]++; // increments number of paydays this turn
	}

	// check if player's location last turn was before 13, and is now past 13
	if ( square_each_turn [ player_info [ 9 ] - 1 ] < 13
		&& square_each_turn [ player_info [ 9 ] ] >= 13 )
	{
		player_info [ 8 ]++; // increments number of paydays this turn
	}

	// check if player's location last turn was before 19, and is now past 19
	if ( square_each_turn [ player_info [ 9 ] - 1 ] < 19
		&& square_each_turn [ player_info [ 9 ] ] >= 19 )
	{
		player_info [ 8 ]++; // increments number of paydays this turn
	}

	// check if player's location last turn was before 23, and is now past 23
	if ( square_each_turn [ player_info [ 9 ] - 1 ] < 23
		&& square_each_turn [ player_info [ 9 ] ] >= 23 )
	{
		player_info [ 8 ]++; // increments number of paydays this turn
	}

	// check if player's location last turn was before 30, and is now past 30 
	if ( square_each_turn [ player_info [ 9 ] - 1 ] < 30
		&& square_each_turn [ player_info [ 9 ] ] >= 30 )
	{
		player_info [ 8 ]++; // increments number of paydays this turn
	}

	// if the user has crossed at least 1 payday this turn, call payday(...)
	if ( player_info [ 8 ] > 0 ) 
	{
		payday ( player_info );
	}

	// next, call auto_borrow to check if the player needs to borrow funds
	auto_borrow ( player_info );

	return;
}


/** ***************************************************************************
 * @author N. Johnson
 *
 * @par Description:
 * After the player has either reached the end of the game board, or pressed 
 * 0 from the main menu, this function will calculate and output the results
 * for the player. If the player's final balance is at or equal to 0, it will
 * output a winning message. Otherwise, it outputs a losing message. 
 *
 * @param[in] player_name - string holding the player's name
 * @param[in, out] player_info - array holding the player's information
 *
 * @returns void
 *****************************************************************************/

void end_game ( string player_name, int player_info [ ] )
{
	if ( player_info [ 4 ] >= 35 ) // if the player passed end of the board
	{
		cout << endl << "Congratulations! You've graduated" << endl;
		cout << endl << "Calculating results for " << player_name << endl;
		player_info [ 0 ] -= ( player_info [ 1 ]
			+ ( ( player_info [ 1 ] / 2000 ) * 500 ) ); // payback interest
		player_info [ 0 ] += 2000 * player_info [ 6 ]; // get 2,000 per dog
		player_info [ 0 ] += 2000 * player_info [ 7 ]; // get 2,000 per cat
		// output player total
		cout << setw ( 17 ) << "Total = $" << player_info [ 0 ] << ".00" 
			<< endl;
		
		if ( player_info [ 0 ] < 0 ) // if player's balance is negative
		{
			cout << "You lost!" << endl;
		}
		
		if ( player_info [ 0 ] >= 0 ) // if player's balance is 0 or greater
		{
			cout << "Congratulations, you win!" << endl;
		}

	}

	cout << endl << "Goodbye" << endl;

	return;
}


/** ***************************************************************************
 * @author N. Johnson
 *
 * @par Description:
 * This function is called once at the beginning of the game to get the user's
 * basic information, such as mode type, player name, and starting sallary. 
 *
 * @param[in, out] player_info - array holding the player's information
 *
 * @returns player_name - string containing the player's name
 *****************************************************************************/

string initialization ( int player_info [ ] )
{
	char mode_choice; // temporarily holds the player's choice of gamemode
	string player_name; // holds the player's name
	int spin_result; // holds the result of the spin

	cout << "Welcome to the Game of College Life" << endl;
	cout << "\nSeed for randomization (T)ime, (U)ser defined, (D)ebug mode: ";
	cin >> mode_choice; // get user input for mode choice
	mode_choice = tolower ( mode_choice ); // set mode_choice to lowercase

	// validate user input
	// if user input isn't 'u', 'd', or 't'
	while ( mode_choice != 'u' && mode_choice != 'd' && mode_choice != 't' )
	{
		cout << "Invalid Option" << endl;
		cout << "Seed for randomization (T)ime, (U)ser defined, "
			<< "(D)ebug mode: ";
		cin >> mode_choice; // get user input again
		mode_choice = tolower ( mode_choice ); // set mode_choice to lowercase
	}

	if ( mode_choice == 't' )
	{
		player_info [ 5 ] = 0; // set the spin mode to time 
		srand ( ( unsigned int ) time ( 0 ) ); // set rand() seed to time(0)
	}

	else if ( mode_choice == 'u' )
	{
		player_info [ 5 ] = 1; // set the game mode to user-defined seed
		cout << "Write a number for the seed: "; // user input for seed #
		cin >> player_info [ 2 ];
		srand ( player_info [ 2 ] ); // set rand() seed to user's seed choice
	}

	else if ( mode_choice == 'd' )
	{
		player_info [ 5 ] = 2; // set the game mode to debugging
		cout << "Write a number for the seed: "; // user input for seed #
		cin >> player_info [ 2 ];
		srand ( player_info [ 2 ] ); // set rand() seed to user's seed choice
	}

	cout << "Name of player 1? "; // get user input for player 1 name
	cin >> player_name;
	cout << "Spinning wheel for payment...";
	// get the spin number given the mode choice and seed choice
	spin_result = spin ( );
	// output the result
	cout << spin_result << "..." << endl;
	// determine each payday sallary based on spin result

	if ( spin_result == 1 || spin_result == 2 )
	{
		player_info [ 3 ] = 500; // sallary is 500
	}

	else if ( spin_result >= 3 && spin_result <= 5 )
	{
		player_info [ 3 ] = 1000; // sallary is 1000
	}

	else if ( spin_result == 6 )
	{
		player_info [ 3 ] = 1500; // sallary is 1500
	}

	cout << "Your payment will be " << player_info [ 3 ] << " on each payday."
		<< endl;

	return player_name; // return player_name to initialization();
}


/** ***************************************************************************
 * @author N. Johnson
 *
 * @par Description:
 * This function is called at the beginning of each turn, as long as the player
 * does not input 0 or pass the end of the game board. It outputs the game
 * board by calling the print_game_board function, displays the user's 
 * current funds and debt, then gives them the option to spin, bet, go to 
 * the bank, or quit. Functions are called according to the user's choice. 
 * Once the user inputs 0, this function returns -1 and main() will call
 * end_game to end the program. 
 *
 * @param[in] player_name - string holding the player's name
 * @param[in, out] player_info - array holding the player's information
 *
 * @returns 0 - continues running program, or 
 * @returns -1 - call end_game() to end the program
 *****************************************************************************/

int main_menu ( string player_name, int player_info [ ] )
{
	int user_choice = -1; // holds the player's selection for the main menu
	
	// display player name, line of '=', game board, then another line of '='
	cout << endl << "Player 1: " << player_name << "'s turn" << endl;
	cout << "================================================" << endl;
	print_game_board ( player_info [ 4 ] );
	cout << "================================================" << endl;
	// display current funds and current debt
	cout << "Current funds : $" << player_info [ 0 ] << ".00" << endl;
	cout << "Current Debt : $" << player_info [ 1 ] << ".00" << endl;
	// display menu for user to select from
	cout << "\n1) Spin\n2) Bet on Wheel\n3) Go to the Bank\n0) Quit" << endl;
	cout << "\nEnter your choice: ";
	// get user input for choice of what to do
	cin >> user_choice;
	// do the appropriate task given the user input

	if ( user_choice == 0 )
	{
		return -1;
	}

	else if ( user_choice == 1 ) // if the user selects 1 from main menu
	{
		move ( player_info ); // call the move function
	}

	else if ( user_choice == 2 ) // if the user selects 2 from main menu
	{
		bet_on_wheel ( player_info ); // call the bet_on_wheel function
	}

	else if ( user_choice == 3 ) // if the user selects 3 from the main menu
	{
		bank_menu ( player_info ); // call the bank_menu function
	}

	else // validate user input
	{
		cout << "Invalid option";
	}

	return 0;
}


/** ***************************************************************************
 * @author N. Johnson
 *
 * @par Description:
 * This function works in conjunction with spin() to move the player through
 * the game board. If the user has selected debug mode, it will allow the user
 * to input a custom spin value. Otherwise, it calls spin() to return a random
 * value between 1 and 6, then moves the player to that square and calls the
 * appropriate function to activate the event of that square. 
 *
 * @param[in, out] player_info - array holding the player's information
 *
 * @returns void
 *****************************************************************************/

void move ( int player_info [ ] )
{
	int spin_result; // holds the result of the spin
	int user_spin_choice = 0; // holds the debug-mode spin choice
	player_info [ 10 ] = 0; /* once the player moves, reset their ability to
	use the bet function */

	if ( player_info [ 5 ] == 2 ) // if the user has selected debug mode
	{
		cout << "Spin value: ";
		cin >> user_spin_choice; // get user's input for the spin
		spin_result = user_spin_choice;
	}

	/* if the user has selected time or user-defined mode, get random spin
	between 1 and 6 by calling spin(...) function */
	if ( player_info [ 5 ] == 0 || player_info [ 5 ] == 1 )
	{
		spin_result = spin ( );
	}

	// display the spin result to th eplayer
	cout << "You spin the wheel and get..." << spin_result;
	player_info [ 4 ] = player_info [ 4 ] + spin_result;
	square_events ( player_info ); // call square_events(...)

	return;
}


/** ***************************************************************************
 * @author N. Johnson
 *
 * @par Description:
 * Applies the appropriate number of paydays to the player, then resets 
 * player_info[8], which is the number of paydays crossed on the current turn
 *
 * @param[in, out] player_info - array holding the player's information
 *
 * @returns void
 *****************************************************************************/

void payday ( int player_info [ ] )
{
	// assigned player_info[4] to int "square" to make code more readable
	int square = player_info [ 4 ]; 

	// avoid outputting "you passed over..." and "payday" at the same time
	if ( square != 6 && square != 13 && square != 19 && square != 23
			&& square != 30 )
		// for each payday this turn ( player_info[ 8 ] ), apply their sallary
	{

		if ( player_info [ 8 ] = 1 )
		{
			cout << "You passed over " << player_info [ 8 ] <<
				" payday so you receive $" << ( player_info [ 3 ]
					* player_info [ 8 ] ) << endl;
		}

		if ( player_info [ 8 ] > 1 )
		{
			cout << "You passed over " << player_info [ 8 ] <<
				" paydays so you receive $" << ( player_info [ 3 ]
					* player_info [ 8 ] ) << endl;
		}

	}

	// balance += number of paydays * sallary
	player_info [ 0 ] += ( player_info [ 8 ] * player_info [ 3 ] );
	player_info [ 8 ] = 0; // reset number of paydays this turn

	return;
}


/** ***************************************************************************
 * @author N. Johnson
 *
 * @par Description:
 * Prints the game board using the game_board character array. It loops up to
 * the symbol "1" (representing player 1) then loops again from the next square
 * to the end of the board. 
 *
 * @param[in] square - the current square the player is on
 *
 * @returns void
 *****************************************************************************/

void print_game_board ( int square )
{
	// array holding the game board
	char game_board [ 36 ] = { '.', '.', '.', '.', '.', '.', 'P', 'S', '.',
		'S', '.', '.', '.', 'P', '.', '.', 'S', '.', '.', 'P', '.', '.',
		'S', 'P', '.', '.', '.', '.', '.', '.', 'P', '.', '.', '.', '.'};
	
	// print the game board with player 1 icon using for loop
	cout << "Game board: ";
	if ( square >= 0 ) // once the player is on the board, display the 1
	{
		
		for ( int i = 0; i < square; i++ ) // display the board behind the 1
		{
			cout << game_board [ i ];
		}
		
		cout << '1'; // show the player's icon on the board
	}
	
	// display the board in front of the 1
	for ( int j = square + 1; j <= 35; j++ ) 
	{
		cout << game_board [ j ];
	}
	
	cout << endl;
	
	return;
}


/** ***************************************************************************
 * @author N. Johnson
 *
 * @par Description:
 * Function used to "spin" the wheel for a number. 
 *
 * @returns random number between 1 and 6
 *****************************************************************************/

int spin ( )
{
	return ( ( rand ( ) % 6 ) + 1 ); // return random number between [1, 6]
}


/** ***************************************************************************
 * @author N. Johnson
 *
 * @par Description:
 * Contains the consequences of squares 0 - 11
 *
 * @param[in, out] player_info - array to hold the player's information
 *
 * @returns void
 *****************************************************************************/

void square0_11 ( int player_info [ ] )
{
	if ( player_info [ 4 ] == 0 ) // if the player lands on square 0
	{
		cout << endl << "Reward: Accepted Party -- gain $500" << endl;
		player_info [ 0 ] += 500; // add 500 to player's balance
	}

	if ( player_info [ 4 ] == 1 ) // if the player lands on square 1
	{
		cout << endl << "Reward: Grandpa gave you money for a car -- "
			<< "gain $1500" << endl;
		player_info [ 0 ] += 1500; // add 1500 to the player's balance
	}

	if ( player_info [ 4 ] == 2 ) // if the player lands on square 2
	{
		cout << endl << "Penalty: Buy Books -- pay $500" << endl;
		player_info [ 0 ] -= 500; // subtract 500 from the player's balance
	}

	if ( player_info [ 4 ] == 3 ) // if the player lands on square 3
	{
		cout << endl << "Reward: Lucky day -- gain $2000" << endl;
		player_info [ 0 ] += 2000; // add 2000 to the player's balance
	}

	if ( player_info [ 4 ] == 4 ) // if the player lands on square 4
	{
		cout << endl << "Penalty: Course Fees -- pay $700" << endl;
		player_info [ 0 ] -= 700; // subtract 700 from the player's balance
	}

	if ( player_info [ 4 ] == 5 ) // if the player lands on square 5
	{
		cout << endl << "Penalty: Buy furniture -- pay $2000" << endl;
		player_info [ 0 ] -= 2000; // subtract 2000 from the player's balance
	}

	if ( player_info [ 4 ] == 6 ) // if the player lands on square 6
	{
		// simply output "Payday." check_for_payday applies payday effects
		cout << endl << "Payday" << endl;
	}

	if ( player_info [ 4 ] == 7 ) // if the player lands on square 7
	{
		cout << endl << "Status: You got a dog" << endl;
		player_info [ 6 ] = 1; // add one dog to the player's inventory
	}

	if ( player_info [ 4 ] == 8 ) // if the player lands on square 8
	{
		cout << endl << "Reward: Sold a project to a company -- gain $10000" 
			<< endl;
		player_info [ 0 ] += 10000; // add 10000 to the player's balance
	}

	if ( player_info [ 4 ] == 9 ) // if the player lands on square 9
	{
		cout << endl << "Status: You got a cat" << endl;
		player_info [ 7 ] += 1; // add one cat to the player's inventory
	}

	if ( player_info [ 4 ] == 10 ) // if the player lands on square 10
	{
		
		if ( player_info [ 1 ] > 0 ) // if the player has debt
		{
			cout << endl << "Penalty: Interest Due. Pay $100 for every "
				<< "$2,000 owed in debt -- pay " << ( player_info [ 1 ] / 20 ) 
				<< endl;
			// subtract the player's debt divided by 20
			player_info [ 0 ] -= ( player_info [ 1 ] / 20 );
		}
		
		else // if the player has no debt
		{
			cout << endl << "Avoided Event" << endl;
		}

	}
	
	if ( player_info [ 4 ] == 11 ) // if the player lands on square 11
	{
		cout << endl << "Reward: Grandma came to visit -- gain $500" << endl;
		player_info [ 0 ] += 500; // add 500 to the player's balance
	}

	return;
}


/** ***************************************************************************
 * @author N. Johnson
 *
 * @par Description:
 * Contains the consequences of squares 12 - 23
 *
 * @param[in, out] player_info - array to hold the player's information
 *
 * @returns void
 *****************************************************************************/

void square12_23 ( int player_info [ ] )
{
	if ( player_info [ 4 ] == 12 ) // if the player lands on square 12
	{
		
		if ( player_info [ 6 ] == 0 ) // if the player does not own a dog
		{
			cout << endl << "Avoided Event" << endl;
		}
	
		else // if the player does own at least one dog
		{
			cout << endl << "Penalty: If you own a dog, your dog chewed "
				<< "through the door -- pay $700" << endl;
			player_info [ 0 ] -= 700; // subtract 700 from the player's balance
		}

	}
	
	if ( player_info [ 4 ] == 13 ) // if the player lands on square 13
	{
		cout << endl << "Payday" << endl;
	}
	
	if ( player_info [ 4 ] == 14 ) // if the player lands on square 14
	{
		cout << endl << "Penalty: Mice found! Call an exterminator "
			<< "-- pay $2000" << endl;
		player_info [ 0 ] -= 2000; // subtract 2000 from the player's balance
	}
	
	if ( player_info [ 4 ] == 15 ) // if the player lands on square 15
	{
		cout << endl << "Reward: Help friend move -- gain $1000" << endl;
		player_info [ 0 ] += 1000; // add 1000 to the player's balance
	}
	
	if ( player_info [ 4 ] == 16 ) // if the player lands on square 16
	{
		cout << endl << "Status: You got a cat" << endl;
		player_info [ 7 ] += 1; // add 1 cat to the player's inventory
	}
	
	if ( player_info [ 4 ] == 17 ) // if the player lands on square 17
	{
		cout << endl << "Reward: Won a new computer -- gain $1500" << endl;
		player_info [ 0 ] += 1500; // add 1500 to the player's balance
	}
	
	if ( player_info [ 4 ] == 18 ) // if the player lands on square 18
	{
		cout << endl << "Reward: Got a scholarship -- gain $5000" << endl;
		player_info [ 0 ] += 5000; // add 5000 to the player's balance
	}
	
	if ( player_info [ 4 ] == 19 ) // if the player lands on square 19
	{
		cout << endl << "Payday" << endl;
	}
	
	if ( player_info [ 4 ] == 20 ) // if the player lands on square 20
	{
		cout << endl << "Reward: Aced your Midterm -- gain $1000" << endl;
		player_info [ 0 ] += 1000; // add 1000 to the player's balance
	}
	
	if ( player_info [ 4 ] == 21 ) // if the player lands on square 21
	{
		
		if ( player_info [ 1 ] > 0 ) // if the player has debt
		{
			cout << endl << "Penalty: Interest Due. Pay $100 for every "
				<< "$2,000 owed in debt -- pay $" << ( player_info [ 1 ] / 20 )
				<< endl;
			// subtract the player's debt divided by 20
			player_info [ 0 ] -= ( player_info [ 1 ] / 20 );
		}
	
		else // if the player has no debt
		{
			cout << endl << "Avoided Event" << endl;
		}

	}
	
	if ( player_info [ 4 ] == 22 ) // if the player lands on square 22
	{
		cout << endl << "Status: You got a dog" << endl;
		player_info [ 6 ] += 1; // add 1 dog to the player's inventory
	}
	
	if ( player_info [ 4 ] == 23 ) // if the player lands on square 23
	{
		cout << endl << "Payday" << endl;
	}
	
	return;
}


/** ***************************************************************************
 * @author N. Johnson
 *
 * @par Description:
 * Contains the consequences of squares 24 - 34
 *
 * @param[in, out] player_info - array to hold the player's information
 *
 * @returns void
 *****************************************************************************/

void square24_34 ( int player_info [ ] )
{
	if ( player_info [ 4 ] == 24 ) // if the player lands on square 24
	{
		cout << endl << "Penalty: Caught the flu -- pay $1000" << endl;
		player_info [ 0 ] -= 1000; // subtract 1000 from the player's balance
	}
	
	if ( player_info [ 4 ] == 25 ) // if the player lands on square 25
	{
	
		if ( player_info [ 6 ] == 0 ) // if the player doesn't have a dog
		{
			cout << endl << "Avoided Event" << endl; // do nothing
		}
		
		else // if the player has at least one dog
		{
			cout << endl << "Penalty: If you have a dog, take it to the vet "
				<< "-- pay $" << 300 * player_info [ 6 ] << endl;
			// subtract 300 * number of dogs from the player's balance
			player_info [ 0 ] -= ( 300 * player_info [ 6 ] );
		}

	}
	
	if ( player_info [ 4 ] == 26 ) // if the player lands on square 26
	{
		
		if ( player_info [ 7 ] == 0 ) // if the player doesn't have a cat
		{
			cout << endl << "Avoided Event" << endl; // do nothing
		}
		
		else // if the player has at least 1 cat
		{
			cout << endl << "Penalty: If you have a cat, take it to the vet "
				<< "-- pay $" << 300 * player_info [ 7 ] << endl;
			// subtract 300 * number of cats to the player's balance
			player_info [ 0 ] -= ( 300 * player_info [ 7 ] );
		}

	}
	
	if ( player_info [ 4 ] == 27 ) // if the player lands on square 27
	{
		
		if ( player_info [ 6 ] == 0 ) // if the player doesn't have a dog
		{
			cout << endl << "Avoided Event" << endl; // do nothing
		}
		
		else // if the player has at least one dog
		{
			cout << endl << "Reward: If you have a dog, it keeps "
				"you calm through finals -- gain $" << 300 * player_info [ 6 ] 
				<< endl;
			// add 300 * number of dogs to the player's balance
			player_info [ 0 ] += ( 300 * player_info [ 6 ] );
		}

	}
	
	if ( player_info [ 4 ] == 28 ) // if the player lands on square 28
	{
	
		if ( player_info [ 7 ] == 0 ) // if the player doesn't have any cats
		{
			cout << endl << "Avoided Event" << endl; // do nothing
		}
	
		else // if the player has at least one cat
		{
			cout << endl << "Reward: If you have a cat, it keeps you " <<
				"calm through finals -- gain $" << 300 * player_info [ 7 ] 
				<< endl;
			// add 300 * number of cats to the player's balance
			player_info [ 0 ] += ( 300 * player_info [ 7 ] );
		}

	}

	if ( player_info [ 4 ] == 29 ) // if the player lands on square 29
	{
		cout << endl << "Penalty: Your computer crashed when you worked on "
			<< "your final paper -- pay $3500" << endl;
		player_info [ 0 ] -= 3500; // subtract 3500 from the player's balance
	}

	if ( player_info [ 4 ] == 30 ) // if the player lands on square 30
	{
		cout << endl << "Payday" << endl;
	}

	if ( player_info [ 4 ] == 31 ) // if the player lands on square 31
	{
		cout << endl << "Reward: Job offer -- gain $5000" << endl;
		player_info [ 0 ] += 5000; // add 5000 to the player's balance
	}

	if ( player_info [ 4 ] == 32 ) // if the player lands on square 32
	{
	
		if ( player_info [ 1 ] > 0 ) // if the player has debt
		{
			cout << endl << "Penalty: Interest Due. Pay $100 for every "
				<< "$2,000 owed in debt -- pay " << ( player_info [ 1 ] / 20 )
				<< endl;
			// subtract the player's debt divided by 20
			player_info [ 0 ] -= ( player_info [ 1 ] / 20 );
		}
	
		else // if the player has no debt
		{
			cout << endl << "Avoided Event" << endl;
		}

	}

	if ( player_info [ 4 ] == 33 ) // if the player lands on square 33
	{
		cout << endl << "Reward: Sold a project to a company -- gain $10000"
			<< endl;
		player_info [ 0 ] += 10000; // add 10000 to the player's balance
	}

	if ( player_info [ 4 ] == 34 ) // if the player lands on square 34
	{
		cout << endl << "Penalty: Sickness due to final exam stress -- pay "
			<< "$1000" << endl;
		player_info [ 0 ] -= 1000; // subtract 1000 from the player's balance
	}

	return;
}


/** ***************************************************************************
 * @author N. Johnson
 *
 * @par Description:
 * A sorting system to call the proper consequence function given what square 
 * the player is on. 
 *
 * @param[in, out] player_info - array to hold the player's information
 *
 * @returns void
 *****************************************************************************/

void square_events ( int player_info [ ] )
{
	
	if ( player_info [ 4 ] < 12 ) // if the player is between squares 0 and 11
	{
		square0_11 ( player_info );
	}

	// if the player is between squares 12 and 23
	else if ( player_info [ 4 ] >= 12 && player_info [ 4 ] < 24 )
	{
		square12_23 ( player_info ); 
	}
	
	// if the player is between squares 24 and 34
	else if ( player_info [ 4 ] >= 24 && player_info [ 4 ] < 35 )
	{
		square24_34 ( player_info );
	}

	return;
}