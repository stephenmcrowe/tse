# CS50 Lab 4
## Stephen Crowe, April 2017

### crawler

The *crawler* is a program that takes a starting url and finds all the links
in that page and then finds all the links in those pages, and then in those 
etc. up to a certain depth. These webpages are saved in a user-created, 
empty directory specified through the command line. These files have the 
url, the depth they were found at, and the html in them.

This is the first module of the TSE

### Usage

```
./crawler seedUrl pageDir maxDepth

Run crawler in the command line with these arguments. seedUrl is a url within
the domain "http://old-www.cs.dartmouth.edu". pageDir is an empty directory 
that has already been created locally. maxdepth specifies the depth of the 
crawl.
```

### Implementation

See the IMPLEMENTATION.md file

### Assumptions

No assumptions beyond those that are clear from the spec.

### Compilation

To compile, simply `make crawler.o`.

See [TESTING](TESTING.md) for details of testing and the savedpages directory for testruns.
