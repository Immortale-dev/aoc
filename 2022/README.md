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

## License
MIT
