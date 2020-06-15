#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>


#define MAX_SIZE 200
#define BUFF_SIZE 500
#define ID_LEN 20
#define GET_SIZE(arr) sizeof(arr) / sizeof(arr[0])

// A representation of a languages documenttation links
typedef struct {
    char* name;
    char* url;
    char* search_url;
    char* secondary_url;
} Doc;


const Doc DOCS[9] = {
    {"Racket", "https://docs.racket-lang.org/", "https://docs.racket-lang.org/search/index.html?q=", NULL},
    {"Elixir", "https://hexdocs.pm/elixir/Kernel.html", "https://hexdocs.pm/elixir/search.html?q=", NULL},
    {"Rust", "https://doc.rust-lang.org/std/index.html", "https://doc.rust-lang.org/std/index.html?search=", NULL},
    {"Javascript", "https://developer.mozilla.org/en-US/", "https://developer.mozilla.org/en-US/search?q=", NULL},
    {"Java", "https://docs.oracle.com/en/java/javase/14/docs/api/index.html", "https://docs.oracle.com/en/java/javase/14/docs/api/index.html", NULL},
    {"Python", "https://docs.python.org/3/", "https://docs.python.org/3/search.html?check_keywords=yes^&area=default^&q=", NULL},
    {"C", "https://en.cppreference.com/w/c/language", "https://en.cppreference.com/mwiki/index.php?title=Special%3ASearch^&search=", "https://en.cppreference.com/w/c/language/"},
    {"C++", "https://en.cppreference.com/w/cpp/language", "https://en.cppreference.com/w/cpp/language", NULL},
    {"Cpp", "https://en.cppreference.com/w/cpp/language", "https://en.cppreference.com/w/cpp/language", NULL}
};

char identifiers[17][ID_LEN] = {
    "break",
    "const", 
    "continue",
    "do",
    "enum",
    "extern",
    "for", 
    "goto",
    "if", 
    "return",
    "sizeof",
    "struct",
    "switch", 
    "typedef",
    "union",
    "while",
    "volatile"
};

// Determines if two string are the same ignoring cases
static bool strcmpNoCase(const char *s1, const char* s2) {
    int i = 0;
    while(true) {
        if(s1[i] == '\0' && s2[i] == '\0') {
            return true;
        } 
        
        else if(s1[i] == '\0' || s2[i] == '\0' ) {
            return false;
        }
        
        if (tolower(s1[i]) != tolower(s2[i])) {
            return false;
        }
        i++;
    }
}

static bool isSpace(char c) {
    return c == ' ';
}

// Trims left side of a string
static char* leftTrim(char *str) {
    while( isSpace(*str)) {
        str++;
    }
    return str;
}

static void openInBrowser(char* url) {
    char command[MAX_SIZE] = "start ";
    strncat(command, url, MAX_SIZE);
    system(command);
    exit(EXIT_SUCCESS);
}

static bool member(char* search, char array[][ID_LEN], int size) {
    for(int i = 0; i < size; i++) {
        if (strcmpNoCase (array[i], search)) {
            return true;
        }
    }
    return false;
}


// checks if the inputted langauge is supported, if so then looks it up in the users
//  browser.
void checkDocs(const char *lang, char *search) {
    for(int i = 0; i < GET_SIZE(DOCS); i++) {
        const Doc *d = &DOCS[i];
        if (strcmpNoCase(d->name, lang)) {
            // See if search is empty? If so just open the home page
            if(strncmp(search, "", MAX_SIZE) == 0) {
                openInBrowser(d->url);
            } else {
                if (strncmp (d->name, "C", MAX_SIZE) == 0) {
                    if(member(search, identifiers, GET_SIZE(identifiers))) {
                        char url[MAX_SIZE] = "";
                        strncat(url, d->secondary_url, MAX_SIZE);
                        strncat(url, search, MAX_SIZE);
                        openInBrowser(url);
                    }
                }
                char url[MAX_SIZE] = "";
                strncat(url, d->search_url, MAX_SIZE);
                strncat(url, search, MAX_SIZE);
                openInBrowser(url);
            }
        }
    }
    printf("Langauge not supported");
}


int main(int argc, char *argv[]) {
    if(argc < 2) {
        printf("Try: doc --help");
        exit(EXIT_FAILURE);
    }

    if (strcmpNoCase(argv[1], "--help")) {
        printf("Command Format:\n");
        printf("  doc <language> <search>  where search is optional.\n");
        printf("The following languages are supported:\n");
        char buffer[BUFF_SIZE];
        for(int i=0; i < GET_SIZE(DOCS); i++) {
            snprintf(buffer, BUFF_SIZE, "  - %s\n", DOCS[i].name);
            printf("%s", buffer);
        }
        exit(EXIT_SUCCESS);
    }

    char search[MAX_SIZE] = "";
    for(int i = 2; i < argc; i++) {
        strncat(search, " ", MAX_SIZE); // add space 
        strncat(search, argv[i], MAX_SIZE);
    }
    checkDocs(argv[1], leftTrim(search));
}
















