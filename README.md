# 4d-plugin-curl-ftp
FTP client based on libcurl

(draft)

### List of 4D Internet Commands and replacements

``FTP_Append``  
``FTP_ChangeDir``  
``FTP_Delete``  
``FTP_GetDirList``  
``FTP_GetFileInfo``  
``FTP_GetPassive`` : n/a (use ``FTPPORT`` option)  
``FTP_GetType`` : n/a (always binary transfer)  
``FTP_Login``  
``FTP_Logout``  
``FTP_MacBinary``  
``FTP_MakeDir``  
``FTP_PrintDir``  
``FTP_Receive``  
``FTP_RemoveDir``  
``FTP_Rename`` : ``cURL_FTP_Rename``
``FTP_Send``  
``FTP_SetPassive`` : n/a (use ``FTPPORT`` option)  
``FTP_SetType`` : n/a (always binary transfer)   
``FTP_System``  
``FTP_VerifyID``  
``FTP_Progress``  

## Syntax

```
error:=cURL_FTP_RemoveDir(options;path)
```

Parameter|Type|Description
------------|------------|----
options|TEXT|``JSON``
path|TEXT|
recursive|LONGINT|
error|LONGINT|[Error code](https://curl.haxx.se/libcurl/c/libcurl-errors.html)

calls ``RMD``

if ``recursive`` is ``1``, ``CURLOPT_WILDCARDMATCH `` is activated and ``DELE path/*`` is called beforehand.

```
error:=cURL_FTP_Rename(options;from;to)
```

Parameter|Type|Description
------------|------------|----
options|TEXT|``JSON``
from|TEXT|
to|TEXT|
error|LONGINT|[Error code](https://curl.haxx.se/libcurl/c/libcurl-errors.html)

calls ``RNFR`` followed by ``RNTO``

Properties of ``options``

* Basic

[URL](https://curl.haxx.se/libcurl/c/CURLOPT_URL.html)   
[USERNAME](https://curl.haxx.se/libcurl/c/CURLOPT_USERNAME.html)  
[PASSWORD](https://curl.haxx.se/libcurl/c/CURLOPT_PASSWORD.html)  
[FTPPORT](https://curl.haxx.se/libcurl/c/CURLOPT_FTPPORT.html)  

use this 
