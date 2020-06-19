#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include <string.h>

#include "SLL.h"

void clear (void) {    
  while ( getchar() != '\n' );
}

void showSLL(const Node_t *pHead) {
    const Node_t *pNext = pHead;

    if (pHead == NULL) {
        printf("The queue is empty.\n");
    }
    else {
        printf("| Name                    | Id           | Age     | Calsulus      | C-programming | Linear Algebra\n");
        printf("----------------------------------------------------------------------------------------------------\n");
        while (pNext != NULL) {
            printf(" %-26s%-15d%-10d%-16.2f%-16.2f%.2f\n",
                   (pNext->info).Name, (pNext->info).Id, (pNext->info).Age, (pNext->info).Calculus, (pNext->info).Cprog, (pNext->info).LinearAlg);
            pNext = pNext->pNextNode;
        }
    }
    printf("A: Add new student  D: Delete student  C: Clear database  Q: Quit\n");
}

void addSLL(Node_t **ppHead, StudentInfo_t data) {
    Node_t *pNext = *ppHead;
    Node_t *pNew = (Node_t *)malloc(sizeof(Node_t));

    if(pNew != NULL) {
        pNew->info = data;
        pNew->pNextNode = NULL;
    }
    if(pNext != NULL) {
        while (pNext->pNextNode != NULL) {
            pNext = pNext->pNextNode;
        }
        pNext->pNextNode = pNew;
    }
    else {
        *ppHead = pNew;
}

}
void deleteNode(Node_t **ppHead, int ID) {
    Node_t *pNext = *ppHead;
    Node_t *pPre = *ppHead;

    if(pNext != NULL) {
        //If the first node need to be deleted
        if ((pNext->info).Id == ID) {
            //Delete the first node and update ppHead
            *ppHead = pNext->pNextNode;
            free(pNext);
        }
        else {
            //scan the queue looking for the right node
            while (pNext->pNextNode != NULL) {
                pNext = pNext->pNextNode;
                if ((pNext->info).Id == ID) {
                    pPre->pNextNode = pNext->pNextNode;
                    free(pNext);
                    break;
                }
                pPre = pNext;
            }
        }
    }
}

void clearSSL(Node_t **ppHead){
    Node_t *pRemove = *ppHead;
    Node_t *pNext = NULL;

    while (pRemove != NULL) {
        pNext = pRemove->pNextNode;
        free(pRemove);
        pRemove = pNext;
    }
    *ppHead = NULL;
}

void saveSLL(Node_t* pHead) {
    FILE* pFile = NULL;
    pFile = fopen("../StudentQueue/StudentList.txt", "w");

    if (pFile == NULL) {
        printf("Cannot open file.\n");
    }

    const Node_t *pNext = pHead;

    if (pHead == NULL) {
        fprintf(pFile, "");
    }
    else {
        while (pNext != NULL) {
            fprintf(pFile, "Name:%s-ID:%d Age:%d Cal:%.2f Cpr:%.2f Lin:%.2f\n",
                   (pNext->info).Name, (pNext->info).Id, (pNext->info).Age, (pNext->info).Calculus, (pNext->info).Cprog, (pNext->info).LinearAlg);
            pNext = pNext->pNextNode;
        }
    }
}

void loadSLL(Node_t** ppHead) {
    FILE* pFile = NULL;
    pFile = fopen("../StudentQueue/StudentList.txt", "r");

    if (pFile == NULL) {
        printf("Cannot open file.\n");
    }

    StudentInfo_t data;
    while (!feof(pFile)) {
        //Regex: [^-] every character but '-'. fscanf() will read until character '-'.
        fscanf(pFile, "Name:%[^-]-ID:%d Age:%d Cal:%f Cpr:%f Lin:%f\n",
               data.Name, &(data.Id), &(data.Age), &(data.Calculus), &(data.Cprog), &(data.LinearAlg));
        addSLL(ppHead, data);
    }
}

void refineName(char *name) {
    //The first character cannot be a space
    while (name[0] == ' ') {
        for (int i=0; i<50; i++) {
            name[i] = name[i+1];
        }
    }

    for (int i=0; i<50; i++) {
        if (name[i] == '\0')
            break;
        //Remove multiple space
        if ((name[i] == ' ') && (name[i+1] == ' ')) {
            for (int j=i; j<50; j++) {
                name[j] = name[j+1];
            }
            i--;
        }
        //Change all character to lower case
        name[i] = tolower(name[i]);
        if (name[i-1] == ' ') {
            //Character after space is always a capital
            name[i] = toupper(name[i]);
        }
    }
    //The first character of name string is always a captital
    name[0] = toupper(name[0]);
}

bool legitScore(float score) {
    if ((score <= 10.0) && (score >= 0.0))
        return true;
    return false;
}

bool legitName(char *name) {
    int i=0;
    while (name[i] != '\0') {
        if((name[i] != ' ') && !isalpha(name[i]))
            return false;
        i++;
    }
    return true;
}

bool legitID(Node_t* pHead, int ID) {
    Node_t* pNext = pHead;
    while(pNext!=NULL) {
        if ((pNext->info).Id == ID) {
            return false;
        }
        pNext = pNext->pNextNode;
    }
    return true;
}

bool addNode(Node_t **ppHead) {
    StudentInfo_t NewStudent;
    char Name_[50];
    int Id_;
    int Age_;
    float Calculus_;
    float Cprog_;
    float LinearAlg_;
    printf("Add new student:\n");
    printf("\tName: ");
    gets(Name_);
    if (!legitName(Name_)) {
        return false;
    }
    refineName(Name_);

    printf("\tId: ");
    scanf("%d", &Id_);
    if (!legitID(*ppHead, Id_)) {
        printf("Existed ID.\n");
        return false;
    }

    printf("\tAge: ");
    scanf("%d", &Age_);

    printf("\tCalculus: ");
    scanf("%f", &Calculus_);
    if (!legitScore(Calculus_)) {
        return false;
    }

    printf("\tC Programming: ");
    scanf("%f", &Cprog_);
    if (!legitScore(Cprog_)) {
        return false;
    }

    printf("\tLinear Algebra: ");
    scanf("%f", &LinearAlg_);

    clear(); //clear the buffer

    if (!legitScore(LinearAlg_)) {
        return false;
    }

    strcpy(NewStudent.Name, Name_);
    NewStudent.Id = Id_;
    NewStudent.Age = Age_;
    NewStudent.Calculus = Calculus_;
    NewStudent.Cprog = Cprog_;
    NewStudent.LinearAlg = LinearAlg_;

    addSLL(ppHead, NewStudent);
    return true;
}
