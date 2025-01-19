#include "struct.h"
#include <stdio.h>
#include <stdlib.h>

int main()
{
    float data_float[1] = { 5.5 };
    mixed_data_t elements[3]; /* can't init due to float conversion to ptr error (also strdup) */

    elements[0].print = &PrintInt;
    elements[0].add = &AddToInt;
    elements[0].clean_up = &IntCleanUp;
    elements[0].data = (void*)5;

    elements[1].print = &PrintFloat;
    elements[1].add = &AddToFloat;
    elements[1].clean_up = &FloatCleanUp;
    elements[1].data = *(void**)&data_float[0]; /* float* cast to void**, dereferenced into void* */
                                /* cant (void*)f, error for trying to convert float into ptr */

    elements[2].print = &PrintString;
    elements[2].add = &AddToStr;
    elements[2].clean_up = &StrCleanUp;
    elements[2].data = strdup("HI");
    
    

    Print(elements, 3);
    Add(elements, 3, 10);
    Print(elements, 3);
    CleanUp(elements, 3);
    Print(elements, 3);
    Add(elements, 3, 10);
    Print(elements, 3);
    CleanUp(elements, 3);
    Add(elements, 3, 50);
    Add(elements, 3, 20);
    Print(elements, 3);
    CleanUp(elements, 3);
    Print(elements, 3);
    return 0;
}
