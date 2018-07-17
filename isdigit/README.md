testing isdigit different ways...

isdigit.c using whatever ctype.h refers to

isdigit_mask.c function which wastefully initializes the mask array at every call

isdigit_mask_init.c initializes mask array once

isdigit_original.c what I believe is the original way to isdigit


Varying results
```
tardis% uname -a
FreeBSD tardis 11.2-RELEASE FreeBSD 11.2-RELEASE #0 r335510: Fri Jun 22 04:32:14 UTC 2018     root@releng2.nyi.freebsd.org:/usr/obj/usr/src/sys/GENERIC  amd64
tardis% time ./isdigit
./isdigit  22.16s user 0.00s system 99% cpu 22.159 total
tardis% time ./isdigit_mask
./isdigit_mask  13.72s user 0.00s system 99% cpu 13.733 total
tardis% time ./isdigit_mask_init
./isdigit_mask_init  7.96s user 0.00s system 99% cpu 7.979 total
tardis% time ./isdigit_original
./isdigit_original  11.32s user 0.00s system 99% cpu 11.316 total
```

```
rbecker@ukko037:~/isdigit$ uname -a
Linux ukko037 4.10.0-35-generic #39~16.04.1-Ubuntu SMP Wed Sep 13 09:02:42 UTC 2017 x86_64 x86_64 x86_64 GNU/Linux
rbecker@ukko037:~/isdigit$ time ./isdigit

real    0m7.920s
user    0m7.912s
sys     0m0.000s
rbecker@ukko037:~/isdigit$ time ./isdigit_mask

real    0m17.079s
user    0m17.068s
sys     0m0.000s
rbecker@ukko037:~/isdigit$ time ./isdigit_mask_init

real    0m9.674s
user    0m9.664s
sys     0m0.000s
rbecker@ukko037:~/isdigit$ time ./isdigit_original

real    0m12.424s
user    0m12.412s
sys     0m0.000s
```



