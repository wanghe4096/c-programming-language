# k-and-r
Exercises from "The C Programming Language" by Kernighan / Ritchie. Each chapter has three subfolders:

* **examples/** - examples from the chapter text, usually written as-is.
* **exercises/** - chapter exercises.
* **faq/** - questions I ask myself to check my understanding, with my own examples.

## Source text
You can find the full 2nd edition text [here](http://cs.indstate.edu/~cbasavaraj/cs559/the_c_programming_language_2.pdf).

## Running
`gcc -std=c99 path/to/src -o out; ./out`
Tested on Ubuntu 17.04

## Skipped exercises
Ch. 1:
* 1-14, 1-22.
* 1-20 and 1-21 were solved, but not using tab stops (which I didn't understand when I wrote the solution); they are simply written as search-and-replace algorithms for the specified characters.

Ch. 3:
* 3.3 is solved but not as cleanly as @robot-dreams 's [solution](https://gist.github.com/robot-dreams/34d10248bc474f5a4312fa72e325656a).

Ch. 4:
* 4.10. I skipped this because I completely re-architected the RPN calculator
to loosely couple and more robustly handle parsing, lexing, and token handling; a solution involving parsing the entire string either would require 1) tightly-recoupling these  things so that in one loop you can handle the entire string, determining symbols and pushing it to the stack, or 2) having an intermediary data structure similar to the ungetch() buffer.

## Special thanks
* [Elliott Jin (@robot-dreams)](https://github.com/robot-dreams) for the many hours of help debugging and review.
