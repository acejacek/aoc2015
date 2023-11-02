#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define INPUT_FILE "day7.txt"

// uncomment for part 2
//#define PART_TWO
#define PART_ONE_RESULT 46065

typedef enum { AND, OR, LSHIFT, RSHIFT, NOT, DIRECT } Function;

typedef struct Node {
    char wire[3];
    Function function;
    unsigned short value;
    char input_a[5];
    char input_b[5];
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

unsigned short calculate(char* gate)
{
    // replace value of wire B with results from part 1
#ifdef PART_TWO
    if (strcmp(gate, "b") == 0) return (unsigned short) PART_ONE_RESULT;
#endif

    if (isdigit(gate[0])) return (unsigned short) atoi(gate); //it's number

    int i = 0;
    for(; strcmp(node[i].wire, gate) != 0 && i < n; ++i);
    if (i == n)
    {
        fprintf(stderr, "Can't find wire %s\n", gate);
        exit(EXIT_FAILURE);
    }

    if (node[i].calculated) return node[i].value;

    switch (node[i].function)
    {
        case DIRECT:
            node[i].value = calculate(node[i].input_a);
            break;

        case AND:
            node[i].value = calculate(node[i].input_a) & calculate(node[i].input_b);
            break;

        case OR:
            node[i].value = calculate(node[i].input_a) | calculate(node[i].input_b);
            break;

        case NOT:
            node[i].value = ~ calculate(node[i].input_a);
            break;

        case LSHIFT:
            node[i].value = calculate(node[i].input_a) << atoi(node[i].input_b);
            break;

        case RSHIFT:
            node[i].value = calculate(node[i].input_a) >> atoi(node[i].input_b);
            break;

        default:
            fprintf(stderr, "Unknown case\n");
            exit(EXIT_FAILURE);
    }
    node[i].calculated = 1;

    return (unsigned short) node[i].value; 
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
            if (strcmp(tmp, "->") == 0)         // single input
                node[n].function = DIRECT;
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
        n++;
    }

    printf("Result: %d\n", calculate("a"));

    fclose(input);
    free(line);
    free(node);

    return 0;
}
