#include <stdio.h>
#include <string.h>
#include <conio.h>
#include "util/Queue.h"
#include "util/Stack.h"

#define MAX 65536
#define CTOI(x) (x) - '0'

int findEndOfLoop(int fp, char program[], char start, char end) {
    int num = 1;
    while (1) {
        int c = program[fp];
        if (c == start) {
            num++;
        } else if (c == end) {
            num--;
        }
        if (num == 0) {
            return fp;
        }
        fp++;
    }
}

int findStartOfLoop(int fp, char program[], char start, char end) {
    int num = 0; // starts on backslash
    while (1) {
        int c = program[fp];
        if (c == end) {
            num++;
        } else if (c == start) {
            num--;
        }
        if (num == 0) {
            return fp;
        }
        fp--;
    }
}

int main(int argc, char *argv[]) {
    char program[MAX];
    char c;

    memset(program, 0, MAX);

    FILE *in = fopen(argv[1], "r");
    for (int i = 0; (c=fgetc(in)) != EOF; i++) program[i] = c; 
    fclose(in);

    int registers[10];
    memset(registers, 0, sizeof(registers));

    int fp = 0;
    int *reg1;
    int *reg2;
    struct Queue *queue = createQueue_queue(MAX);
    struct Stack *stack = createStack_stack(MAX);
    while (fp < strlen(program)) {
        c = program[fp];
        switch (c) {
        case 'a': ;
            reg1 = &registers[CTOI(program[++fp])];
            *reg1 = (*reg1) + registers[CTOI(program[++fp])];
            break;
        case 'b': ;
            reg1 = &registers[CTOI(program[++fp])];
            if ((*reg1) >= 128) {
                *reg1 = 255;
            } else {
               *reg1 = 0;
            }
            break;
        case 'c': ;
            reg1 = &registers[CTOI(program[++fp])];
            *reg1 = *reg1 - 1;
            break;
        case 'd': ;
            reg1 = &registers[CTOI(program[++fp])];
            *reg1 = (*reg1) / registers[CTOI(program[++fp])];
            break;
        case 'e': ;
            reg1 = &registers[CTOI(program[++fp])];
            *reg1 = registers[CTOI(program[++fp])];
            break;
        case 'f': ;
            if (program[++fp] == 'o') {
                reg1 = &registers[CTOI(program[++fp])];
                if (*reg1 == 0) {  // Jump to end of loop
                    fp = findEndOfLoop(fp, program, 'f', '?');
                }
            } else {
                reg1 = &registers[CTOI(program[++fp])];
                if (*reg1 != 0) {  // Jump to end of loop
                    fp = findEndOfLoop(fp, program, 'f', '?');
                }
            }
            break;
        case 'g': ;
            reg1 = &registers[CTOI(program[++fp])];
            reg2 = &registers[CTOI(program[++fp])];
            int tmp = *reg1;
            *reg1 = *reg2;
            *reg2 = tmp;
            break;
        case 'h':
            reg1 = &registers[CTOI(program[++fp])];
            reg2 = &registers[CTOI(program[++fp])];
            *reg1 = *reg1 % *reg2;
            break;
        case 'i':
            reg1 = &registers[CTOI(program[++fp])];
            *reg1 = *reg1 + 1;
            break;
        case 'j': // todo
            reg1 = &registers[CTOI(program[++fp])];
            fp += *reg1 - 1;
            break;
        case 'k':
            reg1 = &registers[CTOI(program[++fp])];
            *reg1 = dequeue_queue(queue);
            break;
        case 'l':
            if (program[++fp] == 'o') {
                reg1 = &registers[CTOI(program[++fp])];
                if (*reg1 == 0) {  // Jump to end of loop
                    fp = findEndOfLoop(fp, program, 'l', '/');
                }
            } else {
                reg1 = &registers[CTOI(program[++fp])];
                if (*reg1 != 0) {  // Jump to end of loop
                    fp = findEndOfLoop(fp, program, 'l', '/');
                }
            }
            break;
        case 'm':
            reg1 = &registers[CTOI(program[++fp])];
            reg2 = &registers[CTOI(program[++fp])];
            *reg1 = *reg1 * *reg2;
            break;
        case 'n':
            reg1 = &registers[CTOI(program[++fp])];
            reg2 = &registers[CTOI(program[++fp])];
            *reg1 = *reg1 & *reg2;
            break;
        case 'o':
            reg1 = &registers[CTOI(program[++fp])];
            reg2 = &registers[CTOI(program[++fp])];
            *reg1 = *reg1 | *reg2;
            break;
        case 'p':
            reg1 = &registers[CTOI(program[++fp])];
            *reg1 = pop_stack(stack);
            break;
        case 'q':
            reg1 = &registers[CTOI(program[++fp])];
            enqueue_queue(queue, *reg1);
            break;
        case 'r':
            reg1 = &registers[CTOI(program[++fp])];
            printf("Character input: ");
            fflush(stdout);
            *reg1 = getch();
            printf("\n");
            break;
        case 't':
            exit(0);
            break;
        case 'u':
            reg1 = &registers[CTOI(program[++fp])];
            push_stack(stack, *reg1);
            break;
        case 'v':
            reg1 = &registers[CTOI(program[++fp])];
            int p2 = fp;
            char buf[MAX];
            while (program[p2] != '-') {
                buf[p2 - fp] = program[p2];
                p2++;
            }
            *reg1 = atoi(buf);
            fp = p2;
            break;
        case 'w':
            reg1 = &registers[CTOI(program[++fp])];
            printf("%c\n", (char)*reg1);
            break;
        case 'x':
            reg1 = &registers[CTOI(program[++fp])];
            reg2 = &registers[CTOI(program[++fp])];
            *reg1 = *reg1 ^ *reg2;
            break;
        case 'y':  // cycle registers array reg1 times
            reg1 = &registers[CTOI(program[++fp])];
            int reg1_val = *reg1;
            for (int i = 0; i < reg1_val; i++) {
                int r9 = registers[9];
                for(int j = 9-1; j > 0; j--)
                {
                    registers[j] = registers[j-1];
                }
                registers[0] = r9;
            }
            break;
        case 'z':
            reg1 = &registers[CTOI(program[++fp])];
            *reg1 = 0;
            break;
        case '|':  // todo: tape
            if (program[++fp] == '<') {

            }
        case '\\': // todo: infinite loop

        case '/':
            fp = findStartOfLoop(fp, program, '/', 'l') - 1;
        case '?':
        case '-':
        default:
            break;
        }
        
        fp++;
    }
    for (int i = 0; i < 10; i++) printf("Register %d: %d\n", i, registers[i]);

    printf("\n");
}
