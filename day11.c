#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define INPUT "hepxcrrq"

bool has_3_increasing_letters(char* word)
{
    for (int i = 0; i < strlen(word) - 3; ++i)
    {
        char x = word[i];
        if (++x == word[i + 1])
            if (++x == word[i + 2])
                return true;
    }
    return false;
}

bool has_iol(char* word)
{
    for (int i = 0; word[i] != '\0'; ++i)
        if (word[i] == 'l' ||
                word[i] == 'o' ||
                word[i] == 'l')
            return true;

    return false;
}

bool has_2_doubble_letters(char* word)
{
    int dbl = 0;
    char x = '\0';

    for (int i = 0; i < strlen(word) - 1; ++i)
        if (word[i] == word[i + 1]
                && word[i] != x)
        {
            if (++dbl == 2) return true;
            x = word[i++];  // remove duplicates
        }
    return false;
}

void increment_password(char* word)
{
    int last = strlen(word) - 1;
    word[last]++ ;

    for (int i = last; i >= 0; --i)
        if (word[i] > 'z')
        {
            word[i] = 'a';
            word[i - 1]++;
        }
}

void find_new_pass(char* pass)
{
    do
        increment_password(pass);
    while (
            ! has_3_increasing_letters(pass) ||
            has_iol(pass) ||
            ! has_2_doubble_letters(pass)
          );
}

int main(void)
{
    char pass[] = INPUT;

    find_new_pass(pass);
    printf("New pass: %s\n", pass);

    find_new_pass(pass);
    printf("Next pass: %s\n", pass);

    return 0;
}
