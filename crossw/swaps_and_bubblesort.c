#include <stdio.h>
#include <stdlib.h> 
#include <string.h>

    void swaps( int *a, int *b);
    void bubble_sort( int n, int **x, int **ar);
    void swaps_array(char **a, char **b);
    void bubble_sort_arr( int n, int *x, char **ar);
    void skip_space(FILE *ifp);
    int printf_ans(char** crossword,int max,int **points,int space_count);
    
    void swaps( int *a, int *b) { 
        int temp ;
        temp = *a ;
        *a = *b ;
        *b = temp ; 
    }

    //this bubble sort is modified in order to sort the word according to first their values then in draw to the number of intersection and then in draw the length  
    void bubble_sort( int n, int **x, int **ar) {
        int i, j, k ;
        for (i=1 ; i <= n-1 ; i++) {
            for (j=n-1 ; j >= i ; j--) {
                if ( (x[j-1][2] > x[j][2]) || (x[j-1][2] == x[j][2] && x[j-1][1] < x[j][1]) || (x[j-1][2] == x[j][2] && x[j-1][1] == x[j][1] && x[j-1][0] < x[j][0]) ) {
                    for(k = 0 ; k < 3 ; k++)swaps(&x[j][k], &x[j-1][k]);
                    for(k = 0 ; k < 4 ; k++)swaps(&ar[j][k],&ar[j-1][k]);
                }
            }
        }

    }

    void swaps_array(char **a, char **b) { 
        char *temp ;
        temp = *a ;
        *a = *b ;
        *b = temp ; 
    }

    void bubble_sort_arr( int n, int *x, char **ar) {
        int i, j;
        for (i=1 ; i < n ; i++) {
            for (j=n-1; j >= i ; j--) {
                if (x[j-1]<x[j]) {
                    swaps(&(x[j-1]),&(x[j]));
                    swaps_array(&(ar[j]),&(ar[j-1]));
                }
            }
        }

    }

    void skip_space(FILE *ifp) {
        int a;
        a = getc(ifp) ;
        while ( a == ' ' || a == '\n' || a == '\t') {   
            a = getc(ifp) ;
        }
        ungetc(a,ifp);
    }

    int printf_ans(char** crossword,int max,int **points,int space_count){ // prints the answer of the crossword (words that solve it)
        int *x_y=malloc(4*sizeof(int));
        if(x_y == NULL){
           return 1; 
        } 
        for(int k = 0 ; k <space_count; k++){ // until we print all the answers
            for(int i = 0 ; i <4 ; i ++)x_y[i] = points[k][i];
            
            if (x_y[0] == x_y[2]) {
                for ( int i = x_y[1] ; i <= x_y[3] ; i++ ) {
                    printf("%c",crossword[x_y[0]][i]);
                }
                putchar('\n');
            }
            else{
                for( int i = x_y[0] ; i <= x_y[2] ; i++) {
                    printf("%c",crossword[i][x_y[1]]);
                }
                putchar('\n');
            }
        }
        free(x_y);
    }
    