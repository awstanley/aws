aws
===


Single-file public domain headers for C++.  Inspired by Sean T. Barrett's kind-hearted and lovely releases.  You might know his work as 'stb'.

Nothing here is particularly remarkable, they exist more as helpers for various projects that I feel are more helpful than not in the wild; that people might enjoy/use them.


library         | lastest version | category       | Language   | description
----------------|-----------------|----------------|------------|----------------------------------------------------------------------------------
aws_protoparser | 1.1.0           | parsing/helper | C++11      | Command-line to (Google) Protocol Buffer parser (requires Protocol Buffers.)




FAQ
---

#### Licence?

Public domain.  You can do whatever you want with them, as with other releases of this nature I appreciate attribution but it is not required legally or otherwise.

If your region does not support public domain code, feel free to consider this release under the MIT licence.


#### Is public domain viral? / If I use it does my code have to be open-source?

No.  You are free to use it as you wish.


#### Why single-header files?

I was largely by Sean T. Barrett (stb), and have released the above as-is for the following reasons:

#. Windows has no default include directory, so adding things to a large number of projects can be painful.  Single file headers dependent only on things noted helps to solve this.
#. Inline headers are really very simple to integrate when dealing with other things; no linker or runtime related issues should arise.
#. If you really dislike it you can, easily, move functions to hpp/cpp files.


#### Why aws?

Those would be my initials (A.W. Stanley).  The code also may stem from my old libraries that I used everywhere (aws, libaws, etc.), so it keeps my references and naming sane.


#### Why C++? Why not C?

C is great, portable, easy to read, etc..  Various changes to C++ make it easier to use, and since I'm not forced to work with C very often (if ever), I tend to use C++.  C++11 also has some really nifty things which make this code easier, saner, and a whole lot more portable.


#### Why public domain?

Because I was inspired to give back to the community which keeps giving, and I find LGPL, GPL, BSD, zlib, and other things don't really fit the "throw away" nature of the code; because I was inspired to follow in the footsteps of a man I admire from afar (Sean Barrett); and because, as stb put it, "more people will use it".  Find it, use it, throw it away.


#### Documentation?

Check each directory for more information; if it's lacking, file an issue or pull request.