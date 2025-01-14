#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

void PressedA();
void PressedT();
void PressedElse();
void LUT();
void SwitchCase();
void IfElse();


typedef void(*func_ptr_t)();
const char escape = 27;

void PressedA()
{
    printf("A-pressed\n");
}

void PressedT()
{
    printf("T-pressed\n"); 
}

void PressedElse()
{
    /* empty function */
}

/*Reviewed by Denis*/
void LUT()
{
    func_ptr_t func_ptr[256];
    int c;

    for(c=0;c<256;++c)
    {
        func_ptr[c] = &PressedElse;
    }

    func_ptr['A'] = &PressedA;
    func_ptr['a'] = &PressedA;
    func_ptr['T'] = &PressedT;
    func_ptr['t'] = &PressedT;

    do 
    {
        c = getchar();
        func_ptr[c]();

    } while (escape != c);

}

/*Reviewed by denis*/
void SwitchCase()
{
    char c;
    do
    {
    	c = toupper(getchar());
        
        switch(c)
        {
            case 'A':
            case 'T':
                printf("%c-pressed\n", c); 
	}
    }while(escape != c);
}

/*Reviewed by denis*/
void IfElse()
{
    char c;
    do
    {
        c = toupper(getchar());

        if('A' == c || 'T' == c)
        {
            printf("%c-pressed\n", c); 
        }
    } while(escape != c);
}

int main()
{
    system("stty -icanon -echo");

    /*IfElse();*/
    /*SwitchCase();*/
    LUT();

    system("stty icanon echo");
    return 0;
}
