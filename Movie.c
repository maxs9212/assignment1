#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "Movie.h"

void displayMovies(char movieData[]){
    FILE *reader = fopen(movieData,"r");
    if(reader==NULL){
        printf("Error opening file");
        exit(1);
    }
    if(reader==NULL){
        printf("The file %s passed to the function doesn't exist.",movieData);
        fclose(reader);
        return;
    }
    printf("********* Movie Database *********\n");
    char carac;
    int condition=0;
    int numCond = 0;
    int num = 1;
    //print each char an check for special characters for correct format
    while(1){
        carac=fgetc(reader);
        if(feof(reader)){
            break;
        }
        if(numCond==0){
            printf("%d. ",num);
            num++;
            numCond=1;
        }
        if(carac=='_'){
            printf(" ");
            continue;
        }
        if(carac==' '){
            if(condition==0){
                printf(" (");
                condition = 1;
                continue;
            }
            else{
                printf(") ");
                continue;
            }
        }
        if(carac=='\n'){
            condition=0;
            numCond=0;
            printf("\n");
            continue;
        }
        printf("%c",carac);
    }
    fclose(reader);
}
//converts a single movie entry into a formatted movie string
char*movieFormat(int movieIndex,char movieData[]){
    FILE*read=fopen(movieData,"r");
    if(read==NULL){
        printf("Error opening file");
        exit(1);
    }
    int length=128;
    char buffer[length];
    for(int i=0;i<=movieIndex;i++){
        fgets(buffer,length,read);
    }
    fclose(read);
    char current='a';
    int i=1;
    while(current!='\0'){
        current=buffer[i];
        i++;
    }
    //i+2 for two parentheses
    char*formatted=(char*)malloc(sizeof(char)*(i+2));
    int cond=0;
    int offset=0;
    for(int j=0;j<i;j++){
        if(buffer[j]=='_'){
            formatted[j]=' ';
            continue;
        }
        if(buffer[j]==' '){
            if(cond==0){
                formatted[j]=' ';
                offset++;
                cond++;
                formatted[j+offset]='(';
                continue;
            }
            else if(cond==1){
                formatted[j+offset]=')';
                offset++;
                formatted[j+offset]=' ';
                continue;
            }
        }
        if(buffer[j]=='\n'){
            formatted[j+offset]='\0';
            continue;
        }
        formatted[j+offset]=buffer[j];
    }

    return formatted;
}
void updateUserNumber(char userRating[]){
    FILE *rating = fopen(userRating,"r+");
    if(rating==NULL){
        printf("Error opening file");
        exit(1);
    }
    int userNum=0;
    int movieNum=0;
    //read the current user number and movie number
    fscanf(rating,"%d%d",&userNum,&movieNum);
    userNum++;
    rewind(rating);
    //update the user number and movie number
    fprintf(rating,"%d %d",userNum,movieNum);
    fclose(rating);
    FILE*append=fopen(userRating,"a");
    //add a row of 0.0 ratings
    float empty=0.0f;
    //fprintf(append,"\n");
    for(int i = 0;i<movieNum;i++){
        fprintf(append,"%0.1f ",empty);
    }
    fprintf(append,"\n");
    fclose(append);
}

float** createMatrix(char userRating[]){
    FILE *reading=fopen(userRating,"r");
    if(reading==NULL){
        printf("Error opening file");
        exit(1);
    }
    int userNum = 0;
    int movieNum = 0;
    fscanf(reading,"%d%d",&userNum,&movieNum);
    float** matrix;//replaced float** by float*
    matrix=malloc(userNum*sizeof(float));
   
    
    for(int i = 0;i<userNum;i++){
        matrix[i]=malloc(userNum*sizeof(float));
        for(int j = 0;j<movieNum;j++){
            fscanf(reading,"%f",&matrix[i][j]);
        }
    }
    fclose(reading);
    return matrix;
}
void mallocMatrix(size_t x,size_t y,float(**ptr)[x][y]){
    *ptr=malloc(sizeof(float[x][y]));
}
void fillMatrix(char userRating[],size_t x,size_t y,float array[x][y]){
    FILE *reading=fopen(userRating,"r");
    if(reading==NULL){
        printf("Error opening file");
        exit(1);
    }
    int userNum = 0;
    int movieNum = 0;
    float temp;
    fscanf(reading,"%d%d",&userNum,&movieNum);
    for(int i=0;i<userNum;i++){
        for(int j=0;j<movieNum;j++){
            fscanf(reading,"%f",&temp);
            array[i][j]=temp;
        }
    }

}
void editMatrix(size_t x,size_t y,float array[x][y],int i, int j, float edit){
    array[i][j]=edit;
}
void arr_print (size_t x, size_t y, float array[x][y])
{
  for(size_t i=0; i<x; i++)
  {
    for(size_t j=0; j<y; j++)
    {
      printf("%f ", array[i][j]);
    }
    printf("\n");
  }
}
int fillUserStruct(struct userStruct*user,int userID,char userRating[]){
    user->userId=userID;
    FILE*read=fopen(userRating,"r");
    int length=256;
    char buffer[length];
    int userNum;
    int movieNum;
    for(int i=0;i<=userID;i++){
        fgets(buffer,length,read);
        if(i==0){
            sscanf(buffer,"%d%d",&userNum,&movieNum);
        }
    }
    //printf("%s",buffer);
    user->ratings=(float*)malloc(sizeof(float)*movieNum);
    float temp;
    int offset;
    char*ptr=buffer;
    for(int i=0;i<movieNum;i++){
        sscanf(ptr,"%f%n",&user->ratings[i],&offset);
        //printf("%f\n",user->ratings[i]);
        ptr+=offset;
    }
    fclose(read);
    return movieNum;
}
//this function allows a valid user to write a rating for a movie
void rateMovie(int userID,char userRating[]){
    int line = userID + 1;
   // float**matrix;
    //matrix=createMatrix(userRating);
    //start of new code
    FILE *reading=fopen(userRating,"r");
    if(reading==NULL){
        printf("Error opening file");
        exit(1);
    }
    size_t userNum = 0;
    size_t movieNum = 0;
    fscanf(reading,"%d%d",&userNum,&movieNum);
    float (*matrix)[userNum][movieNum];
    mallocMatrix(userNum,movieNum,&matrix);
    fillMatrix(userRating,userNum,movieNum,*matrix);
    arr_print(userNum,movieNum,*matrix);
    //end of new code
    int index=0;
    printf("Please enter the number of the movie you would like to rate: ");
    scanf("%d",&index);
    while(index<0||index>10){
        printf("Please enter a valid number(from 1 to 10): ");
        scanf("%d",&index);
    }
    float rating=0;
    printf("Please enter your rating for this movie: ");
    scanf("%f",&rating);
    while(rating<1||rating>5){
        printf("Please enter a valide rating(from 1 to 5): ");
        scanf("%f",&rating);
    }
    editMatrix(userNum,movieNum,*matrix,userID-1,index-1,rating);
    //matrix[userID-1][index-1]=(float)rating;
    printf("%f\n",matrix[userID-1][index-1]);
    //int userNum = 0;
    //int movieNum = 0;
    
    FILE*edit = fopen(userRating,"r+");
    if(edit==NULL){
        printf("Error opening file");
        exit(1);
    }
    fscanf(edit,"%d%d",&userNum,&movieNum);
    rewind(edit);
    fprintf(edit,"%d %d\n",userNum,movieNum);
    for(int i=0;i<userNum;i++){
        for(int j=0;j<movieNum;j++){
            fprintf(edit,"%0.1f ",matrix[i][j]);
        }
        fprintf(edit,"\n");
    }    
    fclose(edit);
/*
    for(int i=0;i<userNum;i++){
        if(matrix[i]==NULL){
            printf("This is wrong %d",i);
            continue;
        }
        free(matrix[i]);
    }
    */
    free(matrix);
}
//this function returns the average rating of other users for a given movie
float movieRating(int movieIndex,char userRating[]){
    float**matrix=createMatrix(userRating);
    FILE*read=fopen(userRating,"r");
    int userNum;
    fscanf(read,"%d",&userNum);
    fclose(read);
    float rating=0;
    int ratingNum=0;
    for(int i=0;i<userNum;i++){
        if(matrix[i][movieIndex]>0.001){
            rating+=matrix[i][movieIndex];
            ratingNum++;
        }
    }
    if(ratingNum>0){
        rating=rating/ratingNum;
    }
    /*
    for(int i=0;i<userNum;i++){
        free(matrix[i]);
    }
    */
    free(matrix);
    
    return rating;
    
}