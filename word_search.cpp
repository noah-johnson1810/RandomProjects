#include <iostream>
#include <string>
#include <vector> 
using namespace std;

void print(string word, int i, int j, int pos);

int main()
{
    bool solved = false;
    vector<string> v = { "000000000000", "000000000000", "000000000000", "000000000000",
        "0000this0000", "0000wats0000", "0000oahg0000",
        "0000fgdt0000", "000000000000", "000000000000", "000000000000", "000000000000", };
    vector<string> words = { "this", "two", "fat", "fats", "at", "wad", "ad", 
        "hat", "that", "his","is","it","ah" };

    // print initial matrix
    cout << "  ";
    for (int i = 1; i <= 4; i++)
        cout << i << " ";
    cout << endl;

    for (int i = 4; i <= v[1].size() - 5; i++)
    {
        cout << i - 3 << " ";
        for (int j = 4; j < v[1].size() - 4; j++)
        {
            cout << v[i][j] << " ";
        }
        cout << endl;
    }

    cout << endl;

    cout << endl;


    for (int i = 4; i < v[1].size() - 4; i++)
    {
        for (int j = 4; j < v[1].size() - 4; j++)
        {
            for (int k = 0; k < words.size(); k++)
            {
                if (v[i][j] == words[k][0])
                {
                    for (int l = 1; l <= words[k].size()-1; l++)
                    {
                        if (
                            v[i][j + l] != words[k][l] &&
                            v[i][j - l] != words[k][l] &&
                            v[i + l][j] != words[k][l] &&
                            v[i - l][j] != words[k][l] &&
                            v[i - l][j - l] != words[k][l] &&
                            v[i + l][j - l] != words[k][l] &&
                            v[i - l][j + l] != words[k][l] &&
                            v[i + l][j + l] != words[k][l] )
                        {
                            break;
                        }
                        else if (l == words[k].size() - 1)
                        {
                            if (v[i][j+l] == words[k][l])
                            {
                                print(words[k], i - 3, j - 3, 1);
                            }
                            if (v[i][j-l] == words[k][l])
                            {
                                print(words[k], i - 3, j - 3, 2);
                            }
                            if (v[i+l][j] == words[k][l])
                            {
                                print(words[k], i - 3, j - 3, 3);
                            }
                            if (v[i - l][j] == words[k][l])
                            {
                                print(words[k], i - 3, j - 3, 4);
                            }
                            if (v[i - l][j-l] == words[k][l])
                            {
                                print(words[k], i - 3, j - 3, 5);
                            }
                            if (v[i + l][j-l] == words[k][l])
                            {
                                print(words[k], i - 3, j - 3, 6);
                            }
                            if (v[i - l][j + l] == words[k][l])
                            {
                                print(words[k], i - 3, j - 3, 7);
                            }
                            if (v[i + l][j + l] == words[k][l])
                            {
                                print(words[k], i - 3, j - 3, 8);
                            }

                        }
                    }
                }
            }
        }
    }
}


void print(string word, int i, int j, int pos)
{
    cout << "\"" << word << "\"" << " found at position: " << i << ", " << j << endl;
    if (pos == 1)
    {
        cout << "Orientation: " << "left-right" << endl;
        cout << endl;
    }
    if (pos == 2)
    {
        cout << "Orientation: " << "right-left" << endl;
        cout << endl;
    }
    if (pos == 3)
    {
        cout << "Orientation: " << "up-down" << endl;
        cout << endl;
    }
    if (pos == 4)
    {
        cout << "Orientation: " << "down-up" << endl;
        cout << endl;
    }
    if (pos == 5)
    {
        cout << "Orientation: " << "diag: bottom right - top left" << endl;
        cout << endl;
    }
    if (pos == 6)
    {
        cout << "Orientation: " << "diag: top right - bottom left" << endl;
        cout << endl;
    }
    if (pos == 7)
    {
        cout << "Orientation: " << "diag: bottom left - top right" << endl;
        cout << endl;
    }
    if (pos == 8)
    {
        cout << "Orientation: " << "diag: top left - bottom right" << endl;
        cout << endl;
    }
}
