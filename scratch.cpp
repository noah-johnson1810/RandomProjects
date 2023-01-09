#include <iostream>
#include <chrono>
using namespace std;
using namespace std::chrono;

int main()
{
    auto start = high_resolution_clock::now();

    int sum = 0;
    int n = 50;

    for (int i = 1; i < n; i++)
    {
        for (int j = 0; j < (i * i); j++)
        {
            if (j % i == 0)
            {
                for (int k = 0; k < j; k++)
                {
                    ++sum;
                }
            }
        }
    }

    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);

    cout << "Time taken: "
        << duration.count() << " microseconds" << endl;

    return 0;
}

