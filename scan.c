#include "all.h"
#include "helper.h"
#include "message.h"

//-------------------------------------------------- Scan functions

double scanDouble(const char *text){
    double tempDouble;
    while(1){
        printf("%s", text);
        if(scanf("%lf", &tempDouble) == 1 && getchar() == '\n'){
            if(tempDouble >= 1 && tempDouble <= 10){
                return tempDouble;
            }
            else{
                printf("%s\n", INTERVAL_ERROR);
            }
        }
        else{
            printf("%s\n", FORMAT_ERROR);
            while (getchar() != '\n');
        }
    }
}

char *scanText(const char *text){
    while(1){
        char tempName[MAX_NAME_SIZE];
        printf("%s", text);
        if(scanf("%29[^\n]s", tempName) == 1 && getchar() == '\n'){
            int len = strlen(tempName);
            if(len <= MAX_NAME_SIZE && !isEmpty(tempName)){
                char *ptr = tempName;
                return ptr;
            }
            else{
                printf("%s\n", INCORRECT_VALUE_ERROR);
            }
        }
        else{
            printf("%s\n", FORMAT_ERROR);
            while (getchar() != '\n');
        }
    }
}

char *scanPath(const char *text){
    while(1){
        char tempName[MAX_PATH_SIZE];
        printf("%s", text);
        if(scanf("%255[^\n]s", tempName) == 1 && getchar() == '\n'){
            int len = strlen(tempName);
            if(len <= MAX_PATH_SIZE && !isEmpty(tempName)){
                char *ptr = tempName;
                return ptr;
            }
            else{
                printf("%s\n", INCORRECT_VALUE_ERROR);
            }
        }
        else{
            printf("%s\n", FORMAT_ERROR);
            while (getchar() != '\n');
        }
    }
}

char *scanTime(const char *text){
    while(1){
        unsigned tempHour, tempMin, tempSec;
        char finalTime[MAX_TIME_SIZE];
        printf("%s", text);

        if(scanf("%2u:%2u:%2u", &tempHour, &tempMin, &tempSec) == 3 && getchar() == '\n'){
            if(tempMin < 60 && tempSec < 60 && tempHour <= 99){
                sprintf(finalTime, "%02u:%02u:%02u", tempHour, tempMin, tempSec);
                if(tempHour > 0 || tempMin > 0 || tempSec > 0){
                    char *ptr = finalTime;
                    return ptr;
                }
                else{
                    printf("%s\n", NEGATIVE_VALUE_ERROR);
                }
            }
            else{
                printf("%s\n", INCORRECT_VALUE_ERROR);
            }
        }
        else{
            printf("%s\n", FORMAT_ERROR);
            while (getchar() != '\n');
        }
    }
}

unsigned scanNumber(const char *text){
    while(1){
        unsigned temp = 0;
        printf("%s", text);

        if(scanf("%9u", &temp) == 1 && getchar() == '\n'){
            return temp;
        }
        else{
            printf("%s\n", FORMAT_ERROR);
            while (getchar() != '\n');
        }
    }
}

unsigned scanYear(const char *text, struct tm timeInfo){
    unsigned tempYear = 0;
    unsigned dateNow = timeInfo.tm_year + MIN_YEAR;

    while(1){
        tempYear = scanNumber(text);
        if(tempYear >= MIN_YEAR && tempYear <= dateNow){
            return tempYear;
        }
        else{
            printf("%s\n", INCORRECT_VALUE_ERROR);
        }
    }
}

//-------------------------------------------------- Select functions

char *selectName(const char *text){
    char badChars[] = "?@%:*\"|<>/\\";
    while(1){
        char *tempName = scanText(text);

        bool correct = true;
        for (int i = 0; i < strlen(badChars); ++i){
            if(strchr(tempName, badChars[i]) != NULL){
                printf("%s\n", RESTRICTED_SYMBOLS_ERROR);
                correct = false;
                break;
            }
        }

        if(correct){
            return tempName;
        }
    }
}

bool selectBool(const char *text){
    unsigned index;

    while(1){
        index = scanNumber(text);
        if(index == 0 || index == 1){
            return index;
        }
        else{
            printf("%s\n", INCORRECT_VALUE_ERROR);
        }
    }
}

unsigned selectAction(const char **actions, unsigned actionLen){
    unsigned tempAction = 0;
    while(1){
        tempAction = scanNumber(SELECT_ACTION);
        if(tempAction >= 1 && tempAction <= actionLen){
            return tempAction;
        }
        else{
            printf("%s\n", INCORRECT_VALUE_ERROR);
        }
    }

    return 0;
}

unsigned selectIndex(FullSongs *fullSongs){
    unsigned index;
    viewAll(fullSongs);
    printf("\n");

    while(1){
        index = scanNumber(SELECT_ENTRY);
        if(index > 0 && index <= fullSongs->size){
            return index;
        }
        else{
            printf("%s\n", INCORRECT_VALUE_ERROR);
        }
    }
}
