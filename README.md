str2long_contest
================

code corresponding to a coding contest posted here: http://blog.regehr.org/archives/909

Notes by codingjourney

**Correctness**

I discovered the contest [after it was over](http://blog.regehr.org/archives/914) but decided to try the challenge anyway. I implemented str2long as a stand-alone program and did some ad-hoc tests from the command line.

Reading John Regehr's evaluation of the other submissions, I realized my code wouldn't pass the "9 billion leading zeroes" test case. I checked out the test harness, ported the code and wrote the second iteration. Running against a comprehensive test suite uncovered another bug - I had wrongly assumed that an overflowed value would be less than the value before the overflow (even under two's complement semantics that fails for multiplication).

My third version finally passed all tests when compiled with *gcc* so I tried compiling with *clang* as well. A test kept failing on a comparison which I was sure was correct. In addition, the test would stop failing when compiled with *-O0*. I was beginning to suspect a compiler bug. A kind soul on the *#llvm* IRC channel pointed me to a [great explanation](http://blog.llvm.org/2011/05/what-every-c-programmer-should-know.html) which lead to [more revelations](http://blog.regehr.org/archives/213).

As I'm basically a Java guy, grokking the full implications of "undefined behavior" in C was an intense experience. Chris Lattner uses the euphemism "pretty scary"; my thoughts were more along the lines of "OMFG this civilization is DOOMED". I eventually realized no continent has yet sunk beneath the waves due to an integer overflow so it may not be quite so bad. I do wonder a bit, however, how it is that my notebook manages to boot every time. John Regehr [puts it best](): "Creating a large piece of safety-critical or security-critical code in C or C++ is the programming equivalent of crossing an 8-lane freeway blindfolded."

So my fourth iteration uses the strategy of detecting that an overflow would happen (vs. trying to detect that it *has* happened). It passes the test suite both under gcc and under clang. Due to time constraints, I haven't tested it in a 64-bit environment, nor with the Intel compiler, nor on an ARM box or under other configurations.

**Performance**

Speed-wise my code is well in the middle of the field so I had a quick look at the fastest submissions to see what was special about them. Under gcc the winner on my machine was davide_3 and under clang it was yang_2. Both use the extra magnitude bit in an unsigned long to detect overflow after-the-fact (seems a bit of a cop-out to me but obviously within the rules). The two are otherwise quite different beasts, however. I found yang_2 very readable if a bit verbose, with all special cases handled outside the loop. davide_3, on the other hand, was quite opaque to me. Especially the unsigned int cast (saving one comparison in digit validation) was especially sneaky, had me scratching my head for a minute.

**Readability**

Compared to both speed champs, my code looks verbose and pompous (long variable names, all special cases handled within the loop). Better white-spacing and some comments would surely improve it. Oh, and it increments a const pointer but, strangely, neither of the compilers complained...

**Conclusion**

I want to thank John Regehr for an unexpected bit of fun (and wasted time...) but mainly for the great work he does promoting correctness in systems programming.
