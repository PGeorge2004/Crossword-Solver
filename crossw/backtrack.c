#include <stdio.h>
#include <stdlib.h> 
#include <string.h>

    int crossword_filler(char* word,char**crossword,int *x_y,int **crossword_int);
    void crossword_deleter( int* x_y, char **crossword, int max, int **crossword_int);
    int backtracking( int **point, int *length, char ***dictionary, int *words_count, int id, char **crossword, int space_count, int max, int **crossword_int );
    int solver( int **point, int *length, char ***dictionary, int *words_count, char **crossword, int space_count, int max);


    int crossword_filler(char* word,char**crossword,int *x_y,int **crossword_int) {//check if the word can fill the crossword and places it 
        int error = 0 ;
        int k = 0 ;
        if (x_y[0] == x_y[2]) { //for horizontal words
            for ( int i = x_y[1] ; (i <= x_y[3]) && error == 0 ; i++ ) {//check if the word can be placed
                if( (word[k] == crossword[x_y[0]][i]) || crossword[x_y[0]][i] == ' ' ) k++;
                else error = 1;
            }
            if (error == 0) {
                k = 0;
                for( int i  = x_y[1] ; i <= x_y[3];i++) {//places the word in the crossword
                    crossword[x_y[0]][i] = word[k] ;
                    crossword_int[x_y[0]][i]++ ; //increases the map values by one in its place a character was placed
                    k++;
                }
            } 
        }
        else{ //for vertical words
            for( int i = x_y[0] ; (i <= x_y[2]) && error == 0 ; i++) {//check if the word can be placed
                if( (word[k] == crossword[i][x_y[1]]) || crossword[i][x_y[1]] == ' ' ) k++;
                else error = 1;
            }
            if (error == 0){
                k = 0;
                for( int i = x_y[0] ; i <= x_y[2];i++) {//places the word in the crossword
                    crossword[i][x_y[1]] = word[k];
                    crossword_int[i][x_y[1]]++; //increases the map values by one in its place a character was placed
                    k++;
                }
            } 
        }
        
        return error;
    }

    void crossword_deleter( int* x_y, char **crossword, int max, int **crossword_int ) {//removes the word from the crossword 
    
        if (x_y[0] == x_y[2]) {//for horizontal words
            for( int i = x_y[1] ; i <= x_y[3] ; i++) {//replaces the characters with spaces
                if (crossword_int[x_y[0]][i] == 1) {
                    crossword[x_y[0]][i] = ' ' ;
                    crossword_int[x_y[0]][i]-- ;//decreases the map values by one in its place a character was removed
                }
                else if (crossword_int[x_y[0]][i] == 2) {
                    crossword_int[x_y[0]][i] -- ;
                }
            }
        }
        else {//for vertical words
            for( int i = x_y[0] ; i <= x_y[2] ; i++ ) {//replaces the characters with spaces
                if (crossword_int[i][x_y[1]] == 1) {
                    crossword[i][x_y[1]] = ' ' ;
                    crossword_int[i][x_y[1]] -- ;//decreases the map values by one in its place a character was removed
                }
                else if (crossword_int[i][x_y[1]] == 2) {
                    crossword_int[i][x_y[1]] -- ;
                }
            }
        }
    }

    int backtracking( int **point, int *length, char ***dictionary, int *words_count, int id, char **crossword, int space_count, int max, int **crossword_int ) {
        id++;
        int i = 0 ;
        int end = 0 ;//works as the end of the backtracking and also flags errors 
        int error = 0 ;//flags the error of the filling of the crossword

        while (end == 0 && (i <words_count[length[id]]) ) {//if end == 0 and i surpasses the limit of the words the loop stops and returns 1 which flags this error 
            error = crossword_filler( dictionary[length[id]][i], crossword,point[id], crossword_int) ;
            //flags the error of the filling of the crossword
            if (error == 0 && id == space_count -1) end = 1 ;
            else if (error == 0 ) {
                error = backtracking( point, length, dictionary, words_count, id, crossword, space_count, max, crossword_int);
                //flags the error of the filling of crossword's next spaces
                if (error == 0 ){//goes at the start of the recursion and returns to solve fuction
                    end = 1 ;
                    break ;
                }
                else {
                    crossword_deleter( point[id], crossword, max, crossword_int) ;
                    i++ ;//goes to the next word
                    continue;
                }  
            }
            else{
                i++;//goes to the next word
                continue;    
            }
        }
        if (end == 1) return 0;

        return 1;
        
    }

    int solver( int **point, int *length, char ***dictionary, int *words_count, char **crossword, int space_count, int max) {
        int id = -1 ;
        int error ;
        int **crossword_int = malloc( max * sizeof(int*)) ;
        if ( crossword_int == NULL) {
            return 2;
        }


        //crossword_int works as a map of the crossword which keeps which spaces are filled and where intersections exist
        //for example: # # a a a   # # 1 1 2  p.s: in crossword_int the hashtags are zero just like the rest of the array
        //             #       b   # 0 0 0 1
        //             a b a b a   1 1 1 1 2
        //                     #   0 0 0 0 #
        //                   # #   0 0 0 # #
        for (int j = 0 ; j < max ; j ++) {
            crossword_int[j] = malloc( max * sizeof(int)) ;
            if ( crossword_int[j] == NULL) {
                return 2;
            }
        }
        for ( int i = 0 ; i < max ;i++) {
            for( int j = 0 ; j < max ; j++) {
                crossword_int[i][j] = 0 ; 
            }
        }
        error = backtracking( point, length, dictionary, words_count, id, crossword, space_count, max, crossword_int) ;
        
        for (int j = 0 ; j < max ; j ++) {
            free (crossword_int[j]);
        }
        free (crossword_int);
        

        return error;
    }
