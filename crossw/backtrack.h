    int crossword_filler(char* word,char**crossword,int *x_y,int **crossword_int);
    void crossword_deleter( int* x_y, char **crossword, int max, int **crossword_int);
    int backtracking( int **point, int *length, char ***dictionary, int *words_count, int id, char **crossword, int space_count, int max, int **crossword_int );
    int solver( int **point, int *length, char ***dictionary, int *words_count, char **crossword, int space_count, int max);