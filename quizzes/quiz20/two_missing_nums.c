#include <stdio.h>

/* Returns the sum of the array */
int getSum(int arr[], int n)
{
    int sum = 0;
    int i;
    for (i = 0; i < n; i++)
    {
        sum += arr[i];
    }
    return sum;
}

/* Function to find two missing numbers in range [1, n] */
void findTwoMissingNumbers(int arr[], int n)
{
    int sum, avg;
    int sumSmallerHalf = 0, sumGreaterHalf = 0;
    int i;
    int totalSmallerHalf, smallerElement;

    /* Sum of 2 Missing Numbers */
    sum = (n * (n + 1)) / 2 - getSum(arr, n - 2);

    /* Find average of two elements */
    avg = sum / 2;

    /* Find sum of elements smaller than avg and greater than avg */
    for (i = 0; i < n - 2; i++)
    {
        if (arr[i] <= avg)
            sumSmallerHalf += arr[i];
        else
            sumGreaterHalf += arr[i];
    }

    printf("Two Missing Numbers are\n");

    /* The first (smaller) missing number */
    totalSmallerHalf = (avg * (avg + 1)) / 2;
    smallerElement = totalSmallerHalf - sumSmallerHalf;
    printf("%d ", smallerElement);

    /* The second (larger) missing number */
    printf("%d\n", sum - smallerElement);
}

int main()
{
    int arr[] = {1, 3, 5, 6};
    int n = 2 + (sizeof(arr) / sizeof(arr[0])); /* Range of numbers is 2 plus size of array */

    findTwoMissingNumbers(arr, n);

    return 0;
}
