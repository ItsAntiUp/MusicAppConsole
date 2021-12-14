/**
 * Author:          Kostas Ragauskas (kostas.ragauskas@stud.mif.vu.lt)
 * Last Modified:   2021-01-25
 *
 * Content:         Main constants / structures / functions of the program.
 **/

#ifndef ALL_H
#define ALL_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <errno.h>
#include <assert.h>
#include <dirent.h>

#define MAX_TIME_SIZE 9
#define MAX_NAME_SIZE 30
#define MAX_ARR_SIZE 999
#define MAX_TEXT_SIZE 100
#define MAX_YEAR_SIZE 4
#define MAX_RATING_SIZE 5
#define MAX_PATH_SIZE 256

#define MIN_YEAR 1900
#define SECONDS 60

#define BITRATE_LOW 128
#define BITRATE_MEDIUM 320
#define BITRATE_HIGH 960
#define BITRATE_LOSSLESS 1411

#define NDEBUG

//Defining the function to clear the screen (depending on OS)
#ifdef _WIN32
    #define clearScreen() system("cls")
#elif defined(unix) || defined(__unix__) || defined(__unix) || (defined(__APPLE__) && defined(__MACH__))
    #define clearScreen() system("clear")
#endif

typedef struct Song{
    char artistName[MAX_NAME_SIZE];
    char songName[MAX_NAME_SIZE];
    char length[MAX_TIME_SIZE];
    unsigned yearReleased;
    double rating;
    bool isFavorite;
}Song;

typedef struct FullSongs{
    Song *songArr;
    size_t size;
} FullSongs;

void showMenu(const char **actions, unsigned actionLen);

void addNew(FullSongs *fullSongs, struct tm timeInfo);
void editSong(FullSongs *fullSongs, struct tm timeInfo, const char **editActions, unsigned editActionLen);
void deleteSong(FullSongs *fullSongs);
void deleteAll(FullSongs *fullSongs);
void viewAll(FullSongs *fullSongs);
void loadFromPath(FullSongs *fullSongs, struct tm timeInfo);

void runTests();
void onStart();
void onEnd();

time_t beginTime;

#endif
