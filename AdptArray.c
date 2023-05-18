#include "AdptArray.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// struct for the dynamic array
typedef struct AdptArray_{
    int ArrSize;
    PElement *pElementArr;
    COPY_FUNC copyFunc; //used to make a copy of an element when it needs to be stored in the dynamic array.
    //provide a way to create a copy of an element so that the dynamic array can store independent instances
    // of the elements rather than just pointers to the original elements
    DEL_FUNC delFunc; //as COPY_FUNC but the purpose is for delete
    PRINT_FUNC printFunc;//as COPY_FUNC but the purpose is for print
}AdptArray, *PAdptArray;


PAdptArray CreateAdptArray(COPY_FUNC copyFunc, DEL_FUNC delFunc,
    PRINT_FUNC printFunc){
    PAdptArray pArr = (PAdptArray)malloc(sizeof(AdptArray));
    if(pArr == NULL){ // aloccatin didnt succed
        return NULL;
    }
    // Initialize
    pArr->ArrSize = 0;
    pArr->pElementArr = NULL;
    pArr->copyFunc = copyFunc;
    pArr->delFunc = delFunc;
    pArr->printFunc = printFunc;
    return pArr;
}

// deleting all the array element and free the memory
void DeleteAdptArray(PAdptArray pArr){
    if(pArr == NULL){
        return;
    }
    for (int i = 0; i < pArr->ArrSize; ++i) {
        if(pArr->pElementArr[i] != NULL)
            pArr->delFunc((pArr->pElementArr)[i]);
    }
    free(pArr->pElementArr);
    free(pArr);
}

// function that gets an index and a new element
Result SetAdptArrayAt(PAdptArray pArr, int idx, PElement pNewElement){
    PElement* newpElement;
    if(pArr == NULL){
        return FAIL;
    }
    // if the index is greater than the size of the array
    if(idx >= pArr->ArrSize){
        if ((newpElement = (PElement*)calloc((idx + 1), sizeof(PElement))) == NULL)
            return FAIL;
        memcpy(newpElement, pArr->pElementArr, (pArr->ArrSize) * sizeof(PElement));
        if(pArr->pElementArr != NULL)
            free(pArr->pElementArr);
        pArr->pElementArr = newpElement;
    }

    if(pArr->pElementArr[idx]!=NULL)
        pArr->delFunc((pArr->pElementArr)[idx]);
    (pArr->pElementArr)[idx] = pArr->copyFunc(pNewElement);
    // Update Array Size
    pArr->ArrSize = (idx >= pArr->ArrSize) ? (idx + 1) : pArr->ArrSize;
    return SUCCESS;
}

// function that gets the array and index and return a copy of the element in the index
PElement GetAdptArrayAt(PAdptArray pArr, int idx){
    if(idx>=pArr->ArrSize)
        return NULL;
    if(pArr->pElementArr[idx]==NULL)
        return NULL;
    PElement cpy = pArr->copyFunc((pArr->pElementArr)[idx]);
    return cpy;
}

// function to return the size of the array
int GetAdptArraySize(PAdptArray arr) {
    if(arr==NULL)
        return -1;
    return arr->ArrSize;
}

//printing all elements in the dynamic array
void PrintDB(PAdptArray pArr){
    if(pArr == NULL){
        return;
    }
    for (int i = 0; i < pArr->ArrSize; ++i) {
        if(pArr->pElementArr[i]!=NULL)
            pArr->printFunc(pArr->pElementArr[i]);
    }
}