#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "User.h"
#include "Movie.h"
#define userFile "user_data.txt"
#define movieData "movie_database.txt"
#define userRating "user_ratings.txt"
int main(int argc, char* argv[]){
    int choice = -1;
    while(choice!=0){

        printf("***** Movie Recommendation System *****\n");
        printf("1. Register User\n");
        printf("2. Display Movies\n");
        printf("3. Rate a Movie\n");
        printf("4. Get Movie Recommendation\n");
        printf("0. Exit\n");
        printf("Enter your choice: ");
        scanf("%d",&choice);

        switch (choice)
        {
        case 1: 
            addUser(userFile);
            updateUserNumber(userRating);
            break;
        case 2:
            printf("----------------------------------\n");
            displayMovies(movieData);
            printf("\n");
            break;
        case 3:{
            printf("Please enter a username: ");
            char*input;
            input = (char*)malloc(sizeof(char)*16);
            scanf("%s",input);
            int x = verifyUser(input,userFile);
            free(input);
            if(x==0){
                printf("User was not found.\n");
                break;
            }
            displayMovies(movieData);
            rateMovie(x,userRating);
            
            }
            break;
        case 4:{ 
            //input username, check and get ID
            printf("Please enter a username: ");
            char*input;
            input = (char*)malloc(sizeof(char)*16);
            scanf("%s",input);
            int x=verifyUser(input,userFile);
            if(x==0){
                printf("User was not found.\n");
                break;
            }
            free(input);
            //create user struct
            struct userStruct*doe=malloc(sizeof(struct userStruct));
            int movieNum=fillUserStruct(doe,x,userRating);
            //figure which movies are unseen by user
            //unseenMovies contains the index of each movie unseen by the user therefore the size is the total number of movies to insure someone who hasn't seen any movies works
            int unseenMovies[movieNum];
            int j=0;
            //store movie index of unseen movies in array
            for(int i=0;i<movieNum;i++){
                if(doe->ratings[i]==0.0){
                unseenMovies[j]=i;
                j++;
                }
            }
            printf("Here are the predicted ratings for the movies you didn't rate yet:\n");
            for(int i=1;i<=j;i++){
                //print a movie with the expected rating
                char*string=movieFormat(unseenMovies[i-1],movieData);
                float rate=movieRating(unseenMovies[i-1],userRating);
                printf("%d. %s ",i,string);
                printf("expected rating: %0.1f\n",rate);
                free(string);
            }
            free(doe->ratings);
            free(doe);
            }
            break;
        
        default:
            break;
        }

    }

    return 0;
}