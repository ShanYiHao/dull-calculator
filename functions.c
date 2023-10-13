#include "header.h"
Status init_stack(Stack* pStack){
    pStack->pBase=(char *)malloc(pStack->size*sizeof(char));
    if(pStack->pBase==NULL)return (enum E)ERROR;
    pStack->pTop=pStack->pBase;
    return (enum E)OK;
}

void stack_free(Stack *pStack){
    free(pStack->pBase);
    pStack->pBase=NULL;
    pStack->pTop=NULL;
    return;
}

void stack_clear(Stack *pStack){
    pStack->pTop=pStack->pBase;
    return;
}

Bool is_empty(Stack* pStack){
    if(pStack->pBase==pStack->pTop)return 1;
    else return 0;
}

int stack_length(Stack *pStack){
    return (pStack->pTop-pStack->pBase)/sizeof(char);
}

Status stack_get_top(Stack *pStack,char *pElem){
    *pElem=*pStack->pTop;
    if(pElem==NULL)return (enum E)ERROR;
    else return (enum E)OK;
}

Status stack_push(Stack *pStack,char *pElem){
    pStack->pTop+=1;
    *pStack->pTop=*pElem;
    if(*pStack->pTop!=*pElem)return (enum E)ERROR;
    else return (enum E)OK;
}

Status stack_pop(Stack *pStack,char *pElem){
    *pElem=*pStack->pTop;
    pStack->pTop--;
    if(pElem==NULL)return (enum E)ERROR;
    else return (enum E)OK;
}

Status stack_traverse(Stack *pStack,Status (*visit)(char*)){
    char *pElem=pStack->pBase+1;
    for(;pElem<=pStack->pTop;pElem++){
        if(!(*visit)(pElem))return (enum E)ERROR;
    }
    return (enum E)OK;
}