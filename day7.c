#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define INPUT_FILE "day7.txt"

typedef enum { AND, OR, LSHIFT, RSHIFT, NOT, DIRECT } Function;

typedef struct Node {
    char wire[3];
    Function function;
    unsigned short value;
    char input_a[3];
    char input_b[3];
    int calculated;
} Node;

Node* node = NULL;
int n = 0;

void check_alloc(void* p)
{
    if (p != NULL) return;

    fprintf(stderr, "Can't allocate memory!\n");
    exit(EXIT_FAILURE);
}

unsigned short calculate(Node gate)
{
    if (gate.calculated) return gate.value;
    switch (gate.function)
    {
        case DIRECT:
            gate.value = calculate(

    return 0; 
}




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
    while ((read = getline(&line, &len, input)) != -1)
    { 
        node = (Node *) realloc(node, sizeof(Node) * (n + 1));
        check_alloc(node);

        node[n].calculated = 0;

        sscanf(line + read - 3, "%s", node[n].wire);

        char tmp[8] = "";
        if (line[0] == 'N') // NOT
        {
            node[n].function = NOT;
            sscanf(line + 4, "%s", node[n].input_a);
        }
        else
        {
            sscanf(line, "%s %s %s", node[n].input_a, tmp, node[n].input_b);
            if (strcmp(tmp, "->") == 0) // single input
            {
                node[n].input_b[0] = '0';
                node[n].function = DIRECT;
            }
            else if (strcmp(tmp, "AND") == 0)
                node[n].function = AND;
            else if (strcmp(tmp, "OR") == 0)
                node[n].function = OR;
            else if (strcmp(tmp, "LSHIFT") == 0)
                node[n].function = LSHIFT;
            else if (strcmp(tmp, "RSHIFT") == 0)
                node[n].function = RSHIFT;
            else
            {
                fprintf(stderr, "Unknow instruction %s\n", tmp);
                exit(EXIT_FAILURE);
            }
        }
        printf("wire: %s inp1: %s, inpB: %s instr: %s func: %d\n",
                node[n].wire, node[n].input_a, node[n].input_b, tmp, node[n].function);

        if (n > 15)  break;

        n++;
    }


    int i = 0;
    for(; strcmp(node[i].wire, "a") != 0 && i < n; ++i);

    printf ("found a at %d\n", i);

    calculate(node[i]);

    fclose(input);
    free(line);
    free(node);

//    printf("Total area of paper: %zd\n", total_area);
//    printf("Total length of ribbon: %zd\n", ribbon);

    return 0;
}
