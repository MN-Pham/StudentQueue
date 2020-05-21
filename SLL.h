#ifndef SLL_H
#define SLL_H

#include <stdbool.h>

typedef struct StudentInfo {
    char Name[50];
    int Id;
    int Age;
    float Calculus;
    float Cprog;
    float LinearAlg;
} StudentInfo_t;

typedef struct Node {
    StudentInfo_t info;
    struct Node *pNextNode;
} Node_t;

void showSLL(const Node_t *pHead);
void addSLL(Node_t **ppHead, StudentInfo_t data);
void deleteNode(Node_t **ppHead, int ID);
void clearSSL(Node_t **ppHead);
void saveSLL(Node_t*);
void loadSLL(Node_t**);

void refineName(char *name);
bool addNode(Node_t **pHead);
bool legitScore(float score);
bool legitName(char* name);
bool legitID(Node_t* pHead, int ID);

#endif // SLL_H
