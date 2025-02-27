/* 
 * p_segments.c
 *
 * man 3 end
 *
 * etext  This  is  the first address past the end of the text segment (the program code).
 *
 * edata  This is the first address past the end of the initialized data segment.
 *
 * end    This is the first address past the end of the uninitialized data  segment (also known as the BSS segment).
 *
 * man 2 brk
 *
 * program break, which defines the end of the process's data segment (i.e., the program break is the first location after the end of the uninitialized data segment).
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

extern char etext, edata, end; /* The symbols must have some type, or "gcc -Wall" complains */

/* Initialized data segment */
char var_data[]="ABCD";

/* Uninitialized data segment (BSS) */
char var_bss;		

int main(int argc, char *argv[]) /* Allocated in frame for main() */
{
    char *var_heap; /* Allocated in frame for main() */

    int * program_break_before_malloc = sbrk(0);

       long pageSize;
     pageSize = sysconf(_SC_PAGESIZE);


    var_heap = malloc(4096*8); /* Points to memory in heap segment */

    printf("-STACK----------------------------------------------------\n");
    printf("                        Address of var_heap %14lp\n", &var_heap);
    printf("-HEAP-----------------------------------------------------\n");
    printf("               Program break after malloc() %14lp\n", sbrk(0));
    printf("                                   var_heap %14lp\n", var_heap);
    printf("              Program break before malloc() %14lp\n", program_break_before_malloc);
    printf("First address past uninitialized data (end) %14lp\n", &end);
    printf("-BSS------------------------------------------------------\n");
    printf("                                    var_bss %14lp\n", &var_bss);
    printf("First address past initialized data (edata) %14lp\n", &edata);
    printf("-DATA-----------------------------------------------------\n");
    printf("                                   var_data %14lp\n", &var_data);
    printf("    First address past program text (etext) %14lp\n", &etext);
    printf("-TEXT-----------------------------------------------------\n");
    printf("                          Address of main() %14lp\n", main);
    printf("----------------------------------------------------------\n");

    printf("PID = %d\n", getpid());
    printf("pageSize = %d\n", pageSize);
    getchar();

    exit(EXIT_SUCCESS);
}
