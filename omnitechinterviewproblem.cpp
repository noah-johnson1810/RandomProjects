#include <iostream>
#include <ctime>
using namespace std;

int main()
{
    int n = 5;


    srand(time(NULL));
    int correctNum = 2;
    int numCorrect = 0;
    int numIncorrect = 0;
    int hostDoor;
    double percentCorrect;

    for (int i = 0; i < 100000; i++)
    {
        int guess = rand() % n;

        if (guess == correctNum)
        {
            numCorrect++;
        }
        else
        {
            numIncorrect++;
        }
    }

    cout << "Case without switching: " << endl;
    percentCorrect = (double)numCorrect / (double) (numCorrect + numIncorrect);
    cout << "Percent correct: " << percentCorrect << endl;

    numCorrect = 0;
    numIncorrect = 0;

    for (int i = 0; i < 100000; i++)
    {
        int guess2;
        int guess1 = rand() % n;
        if (guess1 == correctNum)
            numIncorrect++;

        else
        {
            do
            {
                hostDoor = rand() % n;
            } while (hostDoor == correctNum || hostDoor == guess1);

            guess2 = rand() % n;
            
            while(guess2 == guess1 || guess2 == hostDoor)
            {
                guess2 = rand() % n;
            }
            if (guess2 == correctNum)
            {
                numCorrect++;
            }
            else
            {
                numIncorrect++;
            }
        }

    }

    cout << "Case with switching: " << endl;
    percentCorrect = (double)numCorrect / (double)(numCorrect + numIncorrect);
    cout << "Percent correct: " << percentCorrect << endl;
}