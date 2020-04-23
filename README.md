# Trying to execute a C callable fails...

```
% make && gdb -ex run ./test 
julia -e 'using PackageCompiler; create_sysimage(script="myscript.jl", sysimage_path="myscript.so")'
[ Info: PackageCompiler: creating system image object file, this might take a while...
gcc -std=c99 -Wall -O0 -std=gnu99 -I'/home/oliver/local/src/julia-1.4.0/include/julia' -fPIC -L'/home/oliver/local/src/julia-1.4.0/lib' -Wl,--export-dynamic -Wl,-rpath,'/home/oliver/local/src/julia-1.4.0/lib' -Wl,-rpath,'/home/oliver/local/src/julia-1.4.0/lib/julia' -ljulia -ldl -ggdb test.c -o test
GNU gdb (GDB) 8.3.1
Copyright (C) 2019 Free Software Foundation, Inc.
License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>
This is free software: you are free to change and redistribute it.
There is NO WARRANTY, to the extent permitted by law.
Type "show copying" and "show warranty" for details.
This GDB was configured as "x86_64-pc-linux-gnu".
Type "show configuration" for configuration details.
For bug reporting instructions, please see:
<http://www.gnu.org/software/gdb/bugs/>.
Find the GDB manual and other documentation resources online at:
    <http://www.gnu.org/software/gdb/documentation/>.

For help, type "help".
Type "apropos word" to search for commands related to "word"...
Registered pretty printers for UE4 classes
Reading symbols from ./test...
Starting program: /home/oliver/code/julia/compile-test/test 
[Thread debugging using libthread_db enabled]
Using host libthread_db library "/usr/lib/libthread_db.so.1".
[New Thread 0x7ffff3987700 (LWP 455680)]
[New Thread 0x7fffe1080700 (LWP 455684)]
[New Thread 0x7fffde87f700 (LWP 455685)]
[New Thread 0x7fffdc07e700 (LWP 455686)]
[New Thread 0x7fffd987d700 (LWP 455687)]
[New Thread 0x7fffd907c700 (LWP 455688)]
[New Thread 0x7fffd687b700 (LWP 455689)]
[New Thread 0x7fffd407a700 (LWP 455690)]

Calling myfunc with jl_call1 succeeds
jmyfunc(13) = 39

But calling myfunc directly segfaults

Thread 1 "test" received signal SIGSEGV, Segmentation fault.
0x0000000000000000 in ?? ()
(gdb) backtrace
#0  0x0000000000000000 in ?? ()
#1  0x00007fffc5e64f88 in myfunc () from ./myscript.so
#2  0x0000555555555315 in main () at test.c:45
```
