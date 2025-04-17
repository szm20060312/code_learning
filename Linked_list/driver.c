#include <stdio.h>
#include <stdlib.h>
#include "list.h"
#include "ui.h"

int main(void){
    Node * list = NULL; // the head of the list maintained. 
    Node * listClone = NULL; 
    Node * nodeFound = NULL; // the address of a node found by find_data()
    int num; // record the number to be found. 

    welcome();

    while(5==5){
        char choice;
        show_menu();
        puts("Please pick a choice.");
        choice = get_choice();
        switch(choice){
            case 'a':            
                list = append_data(list, get_integer()); 
                break;
            case 'b': 
                list = prepend_data(list, get_integer()); 
                break;
            case 'c':
                print_list(list);
                break;
            case 'd':
                num = get_integer();
                nodeFound = find_data(list, num); 
                (nodeFound == NULL) ? puts("The integer is not found.") : puts("The integer is found") ; 
                break; 
            case 'e':
                insert_data_after(nodeFound, get_integer());
                break;
            case 'f':
                list = delete_node(list, nodeFound);
                break;
            case 'g':
                if (listClone != NULL)
                    free_list(listClone); // release the previous clone
                listClone = clone_list(list);
                puts("This is the clone of the list");
                print_list(listClone);
                break;
            case 'h':
                printf("The number of integers in the list is: %d\n", count(list));
                break;
            case 'i':
                printf("There are %d nodes freed\n", free_list(list));
                list = NULL;
                break;
            case 'j':
                print_list_v2(list);
                break;
            case 'q':
                free_list(list);
                free_list(listClone);
                goto END;
            default: puts("Wrong choice"); exit(1);
        }
    }
    END: 
        puts("Bye");
    return 0;
}
