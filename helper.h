/**
 * Author:          Kostas Ragauskas (kostas.ragauskas@stud.mif.vu.lt)
 * Last Modified:   2021-01-25
 *
 * Content:         Additional functions to avoid duplication.
 **/

#ifndef HELPER_H
#define HELPER_H

bool isSizeNull(size_t size);
bool isEmpty(const char *text);
bool isReallocated(Song *temp);

unsigned getLineCount(FILE *fp);
unsigned getFileSize(FILE *fp, unsigned bytes);
unsigned getFileYear(const char *filePath);
unsigned getBitrate(const char *extension);

char *getFileDuration(const char *filePath, const char *extension);

void fillEntry(Song *s, struct tm timeInfo);
void saveChanges(FullSongs *fullSongs, Song *songs, size_t size);
void printSelected(Song s, int index);
void actionCanceled();
void sizeLimitReached();
void freeSongs(Song **songs, size_t *size);

int fillFromPath(Song *s, const char *pathName, const char *fileName, const char *extension, struct tm timeInfo);
int readDirectory(FullSongs *fullSongs, const char *pathName, struct tm timeInfo);

#endif
