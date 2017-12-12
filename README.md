# 4d-plugin-curl-ftp
FTP client based on libcurl

(draft)

## Syntax

```
error:=cURL_FTP_Rename(options;from;to)
```

Parameter|Type|Description
------------|------------|----
options|TEXT|``JSON``
from|TEXT|
to|TEXT|
error|LONGINT|

Properties of ``options``

* Basic

[URL](https://curl.haxx.se/libcurl/c/CURLOPT_URL.html) 

ESCAPE apply [curl_easy_escape()](https://curl.haxx.se/libcurl/c/curl_easy_escape.html) to URL

[USERNAME](https://curl.haxx.se/libcurl/c/CURLOPT_USERNAME.html)

[PASSWORD](https://curl.haxx.se/libcurl/c/CURLOPT_PASSWORD.html)
