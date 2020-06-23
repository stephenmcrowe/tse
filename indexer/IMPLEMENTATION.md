# CS50 Lab 5
## Stephen Crowe, May 2018

## indexer implementation

The indexer program follows the pseudocode below:

1.	execute from a command line (./indexer pageDirectory newFilename)
2.	parse the command line, validate parameters, initialize hashtable module
3.	construct the path to the first file with id '0'
4.	while there are more files within the crawler directory
5.		extract the webpage from that file
6. 		while there are more words within the webpage
7.			normalize the word
8.			if that word is in the hashtable already
9.				increment the counter count that refers to it
10.				else create a new counters structure for it and initialize the count to 1
11.	open the new index file for writing
12.	print the index in the file

### Implementation notes

To validate the directory as a page directory created by crawler, indexer searches for an empty file called .crawler within the page directory. The crawler program creates this hidden file by default.

The indexer assumes that the ids are listed from 0 to the end without skipping any numbers.

If a path is not specified, the new index file will be created in the currect working directory.

## indextest implementation

The indextest implementation follows the pseudocode below:

1.	execute from the command line (./indextest oldFilename newFilename)
2.	parse the command line, validate correct number of parameters, initialize hashtable
3.	attempt to open the oldFilename for reading
4.	while there are lines in the old index file
5.		create a new counters module
6.		get the word
7.		while there are still more documents which reference the word
8.		put the docId and the count in the counters structure
9.	insert the counters structure into the hashtable
10.	open the new index file for writing
11.	print the index in the file

### Implementation notes

The indextest program does not check to make sure the newFilename is of the correct format. Errors will occur if the format is not correct.
