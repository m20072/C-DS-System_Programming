#include <signal.h>
#include <stdio.h>

#define MAX3(a,b,c) ((a > b) ? ((a > c) ? a : c ) : ((b > c) ? b : c ))
#define TO_LOWER(a) (a|32)
#define OFFSET(s, f) ((size_t)&((s*)0)->c)

struct test
{
    int a;
    int b;
    int c;
};

struct s
{
    int num;
    char ch1;
    int* ptr;
    char ch2;
};

union u
{
    int num;
    char arr[5];
};

int main()
{
    printf("MAX3(1,2,3): %d\n", MAX3(1,2,3));
    printf("MAX3(2,3,1): %d\n", MAX3(2,3,1));
    printf("MAX3(3,1,2): %d\n", MAX3(3,1,2));
    printf("lowercase on A: %c\n", TO_LOWER('A'));
    printf("struct test with 3 ints a,b,c. offset of c: %lu \n", OFFSET(struct test, c));
    printf("sizeof struct s: %lu\n", sizeof(struct s));
    printf("sizeof union u: %lu\n", sizeof(union u));
    return 0;
}