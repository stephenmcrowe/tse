# CS50 Lab 4
## Stephen Crowe, April 2018

## common

The *common* library provides functions for the Tiny Search Engine (TSE).
Included is the *pagedir* module and *index* module. See below for details.

### pagedir

The *pagedir* module helps with dealing with webpages and urls.
It provides a suite of functions to help the crawler run smoothly.

### Usage

The *pagedir* module, defined in `pagedir.h` and implemented in `pagedir.c`, 
exports the following functions in `pagedir.h`:

```c
/* Attempts to open a new file, '.crawler' within
 * the directory. False if it cannot open the file.
 * It LEAVES the blank file '.crawler' there.
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
```


The pagedir provides functions for easier access and fluidity for the crawler program.
It utilizes the *webpage* module to render easy page fetching. It 

### Assumptions

No assumptions beyond those that are clear from the spec.

If these functions return a more complex data type, that is to avoid pointer errors. As
a consequence, the caller MUST free the data after it receives the pointer.

### Compilation

To compile, simply `make pagedir.o`.

To test, simply `make test`.
See [TESTING](TESTING.md) for details of testing and an example test run.


### index

The *index* module provides functionality for counting words and matching those words to
the associated webpages..

### usage

```c
/* Reads a directory of crawler files and then builds an
 * inverted-index in the hashtable provided.
 * @pageDir - the page directory that has all the crawler
 * files
 * @ht - the hashtable to build and store the index in */
void indexBuild(char *pageDir, hashtable_t *ht);

/* Saves the index stored within the hashtable to the
 * filename specified. Saves the index in the format:
 * 		word docID count [docID count]
 * @filename - the filename to save the index in
 * @ht - the hashtable with the index information */
void indexSave(char *filename, hashtable_t *ht);

/* Loads in the hashtable from the file created by indexer
 * File format needs to be of the format:
 * 		word docID count [docID count]
 * @filname - the name of the file to load created by indexer
 * @ht - the hashtable to store the index information
 * @return - true if it loaded correctly */
bool indexLoad(char *filename, hashtable_t *ht);
```

### Compilation

To compile, simply `make index.o`.
