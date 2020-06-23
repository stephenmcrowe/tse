# CS50 Lab 4
## Stephen Crowe, April 2017

## crawler implementation

The crawler program basically follows the below pseudocode given in class,
with a few notable exceptions.

1.  execute from a command line as shown in the User Interface
2.	parse the command line, validate parameters, initialize other modules
3.	make a webpage for the seedURL, marked with depth=0
4.	add that page to the bag of webpages to crawl
5.	add that URL to the hashtable of URLs seen
6.	while there are more webpages to crawl,
7.		extract a webpage (URL,depth) item from the bag of webpages to be crawled,
8.		pause for at least one second,
9.		use pagefetcher to retrieve a webpage for that URL,
10.		use pagesaver to write the webpage to the pageDirectory with a unique document ID, as described in the Requirements.
11.		if the webpage depth is < maxDepth, explore the webpage to find links:
12.			use pagescanner to parse the webpage to extract all its embedded URLs;
13.			for each extracted URL,
14.				‘normalize’ the URL (see below)
15.				if that URL is not ‘internal’ (see below), ignore it;
16.					try to insert that URL into the hashtable of URLs seen
17.					if it was already in the table, do nothing;
18.					if it was added to the table,
19.						make a new webpage for that URL, at depth+1
20.						add the new webpage to the bag of webpages to be crawled

Lines 1-2 correspond to the main in crawler and its parsing ability.
Line 2 (initializing modules) is in the crawl function
Lines 3-6 are a part of the crawl function.
Lines 7-20 are in the crawlPage function.


### Notable changes to the in class pseudocode:

The pagefetch function instantiates the webpage structure AND attempts to get the html from the link. Therefore line 9 is actually combined with line 19.

The makeProperUrl function is a personal addition of mine to deal with directories that are accessible but do not have a forward slash at the end of the them. webpage fetch fails without the forward slash.
The isCrawlable function uses a personal extractHostname function I created. It may just slow the runtime down, but I can now easily point it at a different seedurl.

### Implementation notes

Because *bag* is instantiated as a stack, this is a depth first search through the pages.
