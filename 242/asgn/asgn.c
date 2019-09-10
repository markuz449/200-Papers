#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>
#include <time.h>
#include <ctype.h>
#include "tree.h"
#include "htable.h"
#include "mylib.h"

/**
 * Printf the help message.
 */
void print_help(){
    printf("Usage: ./sample-asgn [OPTIONS]... <STDIN>\n");
    printf("\n");
    printf("Perform tasks using a hash table or binary tree.  ");
    printf("By default, words \n");
    printf("read from stdin are added to the data structure ");
    printf("before printing \n");
    printf("them, along with their frequencies, to stdout.\n");
    printf("\n");
    printf(" -T           Use a tree data structure (default is ");
    printf("hash table)\n");
    printf(" -c FILENAME  Check spelling of words in FILENAME ");
    printf("using words\n");
    printf("              from stdin as dictionary.  Print ");
    printf("unknown words to\n");
    printf("              stdout, timing info etc to stderr ");
    printf("(ignore -o & -p)\n");
    printf(" -d           Use double hashing (linear probing ");
    printf("is the default)\n");
    printf(" -e           Display entire contents of hash ");
    printf("table on stderr\n");
    printf(" -o           Output the tree in DOT form to file ");
    printf("'tree-view.dot'\n");
    printf(" -p           Print hash table stats instead of ");
    printf("frequencies & words\n");
    printf(" -r           Make the tree an RBT (the default ");
    printf("is a BST)\n");
    printf(" -s SNAPSHOTS Show SNAPSHOTS stats snapshots (if ");
    printf("-p is used)\n");
    printf(" -t TABLESIZE Use the first prime >= TABLESIZE as ");
    printf("htable size\n");
    printf("\n");
    printf(" -h           Display this message\n");
    printf("\n");
}

/**
 * Prints a word and its frequency to standard error.
 *
 * @param freq the frequency if the word.
 * @param word the word to be printed.
 */
static void print_info(int freq, char *word) {
    fprintf(stderr, "%-4d %s\n", freq, word);
}

/**
 * Checks if a given candidate is a prime. If it is, return 1. If not,
 * return 0;
 *
 * @param candidate the integer to be checked.
 * @return an int. 1 if prime, 0 if not prime.
 */
int is_prime(int candidate){
    int n = 2;
    
    for(n = 2; n < candidate; n++){
        if (candidate % n == 0){
            return 0;
        }
    }
    return 1;
}

/**
 * Given a starting int, iterates through odd numbers until it finds a
 * prime. Then it returns that prime.
 *
 * @param n the inital int.
 *
 * @return the closest prime larger than or equal to the given n.
 */
int get_next_prime(int n){
    int is_p = 0;
    if ((n % 2) == 0){
        n++;
    }
    while(is_p == 0){
        if(is_prime(n)){
            return n;
        }else{
            n += 2;
        }
    }
    return n;
}

/**
 * Generates a visual representation of the tree using the "dot" language
 * and saves it as 'tree-view.dot'. The visual representation can be used
 * to see what nodes are red and black for the RBT data structure as well
 * as the frequencies. The visual representation will make the tree look
 * like what it is expected to look like.
 *
 * @param t The tree that will be converted to a visual representation.
 * @param file The output file for the visual representation of the tree.
 */
void generate_dot(tree t, FILE *file){
    file = fopen("tree-view.dot", "ab+");
    if (file == NULL){
        printf("Error opening file!\n");
        exit(1);
    }
    printf("Creating dot file 'tree-view.dot'\n");
    tree_output_dot(t, file);

    fclose(file);
}

/**
 * Checks if the words in a given file are spelled correctly by checking
 * them against the words in the tree. The words that are not spelt
 * correctly are printed as well as the time it took to check through
 * the tree and the file. The amount of words not in the tree is also printed.
 *
 * @param t The tree being used as a dctionary.
 * @param file The file that is being checked for spelling mistakes.
 * @param time The amount of time it took to fill the tree.
 */
void t_print_dictionary(tree t, FILE *file, double time){
    clock_t begin, end;
    int count = 0;
    char str[256];
    
    begin = clock();
    while (getword(str, sizeof str, file) != EOF){
        if (0 == tree_search(t, str)){
            printf("%s\n", str);
            count++;
        }
    }
    end = clock();

    printf("Fill time     : %.6f\n", time);
    printf("Search time   : %.6f\n",
           (double)(end - begin) / CLOCKS_PER_SEC);
    printf("Unknown words = %d\n", count);
}

/**
 * Checks if the words in a given file are spelled correctly by checking
 * them against the words in the hash table. The words that are not spelt
 * correctly are printed as well as the time it took to check through
 * the hash table and the file. The amount of words not in the hash table is
 * also printed.
 *
 * @param h The hash table being used as a dctionary.
 * @param file The file that is being checked for spelling mistakes.
 * @param time The amount of time it took to fill the hash table.
 */
void h_print_dictionary(htable h, FILE *file, double time){
    clock_t begin, end;
    int count = 0;
    char str[256];
    
    begin = clock();
    while (getword(str, sizeof str, file) != EOF){
        if (0 == htable_search(h, str)){
            printf("%s\n", str);
            count++;
        }
    }
    end = clock();
    
    printf("Fill time     : %.6f\n", time);
    printf("Search time   : %.6f\n",
           (double)(end - begin) / CLOCKS_PER_SEC);
    printf("Unknown words = %d\n", count);
}

/**
 * Prints the entire hash table and if the -p optcode is being used
 * the stats of the hash table will also be printed.
 *
 * @param h The hash table that is going to be printed.
 * @param stats_type Checks if the -p optcode is being used.
 */
void print_extended_stats(htable h, int stats_type){
    printf("  Pos  Freq  Stats  Word\n");
    printf("----------------------------------------\n");
    htable_print_entire_table(h);
    if(stats_type == 0){
        htable_print(h, print_info);
    }
}

/**
 * Makes the tree data structure instead of
 * the hash table data structure.
 *
 * Runs any of the functions that were declared by the
 * optcodes in the terminal.
 *
 * Gets the strings from stdin using getword() and inserts
 * them into the tree. After inserting the string the root
 * of the tree is always turned to black to make sure the black
 * height of the tree is always correct.
 *
 * @param tree_type Checks if the -r optcode is being used
 *        turning the bst into a rbt.
 * @param dictionary Checks if the -c optcode is being used.
 * @param out_type Checks if the -o optcode is being used.
 * @param file File stream used for reading and writing from a file.
 */
void make_tree(int tree_type, int dictionary,
               int out_type, FILE *file){
    char str[256];
    tree t = tree_new();
    clock_t begin, end;
    double time;

    begin = clock();
    while(getword(str, sizeof str, stdin) != EOF){
        t = tree_insert(t, str, tree_type);
        t = tree_fix_root(t);
    }
    end = clock();
    time = (double)(end - begin) / CLOCKS_PER_SEC;
    
    if (dictionary == 1){
        t_print_dictionary(t, file, time);
    } else {
        tree_preorder(t, print_info);
        if (out_type == 1){
            generate_dot(t, file);
        }
    }
    tree_free(t);
}

/**
 * Makes the htable data structure and runs any functions declared
 * by the optcodes in the terminal.
 *
 * Gets the strings from stdin using getword() and inserts
 * them into the htable.  
 *
 * @param file File stream used for reading and writing from a file.
 * @param snap The amount of snapshots to be used.
 * @param dictionary Checks if the -c optcode is being used.
 * @param hash_type Checks if the -d optcode is being used.
 * @param display_type Checks if the -e optcode is being used.
 * @param stats_type Checks if the -p optcode is being used.
 * @param table_size The new table size for the hash table.
 */
void make_htable(FILE *file, int snap, int dictionary, int hash_type,
                 int display_type, int stats_type, int table_size){
    char str[256];
    htable h = NULL;
    clock_t begin, end;
    double time;
    
    h = htable_new(table_size, hash_type);
    begin = clock();
    while(getword(str, sizeof str, stdin) != EOF){
        htable_insert(h, str);
    }
    end = clock();
    time = (double)(end - begin) / CLOCKS_PER_SEC;
    
    if (dictionary == 1){
        h_print_dictionary(h, file, time);
    } else {
        if(display_type == 1){
            print_extended_stats(h, stats_type);
        }
        if(stats_type == 1){
            htable_print_stats(h, file, snap);
        }
        if(display_type == 0 && stats_type == 0){
            htable_print(h, print_info);
        }
    }
    htable_free(h);
}

/**
 * This is the main method. Depending on the combination of optcodes used
 * when running the file the data structure will be a htable or a tree and
 * will output in different ways.
 *
 * Run the file with the optcode -h to find out what the optcodes are.
 *
 * @param argc the number of inputs to main.
 * @param argv an array containing all the inputs where the first input
 * is the program name.
 *
 * @return EXIT_SUCCESS.
 */
int main(int argc, char **argv){
    const char *optstring = "Tc:deoprs:t:h";
    char option;
    char *command = "";
    FILE *file = stdout; 
    int snap = 10;
    int size_set;
    
    int struct_type = 0;  /* T. Default struct type htable. */
    int dictionary = 0;   /* c. Default false. */
    int hash_type = 0;    /* d. Default hash type linear probing. */
    int display_type = 0; /* e. Default does not print full table. */
    int out_type = 0;     /* o. Default does not make tree pdf. */
    int stats_type = 0;   /* p. Default does not print extended stats. */
    int tree_type = 0;    /* r. Default tree type BST. */
    int table_size = 113; /* t. Default table size 113. */

    while((option = getopt(argc, argv, optstring)) != EOF){
        switch(option){
            case 'T':
                /* opcode: -T changes the data structure from
                   a hash table to a tree. */
                struct_type = 1;
                break;
            case 'c':
                /* opcode: -c Creates a dictionary from the words given via
                   standard input. Then checks the words in the dictionary
                   against words given in the file.
                   Prints out all misspellings. */
                dictionary = 1;
                command = optarg;
                file = fopen(command, "r");
                break;
            case 'd':
                /* opcode: -d Changes the hashing collision resolution
                   strategy from linear probing to double hashing. */
                hash_type = 1;
                break;
            case 'e':
                /* opcode: -e Prints out the entire contents of the
                   hash table to stderr. Prints out the index, frequency,
                   stats and the key if it exists. */
                display_type = 1;
                break;
            case 'o':
                /* opcode: -o Generates a file 'tree-view.dot' which
                   can be used to represent the tree in a dot format. */
                out_type = 1;
                break;
            case 'p':
                /*opcode: -p Prints out stats info instead of printing
                  the frequencies and words. */
                stats_type = 1;
                break;
            case 'r':
                /*opcode: -r Changes the tree data structure to be a
                  red-black tree data structure instead of a the default
                  binary-search tree. */
                tree_type = 1;
                break;
            case 's':
                /*opcode: -s Displays up to the given amount of snapshots
                  when given -p as an arguement. */
                command = optarg;
                snap = atoi(command);
                if (snap == 0 && command[0] != '0'){
                    snap = 10;
                }
                break;
            case 't':
                /*opcode: -t Changes the table size to the first prime
                  that is greater than or equal to the value given in
                  the terminal. */
                command = optarg;
                size_set = atoi(command);
                if (!(size_set == 0 && command[0] != '0')){
                    table_size = get_next_prime(size_set);
                }
                break;
            case 'h':
                /*opcode: -h Prints out the help message on how to
                  use the program. */
                print_help();
                return EXIT_SUCCESS;
            default:
                /*Prints out the help message on how to use the program
                  as the default or if there is an error in the terminal. */
                print_help();
                return EXIT_SUCCESS;
        }
    }

    if (struct_type == 0){
        /* Uses hash table data structure. */
        make_htable(file, snap, dictionary, hash_type, display_type,
                    stats_type, table_size);
    }else {
        /* Uses tree data structure. */
        make_tree(tree_type, dictionary, out_type, file); 
    }
    
    return EXIT_SUCCESS;
}
