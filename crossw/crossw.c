#include <stdio.h>
#include <stdlib.h> 
#include <string.h>
#include "backtrack.h"
#include "check_draw_dict.h"
#include "crossword_creator.h"
#include "dictionary.h"
#include "swaps_and_bubblesort.h"

    int main(int argc, char *argv[]) {
        int error;
        if (argc == 1) {
            printf("no crossword file \n");
            return 0;
        }

        FILE *ifp;
        int i;
        if ((ifp = fopen(argv[1], "r")) == NULL) {
            perror("fopen source-file");
            return 1;
        }

        int draw = 0 ; //so we know if thw user wants to draw the crossword
        int dict1 = 0 ;//so we know which dictionary the user wants to use
        int check = 0 ;// so the user gives possible answers 

        int max;
        char **crossword = crossword_creator(ifp, &max) ;
        if ( crossword == NULL) {
            perror("Sorry, cannot allocate memory\n");
            return 1;

        }

        fclose(ifp);

        if (argc > 2) {
            for (int i=2; i<argc; i++) {
                if (strcmp(argv[i],"-check") == 0 ) {
                    check = 1;
                    }
                else if (strcmp(argv[i],"-dict") == 0) {
                    dict1 = i ; // to keep the place where the user wrote -dict 
                    }
                else if (strcmp(argv[i],"-draw") == 0) {
                    draw = 1;
                    }
            }
        }
        
        if (dict1) { // opening the dictionary that the user wants
            if (argc == dict1 ||(ifp = fopen(argv[dict1+1], "r")) == NULL) {
                perror("fopen source-file");
                return 1;
            }
        }
        else{ // if the user doesn't specify which dictionary to use (writing dict), we use the default one 
            if ((ifp = fopen("Words.txt", "r")) == NULL) {
                perror("fopen source-file");
                return 1;
            }
        }
        

        //start of dictionary creation factions 
        int all_words =0 ;
        char **dict = array_creator(ifp,&all_words,max);
        if ( dict  ==   NULL){
            perror("Sorry, cannot allocate memory\n");
        }

        int *words_count = malloc((max+1)*sizeof(int)); //count the words of its group sorted by the length of the words
         if ( words_count == NULL) {
            perror("Sorry, cannot allocate memory\n");
        }
        char ***mini_dict = mini_array_creator(dict,max,all_words,words_count);
        if (mini_dict == NULL) {
                perror("Sorry, cannot allocate memory\n");
        } 
        for ( i = 0 ; i <all_words ; i++){
            free(dict[i]);
        }
        free (dict);
        //end of dictionary creation factions 


        //start mapping of the words of the crossword
        int space_count;
        int *length_for_check;//keeps the length of the word that can fill in the crossword
        int **points_for_check;//keeps the location of the words of the crossword
        int *length;//keeps the length of the word that can fill in the crossword but it is sorted

                    //**point keeps the location of the words of the crossword but it is sorted
        int **points =crossword_2d_creator(crossword,max,&length,words_count,&space_count,&length_for_check,&points_for_check);
        //end mapping of the words of the crossword


        //start of check fuction or the crossword solver
        if (check) {
            error = check_f( mini_dict, max, space_count, length_for_check,crossword,points_for_check,words_count);
        } 
        else{
            error = solver(points,length,mini_dict,words_count,crossword,space_count,max);
            if (error == 1){
                perror("Can not solve the crossword");
            }
        }
        //end of check fuction or the crossword solver


        //draw or print of words
        if (error == 0 ){

            if (draw) {
                draw_f(crossword, max);
            }
            else if(check == 0) {
                printf_ans(crossword,max,points_for_check,space_count);
            }
        }


        ////////..............////////

        for ( int i = 0; i<= max ;i++) {
            for ( int j = 0; j<= all_words-1 ;j++) {
                free(mini_dict[i][j]);                  
            }
        }
        for (int  i = 0; i<= max ;i++) {
            free(mini_dict[i]);
        }
        free(mini_dict);

        free(length);
        
        for (i=0; i<space_count; i++) {
            free(points[i]);
        }
        free(points);

        free(words_count);

        for (i  = 0 ; i <max ; i++){
            free(crossword[i]);
        }
        free(crossword);

        for (i=0; i<space_count; i++) {
            free(points_for_check[i]);
        }
        free(points_for_check);
        free(length_for_check);




        fclose(ifp);
 }