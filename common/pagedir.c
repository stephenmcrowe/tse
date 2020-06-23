/*
 * Stephen Crowe
 * CS50 - Prof. Palmer
 * 24 April 2018
 * Lab4 Crawler
 *
 * pagedir.c - module for modifying an internal directory
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include <sys/types.h>
#include <dirent.h>
#include "webpage.h"

bool writableDir(char *path);
bool isEmptyDir(char *dirname);
bool pagesave(webpage_t *webpage, char *pageDir, int id);
webpage_t *pagefetch(char *url, int depth);
char *appendSlash(char *dir);
bool hasExtension(char *path);

/* Attempts to open a new file, '.crawler' within
 * the directory. False if it cannot open the file.
 * It does NOT remove the file before it exits
 * @path - the pathname for the directory
 * @return - true if the directory is writable.*/
bool isWritableDir(char *path) 
{
	// Handle a directory without the forward slash appended
	char *pageDir = appendSlash(path);
	if (pageDir == NULL) { 
		return false; 
	}

	// Construct the absolute path for the dummy .crawler file
	char *newFile = malloc(strlen(pageDir) + 9); // ".crawler" has 8 characters
	strcpy(newFile, pageDir);
	strcat(newFile, ".crawler");
	free(pageDir);

	// "touch" a file .crawler in that directory
	FILE *fp = fopen(newFile, "w");
	if (fp == NULL) {
		return false;
	}
	fclose(fp);
	free(newFile);	
	return true;
}

/* Checks if a directory is empty
 * Will stop after at most five calls
 * Adapted from stackoverflow.com/questions/6383584/check-if-a-directory-is-empty-using-c-on-linux
 * @dirname - the directory to check
 * @return - true if the directory is empty */
bool isEmptyDir(char *dirname) 
{
	int n = 0;
	struct dirent *d;
	DIR *dir = opendir(dirname);
	if (dir == NULL) //Not a directory or doesn't exist
		return false;
	while ((d = readdir(dir)) != NULL) {
		if(++n > 2) // Account for .. (parent)  and . (current) directories
			break;
	}
	closedir(dir);

	if (n <= 2) //Directory Empty
		return true;
	else
		return false;
}

/* Writes each explored page to the pageDirectory with a specified document ID,
 * and the filename is of form pageDirectory/id,
 * and the first line of the file is the URL,
 * and the second line of the file is the depth,
 * and the rest of the file is the page content (the HTML, unchanged).
 * If any arguments are NULL or it cannot write to the directory, then this
 * function returns false
 * @webpage - the webpage to save
 * @pagedir - the internal directory to save the webpage into. Null-terminated
 * @id - the id the webpage will be stored as
 * @return - true if wrote to a file in the target directory
 * Reference: stackoverflow.com/questions/8257714/how-to-convert-an-int-to-string-in-c
 */
bool pagesave(webpage_t *webpage, char *pageDir, int id) 
{
	if (webpage != NULL && webpage_getHTML(webpage) != NULL && pageDir != NULL) {
		// Create a string out of the id
		int numDigits = snprintf(NULL, 0, "%d", id);	//Passing NULL,0 gives length of str
		char *idStr = malloc(numDigits+1);
		if (idStr == NULL) { 
			return false; 
		}
		sprintf(idStr, "%d", id);
		
		// Handle a directory without the forward slash appended
		char *pageDirec = appendSlash(pageDir);

		// Construct the absolute path to the filename
		char *newFile = malloc(strlen(pageDirec) + strlen(idStr) + 1);
		strcpy(newFile, pageDirec);
		strcat(newFile, idStr);
		free(pageDirec);
		free(idStr);
		#ifdef DEBUG
			printf("Writing to file %d...\n", pageDirec);
		#endif

		// Create and write to the file
		FILE *fp = fopen(newFile, "w");
		if (fp == NULL) { 
			return false; 
		}
		fputs(webpage_getURL(webpage), fp);
		fputc('\n', fp);
		fprintf(fp, "%d", webpage_getDepth(webpage));
		fputc('\n', fp);
		fputs(webpage_getHTML(webpage), fp);

		// Cleanup
		fclose(fp);
		free(newFile);
		return true;
	}
	return false;
}

/* Attempts to fetch the webpage from the url and store it in a webpage
 * struct. Will return NULL if the url is unable to be fetched. Returns
 * NULL if depth is negative
 * @url - the url to fetch
 * @depth - the depth the crawler is at for the url
 * @return - the webpage structure with the url, depth, and html saved */
webpage_t *pagefetch(char *url, int depth) 
{
	if (url != NULL && depth >= 0) {
		webpage_t *page = webpage_new(url, depth, NULL);
		if (page != NULL) {
			if (!webpage_fetch(page)) {
				webpage_delete(page);
				return NULL;
			}
			return page;
		}
	}
	return NULL;
}

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
char *appendSlash(char *dir)
{	
	// Construct the absolute path for the filename
	char *buf;
	if (dir[strlen(dir) - 1] != '/') {
		buf = malloc(strlen(dir) + 2); // forward slash is one character
		if (buf == NULL) { 
			return NULL; 
		}
		strcpy(buf, dir);
		strcat(buf, "/");
	}
	else {
		buf = malloc(strlen(dir) + 1);
		if (buf == NULL) { 
			return NULL; 
		}
		strcpy(buf, dir);
	}
	return buf;
}

/* A dumb method to check for an extension.
 * It actually just checks for a period in the
 * last five characters of the string.
 * Useful for determining if the path is a 
 * file or a directory. If it is a directory
 * without a slash, webpage_fetch will fail.
 * @path - the string to check if it has an extension
 * @return - true if a period is found in last
 * 5 characters */
bool hasExtension(char *path)
{
	if (path != NULL && strlen(path) > 5) {
		for (int i=strlen(path)-5; i<strlen(path); i++) {
			if (path[i] == '.') {
				return true;
			}	
		}
	}
	return false;
}

/* A function to test if the directory has the
 * hidden file '.crawler' which should be created
 * by the crawler program.
 * @path - the path to the directory to check
 * @return - true if the directory has been written
 * to by the crawler program*/
bool isCrawlerDir(char *path)
{
	char *buf = malloc(strlen(path) + 9);
	strcpy(buf, path);
	strcat(buf, ".crawler");

	FILE *check;
	check = fopen(buf, "r");
	if (check == NULL) {
		free(buf);
		return false;
	}
	else {
		free(buf);
		fclose(check);
		return true;
	}
}
