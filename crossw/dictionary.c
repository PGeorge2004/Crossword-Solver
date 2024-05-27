#include <stdio.h>
#include <stdlib.h> 
#include <string.h>
#include "swaps_and_bubblesort.h"

    char **array_creator( FILE *ifp, int *number_of_words, int max);
    char ***mini_array_creator( char** array, int max, int number_of_words, int *words_count);

    
    char **array_creator( FILE *ifp, int *number_of_words, int max) {
        char **array ;
        int counter = 0 ;// count the words that can be used in the crossword
        char ch = 0 ;
        int all_words_counter = 0 ;

        int *ascii_frequency = malloc(255*sizeof(int*));//creates an 2d array that acts as an temp dictionary
        if ( ascii_frequency == NULL) {
            perror("Sorry, cannot allocate memory\n");

        }

        for(int i = 0 ; i <=254; i++)ascii_frequency[i] = 0;
        char *temp_array = malloc((2024)* sizeof(char)) ;
        if ( temp_array == NULL ){
            return NULL;
        }
        while (fscanf(ifp,"%s ", temp_array) != EOF){
            if (strlen(temp_array)<=max){
                counter ++;
                for(int i = 0 ; i <strlen(temp_array); i++){
                    ascii_frequency[temp_array[i]]++;
                } 
            }
            all_words_counter ++;
        }

        *number_of_words = counter ;//words that can be used in the crossword
        rewind(ifp);

        array = malloc(counter*sizeof(char*)) ; //creates an 2d array that acts as an temp dictionary
        if ( array  ==   NULL){
            return NULL;
        }
        for (int i=0 ; i <= *number_of_words-1; i++) {
            array[i] = malloc((max+1)*sizeof(char)) ;
            if ( array[i]  ==   NULL){
                return NULL;
            }
        }
        //the value is created in this fuction and it is the sum of the 
        //value of its character of the word which is calculated by the times its character appears in the file
        //(frequency of each character in the file)
        int *words_value = malloc((counter+1)*sizeof(int));
        if ( words_value == NULL ){
            return NULL;
        }

        for(int i = 0 ; i <counter; i++)words_value[i] = 0;

        int i = 0;
        while ( i < *number_of_words) {//fills the 2d array with the words
            fscanf(ifp,"%s ",temp_array) ;
            if ((strlen(temp_array))> max)continue;

            strcpy(array[i],temp_array) ;
            for(int k = 0 ; k <strlen(temp_array); k++){
                words_value[i] = ascii_frequency[temp_array[k]];
            } 
            i++ ;
        }

        bubble_sort_arr(counter,words_value,array);
        free(ascii_frequency);
        free(words_value);
        free(temp_array);
        return array;
    }

    char ***mini_array_creator( char** array, int max, int number_of_words, int *words_count) {
        char ***temp_mini_array ;
        temp_mini_array = malloc((max+1)*sizeof(char**)) ; //creates an 3d array that works as a dictionary sorted by the 
        if (temp_mini_array== NULL) {
            return NULL;
        } 
        for (int  i = 0; i<= max ;i++) {
            temp_mini_array[i]= malloc(number_of_words*sizeof(char*));//length of the words
            if (temp_mini_array[i]== NULL) {
                return NULL;
            } 
        }
        for ( int i = 0; i<= max ;i++) {
            words_count[i] = 0 ;
            for ( int j = 0; j<= number_of_words-1 ;j++) {
                temp_mini_array[i][j]= malloc((max+1)*sizeof(char)) ;
                if (temp_mini_array[i][j]== NULL) {
                    return NULL;
                }             
            }
        }

        for (int i = 0; i< number_of_words ;i++) {//fills the array with the words of the temporary dictionary
            int length_of_word = strlen(array[i]) ;
            strcpy(temp_mini_array[length_of_word][words_count[length_of_word]], array[i]);
            words_count[length_of_word]++;
        }

        return temp_mini_array;
    }
