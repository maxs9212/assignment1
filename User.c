#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "User.h"

int verifyUser(char*userInput, char userFile[]){
    FILE *reader = fopen(userFile,"r");
    if(reader==NULL){
        printf("The file %s passed to the function doesn't exist.",userFile);
        fclose(reader);
        return -1;
    }
    const unsigned MAXLENGTH = 16;
    char buffer[MAXLENGTH];
    //while loop verifies for the presence of userInput in the opened file line by line
    int i = 0;
    int size = strlen(userInput);
    int condition=1;
    int iteration=0;
    while(fgets(buffer,MAXLENGTH,reader)){
        condition=1;
        iteration++;
        //for loop compares each character from userInput with current line from file
        for(i =0;i<size;i++){
            if(tolower(buffer[i])-tolower(userInput[i])==0){//buffer[i]==userInput[i]
                continue;
            }
            else{
                condition=0;
                break;
            }
        }
        //if the loop validated every character from userInput and the next character in buffer is a space, return 1
        if((condition==1)&&(buffer[i]==' ')){
            printf("The user %s was found in the file.\n",userInput);
            fclose(reader);
            return iteration;
        }
    }
    fclose(reader);
    return 0;
}
void addUser(char userFile[]){
    //read file
    FILE *reader = fopen(userFile,"r");
    if(reader==NULL){
        printf("Error when trying to open the file %s\n",userFile);
        fclose(reader);
        return;
    }
    int counter = 1;
    const unsigned BUFFER = 256;
    char buffer[BUFFER];
    //count how many lines in file
    while(fgets(buffer,BUFFER,reader)){
        counter++;
    }
    fclose(reader);
    char*input = (char*) malloc(16);
    if(input==NULL){
        printf("Fatal error when allocating memory.");
        exit(1);
    }
    int result = 1;
    //process user input for username
    while(result>0){
        printf("Please enter the username: ");
        scanf("%s",input);
        result=verifyUser(input,userFile);
    }
    if(result==-1){
        printf("Due to file error, exiting...");
        exit;
    }
    //append the txt file with the username and number
    FILE *append = fopen(userFile,"a");
    //fprintf(append,"\n");
    fprintf(append,input);
    fprintf(append," %d\n",counter);
    fclose(append);
    free(input);
    printf("User is successfully registered\n");
}
