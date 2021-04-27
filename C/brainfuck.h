#ifndef BrainFuck_h
#define BreinFuck_h

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

typedef struct {
    int isp;
    int cur;
    const char* program;
    size_t array_len;
    uint8_t* data;
}BFState;

typedef struct{
    BFState* state;
    int (*execute) (BFState*);
    void (*Deleate) ();
}BrainFuck;

//++[+++[+++[++]+++]+++]++

BrainFuck* newBrainFuck(size_t array_len, const char* programm);
BFState* newBFState(size_t array_len, const char* programm);

void Deleate();

int brainfuck(BFState* state);

//['>'] increment the data pointer (to point to the next cell to the right).
void incPtr(BFState* state);

//['<'] decrement the data pointer (to point to the next cell to the left).
void decPtr(BFState* state);

//['+'] increment (increase by one) the byte at the data pointer.
void incData(BFState* state);

//['-'] decrement (decrease by one) the byte at the data pointer.
void decData(BFState* state);

/*['[']
if the byte at the data pointer is zero,
then instead of moving the instruction pointer forward to the next command,
jump it forward to the command after the matching ] command.
*/
void jez(BFState* state);

/*[']']
if the byte at the data pointer is nonzero,
then instead of moving the instruction pointer forward to the next command,
jump it back to the command after the matching [ command.
*/
void jnz(BFState* state);

#endif