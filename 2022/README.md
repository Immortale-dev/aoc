# Advent of Code 2022
C++ solutions for AOC 2022 event

## Build and Run
you can build solutions for each day using any c++ compiler version >= 14. And then just pipe your input to the input buffer.

***Example:***
```bash
cd d12
g++ -o ./a.exe ./a.cpp
./a.exe < input.txt
```

Some of the problems are fun and you can print the result of execution by defining `PRINT` macro. You can easaly do it with
GNU compiler `-D` flag.

***Example:***
```bash
g++ -o ./a.exe ./a.cpp -D PRINT
```

## Days
* ✅**Day 1:** Simple _constructive_ problem.
* ✅**Day 2:** Easy _constructive_ problem.
* ✅**Day 3:** _Constructive_ problem, solved using hashmaps.
* ✅**Day 4:** Simple _constructive_ problem, requires some basic segments overpal knowledges.
* ✅**Day 5:** Simple _constructive_ problem. Solved using deque containers. P.S. define `PRINT` macro to print the results ;)
* ✅**Day 6:** Simple problem that requires basic knowledges about _hashmaps_.
* ✅**Day 7:** Simple problem requiring _recursion_ knowledges. Finally it started to be interesting :)
* ✅**Day 8:** Simple _constructive_ problem for couple of nested for-loops.
* ✅**Day 9:** The most common AOC _constructive_ problem. Very nice! You can use `PRINT` flag to see the result ;)
* ✅**Day 10:** Another typical _constructive_ AOC problem with device, screen and text result. Very nice! :)
* ✅**Day 11:** Pretty fun _constructive_ problem with a little trick for the second part ;)
* ✅**Day 12:** Simple _dynamic programming_ find shortest path problem. P.S. better to cimpile with `-O3` so the solution runs in less than 1s for the second part. :P
* ✅**Day 13:** Pretty nice _constructive_ problem that wants you to create a class and override operator `<`. ^_^
* ✅**Day 14:** Nice _constructive_ problem. Use `PRINT` flag to visualize the result ;)
* ✅**Day 15:** Great problem that requires some grid decomposition optimisation for the second part. Use `-O3` flag so the second part runs in less than 1s. ;]
* ✅**Day 16:** Pretty hard _dynamic programming_ problem. I'm not sure if my solution works for all of the input data, works for my though :P. P.S. use `-O3` flag so the second part runs in less than a sec.
* ✅**Day 17:** Standard AOC problem when you have a simple _constructive_ problem for the first part, and unbelievably huge limits for the second (but with repeated pattern :P), so you have to figure out how to cut off most of the work >:D
* ✅**Day 18:** Great problem that teaches you some BFS. ^.^
* ✅**Day 19:** Pretty hard _dynamic programming_ problem. My solution again might not work for your data, but it should. Use `-O3` flag as the solution takes some time to complete. I've added a progress bar. :P
* ✅**Day 20:** Great _constructive_ problem that teaches you to use lists, and requires small optimisations for the second part. -_^
* ✅**Day 21:** Awesome _binary search_ problem. Just a bit tricky, but pretty fun to do. :D
* ✅**Day 22:** The most horrible problem so far. So annoying one. It's so hard to make it generic, so my solution might not work for you, sorry. T_T

## License
MIT
