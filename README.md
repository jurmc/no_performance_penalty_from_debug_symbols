Question is: "Do debug symbols has an impact on performance on compiled binary?"

Here is some evidence that debug there is no such impact:

```
./perf_testO0
test_optimization_fsplit_loops (flags: -O0): 9.905 seconds.
test_optimization_fpeel_loops (flags: -O0): 10.537 seconds.
test_optimization_fpredictive_commoning (flags: -O0): 81.981 seconds.
./perf_testO3
test_optimization_fsplit_loops (flags: -O3): 3.674 seconds.
test_optimization_fpeel_loops (flags: -O3): 2.477 seconds.
test_optimization_fpredictive_commoning (flags: -O3): 5.699 seconds.
./perf_testO0ggdb
test_optimization_fsplit_loops (flags: -O0 -ggdb): 9.981 seconds.
test_optimization_fpeel_loops (flags: -O0 -ggdb): 10.595 seconds.
test_optimization_fpredictive_commoning (flags: -O0 -ggdb): 81.861 seconds.
./perf_testO3ggdb
test_optimization_fsplit_loops (flags: -O3 -ggdb): 3.663 seconds.
test_optimization_fpeel_loops (flags: -O3 -ggdb): 2.471 seconds.
test_optimization_fpredictive_commoning (flags: -O3 -ggdb): 5.700 seconds.
```

Debug symbols has an impact on the compiled binary size.
Of course you face performance penalty if you run your binary under a debugger control.
There are other reasons not to ship binaries with debug symbols (for example security),
but when binary is loaded to the memory its debug symbols still reside only on the disk,
and can serve debugger (or other tools) needs if requred.

If you mix debug and optimization flags in your build your debugger might also
become less useful since there will be some code in compiled binary that cannot
be matched with your source code.

