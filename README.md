# 3d
This is my attempt to make something that does 3D using SDL2 and C.

Very simple, it just uses a perspective projection to put a rotating cube on the screen.

(relatively simple)

I made some mistakes:
  - Didn't know why they added the fourth term to the vector, so I ignored it and used 3-vectors (big mistake).
  - Used too many structs when I could've used arrays.
  - The debug code causes a segfault (I removed it).
  - Very messy.
  - Didn't know how to store complicated data, so I just created a header file that adds the object at compile time.

It does render *something* which is miraculous, but I wouldn't go as far as to call it a "cube".

At the last moment I put in a orthographic projection and that also didn't work.

I might revisit this project after I figure out what I'm doing.

Wikipedia seems like it's only for people who already know the topic they are learning.

Run this (why tho):

You need to have the SDL2 development package installed. On apt this package is called `libsdl2-dev`.

You then compile it with `[compiler] test_projection.c -lm -lSDL2 -lSDL2main`.

test_functions.c is only for testing matrix.h.

If you aren't using linux then do the correct thing that you're supposed to do.
