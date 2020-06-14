#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>


#define MAX_SIZE 200
#define BUFF_SIZE 500
#define GET_SIZE(arr) sizeof(arr) / sizeof(arr[0])

// A representation of a languages documenttation links
typedef struct {
    char* name;
    char* url;
    char* search_url;
} Doc;


const Doc DOCS[9] = {
    {"Racket", "https://docs.racket-lang.org/", "https://docs.racket-lang.org/search/index.html?q="},
    {"Elixir", "https://hexdocs.pm/elixir/Kernel.html", "https://hexdocs.pm/elixir/search.html?q="},
    {"Rust", "https://doc.rust-lang.org/std/index.html", "https://doc.rust-lang.org/std/index.html?search="},
    {"Javascript", "https://developer.mozilla.org/en-US/", "https://developer.mozilla.org/en-US/search?q="},
    {"Java", "https://docs.oracle.com/en/java/javase/14/docs/api/index.html", "https://docs.oracle.com/en/java/javase/14/docs/api/index.html"},
    {"Python", "https://docs.python.org/3/", "https://docs.python.org/3/search.html?check_keywords=yes^&area=default^&q="},
    {"C", "https://devdocs.io/c/", "https://devdocs.io/c/"},
    {"C++", "https://devdocs.io/cpp/", "https://devdocs.io/cpp/"},
    {"Cpp", "https://devdocs.io/cpp/", "https://devdocs.io/cpp/"}
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
















