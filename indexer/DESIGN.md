# CS50, Lab 5
## Stephen Crowe, May 2018

## indexer design

The indexer reads the pageDirectory created from the crawler program and saves an inverted index in the filename specified. For datastructures, the indexer creates a hashtable where words found within the pages are the keys and a counters structure is the item. The counters structure holds the id of the filename and the number of times the word appeared in the document. Once this hashtable datastructure is complete, it loops through it to write the structure in a parsable format for later use.
