#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define BUFFER_SZ 50

//prototypes
void usage(char *);
void print_buff(char *, int);
int  setup_buff(char *, char *, int);

//prototypes for functions to handle required functionality
int  count_words(char *, int, int);
//add additional prototypes here


int setup_buff(char *buff, char *user_str, int len){
    //TODO: #4:  Implement the setup buff as per the directions
    char *src = user_str; //Pointer to source string
    char *dest = buff; //Pointer to destination buffer
    int count = 0; //Tracks the number of characters 

    //Processes the user's string
    while (*src != '\0') {
        //Handling whitespace characters
        if (*src == ' ' || *src == '\t') {
            if (count > 0 && *(dest - 1) != ' ') {
                *dest = ' ';
                dest++;
                count++;
            }
        } else {
            *dest = *src;
            dest++;
            count++;
        }
        //When string exceeds buffer size
        if (count > len) {
            fprintf(stderr, "Error: Provided string is too large.\n");
            return -1; 
        }

        src++;
    }

    //Fill remaining buffer with dots
    while (count < len) {
        *dest = '.';
        dest++;
        count++;
    }

    return count;
}

void print_buff(char *buff, int len){
    printf("Buffer:  ");
    for (int i=0; i<len; i++){
        putchar(*(buff+i));
    }
    putchar('\n');
}

void usage(char *exename){
    printf("usage: %s [-h|c|r|w|x] \"string\" [other args]\n", exename);

}

void search_and_replace(char *buff, int str_len, char *search, char *replace) {
    char *pos = NULL; //Poiner to find the word being replaced
    int search_len = 0; //Length of the word to search for
    int replace_len = 0; //Length of the replacement word

    while (search[search_len] != '\0') {
        search_len++;
    }

    while (replace[replace_len] != '\0') {
        replace_len++;
    }

    //Find the word to replace
    for (int i = 0; buff[i] != '\0' && buff[i] != '.'; i++) {
        int match = 1;
        for (int j = 0; j < search_len; j++) {
            if (buff[i + j] != search[j] || buff[i + j] == '\0') {
                match = 0;
                break;
            }
        }
        if (match) {
            pos = &buff[i];
            break;
        }
    }

    //If the word doesn't exist
    if (!pos) {
        printf("Not Implemented!\n");
        exit(1);
    }

    if (replace_len <= search_len) {
        for (int i = 0; i < replace_len; i++) {
            pos[i] = replace[i];
        }

        char *src = pos + search_len;
        char *dst = pos + replace_len;
        while (*src != '\0' && *src != '.') {
            *dst++ = *src++;
        }
        while (dst < buff + str_len) {
            *dst++ = '.';
        }
    } else {
        int shift = replace_len - search_len;
        char *end = buff;

        while (*end != '\0' && *end != '.') {
            end++;
        }

        if ((end - buff) + shift >= str_len) {
            exit(1);
        }

        for (char *src = end; src >= pos + search_len; src--) {
            *(src + shift) = *src;
        }

        //Replacing the word
        for (int i = 0; i < replace_len; i++) {
            pos[i] = replace[i];
        }
    }
}

void print_words_and_length(char *buff, int str_len) {
    printf("Word Print\n----------\n");

    char *start = NULL; //Pointer for the start of a word
    int word_index = 1; //Index for numbering a word
    int word_length = 0; //Length of a word
    int word_count = 0; //Number of words in sentence

    //Iterate through buffer 
    for (int i = 0; i <= str_len; i++) {
        if (buff[i] != ' ' && buff[i] != '.' && buff[i] != '\0') {
            if (start == NULL) {
                start = &buff[i];
            }
            word_length++;
        } else {
            if (start != NULL) {
                printf("%d. ", word_index++);
                //Print all the characters of a word
                for (int j = 0; j < word_length; j++) {
                    putchar(start[j]);
                }
                printf("(%d)\n", word_length);

                start = NULL;
                word_length = 0;
                word_count++;
            }
        }
    }
    printf("\nNumber of words returned: %d\n", word_count);
}

void reverse_string(char *buff, int str_len) {
    char *start = buff;
    char *end = buff + str_len - 1;
    char temp;

    while (*end == '.' && end > start) {
        end--;
    }

    //Reversing the string by swapping the characters
    while (start < end) {
        temp = *start;
        *start = *end;
        *end = temp;
        start++;
        end--;
    }
}

int count_words(char *buff, int len, int str_len){
    //YOU MUST IMPLEMENT
    int count = 0; //Word count
    int in_word = 0; //Tracks if we're inside a word

    for (int i = 0; i < str_len; i++) {
        if (buff[i] != ' ' && buff[i] != '.') {
            if (!in_word) {
                count++;
                in_word = 1; //Inside word
            }
        } else {
            in_word = 0; //Outside word
        }
    }

    return count;
}

//ADD OTHER HELPER FUNCTIONS HERE FOR OTHER REQUIRED PROGRAM OPTIONS

int main(int argc, char *argv[]){

    char *buff;             //placehoder for the internal buffer
    char *input_string;     //holds the string provided by the user on cmd line
    char opt;               //used to capture user option from cmd line
    int  rc;                //used for return codes
    int  user_str_len;      //length of user supplied string

    //TODO:  #1. WHY IS THIS SAFE, aka what if arv[1] does not exist?
    //      PLACE A COMMENT BLOCK HERE EXPLAINING
    //It's safe because it ensures that the user provides a valid
    //argument. If the user doesn't provide a valid argument, then 
    //the program simply exits.
    if ((argc < 2) || (*argv[1] != '-')){
        usage(argv[0]);
        exit(1);
    }

    opt = (char)*(argv[1]+1);   //get the option flag

    //handle the help flag and then exit normally
    if (opt == 'h'){
        usage(argv[0]);
        exit(0);
    }

    //WE NOW WILL HANDLE THE REQUIRED OPERATIONS

    //TODO:  #2 Document the purpose of the if statement below
    //      PLACE A COMMENT BLOCK HERE EXPLAINING
    //The purpose of this if statment is to ensure that the user
    //provides the right amount of arguments. 
    if (argc < 3){
        usage(argv[0]);
        exit(1);
    }

    input_string = argv[2]; //capture the user input string

    //TODO:  #3 Allocate space for the buffer using malloc and
    //          handle error if malloc fails by exiting with a 
    //          return code of 99
    // CODE GOES HERE FOR #3
    buff = (char *)malloc(BUFFER_SZ);
    if (buff == NULL) {
        printf("Error: Memory allocation failed.\n");
        exit(99);
    }

    user_str_len = setup_buff(buff, input_string, BUFFER_SZ);     //see todos
    if (user_str_len < 0){
        printf("Error setting up buffer, error = %d", user_str_len);
        exit(2);
    }

    switch (opt){
        case 'c':
            rc = count_words(buff, BUFFER_SZ, user_str_len);  //you need to implement
            if (rc < 0){
                printf("Error counting words, rc = %d", rc);
                exit(2);
            }
            printf("Word Count: %d\n", rc);
            break;

        //TODO:  #5 Implement the other cases for 'r' and 'w' by extending
        //       the case statement options
        case 'r':
            reverse_string(buff, user_str_len);
            break;

        case 'w':
            print_words_and_length(buff, user_str_len);
            break;

        case 'x':
            if (argc < 5) {
                free(buff);
                exit(1);
            }
            search_and_replace(buff, user_str_len, argv[3], argv[4]);
            break;

        default:
            usage(argv[0]);
            exit(1);
    }

    //TODO:  #6 Dont forget to free your buffer before exiting
    print_buff(buff,BUFFER_SZ);
    free(buff);
    exit(0);
}

//TODO:  #7  Notice all of the helper functions provided in the 
//          starter take both the buffer as well as the length.  Why
//          do you think providing both the pointer and the length
//          is a good practice, after all we know from main() that 
//          the buff variable will have exactly 50 bytes?
//  
//          PLACE YOUR ANSWER HERE
//It is good practice because it improves flexibilty and safety.
//By providing both the pointer and the length, it allows the functions
//to work with buffers of different sizes, and it ensures that 
//operations stay within valid bounds. 