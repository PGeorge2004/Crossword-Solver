#include <stdio.h>
#include <stdlib.h> 
#include <string.h>

    int crossword_filler_for_check(char* word,char**crossword,int *x_y);
    int check_f ( char ***dict,int max, int words_needed, int *word_length,char **crossword,int** point_for_check,int * words_count);
    int draw_f( char **crossword, int N );

    int crossword_filler_for_check(char* word,char**crossword,int *x_y){
    int error = 0 ;
    int k = 0 ;
    if (x_y[0] == x_y[2]){ // for the horizontal words
        for(int i  = x_y[1] ; (i <= x_y[3]) && error == 0;i++){
            if((word[k] == crossword[x_y[0]][i])|| crossword[x_y[0]][i]==' ')k++; //if the letters match or theres space, check the next letter  
            else error = 1; //else there is a problem and the word doesnt match
        }
        if (error == 0){ //if there is no error then we transfer the word inside the crossword
            k = 0;
            for(int i  = x_y[1] ; i <= x_y[3];i++){
                crossword[x_y[0]][i] = word[k];
                k++;
            }
        } 
    }
    else{// for the vertical words
        for(int i  = x_y[0] ; (i <= x_y[2]) && error == 0;i++){
            if((word[k] == crossword[i][x_y[1]])|| crossword[i][x_y[1]]==' ')k++;
            else error = 1;
        }
        if (error == 0){
            k = 0;
            for(int i  = x_y[0] ; i <= x_y[2];i++){
                crossword[i][x_y[1]] = word[k];
                k++;
            }
        } 
    }
    
    return error;
}

    int check_f ( char ***dict,int max, int words_needed, int *word_length,char **crossword,int** point_for_check,int *words_count) {
        
        char *temp;  // to keep the words we get as inputs
        temp = malloc ( 100 *sizeof(char));
        char quotes = 34; // for the " character
        int words_given = 0;

        while (scanf("%s ", temp) != EOF) { // while we get a word from stdin
            
            words_given++; 
            if(words_given > words_needed) {
                printf("More words than needed\n");
                return 1;
            }

            int len = strlen(temp) ;// the length of the word given
            

            if (word_length[words_given-1] != len ) { //if the length of the word given doesn't match the length of the word the array can get then the word cant be placed
                printf ("Word %c%s%c cannot be placed\n", quotes, temp, quotes);
                return 1;
            }


            int b = 1; // value to know whether the loop broke or not
            int i;
            for (i = 0; i < words_count[len] ; i++) { 
                if (strcmp(dict[len][i],temp) == 0 ) { // if the word belongs to the dictionary then we should
                    b=0;                              //check the other scenarios
                    break;
                }
            }
            if (b){ //if the loop never broke then the word is not inside the dictionary
                printf ("Word %c%s%c not in dictionary\n", quotes, temp, quotes);
                return 1;
            }
            

            int error = crossword_filler_for_check(temp,crossword,point_for_check[words_given - 1]);
            if (error){
                printf ("Word %c%s%c cannot be placed\n", quotes, temp, quotes);
                return 1;
            } 
          
        }
        
        if (words_given < words_needed) {
            printf("Not enough words\n");
            return 1;
        }
          
        free (temp);
        return  0;
    }

    int draw_f( char **crossword, int N ) { //printing the crossword
        int i, j;
        for (i=0; i<N; i++) {
            for (j=0; j<N; j++) {
                if (crossword[i][j]=='#'){
                    printf("###");
                }
                else {
                    printf(" %c ",crossword[i][j]);
                }
            }
            printf ("\n");
        }
    }







