/*
 * Stephen Crowe
 * CS50 - Prof. Palmer
 * 24 April 2018
 * Lab4 Crawler
 *
 * pagedirtest.c - unit testing for pagedir.c
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "pagedir.h"
#include "webpage.h"

int main() 
{
	// Test basic functionality
	char path[] = "http://old-www.cs.dartmouth.edu/";
	char dir[] = "/net/ifs-users/scrowe/cs50/labs/tse/common/testfilesPageDir";
	printf("Webpage path is %s\n", path);
	webpage_t *webpage = pagefetch(path, 0);
	printf("Webpage html is \n%s", webpage_getHTML(webpage));
	if (isEmptyDir(dir) && isWritableDir(dir)) {
		pagesave(webpage, dir, 0);
		pagesave(webpage, dir, -1000);
	}
	webpage_delete(webpage);
	printf("\n");

	/* Test methods created for specific edge cases.
	 * i.e urls that point to directories without a
	 * forward slash. */
	char dirPath[] = "http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters";
	printf("The directory path is %s\n", dirPath);
	if (!hasExtension(dirPath)) {
		webpage_t *dirPage = pagefetch(dirPath, 0);
		if (dirPage == NULL) {	
			printf("Cannot access a directory without a forward slash, so append forward slash.\n");
			char *updatedPath = appendSlash(dirPath);
			printf("New path is %s\n", updatedPath);
			dirPage = pagefetch(updatedPath, 0);
			free(updatedPath);
		}
		pagesave(dirPage, dir, 1);
		webpage_delete(dirPage);
	}
	printf("check the %s directory for changes\n", dir);
	printf("\n\n");


	// Test different cases and methods with a pdf file
	char pdfPath[] = "http://old-www.cs.dartmouth.edu/~cs50/Schedule.pdf";
	webpage_t *pdfPage = webpage_new(pdfPath, 1, NULL);
	printf("Testing a pdf file... %s\n", pdfPath);
	bool pdfFetch = webpage_fetch(pdfPage);
	printf("Fetch for pdf returned %s\n", pdfFetch ? "true" : "false");
	printf("webpage fetch for a pdf WITHOUT normalizing it returns \n%s\n", webpage_getHTML(pdfPage));
	if (NormalizeURL(pdfPath)) {
		printf("NormalizeURL() says it will likely contain html\n");
	}
	else {
		printf("The url does not contain html according to NormalizeURL()\n");
	}
	webpage_delete(pdfPage);
	printf("\n");

	// Test pagefetch with a png file
	char pngPath[] = "http://old-www.cs.dartmouth.edu/~scrowe/pretty.png";
	webpage_t *pngPage = pagefetch(pngPath, 1);
	printf("Testing a png file %s...\n", pngPath);
	printf("pagefetch for a png WITHOUT normalizing returns %s\n", webpage_getHTML(pngPage));
	webpage_delete(pngPage);
	printf("\n");


	// Test pagefetch with a broken link
	char brknPath[] = "http://old-www.cs.dartmouth.edu/~scrowe/foo.html";
	webpage_t *brknPage = pagefetch(brknPath, 1);
	printf("Testing a broken link %s...\n", brknPath);
	printf("A broken link returns %s with pagefetch()\n", webpage_getHTML(brknPage));
	webpage_delete(brknPage);
	printf("\n");

	// Test a forbidden path
	char forbiddenPath[] = "http://old-www.cs.dartmouth.edu/~scrowe/forbidden.html";
	webpage_t *forbiddenPage = pagefetch(forbiddenPath, 1);
	printf("Testing a forbidden file %s...\n", forbiddenPath);
	printf("A forbidden page return %s with pagefetch()\n", webpage_getHTML(forbiddenPage));
	webpage_delete(forbiddenPage);
	printf("\n");
	return 0;
}

