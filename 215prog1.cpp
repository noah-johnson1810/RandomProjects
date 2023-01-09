/** **************************************************************************
 * @file
 ****************************************************************************/
 /** **************************************************************************
  * @mainpage Program 1 - Record Sorting
  *
  * @section course_section Course Information
  *
  * @author Noah Johnson    
  *
  * @par Professor:
  *         Roger Schrader
  *
  * @par Course:
  *         CSC215-M001 - Computer Science 2
  *
  * @par Location:
  *         McLaury - M306
  *
  * @date Due March 19, 2021
  *
  * @section program_section Program Information
  *
  * @details
  * This program analyzes records, and consists of two parts. Part a consists of
  * numerous tests, which are used by part b to validate a 4-digit zip code,
  * a 5-digit zip code, an address, a call sign, a radio class, a month, a year,
  * a day, a name, and a state. It also contains functions to extract the 4- and 
  * 5-digit zip codes from one packed zip number. It also contains functions to 
  * extract individual years, months, and days from one packed date number.
  * 
  * Part b of the program uses these functions to both test binary record files,
  * and then outputs the results of those tests to two different output files - 
  * one for correct records, and one for records with errors. It checks the name,
  * birth date, license date, address, city, state, zip code, call sign, and radio
  * class, and outputs error messages corresponding to any errors that need to 
  * be fixed. 
  * 
  * 
  * @section compile_section Compiling and Usage
  *
  * @par Compiling Instructions:
  *      none - a straight compile and link with no external libraries.
  *
  * @par Usage:
    @verbatim
    c:\> prog3.exe inputfile outputfile1 outputfile2
             inputfile  - binary file containing records
             outputfile1 - filename to write correct records to
             outputfile2 - filename to write incorrect records to
    @endverbatim
  *
  * @section todo_bugs_modification_section Todo, Bugs, and Modifications
  *
  * @bug
  *
  * @todo
  *
  * @par Modifications and Development Timeline:
  * This is a link to gitlab's commit as an example. To view <a target="_blank"
  * href="https://gitlab.com/gitlab-org/gitlab-ce/commits/master">click here.</a>
  *
  *****************************************************************************/

#define CATCH_CONFIG_RUNNER
#include "prog1.h"
#include "..\\catch.hpp"

  /** ***************************************************************************
   * @brief global constant bool used in CATCH set to true
   *
   *****************************************************************************/
const bool RUNCATCH = true;
void makeCATCH(int &myargc, char **&myargv);

/** ***************************************************************************
 * @author Noah Johnson
 *
 * @par Description:
 * Main opens the three files for reading and writing, then calls readRecord
 * to read in each record. As these records are being read, readRecord calls
 * writeRecord to output them. The three files are then closed. 
 *
 * @param[in] argc - number of arguments
 * @param[in] argv - array containing first the input file, then the correct 
 * records, then the incorrect records
 *
 * @returns 0 - ran successfully
 *
 *****************************************************************************/

int main(int argc, char** argv)
{
    // declare variables here
    ifstream fin;
    ofstream fout1; // perfect records
    ofstream fout2; // records that contain errors


    //////////////////////////////////// Do not edit this section
    int result = 1;
    int myargc;
    char** myargv;
    if (RUNCATCH)
    {
        makeCATCH(myargc, myargv);
        result = Catch::Session().run(myargc, myargv);
        if (result != 0 )
        {
            cout << "You have errors in your functions" << endl;
            return 0;
        }
    }
    //////////////////////////////////// Place your code here

    // write your code here
    if (argc != 4)
    {
        cout << "Usage: prog1.exe inputfile.bin outputfile1.bin outputfile2.txt" << endl;
        return 0; // fail
    }
    fin.open(argv[1], ios::in | ios::binary);
    if (!fin.is_open())
    {
        cout << "Unable to open input file" << endl;
        return 0; // fail
    }
    
    fout1.open(argv[2], ios::out | ios::app | ios::binary);
    if (!fout1.is_open())
    {
        cout << "Unable to open output file 1" << endl;
        return 0; // fail
    }

    fout2.open(argv[3], ios::out);
    if (!fout2.is_open())
    {
        cout << "Unable to open output file 2" << endl;
        return 0; // fail
    }

    readRecord( fin, fout1, fout2 );
    fin.close();
    fout1.close();
    fout2.close();
    return 0;
}