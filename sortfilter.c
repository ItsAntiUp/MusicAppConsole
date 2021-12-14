#include "all.h"
#include "helper.h"
#include "scan.h"
#include "message.h"

//-------------------------------------------------- Sorting Comparators (Ascending)

int cmpArtistNameASC(const void *v1, const void *v2)
{
    const struct Song *s1 = v1;
    const struct Song *s2 = v2;

    return strcasecmp(s1->artistName, s2->artistName);
}

int cmpSongNameASC(const void *v1, const void *v2){
    const struct Song *s1 = v1;
    const struct Song *s2 = v2;

    int value = strcasecmp(s1->songName, s2->songName);
    if(value == 0){
        value = strcasecmp(s1->artistName, s2->artistName);
    }

    return value;
}

int cmpLengthASC(const void *v1, const void *v2){
    const struct Song *s1 = v1;
    const struct Song *s2 = v2;

    int value = strcmp(s1->length, s2->length);
    if(value == 0){
        value = strcasecmp(s1->artistName, s2->artistName);
    }

    return value;
}

int cmpYearASC(const void *v1, const void *v2){
    const struct Song *s1 = v1;
    const struct Song *s2 = v2;

    if(s2->yearReleased > s1->yearReleased)
        return -1;
    if(s2->yearReleased < s1->yearReleased)
        return 1;

    return strcasecmp(s1->artistName, s2->artistName);
}

int cmpRatingASC(const void *v1, const void *v2){
    const struct Song *s1 = v1;
    const struct Song *s2 = v2;

    if(s2->rating > s1->rating)
        return -1;
    if(s2->rating < s1->rating)
        return 1;

    return strcasecmp(s1->artistName, s2->artistName);
}

int cmpFavoriteASC(const void *v1, const void *v2){
    const struct Song *s1 = v1;
    const struct Song *s2 = v2;

    if(s2->isFavorite > s1->isFavorite)
        return -1;
    if(s2->isFavorite < s1->isFavorite)
        return 1;

    return strcasecmp(s1->artistName, s2->artistName);
}

//-------------------------------------------------- Sorting Comparators (Descending)

int cmpArtistNameDSC(const void *v1, const void *v2)
{
    const struct Song *s1 = v1;
    const struct Song *s2 = v2;

    return -strcasecmp(s1->artistName, s2->artistName);
}

int cmpSongNameDSC(const void *v1, const void *v2){
    const struct Song *s1 = v1;
    const struct Song *s2 = v2;

    int value = -strcasecmp(s1->songName, s2->songName);
    if(value == 0){
        value = strcasecmp(s1->artistName, s2->artistName);
    }

    return value;
}

int cmpLengthDSC(const void *v1, const void *v2){
    const struct Song *s1 = v1;
    const struct Song *s2 = v2;

    int value = -strcmp(s1->length, s2->length);
    if(value == 0){
        value = strcasecmp(s1->artistName, s2->artistName);
    }

    return value;
}

int cmpYearDSC(const void *v1, const void *v2){
    const struct Song *s1 = v1;
    const struct Song *s2 = v2;

    if(s2->yearReleased > s1->yearReleased)
        return 1;
    if(s2->yearReleased < s1->yearReleased)
        return -1;

    return strcasecmp(s1->artistName, s2->artistName);
}

int cmpRatingDSC(const void *v1, const void *v2){
    const struct Song *s1 = v1;
    const struct Song *s2 = v2;

    if(s2->rating > s1->rating)
        return 1;
    if(s2->rating < s1->rating)
        return -1;

    return strcasecmp(s1->artistName, s2->artistName);
}

int cmpFavoriteDSC(const void *v1, const void *v2){
    const struct Song *s1 = v1;
    const struct Song *s2 = v2;

    if(s2->isFavorite > s1->isFavorite)
        return 1;
    if(s2->isFavorite < s1->isFavorite)
        return -1;

    return strcasecmp(s1->artistName, s2->artistName);
}

//-------------------------------------------------- Sort and Filter functions

void sort(FullSongs *fullSongs, const char **sortActions, unsigned sortActionLen){
    Song *songs = fullSongs->songArr;
    size_t size = fullSongs->size;

    if(isSizeNull(size)) {return;}

    printf("%s\n", SORT_BY);
    showMenu(sortActions, sortActionLen);

    unsigned sortByIndex = selectAction(sortActions, sortActionLen);
    if(sortByIndex == sortActionLen){
        actionCanceled();
        return;
    }

    const char *sortOrderActions[] = {"Ascending (A-Z)", "Descending (Z-A)", "Cancel"};
    unsigned sortOrderActionLen = sizeof(sortOrderActions) / sizeof(sortOrderActions[0]);

    printf("%s\n", SORT_ORDER);
    showMenu(sortOrderActions, sortOrderActionLen);

    int sortOrderIndex = selectAction(sortOrderActions, sortOrderActionLen);
    if(sortOrderIndex == sortOrderActionLen){
        actionCanceled();
        return;
    }

    Song *tempSongPtr = (Song *)calloc(size, sizeof(Song));
    for(int i = 0; i < size; ++i){
        tempSongPtr[i] = songs[i];
    }

    switch(sortByIndex){
        case 1:
            sortOrderIndex == 1 ? qsort(tempSongPtr, size, sizeof(Song), cmpArtistNameASC) : qsort(tempSongPtr, size, sizeof(Song), cmpArtistNameDSC);
            break;
        case 2:
            sortOrderIndex == 1 ? qsort(tempSongPtr, size, sizeof(Song), cmpSongNameASC) : qsort(tempSongPtr, size, sizeof(Song), cmpSongNameDSC);
            break;
        case 3:
            sortOrderIndex == 1 ? qsort(tempSongPtr, size, sizeof(Song), cmpLengthASC) : qsort(tempSongPtr, size, sizeof(Song), cmpLengthDSC);
            break;
        case 4:
            sortOrderIndex == 1 ? qsort(tempSongPtr, size, sizeof(Song), cmpYearASC) : qsort(tempSongPtr, size, sizeof(Song), cmpYearDSC);
            break;
        case 5:
            sortOrderIndex == 1 ? qsort(tempSongPtr, size, sizeof(Song), cmpRatingASC) : qsort(tempSongPtr, size, sizeof(Song), cmpRatingDSC);
            break;
        case 6:
            sortOrderIndex == 1 ? qsort(tempSongPtr, size, sizeof(Song), cmpFavoriteASC) : qsort(tempSongPtr, size, sizeof(Song), cmpFavoriteDSC);
            break;
        default:
            clearScreen();
            printf("%s\n", UNEXPECTED_ERROR);
            return;
    }

    FullSongs tempSongStruct;
    tempSongStruct.songArr = tempSongPtr;
    tempSongStruct.size = size;

    clearScreen();
    printf("%s\n", SORT_COMPLETE);

    viewAll(&tempSongStruct);
    free(tempSongPtr);
}

void filter(FullSongs *fullSongs, const char **filterActions, unsigned filterActionLen){
    Song *songs = fullSongs->songArr;
    size_t size = fullSongs->size;

    if(isSizeNull(size)) {return;}

    printf("%s\n", FILTER_BY);
    showMenu(filterActions, filterActionLen);

    unsigned filterIndex = selectAction(filterActions, filterActionLen);
    if(filterIndex == filterActionLen){
        actionCanceled();
        return;
    }

    char *filterValue = calloc(MAX_NAME_SIZE, sizeof(char));
    memcpy(filterValue, selectName(INPUT_FILTER_VALUE), MAX_NAME_SIZE);

    bool *toPrint = calloc(size, sizeof(bool));
    unsigned filteredSize = 0;

    for(int i = 0; i < size; ++i){
        Song s = songs[i];

        char *awardArr = s.isFavorite ? "Yes" : "No";
        char *yearArr = calloc(MAX_YEAR_SIZE, sizeof(char));
        char *ratingArr = calloc(MAX_RATING_SIZE, sizeof(char));

        sprintf(yearArr, "%u", s.yearReleased);
        sprintf(ratingArr, "%.1f", s.rating);

        char *filterStrings[] = {s.artistName, s.songName, s.length, yearArr, ratingArr, awardArr};
        char *filterStr = filterStrings[filterIndex - 1];

        //Gathering strings that contain the filter value.
        if(filterIndex == 1 || filterIndex == 2){
            if(strstr(filterStr, filterValue) != NULL){
                toPrint[i] = 1;
            }
        }
        else{
            if(strcmp(filterStr, filterValue) == 0){
                toPrint[i] = 1;
            }
        }

        free(yearArr);
        free(ratingArr);
    }

    free(filterValue);
    clearScreen();

    for(int i = 0; i < size; ++i){
        Song s = songs[i];
        if(toPrint[i] == 1){
            if(filteredSize++ == 0){
                printf(DATA_HEADER_FORMAT, "No.", "Artist name", "Song name", "Length", "Released", "Rating", "Favorite");
            }

            char *awardArr = s.isFavorite ? "Yes" : "No";
            printf(DATA_FORMAT, i + 1, s.artistName, s.songName, s.length, s.yearReleased, s.rating, awardArr);
        }
    }

    free(toPrint);
    if(filteredSize > 0){
        printf("\n");
    }

    printf("%s %s %u.\n", FILTER_COMPLETE, ENTRIES_FOUND, filteredSize);
}


