/*
Noah Johnson and Drew Norby
CSC315
10/17/2021
Dr. Rohan Loveland
*/


#include "linear_probing.h"
#include <iostream>
using namespace std;


int main()
{
    srand(time(NULL)); // seed for "random" generator
    int val;
    int count;
    int sum = 0;
    double average;

    for (int i = 0; i < 100; i++)
    {
        HashTable<int> H;

        for (int j = 1; j <= 49; j++)
        {
            val = rand() % 999;
            H.insert(val);
        }
        count = 1;
        val = rand() % 999;
        H.insert(val, count);
        sum += count;
    }

    average = (double)sum / 100.000;

    cout << endl << "The average is: " << average << endl;




    return 0;
}

/**
 * Internal method to test if a positive number is prime.
 * Not an efficient algorithm.
 */
bool isPrime(int n)
{
    if (n == 2 || n == 3)
        return true;

    if (n == 1 || n % 2 == 0)
        return false;

    for (int i = 3; i * i <= n; i += 2)
        if (n % i == 0)
            return false;

    return true;
}

/**
 * Internal method to return a prime number at least as large as n.
 * Assumes n > 0.
 */
int nextPrime(int n)
{
    if (n <= 0)
        n = 3;

    if (n % 2 == 0)
        n++;

    for (; !isPrime(n); n += 2)
        ;

    return n;
}

/**
 * A hash routine for string objects.
 */
int hash(const string& key)
{
    int hashVal = 0;

    for (int i = 0; i < key.length(); i++)
        hashVal = 37 * hashVal + key[i];

    return hashVal;
}

/**
 * A hash routine for ints.
 */
int hash(int key)
{
    return key;
}

