arr[row][col] = count;
solveTour(size, row - 2, col + 1, count + 1, arr, solved);
if (solved == false)
solveTour(size, row - 1, col + 2, count + 1, arr, solved);
if (solved == false)
solveTour(size, row + 1, col + 2, count + 1, arr, solved);
if (solved == false)
solveTour(size, row + 2, col + 1, count + 1, arr, solved);

if (solved == false)
solveTour(size, row + 2, col - 1, count + 1, arr, solved);

if (solved == false)
solveTour(size, row + 1, col - 2, count + 1, arr, solved);
if (solved == false)
solveTour(size, row - 1, col - 2, count + 1, arr, solved);
if (solved == false)
solveTour(size, row - 2, col - 1, count + 1, arr, solved);

arr[row][col] = 0;