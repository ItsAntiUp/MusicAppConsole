#include "all.h"
#include "message.h"
#include "scan.h"
#include "sys/stat.h"
#include <math.h>

bool isSizeNull(size_t size){
    if(size == 0){
        printf("%s\n", NO_ENTRIES_FOUND);
        return 1;
    }

    return 0;
}

bool isEmpty(const char *text){
    while(*text){
        if(!isspace(*text)){
           return 0;
        }
        text++;
    }

    return 1;
}

bool isReallocated(Song *temp){
    if(!temp){
        clearScreen();
        printf("%s %s\n", MSG_ERROR, strerror(errno));
        return 0;
    }

    return 1;
}

unsigned getLineCount(FILE *fp){
    fseek(fp, 0, SEEK_END);
    unsigned tempSize = ftell(fp) / sizeof(Song);
    fseek(fp, 0, SEEK_SET);

    return tempSize;
}

unsigned getFileSize(FILE *fp){
    //Getting the file size in kilobytes.
    fseek(fp, 0, SEEK_END);
    unsigned tempSize = ftell(fp) / 1024;
    fseek(fp, 0, SEEK_SET);

    return tempSize;
}

unsigned getFileYear(const char *filePath){
    //If possible, getting the file creation date. Otherwise returning the minimal year value.
    struct stat stats;

    if(stat(filePath, &stats) == 0){
        struct tm timeInfo;
        timeInfo = *(gmtime(&stats.st_mtime));
        return timeInfo.tm_year + MIN_YEAR;
    }
    else{
        return MIN_YEAR;
    }
}

unsigned getBitrate(const char *extension){
    //Getting the approximate bitrate for each format.
    if(strcmp(extension, ".wav") == 0)
        return BITRATE_LOSSLESS;
    else if(strcmp(extension, ".flac") == 0)
        return BITRATE_HIGH;
    else if(strcmp(extension, ".mp3") == 0)
        return BITRATE_MEDIUM;

    return BITRATE_LOW;
}

char *getFileDuration(const char *filePath, const char *extension){
    //Note: this function only gets the approximate duration.
    char totalDuration[MAX_TIME_SIZE] = "00:00:00";
    char *durationPtr = totalDuration;

    FILE *fp;
    if((fp = fopen(filePath, "r")) == NULL){
        return durationPtr;
    }

    size_t size = getFileSize(fp);
    fclose(fp);

    unsigned bitRate = getBitrate(extension);
    unsigned duration = (size * 8) / bitRate;

    int h = duration / pow(SECONDS, 2);
    int m = (duration - (h * pow(SECONDS, 2))) / SECONDS;
    int s = (duration - (h * pow(SECONDS, 2)) - (m * SECONDS));

    sprintf(durationPtr, "%02d:%02d:%02d", h, m, s);
    return durationPtr;
}

void fillEntry(Song *s, struct tm timeInfo){
    memcpy(s->artistName, selectName(ARTIST_NAME), MAX_NAME_SIZE);
    memcpy(s->songName, selectName(SONG_NAME), MAX_NAME_SIZE);
    memcpy(s->length, scanTime(SONG_LENGTH), MAX_TIME_SIZE);
    s->yearReleased = scanYear(RELEASE_YEAR, timeInfo);
    s->rating = scanDouble(USER_RATING);
    s->isFavorite = selectBool(IS_FAVORITE);
}

void saveChanges(FullSongs *fullSongs, Song *songs, size_t size){
    fullSongs->songArr = songs;
    fullSongs->size = size;
}

void printSelected(Song s, int index){
    printf("%s\n\n", SELECTED_ENTRY);
    printf(DATA_HEADER_FORMAT, "No.", "Artist name", "Song name", "Length", "Released", "Rating", "Favorite");
    printf(DATA_FORMAT, index, s.artistName, s.songName, s.length, s.yearReleased, s.rating, s.isFavorite ? "Yes" : "No");
    printf("\n");
}

void actionCanceled(){
    clearScreen();
    printf("%s\n", ACTION_CANCELED);
}

void sizeLimitReached(){
    clearScreen();
    printf("%s\n", ENTRY_LIMIT_EXCEEDED);
}

void freeSongs(Song **songs, size_t *size){
    *size = 0;
    Song *temp = realloc(*songs, 0);
    *songs = temp;
}

int fillFromPath(Song *s, const char *pathName, const char *fileName, const char *extension, struct tm timeInfo){
    char *fullSongName = calloc(MAX_PATH_SIZE, sizeof(char));
    memcpy(fullSongName, fileName, strlen(fileName) - strlen(extension));

    char *tokens = strtok(fullSongName, "-");

    for(int i = 0; i < 2; ++i){
        if(tokens != NULL){
            size_t len = strlen(tokens);
            if(len > MAX_NAME_SIZE){
                return -1;
            }

            //Removing the last char from artist name / first char from song name.
            if(i == 0){
                if(isspace(tokens[len - 1])){
                    tokens[len - 1] = '\0';
                }
                memcpy(s->artistName, tokens, MAX_NAME_SIZE);
            }
            else if(i == 1){
                memcpy(s->songName, ++tokens, MAX_NAME_SIZE);
            }

            tokens = strtok(NULL, "-");
        }
        else{
            //If only one token is found, write it as song name.
            memcpy(s->songName, s->artistName, MAX_NAME_SIZE);
            memcpy(s->artistName, NAME_NOT_FOUND, MAX_NAME_SIZE);
        }
    }

    char *filePath = calloc(MAX_PATH_SIZE, sizeof(char));
    sprintf(filePath, "%s%s%s", pathName, "\\", fileName);

    memcpy(s->length, getFileDuration(filePath, extension), MAX_TIME_SIZE);
    s->yearReleased = getFileYear(filePath);
    s->rating = 0;
    s->isFavorite = 0;

    free(fullSongName);
    free(filePath);

    return 0;
}

int readDirectory(FullSongs *fullSongs, const char *pathName, struct tm timeInfo){
    Song *songs = fullSongs->songArr;
    size_t size = fullSongs->size;

    DIR *directory = opendir(pathName);
    if(directory == NULL){
        return -1;
    }

    struct dirent *dir;

    char *pathToPass = calloc(MAX_PATH_SIZE, sizeof(char));
    memcpy(pathToPass, pathName, MAX_PATH_SIZE);

    char *formats[] = {".mp3", ".wav", ".flac", ".m4a"};
    unsigned formatSize = sizeof(formats) / sizeof(formats[0]);
    unsigned fileCount = 0;

    while((dir = readdir(directory)) != NULL && fileCount < MAX_ARR_SIZE){
        char *fileName = dir->d_name;
        char *extension;

        if((extension = strchr(fileName, '.')) != NULL){
            for(int i = 0; i < formatSize; ++i){
                if(strcmp(extension, formats[i]) == 0){
                    Song s;
                    if(fillFromPath(&s, pathToPass, fileName, extension, timeInfo) == -1){
                        break;
                    }

                    if(fileCount++ == 0){
                        freeSongs(&songs, &size);
                    }

                    Song *temp = realloc(songs, (size + 1) * sizeof(Song));
                    if(!isReallocated(temp)){
                        return fileCount - 1;
                    }

                    songs = temp;
                    songs[size] = s;
                    ++size;

                    saveChanges(fullSongs, songs, size);
                    break;
                }
            }
        }
    }

    free(pathToPass);
    closedir(directory);

    return fileCount;
}
