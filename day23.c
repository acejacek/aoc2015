#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INPUT_FILE "day23.txt"

// change for part 2
#define PART 1

typedef enum { REGISTER_A, REGISTER_B, EMPTY } RegisterID;

typedef struct 
{
    size_t register_a;
    size_t register_b;
    size_t program_counter;
} Computer;

typedef struct
{
    int instr_id;
    RegisterID register_id;
    int param;
} Instruction;

void check_alloc (void* p)
{
    if (p != NULL) return;

    fprintf (stderr, "Can't allocate memory!\n");
    exit (EXIT_FAILURE);
}

void init_computer(Computer* c)
{
#if PART == 2
    c->register_a = 1;
#else
    c->register_a = 0;
#endif
    c->register_b = 0;
    c->program_counter = 0;
}

void instr_hlf(Computer* c, const int r, const int l)
{
    if (r == REGISTER_A)
        c->register_a /= 2;
    else
        c->register_b /= 2;

    c->program_counter++;
}

void instr_tpl(Computer* c, const int r, const int l)
{
    if (r == REGISTER_A)
        c->register_a *= 3;
    else
        c->register_b *= 3;

    c->program_counter++;
}

void instr_inc(Computer* c, const int r, const int l)
{
    if (r == REGISTER_A)
        c->register_a++;
    else
        c->register_b++;

    c->program_counter++;
}

void instr_jmp(Computer* c, const int r, const int offset)
{
        c->program_counter += offset;
}

void instr_jie(Computer* c, const int r, const int offset)
{
    switch (r)
    {
        case REGISTER_A:
            if (c->register_a % 2 == 0)
                c->program_counter += offset;
            else
                c->program_counter++;
            break;

        case REGISTER_B:
            if (c->register_b % 2 == 0)
                c->program_counter += offset;
            else
                c->program_counter++;
            break;
    }
}

void instr_jio(Computer* c, const int r, const int offset)
{
    switch (r)
    {
        case REGISTER_A:
            if (c->register_a == 1)
                c->program_counter += offset;
            else
                c->program_counter++;
            break;

        case REGISTER_B:
            if (c->register_b == 1)
                c->program_counter += offset;
            else
                c->program_counter++;
            break;
    }
}

int main(void)
{
    const char filename[] = INPUT_FILE;
    FILE* input = fopen (filename, "r");
    if (!input)
    {
        fprintf (stderr, "Can't load file %s.\n", filename);
        exit (EXIT_FAILURE);
    } 

    char* line = NULL;
    size_t len = 0;

    Computer computer;
    init_computer(&computer);

    Instruction* program = NULL;
    int instr_counter;
    
    void (*instr[6])(Computer*, const int, const int);
    instr[0] = &instr_hlf;
    instr[1] = &instr_tpl;
    instr[2] = &instr_inc;
    instr[3] = &instr_jmp;
    instr[4] = &instr_jie;
    instr[5] = &instr_jio;

    for (instr_counter = 0; (getline (&line, &len, input)) != -1; ++instr_counter)
    {
        program = realloc(program, sizeof(Instruction) * (instr_counter + 1));
        check_alloc (program);

        int ind = 2;
        switch (line[ind])
        {
            case 'f':
                program[instr_counter].instr_id = 0;
                break;
            case 'l':
                program[instr_counter].instr_id = 1;
                break;
            case 'c':
                program[instr_counter].instr_id = 2;
                break;
            case 'p':
                program[instr_counter].instr_id = 3;
                break;
            case 'e':
                program[instr_counter].instr_id = 4;
                break;
            case 'o':
                program[instr_counter].instr_id = 5;
                break;
            default:
                fprintf(stderr, "Unknown instruction in line %s", line);
                goto dispose;
        }

        ind = 4;
        if (line[ind] == 'a')
        {
            program[instr_counter].register_id = REGISTER_A;
            ind++;
        }
        else if (line[ind] == 'b')
        {
            program[instr_counter].register_id = REGISTER_B;
            ind++;
        }

        if (line[ind] == ',')
            ind += 2;

        program[instr_counter].param = atoi(line + ind);
    }

    // program loop
    for (int i = 0; i < instr_counter;)
    {
        instr[program[i].instr_id] (&computer, program[i].register_id, program[i].param);
        i = computer.program_counter;
    }

    printf("Computer status:\nregister A: %ld\nregister B: %ld\n", computer.register_a, computer.register_b);

dispose:
    fclose(input);
    free(line);
    free(program);
    return 0;
}
