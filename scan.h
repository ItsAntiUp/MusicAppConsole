/**
 * Author:          Kostas Ragauskas (kostas.ragauskas@stud.mif.vu.lt)
 * Last Modified:   2021-01-19
 *
 * Content:         User input functions.
 **/

#ifndef SCAN_H
#define SCAN_H

char *selectName(const char *text);
bool selectBool(const char *text);
unsigned selectIndex(FullSongs *fullSongs);
unsigned selectAction(const char **actions, unsigned actionLen);

char *scanText(const char *text);
char *scanPath(const char *text);
char *scanTime(const char *text);
double scanDouble(const char *text);
unsigned scanYear(const char *text, struct tm timeInfo);
unsigned scanNumber(const char *text);

#endif
