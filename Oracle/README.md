# Words with Friends Problem

## Problem Statement

Given the included dictionary file `words.txt` write a program to take a shuffled set of letters and return:

 - What words from the dictionary the user can spell with these letters?
 - What words begin with these letters as a prefix?
 - What words end with these letters as a suffix?

You may use any programming language with which you are comfortable but bonus points for using python.

Along with your source code, include any documentation necessary to compile / run your program.

Extra credit for performance optimizations and/or unit tests.

## Example Usage

Assume your program is called "scrabbler".

To find all the words you can spell with 7 letters "abcdefg" you should be able to type:

    $ scrabbler abcdefg

And get back a list of words as output. Something like:

        abed
        ace
        aced
        ad
        age
         ...
        fade
        fag
        fed
        gab
        gad

**NOTICE:** Each letter can be used only once.

To find all words that begin with a specific prefix:

    $ scrabbler --prefix fi
        fiance
        fiancee
        fiancees
        fiances
        fiasco
         ...
        fizzle
        fizzled
        fizzles
        fizzling
        fizzy

To find all words with a specific suffix:

    $ scrabbler --suffix o
        achoo
        adagio
        ado
        aficionado
        ago
         ...
        woo
        yahoo
        yo
        zero
        zoo


# Performance analysis
Uptill now I have implemented two versions for this problem, one is actually pure C with quicksort while another one is C++11 with a map like structure, in theory the C++ version should outbeat pure C version especially say about the map structure, but the fact is C outbeats the C++ and it is more clean and general than C++. :)

Here's the result from ```C```'s version:
```sh
# time ./c_scrabbler abcdefg
...
real    0m0.011s
user    0m0.008s
sys    0m0.002s
```

Here's the result from ```C++```'s version
```sh
# time ./cpp_scrabbler abcdefg
...
real    0m0.029s
user    0m0.026s
sys    0m0.002s
```

