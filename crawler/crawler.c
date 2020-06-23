/*
 * Stephen Crowe
 * CS50 - Prof. Palmer
 * TSE: Crawler
 * April 24, 2018
 *
 * crawler.c - the crawler program starts at a url specified by the user (seedURL).
 * It then will find all pages within that seed and save them to a the directory
 * specified by the user (pageDir). It only goes down a certain depth indicated by
 * the user (maxdepth). First module of the TSE. For further information, see the
 * README.md
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "bag.h"
#include "hashtable.h"
#include "pagedir.h"
#include "webpage.h"

/* Local functions */
bool crawl(char *seedURL, char *pageDir, int maxDepth);
void crawlPage(webpage_t *page, char *pageDir, int id,  bag_t *bag, 
		hashtable_t *ht, int maxdepth, char *hostnm);
bool isCrawlable(char *url, char *hostnm);
char *extractHostname(const char *url);
char *makeProperURL(char *url);
inline static void logr(const char *word, const int depth, const char *url);


int main(const int argc, char *argv[]) 
{
	int maxdepth;
	if (argc == 4 && NormalizeURL(argv[1]) && IsInternalURL(argv[1]) && sscanf(argv[3], "%i", &maxdepth) == 1) {
		if (isEmptyDir(argv[2]) && isWritableDir(argv[2])) {
			crawl(argv[1], argv[2], maxdepth);
		}
		else {
			fprintf(stderr, "Directory %s is either not empty or cannot be written in\n", argv[2]);
			exit(2);
		}
	}
	else {
		fprintf(stderr, "usage: crawler.c seedUrl pageDirectory maxDepth\n");
		exit(1);
	}
}

/* This is the start of crawler. It instantiates all the modules and initializes the seed
 * as a webpage. It then iterates and passes the important information to crawlPage.
 * @seedUrl - the starting url passed in by the user. Will be converted to a properUrl,
 * that is, it will be of the form .html or path/dirname/
 * See IMPLEMENTATION.md for pseudocode
 * @pageDir - the directory to save all the pages
 * @maxdepth - the depth to traverse
 * @return - true if modules are instantiated properly */
bool crawl(char *seedURL, char *pageDir, int maxdepth)
{	
	//Initialize modules
	bag_t *bag = bag_new();
	hashtable_t *ht = hashtable_new(10000);	//Only allow for 10000 unique urls
	//Proper seed to deal with directories as files (see makeProperURL)
	char *properSeed = makeProperURL(seedURL);
	webpage_t *seed = pagefetch(properSeed, 0);
	char *hostname = extractHostname(properSeed);
	if (bag == NULL || ht == NULL || seed == NULL) {
		return false;
	}
	bag_insert(bag, seed);
	hashtable_insert(ht, properSeed, "foo");
	webpage_t *page;
	int id = 0;
	while ((page = bag_extract(bag)) != NULL) {
		//Iterate
		crawlPage(page, pageDir, id, bag, ht, maxdepth, hostname);
		webpage_delete(page);
		id++;
	}

	//Free bag and its webpages, free the hashtable, free the hostname
	bag_delete(bag, webpage_delete);
	hashtable_delete(ht, NULL);
	free(properSeed);
	free(hostname);
	return true;	
}

/* This function crawls a webpage and adds all the valid urls it finds
 * to the bag to be crawled. All the prints are in this function
 * See IMPLEMENTATION.md for further details
 * @page - the page to be crawled
 * @pageDir - the directory to save the page
 * @id - the filename of the page within the page directory
 * @bag - the data structure to add the found pages
 * @ht - to verify that the the urls have not been traversed already
 * @maxdepth - a check to make sure it stops at the correct depth
 * @hostnm - the hostname extracted from the seedUrl. It should be
 * old-www.cs.dartmouth.edu */
void crawlPage(webpage_t *page, char *pageDir, int id,  bag_t *bag, 
		hashtable_t *ht, int maxdepth, char *hostnm)
{
	// Check parameters
	if (page != NULL && pageDir != NULL && 
	  bag != NULL && ht != NULL && hostnm != NULL) {
		logr("Extracted", webpage_getDepth(page), webpage_getURL(page));

		// Save the page to the proper directory
		if (pagesave(page, pageDir, id)) {
			logr("Saved", webpage_getDepth(page), webpage_getURL(page));

			// Crawl the page if it's less than maxdepth
			if (webpage_getDepth(page) < maxdepth) {
				logr("Scanning", webpage_getDepth(page), webpage_getURL(page));

				int pos = 0;
				char *url;
				//Extract URLs
				while((pos = webpage_getNextURL(page, pos, &url)) > 0) {
					char *properUrl = makeProperURL(url);
					logr("Found", webpage_getDepth(page), properUrl);

					// Make sure the url is crawlable and not seen before
					if (isCrawlable(properUrl, hostnm)) {
						//Separate isCrawlable from ht_insert for printing reasons
						if (hashtable_insert(ht, properUrl, "foo")) {
							webpage_t *newpage = pagefetch(properUrl, webpage_getDepth(page) + 1);
							if (newpage != NULL) {
								bag_insert(bag, newpage);
								logr("Added", webpage_getDepth(page), properUrl);
							}
							else {
								logr("IgnBroken", webpage_getDepth(page), properUrl);
							}
						}
					}
					else {
						logr("IgnExtern", webpage_getDepth(page), properUrl);
					}

					// Free the allocated urls from webpage_getNextURL
					free(url);
					free(properUrl);
				}
			}
		}
	}
}

/* Check if the url is crawlable
 * That is, is the url internal?
 * Is it a normal url? i.e not a pdf or png
 * @url - the url to check.
 * @hostnm - the hostname to compare with
 * @return - true if the url is "crawlable" */
bool isCrawlable(char *url, char *hostnm)
{
	if (url && NormalizeURL(url) && hostnm) {

		char *urlHostnm = extractHostname(url);
		if (urlHostnm && strcmp(hostnm, urlHostnm) == 0) {
			free(urlHostnm);
			return true;
		}
	}
	return false;
}

/* Extract the hostname from a valid url
 * sscanf adapted from https://gist.github.com/fknaopen/1475257
 * Will not modify the url and will return the hostname
 * in an allocated string. It is the RESPONSABILITY of the caller
 * to free the returned string. Will return NUll if url is NULL,
 * cannot malloc memory, or invalid url.
 * @url - the url with a hostname to extract
 * @return - the allocated hostname. Will need to be freed */
char *extractHostname(const char *url)
{
	if (url != NULL) {
		char *result = malloc(strlen(url)+1);
		if (result != NULL) {
			//%*[^/] = throw away everything up to first slash. "http:"
			//%*[/] = throw away next forward slashes
			//%[^/] = get everything up to next forward slash.
			//"http://www.a.b.c/cgi/jobs.cgi?h=99&z=3" -> www.a.b.c
			if (sscanf(url, "%*[^/]%*[/]%[^/]", result) == 1) {
				return result;
			}
		}
	}
	return NULL;
}

/* A function to make a proper url to be fetched.
 * Deals with directories being referenced as files to
 * be fetched.
 * 1. Check to see if file has an extension
 * 2. If it doesn't, make sure the url has an ending forward slash
 * 3. Otherwise return the url as a valid path
 * @url - the url to be properly made
 * @return - a proper url to be fetched.
 * It is the caller's responsability to FREE this returned string. */
char *makeProperURL(char *url)
{
	char *proper;
	if (!hasExtension(url)) {
		proper = appendSlash(url);
	}
	else {
		proper = malloc(strlen(url)+1);
		strcpy(proper, url);
	}
	return proper;
}

/* Print format for crawler output
 * Taken from http://www.cs.dartmouth.edu/~cs50/Lectures/crawler/ 
 * Prints depth, 1 word, and the corresponding url.
 * Indents according to the depth */
inline static void logr(const char *word, const int depth, const char *url)
{
	  printf("%2d %*s%9s: %s\n", depth, depth, "", word, url);
}
