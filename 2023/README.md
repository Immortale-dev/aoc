# Advent of Code 2023
C++ solutions for AOC 2023 event

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
* ✅**Day 1:** Simple _constructive_ problem for any language but C++. Solved with hacks. :P
* ✅**Day 2:** Simple _constructive_ problem. Even parsing was not that bad :D
* ✅**Day 3:** Simple _constructive_ problem. Solved naivly :}
* ✅**Day 4:** Simple _dynamic programming_ problem :]
* ✅**Day 5:** Very nice problem on _ranges manipulation_ ^_*
* ✅**Day 6:** Interesting problem that can be solved by using quadratic equations, or binary search, but the limits are so low, that brute force does the work :')
* ✅**Day 7:** Pretty cool _sorting_/_wildcart_ problem! But feels more like constructive ;P
* ✅**Day 8:** Great problem for training your _dividers finding_ and _LCM_ skills ^.^
* ✅**Day 9:** Pretty easy problem. Very elegantly solved using _recursions_ ;]
* ✅**Day 10:** Very interesting problem for _BFS_ and a bit over complicated _point inside enclosed path_ algorithm problems :F
* ✅**Day 11:** Very easy but great problem! Solved _naivly_ with a bit of range finding optimization %)
* ✅**Day 12:** Awesome problem! First part is solved with _brute force_, so better co compile it with `-O2` flag. and second part for solved using _memoization_ algorithm :@
* ✅**Day 13:** Very easy _constructive_ problem. Feels like next day should be extreamly hard xD
* ✅**Day 14:** Good but pretty easy problem on _finding patterns_ in a sequence of values -_-
* ✅**Day 15:** Easy but fancy _data structures_ problem. Solved using lists + hashmaps ^_^
* ✅**Day 16:** Great _BFS_ problrm! Solved with help of _bit manipilation_ algorithms \o.o/
* ✅**Day 17:** Awesome _DP_ problem. Used _BFS_ approach, not best, so consider compiling with `-O2` flag, so the solution runs in couple of seconds ;)
* ✅**Day 18:** Very nice problem, for _segments manipulations_. One of the hardest so far, even though it is somehow similar to **day 10** problem, but more annoying T_T
* ✅**Day 19:** First part is simple _constructive_ problem, the the second one is One of the best _combinatoric_ problems so far! Solved by using _ranges_ together with  _grid decomposition_ algorithm :8)
* ✅**Day 20:** Ah, classic AOC problem. Probably the best of its kind so far! First part is just _constructive_, but to solve the second part and to build a solution you have to _analyze_ input data just a bit. Solved using _cycle detection_, and generating the answer with _LCM_ ^j^
* ✅**Day 21:** Awesome _combinatory_/_BFS_ problem! Absolutely love it! Although I spent a lot of time debugging it, the process was 100% pleasant }:P
* ✅**Day 22:** Pretty cool _constructive_/ _graph travel_ problem, but I was to lazy to build a graph, and _brute forced_ the solution. Better to compile with `-O2` flag, and be patient to wait **~10s** for algorithm to finish ]:|
* ✅**Day 23:** Classic **NP-hard** _travelling salesman_ problem. Input is low enough for algorithm to work within a reasonable time **<10m**, so compile with `-O2` flag, and be patient /@-@\


## License
MIT
