# CS50 Lab 5
## Stephen Crowe, May 2018

### Testing 'indexer'

To test my *indexer* program I executed it a few times with outputs from crawler and then verified the file created.

The following commands were executed. Below them, I will explain my logic for testing.

./indexer ../crawler/testruns/savedPages/letters10pages/ ../crawler/testruns/savedPages/letters10pages/index                                                        
The index ../crawler/testruns/savedPages/letters10pages/index has been created.
This tests the indexer with simple, valid input. Letters10pages does not have many files, but the index does need to go through all of them. It should store the data in the index file.


./indexer ../crawler/testruns/savedPages/wikipedia2pages/ ../crawler/testruns/savedPages/wikipedia2pages/index                                                      
The index ../crawler/testruns/savedPages/wikipedia2pages/index has been created.
This testrun is executed on the wikipedia2pages directory, which holds ~1700 files. It indexs all of them into the index file stored in the same directory.



myvalgrind ./indexer ../crawler/testruns/savedPages/letters10pages/ ../crawler/testruns/savedPages/letters10pages/index
==14700== Memcheck, a memory error detector
==14700== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
==14700== Using Valgrind-3.13.0 and LibVEX; rerun with -h for copyright info
==14700== Command: ./indexer ../crawler/testruns/savedPages/letters10pages/ ../crawler/testruns/savedPages/letters10pages/index
==14700== 
The index ../crawler/testruns/savedPages/letters10pages/index has been created.
==14700== 
==14700== HEAP SUMMARY:
==14700==     in use at exit: 0 bytes in 0 blocks
==14700==   total heap usage: 1,651 allocs, 1,651 frees, 216,117 bytes allocated
==14700== 
==14700== All heap blocks were freed -- no leaks are possible
==14700== 
==14700== For counts of detected and suppressed errors, rerun with: -v
==14700== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
Check for memory leaks.



./indexer  
usage: ./indexer pageDirectory indexFilename
Test abnormal user input.



./indexer testruns/savedPages/letters10pages/ indexer.out
usage: ./indexer pageDirectory indexFilename
Test an incorrect crawler directory.



./indexer ../crawler/testruns/savedPages/letters10pages ../common/unknown/indexer.out
Please provide a valid pathname for the indexFilename.
usage: ./indexer pageDirectory indexFilename
Test an unopenable filename.


### Test run

Example runs of the indexer are found in ~/cs50/labs/tse/crawler/testruns/savedPages/[directory]/

`make test` will run both the indexer and indextest. Indextest will output a file in the current working directory.

### Limitations

There are more edge cases to work around. Both indexer and indextest make assumptions about the layout of the page directory and index file format.
