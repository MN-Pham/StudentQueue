#include <stdio.h>
#include <stdlib.h>

#include "SLL.h"
#include "CommandHandler.h"

int main()
{
    Node_t *pHead = NULL;
    loadSLL(&pHead);
    showSLL(pHead);
    while(!Handler(&pHead)) { }
    return 0;
}
