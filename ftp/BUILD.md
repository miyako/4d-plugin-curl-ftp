### source code change

* memdebug.c #113, #452
* netrc.c #111
* gtls.c #255
* openssl.c #959, #3103
* vtls.c #886
* mime.c (split from formdata.c) #130, #153, #209, #212
* file.c #77
* cookie.c #1008, #1376

``fopen`` -> ``ufopen``  

* curl_setup.h #261, #361

``#include "ufopen.h"``  
``_stati64(fname, stp)`` -> ``ustati64(fname, stp)``  

### windows

```
Set RTLIBCFG=static
nmake /f Makefile.vc mode=static VC=14 MACHINE=x86 DEBUG=no WITH_SSL=static WITH_ZLIB=static WITH_SSH2=static
nmake /f Makefile.vc mode=static VC=14 MACHINE=x64 DEBUG=no WITH_SSL=static WITH_ZLIB=static WITH_SSH2=static
```

preprocessor

```
CURL_STATICLIB 
```

libs

```
msvcrt.lib;libcmt.lib;Ws2_32.lib;legacy_stdio_definitions.lib;Shell32.lib;
```

for debug, add

```
msvcrtd.lib;vcruntimed.lib;ucrtd.lib;
```
