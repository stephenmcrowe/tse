# CS50 Lab 5
## Stephen Crowe, May 2018

### Testing 'indexer'

**Test Regular Cases**

This test occurred when I finished the final counters structure for the query. It was testing my logic for 'and' statements and 'or' statements. The words 'a', 'e', and 'f' are being tested on letters. 'a' has (0,2) (1,2) (2,2) and (4,1). 'e' has (3,1) and (4,2). 'f' has (4,1) and (7,2). 
Notable parts of the test: 
1. all different 'and' statements should result in (4,1).
2. putting 'or' in between all of them should have (4,4).
3. 'a' without an 'and' should result in many documents.

./querier ../crawler/testruns/savedPages/letters10pages/ ../crawler/testruns/savedPages/letters10pages/index < tests/andorlogic.txt                                 
loaded index                                       
Query: a                                           
 0 2 1 2 2 2 4 1                                   
Query: e                                           
 3 1 4 2                                           
Query: f                                           
 4 1 7 2                                           
Query: a e                                         
 4 1                                               
Query: a f                                         
 4 1                                               
Query: e f                                         
 4 1                                               
Query: e and a                                     
 4 1                                               
Query: f and a                                     
 4 1                                               
Query: f and e                                     
 4 1                                               
Query: a or e                                      
 3 1 0 2 1 2 2 2 4 3                               
Query: a or f                                      
 7 2 0 2 1 2 2 2 4 2                               
Query: e or f                                      
 7 2 3 1 4 3                                       
Query: a e f                                       
 4 1                                               
Query: a and e and f                               
 4 1                                               
Query: a or e or f                                 
 7 2 3 1 0 2 1 2 2 2 4 4                           
Query: a and e or f                                
 7 2 4 2                                           
Query: f or a and e                                
 4 2 7 2                                           
Query: a e or f                                    
 7 2 4 2                                           
Query: f or a e                                    
 4 2 7 2                                           
Query: a or f and e                                
 0 2 1 2 2 2 4 2                                   
Query: f e or a                                    
 0 2 1 2 2 2 4 2                                   
Query: f and a or e                                
 3 1 4 3                                           
Query: e or a f                                    
 3 1 4 3

Finalized version of this test is saved in ~/cs50/labs/tse/querier/tests/andorlogic.out
./querier ../crawler/testruns/savedPages/letters10pages/ ../crawler/testruns/savedPages/letters10pages/index < tests/andorlogic.txt > tests/andorlogic.out


**Test Edge Cases**

Test the 'and' 'or' logic for a query.

./querier ../crawler/testruns/savedPages/letters10pages/ ../crawler/testruns/savedPages/letters10pages/index < tests/andorerrors.txt
Query: and 
'and' cannot be first
Query: and apple 
'and' cannot be first
Query: apple and 
'and' cannot be last
Query: or 
'or' cannot be first
Query: or apple 
'or' cannot be first
Query: apple or 
'or' cannot be last
Query: and or 
'and' cannot be first
Query: or and 
'or' cannot be first
Query: apple and and banana 
keywords 'and' and 'or' cannot be adjacent
Query: apple and or banana 
keywords 'and' and 'or' cannot be adjacent
Query: apple or or banana 
keywords 'and' and 'or' cannot be adjacent
Query: apple or and banana 
keywords 'and' and 'or' cannot be adjacent


Test bad characters within the query.

./querier ../crawler/testruns/savedPages/letters10pages/ ../crawler/testruns/savedPages/letters10pages/index < tests/punctuation.txt 
Query: dartmouth college 
No documents match
Error: bad character '2' in query.
Error: bad character '1' in query.
Error: bad character '.' in query.
Error: bad character '@' in query.
Error: bad character '-' in query.
Error: bad character '@' in query.
Error: bad character '&ast;' in query.
Error: bad character '?' in query.


### Test run

Example runs of the querier are found in ~/cs50/labs/tse/querier/tests/

`make test` will run the querier with a simple test on the wikipedia pages

### Limitations

