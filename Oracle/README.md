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
