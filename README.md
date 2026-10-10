# MyCat

My own version of the `cat` command, written in C.

`cat` is a small tool that prints what is inside a file. I'm building it from scratch to understand what my computer does when I ask it to read a file.

This is week 1 of my systems programming plan.

## What it does

- Prints one file: `./mycat file.txt`
- Prints many files, one after another: `./mycat a.txt b.txt`
- Reads from the keyboard or a pipe when no file is given: `echo hi | ./mycat`
- If a file can't be opened, it skips that file and keeps going

## Two versions

I'm writing this twice on purpose.

### Version 1: using the C library (done)

File: `mycat_stdio.c`

This version uses the easy tools that C gives you: `fopen`, `getc`, `putchar` and `fclose`. You ask for one character at a time and print it.

How to build and run it:

    gcc -Wall -Wextra mycat_stdio.c -o mycat
    ./mycat testfile.txt

How I checked it: I ran my version and the real `cat` on the same files, then compared the outputs with `cmp`. If `cmp` prints nothing, the two outputs are identical.

What surprised me: my loop asks for one character at a time, so for an 81-byte file I expected 81 requests to the operating system. I ran `strace` to watch. There were only 2 `read` calls. The C library had quietly read the whole file in one go and handed me the characters from its own storage. The easy tools were hiding the real work from me.

### Version 2: doing it myself (in progress)

File: coming soon

This version will not use the easy tools. It will talk to the operating system directly with `open`, `read`, `write` and `close`. I will have to decide how much to read at a time and handle the cases where things go wrong.

I'll fill in this section when it works. I plan to try different read sizes, compare them with `strace -c`, and write down what changes.

## What I learned so far

- The shell splits a command into words and gives them to my program as `argc` and `argv`. My program doesn't split them itself.
- Open files are numbered. 0 is the keyboard, 1 is the screen, 2 is for errors. The first file I open gets 3.
- Messages for the user and the file's contents should go to different places, so one doesn't mix into the other.
- `strace` shows what my program really asks the operating system to do.

## Files

- `mycat_stdio.c` - version 1, using the C library
- `testfile.txt`, `testfile2.txt` - small files I use for testing
