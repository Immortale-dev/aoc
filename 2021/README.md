# Advent of Code 2021
C++ solutions for AOC 2021 event

## Build and Run
you can build solutions for each day using any c++ compiler version at least 14. And then just pipe your input to the input buffer.

***Example:***
```bash
cd d12
g++ -o ./a.exe ./a.cpp
./a.exe < input.txt
```

## Days
* ✅**Day 1:** Simple _constructive_ problem.
* ✅**Day 2:** Simple _constructive_ problem. Not harder then the first one.
* ✅**Day 3:** _Constructive_ problem + bit operations.
* ✅**Day 4:** _Constructive_ problem could be optimized to work faster, but the input is small enough for the _brute force_.
* ✅**Day 5:** _Constructive_ problem. Input size is small enough to build a grid and fill it with numbers.
* ✅**Day 6:** Simple _constructive_ with requirement of some optimisations for the second part.
* ✅**Day 7:** First part is _finding median_ problem, and the second one probably could be solved in some pretty way, but the input is small enough to _brute force_.
* ✅**Day 8:** Could be solved with _brute force_ in just O(7! * n) but you get more fun by figuring out digit parts relations. :P
* ✅**Day 9:** Simple _bfs_ problem.
* ✅**Day 10:** Pretty simple problem that could be solved using _stacks_.
* ✅**Day 11:** _Constructive problem_ with a bit of _recursion_. P.S. left some comments for visualisation. ;)
* ✅**Day 12:** Simple _graph_ problem. Solved using _dfs_.
* ✅**Day 13:** Simple _custructive_ problem. P.S. better to compile with `-O3` flag. :P
* ✅**Day 14:** Pretty interesting problem. First part is simple _constructive_, but for the second part some optimisations required (similar to day 6). :P
* ✅**Day 15:** Simple _shortest path finding_ problem. Solved using _bfs_.
* ✅**Day 16:** The most beautiful _constructive_ problem so far! It includes work for parsing bitstream, building multi level structures, and travel these structures with _dfs_. ^_^
* ✅**Day 17:** Pretty werid _constructive_ problem. Could be solved in more elegant way, but input is small enough to _brute force_. :\ 
* ✅**Day 18:** Pretty interesting _constructive_ problem. Should be solved in the same beautiful way as problem from day 16, but I was too lazy, so my solution is a bit hacky :{
* ✅**Day 19:** The hardest _constructive_ problem so far! Needs a lot of code to be written, it's hard to debug, but I liked it! P.S. better to compile with `-O3` flag, as finding solution might take some time. I've put the indicater to see the progress :D
* ✅**Day 20:** Pretty easy _constructive_ problem. Nothing special. Be aware of the first and last bit of enhance map. ;)
* ✅**Day 21:** First part is simple _constructive_, but the second part is pretty nice _dp_ problem! I've truly enjoyed it. :']
* ✅**Day 22:** Very nice _axis optimization_ problem! Beautiful! Don't forget to compile with `-O3` flag, as it takes ~10s to complete, added progress bar. :P
* ✅**Day 23:** Pretty annoying _brute force_ problem... It looks not that hard from the first blance, but it requires a lot of coding and it's easy to screw a lot of things. Don't forget to compile with `-O3` falg, so the solutions runs in 1s.
* ✅**Day 24:** Ah, classic AOC problem where you need to figure out solution by analyzing the input data. Very nice problem! P.S. I figured out it, so you can just send your data as usual. ;) And don't forget to compile with `-O3`. :P
* ✅**Day 25:** Some easy _constructive_ problem in the end! :)

## License
MIT
