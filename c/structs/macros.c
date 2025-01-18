#include <stdio.h>
#define MAX2(a, b) ((a)<(b)?(b):(a))
#define MAX3(a, b, c) ((a>b)?((a>c)?a:c):((b>c)?b:c))
#define SIZEOF_VAR(x) (unsigned int)((char*)(&x+1) - (char*)&x) /* cast to char to bypass ptr arithmetics of original type */
#define SIZEOF_TYPE(x) (unsigned long)((x*)0+1) /* cast to type* to work with ptr arithmetics, address 0 + 1 gives size */

typedef struct hi
{
int x;
} hi_tt;

typedef struct hi hi_t;

struct hey
{
    int x;
} so; /* can also do so = {5};*/

struct point
{
    int x;
    int y;
};


int main()
{
    int d;
    struct hey hi = so;
    struct point p = {1,2};
    int n = *(int*)&p;
    printf("%d\n", MAX2(1,2));
    printf("%d\n", MAX3(1,2,3));

    printf("%u\n", SIZEOF_VAR(d));
    printf("%lu\n", SIZEOF_TYPE(int));

    printf("%d", n);
    return 0;
}