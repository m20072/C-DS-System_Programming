#include <stdio.h>
#include <stdlib.h>

/* Function to find two missing numbers in range [1, n] */
void findTwoMissingNumbers(int arr[], int n)
{
    int XOR = 0, set_bit_no, x = 0, y = 0;
    int i;

    /* Get the XOR of all elements in arr[] and {1, 2 .. n} */
    for (i = 0; i < n - 2; i++)
    {
        XOR ^= arr[i];
    }
    for (i = 1; i <= n; i++)
    {
        XOR ^= i;
    }

    /* Get a set bit of XOR (rightmost set bit) */
    set_bit_no = XOR & ~(XOR - 1);

    /* Divide elements in two sets based on set_bit_no */
    for (i = 0; i < n - 2; i++)
    {
        if (arr[i] & set_bit_no)
        {
            x ^= arr[i]; /* XOR of first set in arr[] */
        }
        else
        {
            y ^= arr[i]; /* XOR of second set in arr[] */
        }
    }
    for (i = 1; i <= n; i++)
    {
        if (i & set_bit_no)
        {
            x ^= i; /* XOR of first set in arr[] and {1, 2, ...n } */
        }
        else
        {
            y ^= i; /* XOR of second set in arr[] and {1, 2, ...n } */
        }
    }

    printf("Two Missing Numbers are %d %d\n", x, y);
}

int main()
{
    int arr[] = {1, 3, 5, 6};

    /* Range of numbers is 2 plus size of array */
    int n = 2 + (sizeof(arr) / sizeof(arr[0]));

    findTwoMissingNumbers(arr, n);

    return 0;
}
