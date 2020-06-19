#include "CommandHandler.h"
#include "SLL.h"
#include <stdlib.h>
#include <stdio.h>

int Handler(Node_t** ppHead) {
    int ID_=0; //Used for 'Delete'
    int in = getchar();
    clear(); //clear the buffer after get()
    switch(in) {
        case 'A':
        case 'a':
            if(!addNode(ppHead)) {
                printf("Invalid input\n");
            }
            break;
        case 'Q':
        case 'q':
            printf("Do you want to save the list? (y/n)");
            if (getchar() == 'y') {
                saveSLL(*ppHead);
            }
            return 1;
        case 'C':
        case 'c':
            printf("Are you sure to clear the list? (y/n)");
            if (getchar() == 'y') {
                clearSSL(ppHead);
                break;
            }
            else if (getchar() == 'n') break;
            else {
                printf("Invalid input\n");
                break;
            }
        case 'D':
        case 'd':
            printf("ID of student:");
            scanf("%d", &ID_);
            clear(); //clear the buffer
            printf("Are you sure to delete student %d from the list? (y/n)", ID_);
            if (getchar() == 'y') {
                deleteNode(ppHead,ID_);
                break;
            }
            else if (getchar() == 'n') break;
            else {
                printf("Invalid input\n");
                break;
            }
        default:
            printf("Invalid input\n");
            break;
    }
    usleep(500000); //delay 0.5 sec to show error message (if there are any)
    //Reset the output
    system("@cls||clear"); //Clear output screen
    showSLL(*ppHead); //Print updated list
    clear(); //clear the buffer after get()
    return 0;
}
