/*
 * Stephen Crowe
 * CS50 - Prof. Palmer
 * 24 April 2018
 * Lab4 Crawler
 *
 * pagedir.h - header file for the pagedir.c module
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "webpage.h"
#include <sys/types.h>
#include <dirent.h>

/* Attempts to open a new file, '.crawler' within
 * the directory. False if it cannot open the file.
 * It does not remove the blank file after it is created
 * @path - the pathname for the directory
 * @return - true if the directory is writable.*/
bool isWritableDir(char *path);

/* Checks if a directory is empty
 * Will stop after at most five calls
 * Adapted from stackoverflow.com/questions/6383584/check-if-a-directory-is-empty-using-c-on-linux
 * @dirname - the directory to check
 * @return - true if the directory is empty */
bool isEmptyDir(char *dirname);

/* writes each explored page to the pageDirectory with a unique document ID,
 * and the filename is of form pageDirectory/id,
 * and the first line of the file is the URL,
 * and the second line of the file is the depth,
 * and the rest of the file is the page content (the HTML, unchanged).
 * @webpage - the webpage to save
 * @pagedir - the internal directory to save the webpage into
 * @id - the id the webpage will be stored as
 */
bool pagesave(webpage_t *webpage, char *pageDir, int id);

/* Attempts to fetch the webpage from the url and store it in a webpage
 * struct. Will return NULL if the url is unable to be fetched. Returns
 * NULL if depth is negative
 * @url - the url to fetch
 * @depth - the depth the crawler is at for the url
 * @return - the webpage structure with the url, depth, and html saved */
webpage_t *pagefetch(char *url, int depth);

/* Adds a slash to the input string and returns a
 * newly malloced string with forward slash in it.
 * If the input string already has a forward slash
 * as the last character, it returns a copy of the
 * same string. Useful for using webpage_fetch on
 * directories. Otherwise, they are inaccessible.
 * The user is responsable for FREEing the string
 * @dir - the name of the directory to add a
 * forward slash to.
 * @return - the directory name in a new string
 * with a forward slash at the end.*/
char *appendSlash(char *dir);

/* A dumb method to check for an extension.
 * It actually just checks for a period in the
 * last five characters of the string.
 * Useful for determining if the path is a 
 * file or a directory. If it is a directory
 * without a slash, webpage_fetch will fail.
 * @path - the string to check if it has an extension
 * @return - true if a period is found in last
 * 5 characters */
bool hasExtension(char *path);

/* A function to test if the directory has the
 * hidden file '.crawler' which should be created
 * by the crawler program.
 * @path - the path to the directory to check
 * @return - true if the directory has been written
 * to by the crawler program*/
bool isCrawlerDir(char *path);
