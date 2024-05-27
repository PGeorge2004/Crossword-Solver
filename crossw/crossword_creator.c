#include <stdio.h>
#include <stdlib.h> 
#include <string.h>
#include "swaps_and_bubblesort.h"

    char **crossword_creator( FILE *ifp, int *num);
    int **crossword_2d_creator( char **crossword, int max, int **pl, int *words_count, int *space_count, int **length_for_check, int ***points_for_check);
    int words_counter( char **crossword, int max, int *words_hor, int *words_ver);
    
    char **crossword_creator( FILE *ifp, int *num) { // creating the crossword pattern
        
        fscanf(ifp,"%d ",num);
        char **temp_crossword = malloc((*num)*sizeof(char*)) ;
        if ( temp_crossword == NULL) {
            return NULL;
        }
        for (int i = 0 ; i <= (*num)-1 ; i ++) {
            temp_crossword[i] = malloc((*num)*sizeof(char));
            if ( temp_crossword[i] == NULL) {
                return NULL;
            }   
        }
        for ( int  i = 0 ; i <= (*num)-1 ; i ++) {
            for ( int j =0 ; j <= (*num) - 1;j++) {
                temp_crossword[i][j] = ' '; 
            }
        }
        int a,b;
        while(fscanf(ifp,"%d %d ",&a,&b)!= EOF) {
            temp_crossword[a-1][b-1] = '#' ;
        }
        return temp_crossword;
    }

    int **crossword_2d_creator( char **crossword, int max, int **pl, int *words_count, int *space_count, int **length_for_check, int ***points_for_check) {
        
        int i,j ;
        int words_hor = 0;
        int words_ver = 0;
        int words = words_counter(crossword,max,&words_hor,&words_ver);

        int **temp_point = malloc(words*sizeof(int*));//keeps the location of the start and the end of its word of the crossword
        if ( temp_point == NULL) {
                return NULL;
        } 
        for ( i = 0; i < words; i++) {
            temp_point[i] = malloc(4*sizeof(int)) ;
            if ( temp_point[i] == NULL) {
                return NULL;
            } 
        
        }
        *pl =  malloc(words*sizeof(int));  
        if ( *pl == NULL) {
                return NULL;
        } 

        *length_for_check =  malloc(words*sizeof(int)); 
        if ( *length_for_check == NULL) {
            return NULL;
        }

        *points_for_check = malloc(words*sizeof(int*));
        if ( *points_for_check == NULL) {
            return NULL;
        } 
        for (i = 0 ; i <words ; i ++) {
            ((*points_for_check))[i] = malloc(4*sizeof(int));
            if ( (*points_for_check)[i] == NULL) {
                return NULL;
            }
        }

        int **hor_length_value = malloc(words_hor*sizeof(int*)) ;
            if ( hor_length_value == NULL) {
                return NULL;
            }
        for ( i = 0; i < words_hor; i++) {
            hor_length_value[i] = malloc(3*sizeof(int));
            if ( hor_length_value[i] == NULL) {
                return NULL;
            }
        }

        int **ver_length_value = malloc(words_ver*sizeof(int*));
        if ( ver_length_value == NULL) {
            return NULL;
        }
        for ( i = 0; i < words_ver; i++) {
            ver_length_value[i] = malloc(3*sizeof(int));
            if ( ver_length_value[i] == NULL) {
                return NULL;
            }
        }

        int **hor_temp_points;
        hor_temp_points = malloc(words_hor*sizeof(int*));
        if ( hor_temp_points == NULL) {
            return NULL;
        }
        for ( i = 0; i < words_hor; i++) {
            hor_temp_points[i] = malloc(4*sizeof(int));
            if ( hor_temp_points[i] == NULL) {
                return NULL;
            }
        }

        int **ver_temp_points;
        ver_temp_points = malloc(words_ver*sizeof(int*));
        if ( ver_temp_points == NULL) {
            return NULL;
        }
        for ( i = 0; i < words_ver; i++) {
            ver_temp_points[i] = malloc(4*sizeof(int));
            if ( ver_temp_points[i] == NULL) {
                return NULL;
            }
        }

        int start = 0 ; // checking where the word starts from 
        int x,y,k,l;
        words_hor = 0;
        words_ver = 0;
        int value = 0 ;

        //for the horizontal
        for ( i = 0 ; i < max ;i++) { 
            value = 0 ;
            start = 0 ; 
            for (j = 0 ; j < max; j ++) {
                if (crossword[i][j] == ' ') { 
                    start ++;
                    if (((i-1)>=0 && crossword[i-1][j]==' ') || ((i+1)<max && crossword[i+1][j]==' '))value++; //
                    if (start == 1) { //keeping the coordinates from where the word begins
                    x = i; 
                    y = j;    
                    }
                }
                else if (start != 0 && crossword[i][j]== '#' ) {
                    if (start >= 2) {
                        hor_temp_points[words_hor][0]= x;
                        hor_temp_points[words_hor][1]= y;
                        hor_temp_points[words_hor][2]= i;    // to keep the coordinates of where the words ends
                        hor_temp_points[words_hor][3]= j-1; 
                        
                        hor_length_value[words_hor][0]= start; // length of the word
                        hor_length_value[words_hor][1]= value;
                        hor_length_value[words_hor][2]= words_count[start];
                        words_hor ++ ; 
                    }
                    value = 0 ; // reseting the variables
                    start = 0 ;
                }
            }
            if (start >= 2) {//to take the case in which the word ends at the end of the crossword
                hor_temp_points[words_hor][0]= x;
                hor_temp_points[words_hor][1]= y;
                hor_temp_points[words_hor][2]= i;
                hor_temp_points[words_hor][3]= j-1;
                        
                hor_length_value[words_hor][0]= start;
                hor_length_value[words_hor][1]= value;
                hor_length_value[words_hor][2]= words_count[start];
                words_hor ++ ;
            }
            
        }
        //for the vertical 
        for ( i = 0 ; i < max ;i++) {
            value = 0 ;
            start = 0 ;
            for (j = 0 ; j < max; j ++) {
                if (crossword[j][i] == ' ') {
                    start ++;
                    if (((i-1)>=0 && crossword[j][i-1] == ' ') || ((i+1)<max && crossword[j][i+1] == ' '))value++;
                    if (start == 1) {
                    x = j; 
                    y = i;    
                    }    
                }
                else if (start != 0 && crossword[j][i]== '#' ) {
                    if (start >= 2) {
                        ver_temp_points[words_ver][0]= x;
                        ver_temp_points[words_ver][1]= y;
                        ver_temp_points[words_ver][2]= j-1;
                        ver_temp_points[words_ver][3]= i;

                        ver_length_value[words_ver][0]= start;
                        ver_length_value[words_ver][1]= value;
                        ver_length_value[words_ver][2]= words_count[start];
                        words_ver ++ ;
                    }
                    value = 0 ;
                    start = 0 ;
                }
            }
            
            if (start >= 2) {
                ver_temp_points[words_ver][0]= x;
                ver_temp_points[words_ver][1]= y;
                ver_temp_points[words_ver][2]= j-1;
                ver_temp_points[words_ver][3]= i;

                ver_length_value[words_ver][0]= start;
                ver_length_value[words_ver][1]= value;
                ver_length_value[words_ver][2]= words_count[start];
                words_ver ++ ;
            }
                
            
        }

        i = 0 ;
        j = 0 ;
        l = 0 ;
        k = 0 ;
        
        //merging the horizontal and then the vertical array in one so we can use it for the check case  
        //for the points
        while(i < words_hor ) {
            for(k = 0 ; k < 4 ; k++)(*points_for_check)[l][k] = hor_temp_points[i][k];
            i++;
            l++;  
        }
        while(j < words_ver ) {
            for(k = 0 ; k < 4 ; k++)(*points_for_check)[l][k] = ver_temp_points[j][k];
            j++;
            l++;  
        }
        // for the length
        for (int i = 0 ; i <words_hor ; i ++)(*length_for_check)[i] = hor_length_value[i][0];
        for( int i = 0 ; i <words_ver ; i ++ )(*length_for_check)[i+words_hor] = ver_length_value[i][0]; 

        bubble_sort(words_hor,hor_length_value,hor_temp_points);

        bubble_sort(words_ver,ver_length_value,ver_temp_points);

        i = 0 ;
        j = 0 ;
        l = 0 ;
        k = 0 ;
        // merging the horizontal and the vertical array by turns 
        int toggle = 1; // to know whether to put a horizontal or vertical word
        while ((i < words_hor) && (j < words_ver)) {
            if (toggle) {
            (*pl)[l] = hor_length_value[i][0];
            for(k = 0 ; k < 4 ; k++)temp_point[l][k] = hor_temp_points[i][k];
            i++;
            l++;
            toggle = 0 ;
            }
            else {
            (*pl)[l] = ver_length_value[j][0];
            for(k = 0 ; k < 4 ; k++)temp_point[l][k] = ver_temp_points[j][k];
            j++;
            l++;
            toggle = 1 ;   
            }
        }
        while(i < words_hor ) {
            (*pl)[l] = hor_length_value[i][0];
            for(k = 0 ; k < 4 ; k++)temp_point[l][k] = hor_temp_points[i][k];
            i++;
            l++;  
        }
        while(j < words_ver ) {
            (*pl)[l] = ver_length_value[j][0];
            for(k = 0 ; k < 4 ; k++)temp_point[l][k] = ver_temp_points[j][k];
            j++;
            l++;  
        }

        *space_count = words;

        for (i = 0 ; i <words_hor ; i ++) {
            free(hor_length_value[i]);
            free(hor_temp_points[i]);
        }
        free(hor_length_value);
        free(hor_temp_points);

        for(i = 0 ; i <words_ver ; i ++) {
            free(ver_length_value[i]);
            free(ver_temp_points[i]);
        }
        free(ver_length_value);
        free(ver_temp_points);
        return temp_point;
    }

    int words_counter( char **crossword, int max, int *words_hor, int *words_ver) {//counts the words needed to fill the crossword
        int words = 0 ;
        int start = 0 ;
        int i;
        int j;
        int words_hor2 = 0;
        int words_ver2 = 0 ;
        for ( i = 0 ; i < max ;i++) {
            start = 0;
            for (j = 0 ; j < max; j ++) {
                if ( crossword[i][j]==' ' ) {
                    start ++;
                }
                else if (start !=0 && crossword[i][j]== '#' ) {
                    if (start >= 2) {
                        words ++ ;
                        words_hor2++;
                    }
                    start = 0 ;
                }
            }
            if (start >= 2) {
                 words ++ ;
                words_hor2++;
            }  
        }
        for ( i = 0 ; i < max ;i++) {
            start = 0;
            for ( j = 0 ; j < max ; j ++) {
                if ( crossword[j][i]==' ') {
                    start ++;
                }
                else if (start != 0 && crossword[j][i]== '#' ) {
                    if (start >= 2) {
                        words ++ ;
                        words_ver2++;
                    }
                    start = 0 ;
                }
            }
            if (start >= 2) {
                words ++ ;
                words_ver2++;
            }
            
        }
        *words_ver = words_ver2;
        *words_hor = words_hor2;
        return words; 
    }
