#include <stdio.h>
#include <string.h>

void ReverseWords(char* str);
void ReverseString(char* start, char* end);
char* GetWordEnd(char* word);

int main()
{
    char words[] = "i am student";


    printf("before: %s\n", words);
    ReverseWords(words);
    printf("after: %s\n", words);
    return 0;
}

void ReverseWords(char* str)
{
    char* start_runner = str;
    char* end_runner = str + (strlen(str) - 1);

    ReverseString(start_runner, end_runner);

    while( '\0' != *end_runner) /* reverse each word until at \0 (including)*/
    {
        end_runner = GetWordEnd(start_runner);
        ReverseString(start_runner, end_runner);
        ++end_runner;
        if(' ' == *end_runner) /*otherwise its \0 and that means we end */
        {
            ++end_runner;
            start_runner = end_runner;
        }
    }
}

void ReverseString(char* start, char* end)
{
    char tmp = 0;
    while(start < end)
    {
        tmp = *start;
        *start = *end;
        *end = tmp;
        ++start;
        --end;
    }
}

char* GetWordEnd(char* word)
{
    while(*(word + 1) != '\0' && (*(word + 1) != ' '))
    {
        ++word;
    }
    return (word);
}