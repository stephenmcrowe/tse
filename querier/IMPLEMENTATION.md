# CS50 Lab 6
## Stephen Crowe, May 2018

## querier implementation

The querier program follows the pseudocode below:

1. execute from a command line
2. parse the command line, validate parameters, initialize index
3. read from the stdin
4.   normalize the query, breaking it up into words 
5.	 print a clean query
6. 	 validate the 'and' 'or' syntax
7.	 combine counters structs into one to rank by parsing the query
8.	 sort the final structure
9.	 print all the matching documents

### Implementation notes


