/**
 * Author:          Kostas Ragauskas (kostas.ragauskas@stud.mif.vu.lt)
 * Last Modified:   2021-01-21
 *
 * Content:         Text messages / printing formats.
 **/

#ifndef MESSAGE_H
#define MESSAGE_H

//Error related messages
#define UNEXPECTED_ERROR            "Unexpected error occured."
#define NEGATIVE_VALUE_ERROR        "The value cannot be less or equal to zero."

#define PATH_NOT_FOUND              "Error: The inputed path was not found."
#define FORMAT_ERROR                "Error: The inputed value is not in the correct format."
#define INCORRECT_VALUE_ERROR       "Error: The inputed value is incorrect."
#define INTERVAL_ERROR              "Error: The inputed value does not belong to the interval [1;10]."
#define RESTRICTED_SYMBOLS_ERROR    "Error: The inputed value contains restricted symbols."
#define TOO_MANY_ENTRIES_ERROR      "Error: The save file contains too many entries."
#define EMPTY_FILE_ERROR            "Error: The save file is empty."
#define MSG_ERROR                   "Error:"

//Formats / Files
#define DATA_HEADER_FORMAT          "%4s %-30.30s %-30.30s %-15s %-10s %-10.10s %-10.10s\n"
#define DATA_FORMAT                 "%3d. %-30.30s %-30.30s %-15s %-10u %-10.1lf %-10.10s\n"
#define SAVE_FILE_FORMAT            ".bin"
#define LOG_FILE                    "log.txt"

//Other messages
#define WELCOME_MESSAGE             "Welcome to the Music Management Tool!"
#define HORIZONTAL_LINE             "--------------------------------------------------"

#define INPUT_SUCCESS               "Input successful!"
#define SAVE_SUCCESS                "saved successfully!"
#define LOAD_SUCCESS                "loaded successfully!"
#define DELETE_SUCCESS              "deleted successfully!"
#define DELETE_ALL_SUCCESS          "All entries deleted successfully!"
#define CHANGES_SUCCESS             "Changes applied successfully!"

#define DELETE_ENTRY_QUESTION       "Are you sure you want to delete this entry? This action cannot be reverted. (Yes = 1, No = 0)\n"
#define DELETE_ALL_ENTRIES_QUESTION "Are you sure you want to delete all entries? This action cannot be reverted. (Yes = 1, No = 0)\n"
#define SAVE_TO_FILE_QUESTION       "Are you sure you want to save your data to the file:"
#define EDIT_FIELD_QUESTION         "What field do you want to edit?"

#define ACTION_CANCELED             "Action canceled."
#define NO_ENTRIES_FOUND            "No entries found."
#define NO_FILES_FOUND              "No music files found."
#define ENTRIES_FOUND               "Entries found:"
#define SELECTED_ENTRY              "Selected entry:"
#define NAME_NOT_FOUND              "[Name not found.]"
#define ENTRY_LIMIT_EXCEEDED        "The limit of entries exceeded."
#define PROGRAM_STARTED             "Program started, current time:"
#define PROGRAM_ENDED               "Program ended, total time elapsed:"

//Select / Input messages
#define SELECT_ACTION               "Please select an action by writing the corresponding number: "
#define SELECT_ENTRY                "Please select an entry by writing the corresponding number: "
#define INPUT_PATH                  "Please input your directory path: "
#define INPUT_FILE_NAME             "Please input the name of the binary save file (without the extension suffix): "
#define INPUT_FILTER_VALUE          "Please input a value to search (filter) for: "
#define INPUT_ADD_DATA              "To add a new entry, please input the following data: "

//Field messages
#define ARTIST_NAME                 "Name of the artist: "
#define SONG_NAME                   "Name of the song: "
#define SONG_LENGTH                 "Length of the song (format - hh:mm:ss): "
#define RELEASE_YEAR                "Year of the release: "
#define USER_RATING                 "User rating of the song (format - real value between 1 and 10): "
#define IS_FAVORITE                 "Added to favorites? (Yes = 1, No = 0): "

//Unit test messages
#define STARTING_TESTS              "Unit testing started"
#define TEST_FORMAT                 "%d - %s\n"
#define PASSED                      "Test passed."
#define ENDING_TESTS                "All tests passed successfully!"

//Filter / Sort messages
#define SORT_BY                     "Sort by:"
#define SORT_ORDER                  "Sorting order:"
#define SORT_COMPLETE               "Data sorting completed!"

#define FILTER_BY                   "Filter by:"
#define FILTER_COMPLETE             "Data filtering completed!"

#endif
