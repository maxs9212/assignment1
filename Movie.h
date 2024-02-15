#ifndef Movie_H_
#define Movie_H_
struct userStruct{
    int userId;
    float*ratings;
};
void displayMovies(char movieData[]);
char*movieFormat(int movieIndex,char movieData[]);
void updateUserNumber(char userRating[]);
float** createMatrix(char userRating[]);
void mallocMatrix(size_t x,size_t y,float(**ptr)[x][y]);
void fillMatrix(char userRating[],size_t x,size_t y,float array[x][y]);
void editMatrix(size_t x,size_t y,float array[x][y],int i, int j, float edit);
void arr_print (size_t x, size_t y, float array[x][y]);
int fillUserStruct(struct userStruct*user,int userID,char userRating[]);
void rateMovie(int userID,char userRating[]);
float movieRating(int movieIndex,char userRating[]);
#endif