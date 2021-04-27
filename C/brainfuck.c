#include "brainfuck.h"
#include <malloc.h>

void PrintArray(BFState* state)
{
    printf("Inst: %c\t", *(state->program));
    for(int i = 0; i < state->array_len; i++){
        printf("%d ", (int)state->data[i]);
    }
    printf("\n");
}

int main()
{
    char* programm = "[->+<]";
    BrainFuck* bf = newBrainFuck(12, programm);
    if(bf == NULL) return 0;
    bf->execute(bf->state);

    PrintArray(bf->state);
    printf("\nEOP\n");
    printf("\n");
}


BrainFuck* newBrainFuck(size_t array_len, const char* programm){
    BrainFuck* out = malloc(sizeof(BrainFuck));
    //BFState* state = 0;
    //if(out == NULL)
    //{
        //printf("UNABLE TO ALLOCATE BFSTATE!");
        //return NULL;
    //}

    //state = newBFState(array_len, programm);

    //if(state == NULL){
        //printf("UNABLE TO ALLOCATE BFSTATE!");
        //return NULL;    
    //}
    
    //out->state = state;
    //out->execute = &brainfuck;
    //out->Deleate = &Deleate;

    return out;
}

BFState* newBFState(size_t array_len, const char* programm){
    BFState* out = (BFState*)malloc(sizeof(BFState));
    
    if(out == NULL)
    {
        printf("UNABLE TO ALLOCATE BFSTATE!");
        return NULL;
    }

    uint8_t* data = (uint8_t*)malloc(sizeof(uint8_t)*array_len);
    if(data == NULL) {
        printf("FAILD TO ALLOCATE DATA ARRAY!\n");
        return NULL;
    }

    for(int i = 0; i < array_len; i++)
    {
        data[i] = 48;
    }

    out->array_len = array_len;
    out->data = data;
    out->cur = 0;
    out->isp = 0;
    out->program = programm;
    return out;
}

void Deleate(){

}

int brainfuck(BFState* state){
    while(state->program[state->isp] != 0){
        
        char c = state->program[state->isp];
        switch(c)
        {
            case '>':
                incPtr(state);
            break;
            case '<':
                decPtr(state);
            break;
            case '+':
                incData(state);
            break;
            case '-':
                decData(state);
            break;
            case '[':
                jez(state);
            break;
            case ']':
                jnz(state);
            break;
            default:
            printf("UNKNOWN CHAR: %c\n", c);
            return 0;
        }
    }
    return 1;
}


//['>'] increment the data pointer (to point to the next cell to the right).
void incPtr(BFState* state){
    state->cur++;
    state->isp++;
}

//['<'] decrement the data pointer (to point to the next cell to the left).
void decPtr(BFState* state){
    state->cur--;
    state->isp++;
}

//['+'] increment (increase by one) the byte at the data pointer.
void incData(BFState* state){
    state->data[state->cur] += 1;
    state->isp++;
}

//['-'] decrement (decrease by one) the byte at the data pointer.
void decData(BFState* state){
    state->data[state->cur] -= 1; 
    state->isp++;
}

/*['[']
if the byte at the data pointer is zero,
then instead of moving the instruction pointer forward to the next command,
jump it forward to the command after the matching ] command.
*/

void jez(BFState* state){
    int i = 1;
    while(state->data[state->cur] == 0 && i > 0 && state->program[state->isp] != 0){
        state->isp++;
        if(*(state->program) == ']'){
            i--;
        }
        if(*(state->program) == '['){
            i++;
        }
    }
    state->isp++;
}


/*[']']
if the byte at the data pointer is nonzero,
then instead of moving the instruction pointer forward to the next command,
jump it back to the command after the matching [ command.
*/
void jnz(BFState* state){
    int i = 1;
    while(state->data[state->cur] != 0 && i > 0){
        state->program--;
        if(*(state->program) == ']'){
            i++;
        }
        if(*(state->program) == '['){
            i--;
        }
    }
    state->program++;
}