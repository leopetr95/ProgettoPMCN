#include "basic.h"
#include "parser.h"
#include <stdio.h>
#include <stdlib.h>
#include "basic.h"
#include "dynamic_list.h"
#include <string.h>


void move_pointer(char**string,int n){//sposta un puntatore di n posizioni,n può essere negativo
    if(string==NULL || *string==NULL){
        handle_error_with_exit("error in move_pointer\n");
    }
    else if(n>0) {
        for (int i = 0; i < n; i++) {
            (*string)++;
        }
    }
    else if(n<0){
        for (int i = 0; i < n; i++) {
            (*string)--;
        }
    }
    return;
}

int skip_space(char**string){//sposta un puntatore finquando trova caratteri uguali allo spazio
    if(*string==NULL || string==NULL){
        handle_error_with_exit("error in move_pointer\n");
    }
    int count=0;
    while(**string==' '){
        (*string)++;
        count++;
    }
    return count;
}
char is_blank(char*string){//ritorna vero se la stringa è composta solo da spazi
    if(string==NULL){
        handle_error_with_exit("error in is_blank\n");
    }
    while(*string!='\0'){
        if(*string==' '){
            string++;
        }
        else{
            return 0;
        }
    }
    return 1;
}

int parse_integer_and_move(char**string) {//fa il parse dell'intero e sposta il puntatore al carattere dopo l'intero
    if(*string==NULL || string==NULL){
        handle_error_with_exit("error in parse_integer\n");
    }
    char*errptr;
    int value;
    errno = 0;
    value= (int) strtol(*string, &errptr, 0);
    if (errno != 0 || (*errptr != '\0' && *errptr!=' ' && *errptr!='\n')) {
        handle_error_with_exit("invalid number\n");
    }
    *string=errptr;//sposta il puntatore
    return value;
}

long parse_long_and_move(char**string) {
    if(*string==NULL || string==NULL){
        handle_error_with_exit("error in parse_integer\n");
    }
    char*errptr;
    long value;
    errno = 0;
    value=strtol(*string, &errptr, 0);
    if (errno != 0 || (*errptr != '\0' && *errptr!=' ' && *errptr!='\n')) {
        handle_error_with_exit("invalid number\n");
    }
    *string=errptr;//sposta il puntatore
    return value;
}

double parse_double_and_move(char**string){
    if(*string==NULL || string==NULL){
        handle_error_with_exit("error in parse_double\n");
    }
    char*errptr;
    double value;
    errno = 0;
    value=strtod(*string, &errptr);
    if (errno != 0 || (*errptr != '\0' && *errptr!=' ' && *errptr!='\n')) {
        handle_error_with_exit("invalid number\n");
    }
    *string=errptr;//sposta il puntatore
    return value;
}
long parse_long(char*string) {//fa il parse per ottenere un long
    if(string==NULL){
        handle_error_with_exit("error in parse_integer\n");
    }
    char*errptr;
    long value;
    errno = 0;
    value= (int) strtol(string, &errptr, 0);
    if (errno != 0 || (*errptr != '\0' && *errptr!=' ')) {
        handle_error_with_exit("invalid number\n");
    }
    return value;
}
int parse_integer(char*string) {
    if(string==NULL){
        handle_error_with_exit("error in parse_integer\n");
    }
    char*errptr;
    int value;//
    errno = 0;
    value= (int) strtol(string, &errptr, 0);
    if (errno != 0 || (*errptr != '\0' && *errptr!=' ')) {
        handle_error_with_exit("invalid number\n");
    }
    return value;
}

double parse_double(char*string){
    if(string==NULL){
        handle_error_with_exit("error in parse_double\n");
    }
    char*errptr;
    double value;
    errno = 0;
    value=strtod(string, &errptr);
    if (errno != 0 || (*errptr != '\0' && *errptr!=' ')) {
        handle_error_with_exit("invalid number\n");
    }
    return value;
}
int parse_integer_S_from_command_line(int argc,char*argv[],int N){//fa il parse di S da riga di comando.argc=numero paraetri+1,argv vettore di puntatori a char
    if(N<=0){
        handle_error_with_exit("N must be greater than 0\n");
    }
    if(argc!=2) {
        handle_error_with_exit("value S not specified\n");
    }
    int S=parse_integer(argv[1]);
    if(S>N || S<0){
        handle_error_with_exit("S is greater than N\n");
    }
    return S;
}
