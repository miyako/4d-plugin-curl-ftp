# 4d-plugin-curl-ftp
FTP client based on libcurl

(draft)

### List of 4D Internet Commands and replacements

``FTP_Append`` :  n/a (use ``APPEND`` option)    
``FTP_ChangeDir`` : n/a (sessions are not kept open)  
``FTP_Delete`` : ``cURL_FTP_Delete``  
``FTP_GetDirList`` : ``cURL_FTP_GetDirList``  
``FTP_GetFileInfo`` : ``cURL_FTP_GetFileInfo``  
``FTP_GetPassive`` : n/a (use ``FTPPORT`` option)  
``FTP_GetType`` : n/a (always binary transfer)  
``FTP_Login`` : n/a (sessions are not kept open)  
``FTP_Logout`` : n/a (sessions are not kept open)  
``FTP_MacBinary`` : n/a (deprecated)  
``FTP_MakeDir`` : ``cURL_FTP_MakeDir``  
``FTP_PrintDir`` : ``cURL_FTP_PrintDir``  
``FTP_Receive``  
``FTP_RemoveDir`` : ``cURL_FTP_RemoveDir``    
``FTP_Rename`` : ``cURL_FTP_Rename``  
``FTP_Send``  
``FTP_SetPassive`` : n/a (use ``FTPPORT`` option)  
``FTP_SetType`` : n/a (always binary transfer)   
``FTP_System``: ``cURL_FTP_System``  
``FTP_VerifyID`` : n/a (sessions are not kept open)   
``FTP_Progress`` : n/a (use ``PRIVATE`` option)   

## Syntax

```
error:=cURL_FTP_Delete(options;path)
```

Parameter|Type|Description
------------|------------|----
options|TEXT|``JSON``
name|TEXT|
error|LONGINT|[Error code](https://curl.haxx.se/libcurl/c/libcurl-errors.html)

calls ``DELE``

```
error:=cURL_FTP_GetDirList(options;path)
```

Parameter|Type|Description
------------|------------|----
options|TEXT|``JSON``
name|TEXT|
error|LONGINT|[Error code](https://curl.haxx.se/libcurl/c/libcurl-errors.html)

calls ``LIST`` via [CURLOPT_CUSTOMREQUEST](https://curl.haxx.se/libcurl/c/CURLOPT_CUSTOMREQUEST.html)

```
error:=cURL_FTP_GetFileInfo(options;path)
```

Parameter|Type|Description
------------|------------|----
options|TEXT|``JSON``
name|TEXT|
error|LONGINT|[Error code](https://curl.haxx.se/libcurl/c/libcurl-errors.html)

uses [curl_easy_getinfo](https://curl.haxx.se/libcurl/c/curl_easy_getinfo.html).

```
error:=cURL_FTP_MakeDir(options;path)
```

Parameter|Type|Description
------------|------------|----
options|TEXT|``JSON``
name|TEXT|
error|LONGINT|[Error code](https://curl.haxx.se/libcurl/c/libcurl-errors.html)

calls ``MKD``

```
error:=cURL_FTP_PrintDir(options;path)
```

Parameter|Type|Description
------------|------------|----
options|TEXT|``JSON``
name|TEXT|
error|LONGINT|[Error code](https://curl.haxx.se/libcurl/c/libcurl-errors.html)

calls ``NLST`` via [CURLOPT_DIRLISTONLY](https://curl.haxx.se/libcurl/c/CURLOPT_DIRLISTONLY.html)

```
error:=cURL_FTP_RemoveDir(options;path)
```

Parameter|Type|Description
------------|------------|----
options|TEXT|``JSON``
name|TEXT|
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

```
error:=cURL_FTP_System(options)
```

Parameter|Type|Description
------------|------------|----
options|TEXT|``JSON``
error|LONGINT|[Error code](https://curl.haxx.se/libcurl/c/libcurl-errors.html)

calls ``SYST``

---

Properties of ``options``

* General

[URL](https://curl.haxx.se/libcurl/c/CURLOPT_URL.html)  
[USERNAME](https://curl.haxx.se/libcurl/c/CURLOPT_USERNAME.html)  
[PASSWORD](https://curl.haxx.se/libcurl/c/CURLOPT_PASSWORD.html)  
[FTPPORT](https://curl.haxx.se/libcurl/c/CURLOPT_FTPPORT.html)  
[APPEND](https://curl.haxx.se/libcurl/c/CURLOPT_APPEND.html)  
[ACCOUNT](https://curl.haxx.se/libcurl/c/CURLOPT_FTP_ACCOUNT.html)  
[PRIVATE](https://curl.haxx.se/libcurl/c/CURLOPT_PRIVATE.html)  

* RFC 2428

[EPRT](https://curl.haxx.se/libcurl/c/CURLOPT_FTP_USE_EPRT.html)  
[EPSV](https://curl.haxx.se/libcurl/c/CURLOPT_FTP_USE_EPSV.html)  

* Host Specific

[PRET](https://curl.haxx.se/libcurl/c/CURLOPT_FTP_USE_PRET.html)  

* Connection

[KEEPALIVE]  
[KEEPIDLE]  
[KEEPINTVL]  

* Threshold

[RESPONSE_TIMEOUT](https://curl.haxx.se/libcurl/c/CURLOPT_FTP_RESPONSE_TIMEOUT.html)  
[CONNECTTIMEOUT]  
[TIMEOUT]  
[LOW_SPEED_TIME]  
[LOW_SPEED_LIMIT]  

* Verification

[VERIFYHOST]
[VERIFYPEER]  
[CAINFO]  
