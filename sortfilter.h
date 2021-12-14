/**
 * Author:          Kostas Ragauskas (kostas.ragauskas@stud.mif.vu.lt)
 * Last Modified:   2021-01-26
 *
 * Content:         Sort and filter functions (comparators included).
 **/

#ifndef SORTFILTER_H
#define SORTFILTER_H

void sort(FullSongs *fullSongs, const char **sortActions, unsigned sortActionLen);
void filter(FullSongs *fullSongs, const char **filterActions, unsigned filterActionLen);

int cmpArtistNameASC(const void *v1, const void *v2); //qsort comparators Ascending
int cmpSongNameASC(const void *v1, const void *v2);
int cmpLengthASC(const void *v1, const void *v2);
int cmpYearASC(const void *v1, const void *v2);
int cmpRatingASC(const void *v1, const void *v2);
int cmpFavoriteASC(const void *v1, const void *v2);

int cmpArtistNameDSC(const void *v1, const void *v2); //qsort comparators Descending
int cmpSongNameDSC(const void *v1, const void *v2);
int cmpLengthDSC(const void *v1, const void *v2);
int cmpYearDSC(const void *v1, const void *v2);
int cmpRatingDSC(const void *v1, const void *v2);
int cmpFavoriteDSC(const void *v1, const void *v2);

#endif
