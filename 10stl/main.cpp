#include <iostream>

static int times = 0;

void funcc(int *A, int low, int high)
{
    int i = low;
    int j = high;
    int x = A[(low + high) / 2];
    times++;
    std::cout << "i-j: " << i << " - " << j << " times: " << times << std::endl;
    do
    {
        while (A[i] < x)
            ++i;
        while (A[j] > x)
            --j;
        if (i <= j)
        {
            int temp = A[i];
            A[i] = A[j];
            A[j] = temp;
            i++;
            j--;
        }
    } while (i < j);
    if (low < j) // recursion
        funcc(A, low, j);
    if (i < high) // recursion
        funcc(A, i, high);
}

// func(a,0,9);
// i:0 j:9 x: A[4]

int main()
{
    int arr[] = {31, 30, 29, 28, 27, 26, 25, 24, 23, 22, 21, 20, 19, 18, 17, 16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0};
    funcc(arr, 0, 32);

    // int arr[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31};
    // funcc(arr, 0, 32);
    // int arr[] = {1, 2, 3, 4, 5, 6, 7};
    // funcc(arr, 0, 6);
}