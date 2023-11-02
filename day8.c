#include <stdio.h>
#include <stdlib.h>

#define INPUT_FILE "day8.txt"

int main()
{
    const char filename[] = INPUT_FILE;
    FILE* input = fopen(filename, "r");
    if (!input)
    {
        fprintf(stderr, "Cant load file %s.\n", filename);
        exit(EXIT_FAILURE);
    }

    char* line = NULL;
    size_t len = 0;
    ssize_t read = 0;

    size_t bytes_of_code = 0;
    size_t bytes_of_memory = 0;
    size_t bytes_encoded = 0;

    while ((read = getline(&line, &len, input)) != -1)
    {
        bytes_of_code += --read;  // remember to ignore EOL

        // calculate part 1

        int i = 0;
        do
        {
            if (line[i] == '"')   // ignore "
            {
                i++;
                continue;
            }
            if (line[i] == '\\')   // skip \, there will be a byte of code after
            {
                i++;
                bytes_of_memory++;

               if ((line[i] == '\\') || (line[i] == '"'))
                {
                    i++;
                    continue;
                }
               if (line[i] == 'x') 
                {
                    i += 3;
                    continue;
                }
            }
            bytes_of_memory++;
            i++;
        } while (i < read);

        // calculate part 2

        bytes_encoded += 2;  // provision for new opening and closing "
        i = 0;
        do
        {
            if (line[i] == '"' || line[i] == '\\')
                bytes_encoded++;

            bytes_encoded++;
            i++;
        } while (i < read);
    }

    fclose(input);
    free(line);

    printf("Total bytes of code: %zd\n", bytes_of_code);
    printf("Total bytes of memory: %zd\n", bytes_of_memory);
    printf("Delta: %zd\n", bytes_of_code - bytes_of_memory);

    printf("\nTotal bytes of encoded text: %zd\n", bytes_encoded);
    printf("Delta: %zd\n", bytes_encoded - bytes_of_code);
    return 0;
}
