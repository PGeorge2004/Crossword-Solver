
    char **crossword_creator( FILE *ifp, int *num);
    int **crossword_2d_creator( char **crossword, int max, int **pl, int *words_count, int *space_count, int **length_for_check, int ***points_for_check);
    int words_counter( char **crossword, int max, int *words_hor, int *words_ver);
    void swaps( int *a, int *b);
    void bubble_sort( int n, int **x, int **ar);
    void swaps_array(char **a, char **b);
    void bubble_sort_arr( int n, int *x, char **ar);
    void skip_space(FILE *ifp);