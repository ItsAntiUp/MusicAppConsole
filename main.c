#include "all.h"
#include "sortfilter.h"
#include "scan.h"
#include "helper.h"
#include "saveload.h"
#include "message.h"

int main()
{
    onStart();
    atexit(onEnd);
    runTests();

    struct tm timeInfo = *localtime(&beginTime);

    FullSongs fullSongs;
    fullSongs.size = 0;
    fullSongs.songArr = (Song *)calloc(0, sizeof(Song));

    const char *menuActions[] = {"Add new", "Edit", "Delete", "Delete all", "View all", "Sort", "Filter", "Save to file", "Load from file", "Load from path", "Exit application"};
    const char *editActions[] = {"Edit the whole entry", "Name of the artist", "Name of the song", "Length of the song", "Year of the release", "Rating", "Added to favorites?", "Cancel"};
    const char *mainFields[] = {"Name of the artist", "Name of the song", "Length of the song", "Year of the release", "Rating", "Added to favorites?", "Cancel"};

    unsigned menuActionLen = sizeof(menuActions) / sizeof(menuActions[0]);
    unsigned editActionLen = sizeof(editActions) / sizeof(editActions[0]);
    unsigned mainFieldLen = sizeof(mainFields) / sizeof(mainFields[0]);

    printf("%s\n", WELCOME_MESSAGE);
    showMenu(menuActions, menuActionLen);

    while(1){
        switch(selectAction(menuActions, menuActionLen)){
            case 1:
                clearScreen();
                addNew(&fullSongs, timeInfo);
                break;
            case 2:
                clearScreen();
                editSong(&fullSongs, timeInfo, editActions, editActionLen);
                break;
            case 3:
                clearScreen();
                deleteSong(&fullSongs);
                break;
            case 4:
                clearScreen();
                deleteAll(&fullSongs);
                break;
            case 5:
                clearScreen();
                viewAll(&fullSongs);
                break;
            case 6:
                clearScreen();
                sort(&fullSongs, mainFields, mainFieldLen);
                break;
            case 7:
                clearScreen();
                filter(&fullSongs, mainFields, mainFieldLen);
                break;
            case 8:
                clearScreen();
                saveToBin(&fullSongs);
                break;
            case 9:
                clearScreen();
                loadFromBin(&fullSongs);
                break;
            case 10:
                clearScreen();
                loadFromPath(&fullSongs, timeInfo);
                break;
            case 11:
                clearScreen();
                free(fullSongs.songArr);
                return 0;
            default:
                clearScreen();
                printf("%s\n", UNEXPECTED_ERROR);
                break;
        }

        showMenu(menuActions, menuActionLen);
    }

    return 0;
}

void showMenu(const char **actions, unsigned actionLen){
    printf("\n%s\n", HORIZONTAL_LINE);

    for(int i = 0; i < actionLen; ++i){
        printf("%3d %s\n", i + 1, actions[i]);
    }

    printf("%s\n", HORIZONTAL_LINE);
}

void addNew(FullSongs *fullSongs, struct tm timeInfo){
    Song *songs = fullSongs->songArr;
    size_t size = fullSongs->size;

    if(size >= MAX_ARR_SIZE){
        sizeLimitReached();
        return;
    }

    printf("%s\n", INPUT_ADD_DATA);

    Song s;
    fillEntry(&s, timeInfo);

    Song *temp = realloc(songs, (size + 1) * sizeof(Song));
    if(!isReallocated(temp)) {return;}

    songs = temp;
    songs[size] = s;
    ++size;

    saveChanges(fullSongs, songs, size);

    clearScreen();
    printf("%s\n", INPUT_SUCCESS);
}

void editSong(FullSongs *fullSongs, struct tm timeInfo, const char **editActions, unsigned editActionLen){
    Song *songs = fullSongs->songArr;
    size_t size = fullSongs->size;

    if(isSizeNull(size)) {return;}

    unsigned editIndex = selectIndex(fullSongs);
    Song s = songs[editIndex-1];

    clearScreen();
    printSelected(s, editIndex);

    printf("%s\n", EDIT_FIELD_QUESTION);
    showMenu(editActions, editActionLen);

    switch(selectAction(editActions, editActionLen)){
        case 1:
            fillEntry(&s, timeInfo);
            break;
        case 2:
            memcpy(s.artistName, selectName(ARTIST_NAME), MAX_NAME_SIZE);
            break;
        case 3:
            memcpy(s.songName, selectName(SONG_NAME), MAX_NAME_SIZE);
            break;
        case 4:
            memcpy(s.length, scanTime(SONG_LENGTH), MAX_TIME_SIZE);
            break;
        case 5:
            s.yearReleased = scanYear(RELEASE_YEAR, timeInfo);
            break;
        case 6:
            s.rating = scanDouble(USER_RATING);
            break;
        case 7:
            s.isFavorite = selectBool(IS_FAVORITE);
            break;
        case 8:
            clearScreen();
            printf("%s\n", ACTION_CANCELED);
            return;
        default:
            clearScreen();
            printf("%s\n", UNEXPECTED_ERROR);
            return;
    }

    songs[editIndex - 1] = s;
    saveChanges(fullSongs, songs, size);

    clearScreen();
    printf("%s\n", CHANGES_SUCCESS);
}

void deleteSong(FullSongs *fullSongs){
    Song *songs = fullSongs->songArr;
    size_t size = fullSongs->size;

    if(isSizeNull(size)) {return;}

    unsigned deleteIndex = selectIndex(fullSongs);
    Song s = songs[deleteIndex-1];

    clearScreen();
    printSelected(s, deleteIndex);

    bool accepted = selectBool(DELETE_ENTRY_QUESTION);
    if(!accepted){
        actionCanceled();
        return;
    }

    if(size > 1){
        for(int i = deleteIndex - 1; i < size; ++i){
            songs[i] = songs[i + 1];
        }
    }

    Song *temp = realloc(songs, (size - 1) * sizeof(Song));
    if(size > 1 && !isReallocated(temp)) {return;}

    songs = temp;
    --size;

    saveChanges(fullSongs, songs, size);

    clearScreen();
    printf("Entry (%u) %s\n", deleteIndex, DELETE_SUCCESS);
}

void deleteAll(FullSongs *fullSongs){
    Song *songs = fullSongs->songArr;
    size_t size = fullSongs->size;

    if(isSizeNull(size)) {return;}

    bool accepted = selectBool(DELETE_ALL_ENTRIES_QUESTION);
    if(!accepted){
        actionCanceled();
        return;
    }

    freeSongs(&songs, &size);
    saveChanges(fullSongs, songs, size);

    clearScreen();
    printf("%s\n", DELETE_ALL_SUCCESS);
}

void viewAll(FullSongs *fullSongs){
    Song *songs = fullSongs->songArr;
    size_t size = fullSongs->size;

    if(isSizeNull(size)) {return;}

    printf("%s %Iu.\n\n", ENTRIES_FOUND, size);
    printf(DATA_HEADER_FORMAT, "No.", "Artist name", "Song name", "Length", "Released", "Rating", "Favorite");

    for(int i = 0; i < size; ++i){
        Song s = songs[i];
        char *awardArr = s.isFavorite ? "Yes" : "No";
        printf(DATA_FORMAT, i + 1, s.artistName, s.songName, s.length, s.yearReleased, s.rating, awardArr);
    }
}

void loadFromPath(FullSongs *fullSongs, struct tm timeInfo){
    char *pathName = scanPath(INPUT_PATH);
    int fileCount = readDirectory(fullSongs, pathName, timeInfo);
    clearScreen();

    if(fileCount == -1){
        printf("%s\n", PATH_NOT_FOUND);
        return;
    }
    else if(fileCount == 0){
        printf("%s\n", NO_FILES_FOUND);
        return;
    }
    else if(fileCount >= MAX_ARR_SIZE){
        sizeLimitReached();
    }

    char *form = fileCount == 1 ? "Entry" : "Entries";
    printf("%d %s %s\n", fileCount, form, LOAD_SUCCESS);
}

void runTests(){
    #ifdef NDEBUG
        return;
    #endif

    clearScreen();
    int counter = 0;

    printf("%s\n\n", STARTING_TESTS);

    //UNIT TEST: helper.c -> bool isEmpty(const char *text);
    assert(isEmpty("") == 1);
    printf(TEST_FORMAT, ++counter, PASSED);
    assert(isEmpty("Test") == 0);
    printf(TEST_FORMAT, ++counter, PASSED);
    assert(isEmpty("12345") == 0);
    printf(TEST_FORMAT, ++counter, PASSED);

    //UNIT TEST: helper.c -> unsigned getFileYear(const char *filePath);
    assert(getFileYear("") == MIN_YEAR);
    printf(TEST_FORMAT, ++counter, PASSED);
    assert(getFileYear("main.c") == 2021);
    printf(TEST_FORMAT, ++counter, PASSED);

    //UNIT TEST: helper.c -> void freeSongs(Song **songs, size_t *size);
    size_t size = 5;
    Song *arr = (Song *)calloc(size, sizeof(Song));
    freeSongs(&arr, &size);

    assert(arr == NULL && size == 0);
    printf(TEST_FORMAT, ++counter, PASSED);

    printf("\n%s\n\n", ENDING_TESTS);
}

void onStart(){
    FILE *fp;
    if ((fp = fopen(LOG_FILE, "a")) == NULL){
        return;
    }

    beginTime = time(NULL);
    struct tm timeInfo = *localtime(&beginTime);

    fprintf(fp, "%s %04d-%02d-%02d %02d:%02d:%02d\n", PROGRAM_STARTED, timeInfo.tm_year + MIN_YEAR, timeInfo.tm_mon + 1, timeInfo.tm_mday, timeInfo.tm_hour, timeInfo.tm_min, timeInfo.tm_sec);
    fclose(fp);
}

void onEnd(){
    FILE *fp;
    if ((fp = fopen(LOG_FILE, "a")) == NULL){
        return;
    }

    int timeElapsed = (time(NULL) - beginTime);

    fprintf(fp, "%s %d seconds.\n\n", PROGRAM_ENDED, timeElapsed);
    fclose(fp);
}
