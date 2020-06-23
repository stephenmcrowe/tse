# CS50 Lab 4
## Stephen Crowe, April 2017

### Testing 'pagedir'

To test my *pagedir* module I wrote a test program, [pagedirtest](pagedirtest.c), to explore the capabilities of the *pagedir* data structure..

This test program tests the basic capabilities of the *pagedir* module.

These basic capabilities include the normal usage of its functions:
`isWritableDir`
`isEmptyDir`
`pagesave`
`pagefetch`
`appendSlash`
`hasExtension`

It tests the dummy directory to see if `isWritableDir` and `isEmptyDir` function correctly.

It tests fetching a page with `pagefetch` and then saving it to the writable, empty directory with `pagefetch`.

Following these it tests the functions `appendSlash` and `hasExtension` to test a file to be explored but which points to a directory. `pagefetch` will operate incorrectly on a directory that is readable but does not have a forward slash on the end of it.

Finally, `pagefetch` is tested with specific urls like pdfs, pngs, broken links, and forbidden files.

### Test run

An example test run is in `pagedirtest.out`, built with

	make

and 

	./pagedirtest > pagedirtest.out

### Limitations

The module performs very specific functions that are not that useful (or smart), especially appendSlash and hasExtension.
