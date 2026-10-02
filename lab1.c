#include <stdio.h>
#include <stdlib.h>

#define MAX_PROCESSES 10

/* ============================================================
   DATA STRUCTURES AND GLOBAL CONSTANTS
   ============================================================ */

/*
    TODO:
    - Define the children linked-list node structure
    - Define the PCB structure
    - Define MAX_PROCESSES
    - Create the PCB array
*/

typedef struct childNode{
  int child; 
  struct childNode *next;
 } childNode;


typedef struct pcb{
  int parent;
  childNode *children;
 } pcb;



pcb *PCB[MAX_PROCESSES];

/* ============================================================
   PRINT PROCESS HIERARCHY
   ============================================================ */

void printHierarchy() {

    /*
        TODO:

        1. Declare local variables.

        2. Loop through process indexes:
              0 to MAX_PROCESSES - 1

        3. If PCB[i] is NOT NULL:
              - Print process ID
              - Print parent ID
              - Print all child process IDs

        You will need to traverse the linked list
        of children for each process.
    */
    for ( int i = 0 ; i < MAX_PROCESSES ; i++){
        if(PCB[i] != NULL){
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

    /*
        TODO:

        1. Allocate memory for PCB[0].

        2. Initialize PCB[0].

        3. Initialize all other PCB entries to NULL.

        4. Print the process hierarchy.
    */
   PCB[0] = malloc(sizeof(pcb));
   PCB[0]->parent = -1;
   PCB[0]->children = NULL;

   for ( int i = 1 ; i < MAX_PROCESSES ; i++){
    PCB[i] = NULL;
   }
}




// option 2. creating child
void createChild() {

    /*
        TODO:

        1. Declare local variables.

        2. Ask user for parent process index p.

        3. Check whether PCB[p] exists.

           If PCB[p] == NULL:
               print an error message
               return

        4. Search for the first available PCB index q.

           In other words, find the first:

               PCB[q] == NULL

        5. If no available PCB exists:
               print an error message
               return

        6. Allocate memory for PCB[q].

        7. Initialize the new child process:

               parent = p
               children = NULL

        8. Create a new linked-list node
           containing child process index q.

        9. Append that node to the children
           linked list of PCB[p].

       10. Print the process hierarchy.
    */
   int p; //for inputing parent
   int q; // for finding the first available array index


   printf(" create: ");
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

   // allocate space for the new process initializing the parent chidldren
   PCB[q] = malloc(sizeof(pcb));
   PCB[q]->parent = p;
   PCB[q]->children = NULL;

    // delaing with adding the new process to the parent children
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

    /*
        TODO:

        1. BASE CASE:
           Check whether we reached the end
           of the linked list.

           If yes:
               return

        2. Recursively process the NEXT node
           in the linked list.

        3. Store the current node's process index
           inside variable q.

        4. Recursively destroy the children
           belonging to PCB[q].

        5. Free PCB[q].

        6. Set PCB[q] to NULL.

        7. Free the current linked-list node.
    */

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

    /*
        TODO:

        1. Ask user for process index p.

        2. Call destroyChildren() using the children
           linked list belonging to PCB[p].

        3. After all descendants are destroyed:

               PCB[p]->children = NULL

        4. Print the process hierarchy.

        IMPORTANT:

        Do NOT destroy process p itself.

        Only destroy its descendants:
            children
            grandchildren
            great-grandchildren
            etc.
    */
    int p;

    printf (" Delete : ");
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

    /*
        TODO:

        1. Check whether PCB[0] exists.

        2. If PCB[0] has children:
               destroy all of its descendants.

        3. Free any remaining PCB memory.

        This makes sure dynamically allocated memory
        is cleaned before the program exits.
    */
   destroyChildren(PCB[0]->children);

   free(PCB[0]);

   PCB[0] = NULL;

}




// main
int main() {

    /*
        TODO:

        1. Declare variable for user's menu choice.

        2. Keep displaying the menu until
           the user chooses option 4.

        Menu:

            Process creation and destruction
            --------------------------------
            1) Initialize process hierarchy
            2) Create a new child process
            3) Destroy all descendants of a process
            4) Quit program and free memory

        3. Read user's choice.

        4. Use switch(choice):

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
    */

    // printf("program complied\n");

    // initializeHierarchy();

    // printHierarchy();

    // createChild();

    // createChild();

    // destroyDescendants();

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