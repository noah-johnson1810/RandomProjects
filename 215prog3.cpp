/** ***************************************************************************
 * @file
 *
 * @brief The only .cpp file for program 3
 *****************************************************************************/

/** **************************************************************************
 * 
 * @mainpage Program 3 - Knight's Tour
 *
 * @section course_section Course Information
 *
 * @author Noah Johnson
 *
 * @par Professor:
 *         Roger L. Schrader
 *
 * @par Course:
 *         CSC215 - M001 - Programing Techniques
 *
 * @par Location:
 *         McLaury - M306
 *
 * @date Due 4/30/2021
 *
 * @section program_section Program Information
 *
 * @details
 * This program receives the input of a board size and starting square, and shows
 * one solution to the "knight's tour" - which is to make a knight land on each
 * square of the board exactly once, with no backtracks and without landing on 
 * the same square twice. It can either be run via a menu system in the console
 * output, or a file can be inputted containing the tours to be solved, in which 
 * case the solutions will be outputted to a file named solutions.tours. 
 * 
 * If the menu system is selected, the menu will allow the user to change the 
 * board size and starting location. When the user is satisfied with the 
 * board size and location, they can choose to solve the tour and exit, in which
 * case the solved tour (if one is found) will be outputted to the console and 
 * the program will close with a return value of 0. 
 
 * It solves the problem recursively, calling solveTour over and over until it 
 * reaches the nxnth place, then it returns and prints the solution. It's a 
 * brute force algorithm, so I made it favor the upper right location and move
 * in a clockwise direction after that, trying all permutation of the 
 * possibilites from that square. 
 * 
 *
 *
 * @section compile_section Compiling and Usage
 *
 * @par Compiling Instructions:
 *
 * @par Usage:
   @verbatim
   c:\> prog3.exe
            run with the menu system, don't use any command line arguments
   c:\> prog3.exe inputfile 
            inputfile  - text file containing integers of the tours to solve. 
    @endverbatim

 * @section todo_bugs_modification_section Todo, Bugs, and Modifications
 *
 * @bug No bugs found at this time. 
 *
 * @todo
 *
 * @par Modifications and Development Timeline:
 * <a target="_blank"
 * href="https://gitlab.mcs.sdsmt.edu/7507264/csc215s21programs/-/tree/master/prog3">
 * Gitlab commit log</a>
 *
 *****************************************************************************/


// include and using statements
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <iomanip>
#include <vector>
#include <string>
using namespace std;


// function declarations
void changeLocation(int rows, int& srow, int& scol);
void displayMenu(int size, int srow, int scol, ofstream& fout);
void initializeArray(int size, int srow, int scol, ofstream& fout,
    char mode, int tourNum);
void printTour(int**& arr, char mode, int size, bool& solved, 
    ofstream& fout, int count, int row, int col, int num);
void resizeBoard(int& size, int srow, int scol);
void solveTour(int size, int row, int col, int count, int**& arr, bool& solved, 
    ofstream& fout, char mode, int srow, int scol, int tourNum);
void toursFromFile(ifstream& fin, ofstream& fout);



/** ***************************************************************************
 * @author Noah Johnson
 *
 * @par Description:
 * 
 * If command line arguments are correct and files are opened,
 * begins the process by calling either displayMenu (no input file)
 * or toursFromFile (input file).
 * 
 * @param[in]     argc - holds the number of command line arguments
 * @param[in]     argv - holds the command line arguments
 *
 * @returns 0 - program ran succesfully
 * @returns 1 - incorrect commandline arguments
 * @returns 2 - error opening file
 *
 *****************************************************************************/
int main(int argc, char** argv)
{
    ifstream fin;
    ofstream fout;
    int sRow = 2; // starting x-coordinate
    int sCol = 4; // starting y-coordinate
    int size = 5;

    if (argc == 2) // file is provided
    {

        fin.open(argv[1]); // attempt to open input file
        if (!fin.is_open())
        {
            cout << "Unable to open input file" << endl;
            return 2; // fail
        }
        fout.open("solutions.tours", ios::app); // attempt to open output file
        if (!fout.is_open())
        {
            cout << "Unable to open output file" << endl;
            return 2; // fail
        }
        toursFromFile(fin, fout); // call toursFromFile to continue
    }
    else if (argc == 1) // no input file provided
    {
        displayMenu(size, sRow, sCol, fout);
    }
    else // usage statement
    {
        cout << "Usage: " << endl;
        cout << "prog3.exe" << endl;
        cout << "OR" << endl;
        cout << "prog3.exe tourfile";
        return 1; // fail
    }

    return 0; // program ran successfully
}



/** ***************************************************************************
 * @author Noah Johnson
 *
 * @par Description:
 *
 * Function to change starting location. It checks to see if it is less than the
 * board size but greater than 0.
 *
 * @param[in] rows - size of nxn board
 * @param[in, out] srow - starting row
 * @param[in, out] scol - starting column
 *
 * @returns void
 *****************************************************************************/

void changeLocation(int rows, int& srow, int& scol)
{
    int newRow;
    int newCol;
    string arr;

    cout << "Enter starting coordinates [ row, col ]: ";
    cin >> newRow >> newCol; // get user input for coordinates

    // new row and column must be less than n but greater than 0 
    if (newRow < rows && newCol < rows && newRow >= 0 && newCol >= 0)
    {
        srow = newRow;
        scol = newCol;
    }
    else // couldn't change to specified location
    {
        cout << "Cannot change starting location to [" << newRow << ", " << newCol <<
            "] when board size is " << rows << "x" << rows << "." << endl;
        cout << endl;
    }

    return;
}



/** ***************************************************************************
 * @author Noah Johnson
 *
 * @par Description:
 *
 * Menu that allows the user to either 1) change board size, 2) change starting
 * location, or 3) exit and solve tour. The menu will continue being called until
 * the user chooses to exit and solve.
 *
 * @param[in] size - the nxn board size
 * @param[in] srow - the starting row
 * @param[in] scol - the starting column
 * @param[in, out] fout - file output stream
 *
 * @returns void
 *****************************************************************************/

void displayMenu(int size, int srow, int scol, ofstream& fout)
{
    int choice;
    bool solved = false;
    char mode = 'c';

    // initial menu display
    cout << "1) Change Board Size from " << size << "x" << size << endl;
    cout << "2) Change starting location from [" << srow << ", " << scol
        << "]" << endl;
    cout << "3) Exit and Solve Tour" << endl;
    cout << "Enter Choice: ";
    cin >> choice;
    if (choice == 1) // change board size
    {
        resizeBoard(size, srow, scol);
        displayMenu(size, srow, scol, fout);
    }
    else if (choice == 2) // change starting location
    {
        changeLocation(size, srow, scol);
        displayMenu(size, srow, scol, fout);
    }
    else if (choice == 3) // exit and solve tour
    {
        initializeArray(size, srow, scol, fout, mode, 1);
    }
    else // continue displaying the menu until they select exit
    {
        displayMenu(size, srow, scol, fout);
    }
}



/** ***************************************************************************
 * @author Noah Johnson
 *
 * @par Description:
 *
 * Dynamically allocates the 2-d arrays and pads the outer 2 rows and columns
 * with -1's. It then calls solveTour to solve the tour, and if no solution
 * was found, it calls printTour to print the failure message.
 *
 * @param[in] size - size of nxn board
 * @param[in] srow - starting row
 * @param[in] scol - starting column
 * @param[in, out] fout - file stream for tour output
 * @param[in] mode - 'c' for console output, 'f' for file output
 * @param[in] tourNum - the number that this tour is
 *
 * @returns void
 *****************************************************************************/

void initializeArray(int size, int srow, int scol, ofstream& fout, 
    char mode, int tourNum)
{
    int i;
    int j;
    bool solved = false;

    size += 4; // allow for padding with -1's.
    srow += 2;
    scol += 2;


    int** arr = nullptr; 
    arr = new (nothrow) int* [size]; // dynamically allocate array
    if (arr == nullptr) // failure to allocate array
    {
        exit(1);
    }
    for (i = 0; i < size; i++)
    {
        arr[i] = new (nothrow) int[size];
        if (arr[i] == nullptr)
        {
            exit(1);
        }
    }

    for (i = 0; i < size; i++) // fill array 
    {
        for (j = 0; j < 2; j++)
        {
            arr[i][j] = -1;
        }
        for (j = 2; j < size - 2; j++)
        {
            arr[i][j] = 0;
        }
        for (j = size - 2; j < size; j++)
        {
            arr[i][j] = -1;
        }
    }

    for (i = 0; i < 2; i++) // pad first two rows
    {
        for (j = 0; j < size; j++)
        {
            arr[i][j] = -1;
        }
    }
    for (i = size - 2; i < size; i++) // pad last two rows
    {
        for (j = 0; j < size; j++)
        {
            arr[i][j] = -1;
        }
    }
    // call solveTour to solve the tour now that it's been initialized
    solveTour(size, srow, scol, 1, arr, solved, fout, mode, 
        srow - 4, scol - 4, tourNum);
    // if no tour was found
    if (solved == false)
    {
        if (mode == 'f')
        {
            printTour(arr, 'f', size, solved, fout, 0, srow - 4, 
                scol - 4, tourNum);
        }
        else
        {
            printTour(arr, 'c', size, solved, fout, 0, srow - 4, 
                scol - 4, tourNum);
        }
    }
    delete[] arr; // free up memory

    return;
}



/** ***************************************************************************
 * @author Noah Johnson
 *
 * @par Description:
 *
 * Function to print the tour to the correct location (console or file). It
 * formats the tour into neat, indented columns, and displays the tour # as 
 * well as the dimensions of the board and starting location. If there are 
 * already tours in the output file, it will append the new tours to the end
 * of the file, starting the count over at 1. 
 *
 * @param[in] arr - array containing the solution
 * @param[in] mode - 'c' for console output, 'f' for file output
 * @param[in] size - size of nxn board
 * @param[in, out] solved - whether or not a solution was found
 * @param[in, out] fout - file output stream
 * @param[in, out] count - the number of items in array
 * @param[in] row - starting row
 * @param[in] col - starting column
 * @param[in] num - number of tour
 *
 * @returns void
 *****************************************************************************/
void printTour(int**& arr, char mode, int size, bool& solved,
    ofstream& fout, int count, int row, int col, int num)
{
    int i;
    int j;

    if (mode == 'c') // console output
    {
        
        cout << endl << "Tour # " << num << endl;

        cout << setw(6) << " " << (size-4) << " x " << (size-4) << " starting at (" 
            << row+2 << ", " << col+2 << ")" << endl;
        cout << endl;
        if (solved == false)
        {
            cout << "No solutions for this case." << endl;
            cout << endl;
            return;
        }

        // output board
        for (i = 2; i < size-2; i++)
        {
            for (j = 2; j < size-2; j++)
            {
                if (j == 2)
                {
                    cout << setw(6) << " ";
                }
                cout << setw(2) << arr[i][j] << " ";
            }
            cout << endl;
        }
        cout << endl;
    }
    else if (mode == 'f') // file output
    {
        // tour information
        fout << endl << "Tour # " << num << endl;
        fout << setw(6) << " " << (size - 4) << " x " 
            << (size - 4) << " starting at (" 
            << row + 2 << ", " << col + 2 << ")" << endl;
        fout << endl;

        // unable to solve tour
        if (solved == false)
        {
            fout << "No solutions for this case." << endl;
            fout << endl;
            return;
        }

        // output board
        for (i = 2; i < size - 2; i++)
        {
            for (j = 2; j < size - 2; j++)
            {
                if (j == 2)
                {
                    fout << setw(6) << " ";
                }
                fout << setw(2) << arr[i][j] << " ";
            }
            fout << endl;
        }
        fout << endl;
    }

    return;
}



/** ***************************************************************************
 * @author Noah Johnson
 *
 * @par Description:
 *
 * Function to resize the nxn board for the tours. It must be greater than 3,
 * and it does error checking to see if it is a valid change given the starting
 * location.
 *
 * @param[in, out] size - size of nxn board
 * @param[in] srow - starting row
 * @param[in] scol - starting column
 *
 * @returns void
 *****************************************************************************/

void resizeBoard(int& size, int srow, int scol)
{
    int newSize;
    cout << "Enter the size of the NxN Board(> 3) : ";
    cin >> newSize;
    if (newSize <= 3) // size must be greater than 3
    {
        cout << "Must resize board to a value greater than 3." << endl;
        cout << endl;
        return;
    }
    // size must be greater than the starting row and column
    else if (newSize > srow && newSize > scol)
    {
        size = newSize;
        return;
    }
    else // couldn't change to specified board size
    {
        cout << "Cannot change board size to " << newSize << "x" << newSize <<
            " when starting position is [" << srow << ", " << scol
            << "]." << endl;
        cout << endl;
        return;
    }
}



/** ***************************************************************************
 * @author Noah Johnson
 *
 * @par Description:
 *
 * Recursive function to solve the knight's tour. The base case is if the number
 * of times it's been called is equal to the size of the chess board. Then, it 
 * tries every possible sequence of moves from the starting square until it finds
 * a solution. It "prefers" the 2-up 1-right step and moves clockwise, testing 
 * positions in that order. When it finds a solution, it calls printTour. 
 *
 * @param[in] size - size of nxn board
 * @param[in] row - current row to try
 * @param[in] col - current column to try
 * @param[in, out] count - the number of items in array
 * @param[in] arr - array containing the solution
 * @param[in, out] fout - file output stream
 * @param[in, out] solved - whether or not a solution was found
 * @param[in] mode - 'c' for console output, 'f' for file output
 * @param[in] srow - starting row
 * @param[in] scol - starting column
 * @param[in] tourNum - number of tour
 *
 * @returns void
 *****************************************************************************/

void solveTour(int size, int row, int col, int count, int**& arr, bool& solved, 
    ofstream& fout, char mode, int srow, int scol, int tourNum)
{
    // base case, if the whole board is filled
    if (count == ( (size-4) * (size-4) )+1)
    {
        solved = true;
        printTour(arr, mode, size, solved, fout, count, srow, scol, tourNum);
    }

    // recursive calls
    if (arr[row][col] == 0 && solved == false)
    {
        arr[row][col] = count;
        solveTour(size, row - 2, col + 1, count + 1, arr, solved, fout, mode,
            srow, scol, tourNum);
        if (solved == false)
            solveTour(size, row - 1, col + 2, count + 1, arr, solved, fout,
                mode, srow, scol, tourNum);
        if (solved == false)
            solveTour(size, row + 1, col + 2, count + 1, arr, solved, fout,
                mode, srow, scol, tourNum);
        if (solved == false)
            solveTour(size, row + 2, col + 1, count + 1, arr, solved, fout,
                mode, srow, scol, tourNum);
        if (solved == false)
            solveTour(size, row + 2, col - 1, count + 1, arr, solved, fout,
                mode, srow, scol, tourNum);

        if (solved == false)
            solveTour(size, row + 1, col - 2, count + 1, arr, solved, fout,
                mode, srow, scol, tourNum);
        if (solved == false)
            solveTour(size, row - 1, col - 2, count + 1, arr, solved, fout,
                mode, srow, scol, tourNum);
        if (solved == false)
            solveTour(size, row - 2, col - 1, count + 1, arr, solved, fout,
                mode, srow, scol, tourNum);

        arr[row][col] = 0;
    }

    return;
}


/** ***************************************************************************
 * @author Noah Johnson
 *
 * @par Description:
 *
 * This function reads in and calls solveTour if there is an input file 
 * provided. 
 *
 * @param[in, out] fin - file stream to read in tours
 * @param[in, out] fout - file stream to output tours
 *
 * @returns void
 *****************************************************************************/
void toursFromFile(ifstream& fin, ofstream& fout)
{
    int temp;
    int count = 0;
    vector<int> data;
    int size;
    int row;
    int col;
    int i = 2;
    char mode = 'f';
    int tourNum = 1;

    // read in integers from file
    while (fin >> temp)
    {
        data.push_back(temp);
        count++;
    }

    // translate data into tours and solve them
    while (i < count)
    {
        size = data[i - 2];
        row = data[i - 1];
        col = data[i];
        initializeArray(size, row, col, fout, mode, tourNum);
        tourNum++;
        i += 3;
    }
    
    return;
}