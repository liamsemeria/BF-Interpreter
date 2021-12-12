#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

char garden[30000] = {0}; char *plant = garden;

// returns the string after the match of the first paren
char* mirrorfind(char* s,int n) {
    if (strlen(s)==0) return "a";
    if (*s == '[') { 
        return mirrorfind(s+1,n+1);
    }else if (*s == ']') {
        if (n==1) return s+1;
        return mirrorfind(s+1,n-1);
    }
    else return mirrorfind(s+1,n);
}
// +++ > ++++ < [>[->+>+<<]>[-<+>]<<-]>>>@

void brainfuck(char* s, char* tape) {
    if (strlen(s)==0) return;
    //printf("%s \n",s);
    switch (*s) {
        case '>': tape++; break;
        case '<': tape--; break;
        case '+': *tape+=1; break;
        case '-': *tape-=1; break;
        case '.': printf("%c",*tape); break;
        case '@': printf("{%d} \n",*tape); break;
        case '[':
            while(*tape>0) brainfuck(s+1,tape);
            if (*tape==0) brainfuck(mirrorfind(s,0),tape);
            return;
            // tape same after bc call stack need to return env
            break;
        case ']':
            return;
            //if (*tape > 0) return;
            //else printf("((%s))",s);
            break;
        default: break;
    }
    brainfuck(s+1,tape);
    return;
}

int main(int argc, char** argv)
{
    for (int i = 2; i < argc; i++) {
        garden[i-2] = argv[i][0];
    }
    FILE *fp;
    fp = fopen(argv[1], "r");
    if (fp == NULL) exit(EXIT_FAILURE);
    long length;
    char* buffer;
    if (fp) {
        fseek (fp, 0, SEEK_END);
        length = ftell (fp);
        fseek (fp, 0, SEEK_SET);
        buffer = malloc (length);
        if (buffer) fread (buffer, 1, length, fp);
        fclose (fp);
    }
    //printf("%s \n",mirrorfind(buffer,0));
    //printf("%s \n",buffer);
    brainfuck(buffer,plant);

    exit(EXIT_SUCCESS);
}