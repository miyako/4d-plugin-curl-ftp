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
