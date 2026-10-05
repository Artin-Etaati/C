#include <stdio.h>
#include <stdlib.h>

#define MAX_PROCESSES 10



typedef struct childNode{
  int child; 
  struct childNode *next;
 } childNode;


typedef struct pcb{
  int parent;
  childNode *children;
 } pcb;



pcb *PCB[MAX_PROCESSES];

//printing
void printHierarchy() {
    for ( int i = 0 ; i < MAX_PROCESSES ; i++){
        if(PCB[i] != NULL){
            printf("-----------\n");
            printf("Process id: %d\n", i);

            if(PCB[i]->parent == -1){
                printf("No parent\n");
            }
            else {
                printf(" parent process id: %d\n", PCB[i]->parent);
            }
        
        if (PCB[i]->children == NULL){
            printf("no child processes\n");
        }
        else{
            childNode *current = PCB[i]->children;

            while(current != NULL){
                printf("Child prcess: %d\n", current->child);

                current = current->next;
            }
        }
        }
    }
}




// option 1. initialize
void initializeHierarchy() {
   PCB[0] = malloc(sizeof(pcb));
   PCB[0]->parent = -1;
   PCB[0]->children = NULL;

   for ( int i = 1 ; i < MAX_PROCESSES ; i++){
    PCB[i] = NULL;
   }
}




// option 2. creating child
void createChild() {

   int p; //for inputing parent
   int q; // for finding the first available array index


   printf(" Enter process id (create): ");
   scanf("%d", &p);

   if(p < 0 || p >= MAX_PROCESSES){
    printf("This is invalid input");
    return;
   }

   q = 0;

   while(q < MAX_PROCESSES && PCB[q] != NULL){
    q++;
   } // find the first aailable index

   if ( q == MAX_PROCESSES){
    printf("No mrore available PCBs.\n");
    return;
   }

   // allocate space 
   PCB[q] = malloc(sizeof(pcb));
   PCB[q]->parent = p;
   PCB[q]->children = NULL;

    // adding the new process to the parent
   childNode *newChild = malloc(sizeof(childNode));
   newChild->child = q;
   newChild->next = NULL;

   if (PCB[p]->children == NULL){
    PCB[p]->children = newChild;
   }
   else{
    childNode *current = PCB[p]->children;

    while(current->next != NULL){
        current = current->next;
    }
    current->next = newChild;
   }

   printHierarchy();

}




// option 3
void destroyChildren(childNode *current) {

    if ( current == NULL){
        return;
    }

    destroyChildren(current->next);

    int q = current->child;

    destroyChildren(PCB[q]->children);

    free(PCB[q]);
    PCB[q] = NULL;

    free(current);

}




// option 3 
void destroyDescendants() {

    int p;

    printf (" Enter process id (delete) : ");
    scanf("%d", &p);

    if(p < 0 || p >= MAX_PROCESSES){
        printf("this is invlaid input \n");
        return;
    }

    if(PCB[p] == NULL){
        printf("process %d does not exist. \n", p);
    }

    destroyChildren(PCB[p]->children);

    PCB[p]->children = NULL;

    printHierarchy();

}




// option 4 and quiting the program and freein up the space
void quitProgram() {

   destroyChildren(PCB[0]->children);

   free(PCB[0]);

   PCB[0] = NULL;

}




// main
int main() {


    int choice;

    do {
        printf("\nProcess Creation Hierarchy\n");
        printf("--------------------------\n");
        printf("1) Initialize process hierarchy\n");
        printf("2) Create a new child process\n");
        printf("3) Destroy all descendants of a process\n");
        printf("4) Quit program and free memory\n");

        printf("\nEnter choice: ");
        scanf("%d", &choice);
        
        switch ( choice ){
            case 1:
                initializeHierarchy();
                break;
            case 2:
                createChild();
                break;
            case 3:
                destroyDescendants();
                break;
            case 4:
                quitProgram();
                break;
            default:
                printf("Invalid choice. \n");
        }
    } while (choice != 4);


    return 1;
}