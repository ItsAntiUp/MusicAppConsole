#include "all.h"
#include "helper.h"
#include "scan.h"
#include "message.h"
#include "helper.h"

void saveToBin(FullSongs *fullSongs){
    Song *songs = fullSongs->songArr;
    size_t size = fullSongs->size;

    if(isSizeNull(size)) {return;}

    char *fileName = calloc(MAX_NAME_SIZE, sizeof(char));
    memcpy(fileName, selectName(INPUT_FILE_NAME), MAX_NAME_SIZE);
    strcat(fileName, SAVE_FILE_FORMAT);

    char *text = calloc(MAX_TEXT_SIZE, sizeof(char));
    sprintf(text, "%s \"%s\"? (Yes = 1, No = 0)\n", SAVE_TO_FILE_QUESTION, fileName);

    bool accepted = selectBool(text);
    free(text);

    if(!accepted){
        actionCanceled();
        free(fileName);
        return;
    }

    FILE *fp;
    if ((fp = fopen(fileName, "wb")) == NULL){
        clearScreen();
        printf("%s %s\n", MSG_ERROR, strerror(errno));
        free(fileName);
        return;
    }

    fwrite(songs, sizeof(Song), size, fp);

    fclose(fp);
    free(fileName);

    saveChanges(fullSongs, songs, size);
    clearScreen();

    char *form = size == 1 ? "Entry" : "Entries";
    printf("%Iu %s %s\n", size, form, SAVE_SUCCESS);
}

void loadFromBin(FullSongs *fullSongs){
    Song *songs = fullSongs->songArr;
    size_t size = fullSongs->size;

    char *fileName = calloc(MAX_NAME_SIZE, sizeof(char));
    memcpy(fileName, selectName(INPUT_FILE_NAME), MAX_NAME_SIZE);
    strcat(fileName, SAVE_FILE_FORMAT);

    FILE *fp;
    if ((fp = fopen(fileName, "rb")) == NULL){
        clearScreen();
        printf("%s %s\n", MSG_ERROR, strerror(errno));
        free(fileName);
        return;
    }

    unsigned tempSize = getLineCount(fp);
    if(tempSize <= 0 || tempSize >= MAX_ARR_SIZE){
        clearScreen();

        if(tempSize <= 0){
            printf("%s\n", EMPTY_FILE_ERROR);
        }
        else{
            printf("%s\n", TOO_MANY_ENTRIES_ERROR);
        }

        fclose(fp);
        free(fileName);
        return;
    }

    Song *temp = realloc(songs, tempSize * sizeof(Song));
    if(!isReallocated(temp)){
        fclose(fp);
        free(fileName);
        return;
    }

    songs = temp;
    for (size = 0; !feof(fp); ++size){
        if (fread(&songs[size], sizeof(Song), 1, fp) != 1)
            break;
    }

    fclose(fp);
    free(fileName);

    saveChanges(fullSongs, songs, size);
    clearScreen();

    char *form = size == 1 ? "Entry" : "Entries";
    printf("%Iu %s %s\n", size, form, LOAD_SUCCESS);
}
