# CS50 Lab 4
## Stephen Crowe, April 2017

### Testing 'crawler'

To test my *crawler* program I created a `testruns` directory which has files that saved the outputs of testruns. The `testruns` directory also contains a `savedPages` directory which stores all the files for crawler.


The following test cases tested different seed urls and different depths. I will normally test the seed url before I test depths.

./crawler http://old-www.cs.dartmouth.edu/~cs50/index.html /net/ifs-users/scrowe/cs50/labs/tse/crawler/testruns/savedPages/cs50index0pages/ 0 > testruns/cs50index0.out
This is one of the simplest tests. It does not search for other urls within the html and is a simple .html file extension. It saves the large page in cs50index0pages/

 ./crawler http://old-www.cs.dartmouth.edu/~cs50/index.html /net/ifs-users/scrowe/cs50/labs/tse/crawler/testruns/savedPages/cs50index5pages/ 5 > testruns/cs50index5.out
This is a more complex version of the ~cs50/index.html seed. It has a maxdepth of 5, but it doesn't matter because most of the links are not internal. Great test for checking pdfs and external urls.

./crawler http://old-www.cs.dartmouth.edu/~scrowe /net/ifs-users/scrowe/cs50/labs/tse/crawler/testruns/savedPages/scrowe1pages/ 1 > testruns/scrowe1.out
This tests a seedurl which is valid but is a directory without a forward slash at the end. Important for that specific edge case.

./crawler http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters /net/ifs-users/scrowe/cs50/labs/tse/crawler/testruns/savedPages/letters10pages/ 10 > testruns/letters10.out
Letters provides a testsuite with specific tripups. Tests quite a few different test cases. Depth of 10 here is unimportant since it basically means "get the whole thing"

./crawler http://old-www.cs.dartmouth.edu/~cs50/data/tse/letters /net/ifs-users/scrowe/cs50/labs/tse/crawler/testruns/savedPages/letters10pages/ 10 > testruns/letters10.out
The mama tester. It gave me ~1700 files.


Testing memory leaks
myvalgrind ./crawler http://old-www.cs.dartmouth.edu/~scrowe /net/ifs-users/scrowe/cs50/labs/tse/crawler/testruns/savedPages/scrowe1pages/ 1
==10066==                                          
==10066== HEAP SUMMARY:                            
==10066==     in use at exit: 0 bytes in 0 blocks  
==10066==   total heap usage: 28,172 allocs, 28,172 frees, 26,423,188 bytes allocated                 
==10066==                                          
==10066== All heap blocks were freed -- no leaks are possible                                         
==10066==                                          
==10066== For counts of detected and suppressed errors, rerun with: -v                                
==10066== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)

### Limitations

I should have run valgrind pointing to the wikipedia section overnight in a tmux terminal. Or a cronjob. Unfortunately, I never set it up.
