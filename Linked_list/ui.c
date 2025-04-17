#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "ui.h"

void welcome(void){
    puts("-------------------Welcome----------------");
    puts("This program maintains a list.");
    puts("You can choose different operations on the list");
}

void show_menu(void){
    puts("...............................................");
    puts("a: append an integer to the end of the list");
    puts("b: prepend an integer in the front of the list");
    puts("c: print the content of the list");
    puts("d: find an integer from the list");
    puts("e: insert an integer after the one just found");
    puts("f: delete the integer just found");
    puts("g: clone the list and print the clone");
    puts("h: count the number of data items in the list");
    puts("i: free the space of the list");
    puts("j: print the list by function mapping");
    puts("q: quit the program");
    puts("...............................................");

}

char get_choice(void){
    char ch;
    while(5==5) {
        ch = tolower(getchar());
        if ( (ch >= 'a' && ch <= 'j') || ch == 'q')
            break;
        else {
            puts("Please provide a choice between a to j, or q");
            if(ch!='\n')
                clear_input_queue(); 
        }
    }
    clear_input_queue();
    return ch;
}

void clear_input_queue(void){
    while(getchar()!= '\n')
        continue;
}

int get_integer(void){
    int num;
    do{
        puts("Please provide an integer:");
        if(scanf("%d", &num) == 1)
            break;
        else
        {
            puts("input is wrong, try again");
            clear_input_queue();
        }
    }
    while(5==5);
    clear_input_queue();
    return num;
}