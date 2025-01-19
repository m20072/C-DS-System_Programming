#include "struct.h"

int main()
{
    float data_float[1] = { 5.5 };
    data_t data[3]; /* can't init due to float conversion to ptr error (also strdup) */

    data[0].type = INT;
    data[0].data = (void*)5;

    data[1].type = FLOAT;
    data[1].data = *(void**)&data_float[0]; /* float* cast to void**, dereferenced into void* */
                                /* cant (void*)f, error for trying to convert float into ptr */

    data[2].type = STRING;
    data[2].data = strdup("HI");

    Print(data, 3);
    Add(data, 3, 10);
    Print(data, 3);
    CleanUp(data, 3);
    Print(data, 3);
    Add(data, 3, 10);
    Print(data, 3);
    CleanUp(data, 3);
    Add(data, 3, 50);
    Add(data, 3, 20);
    Print(data, 3);
    CleanUp(data, 3);
    Print(data, 3);
    return 0;
}
