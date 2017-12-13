# 4d-plugin-curl-ftp
FTP/SFTP/FTPS client based on libcurl-7.57.0

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
``FTP_Receive`` : ``cURL_FTP_Receive``  
``FTP_RemoveDir`` : ``cURL_FTP_RemoveDir``    
``FTP_Rename`` : ``cURL_FTP_Rename``  
``FTP_Send`` : ``cURL_FTP_Send``  
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
error:=cURL_FTP_Receive(options;path;numberOfRetries;callbackMethod;wildcardMatch)
```

Parameter|Type|Description
------------|------------|----
options|TEXT|``JSON``
path|TEXT|local system path
numberOfRetries|LONGINT|
callbackMethod|TEXT|
wildcardMatch|LONGINT|
error|LONGINT|[Error code](https://curl.haxx.se/libcurl/c/libcurl-errors.html)

[CURLOPT_WILDCARDMATCH](https://curl.haxx.se/libcurl/c/CURLOPT_WILDCARDMATCH.html) is used if ``wildcardMatch`` is ``1``

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
error:=cURL_FTP_Send(options;path;numberOfRetries;callbackMethod)
```

Parameter|Type|Description
------------|------------|----
options|TEXT|``JSON``
path|TEXT|local system path
numberOfRetries|LONGINT|
callbackMethod|TEXT|
error|LONGINT|[Error code](https://curl.haxx.se/libcurl/c/libcurl-errors.html)

```
error:=cURL_FTP_System(options;system)
```

Parameter|Type|Description
------------|------------|----
options|TEXT|``JSON``
system|TEXT|
error|LONGINT|[Error code](https://curl.haxx.se/libcurl/c/libcurl-errors.html)

calls ``SYST``

[CURLOPT_PREQUOTE](https://github.com/curl/curl/issues/1514) not available for SFTP

---

Properties of ``options``

* General

[URL](https://curl.haxx.se/libcurl/c/CURLOPT_URL.html)  
[USERNAME](https://curl.haxx.se/libcurl/c/CURLOPT_USERNAME.html)  
[PASSWORD](https://curl.haxx.se/libcurl/c/CURLOPT_PASSWORD.html)  
[FTPPORT](https://curl.haxx.se/libcurl/c/CURLOPT_FTPPORT.html)  
[APPEND](https://curl.haxx.se/libcurl/c/CURLOPT_APPEND.html)  
[FTP_ACCOUNT](https://curl.haxx.se/libcurl/c/CURLOPT_FTP_ACCOUNT.html)  
[PRIVATE](https://curl.haxx.se/libcurl/c/CURLOPT_PRIVATE.html)  

* RFC 2428

[FTP_USE_EPRT](https://curl.haxx.se/libcurl/c/CURLOPT_FTP_USE_EPRT.html)  
[FTP_USE_EPSV](https://curl.haxx.se/libcurl/c/CURLOPT_FTP_USE_EPSV.html)  

* Host Specific

[FTP_USE_PRET](https://curl.haxx.se/libcurl/c/CURLOPT_FTP_USE_PRET.html)  
[FTP_ALTERNATIVE_TO_USER](https://curl.haxx.se/libcurl/c/CURLOPT_FTP_ALTERNATIVE_TO_USER.html)  
[FTP_FILEMETHOD](https://curl.haxx.se/libcurl/c/CURLOPT_FTP_FILEMETHOD.html)

* Connection

[TCP_KEEPALIVE](https://curl.haxx.se/libcurl/c/CURLOPT_TCP_KEEPALIVE.html)  
[TCP_KEEPIDLE](https://curl.haxx.se/libcurl/c/CURLOPT_TCP_KEEPIDLE.html)  
[TCP_KEEPINTVL](https://curl.haxx.se/libcurl/c/CURLOPT_TCP_KEEPINTVL.html)  

* Threshold

[FTP_RESPONSE_TIMEOUT](https://curl.haxx.se/libcurl/c/CURLOPT_FTP_RESPONSE_TIMEOUT.html)  
[CONNECTTIMEOUT](https://curl.haxx.se/libcurl/c/CURLOPT_CONNECTTIMEOUT.html)  
[TIMEOUT](https://curl.haxx.se/libcurl/c/CURLOPT_TIMEOUT.html)  
[LOW_SPEED_TIME](https://curl.haxx.se/libcurl/c/CURLOPT_LOW_SPEED_TIME.html)  
[LOW_SPEED_LIMIT](https://curl.haxx.se/libcurl/c/CURLOPT_LOW_SPEED_LIMIT.html)  

* Verification

[SSL_VERIFYHOST](https://curl.haxx.se/libcurl/c/CURLOPT_SSL_VERIFYHOST.html)  
[SSL_VERIFYPEER](https://curl.haxx.se/libcurl/c/CURLOPT_SSL_VERIFYPEER.html)  
[CAINFO](https://curl.haxx.se/libcurl/c/CURLOPT_CAINFO.html)  

* Encryption

[FTPSSLAUTH](https://curl.haxx.se/libcurl/c/CURLOPT_FTPSSLAUTH.html)  
[FTP_SSL_CCC](https://curl.haxx.se/libcurl/c/CURLOPT_FTP_SSL_CCC.html)  

* SSH

[SSH_AUTH_TYPES](https://curl.haxx.se/libcurl/c/CURLOPT_SSH_AUTH_TYPES.html)  
[SSH_COMPRESSION](https://curl.haxx.se/libcurl/c/CURLOPT_SSH_COMPRESSION.html)  
[SSH_HOST_PUBLIC_KEY_MD5](https://curl.haxx.se/libcurl/c/CURLOPT_SSH_HOST_PUBLIC_KEY_MD5.html)  
[SSH_PUBLIC_KEYFILE](https://curl.haxx.se/libcurl/c/CURLOPT_SSH_PUBLIC_KEYFILE.html)  
[SSH_PRIVATE_KEYFILE](https://curl.haxx.se/libcurl/c/CURLOPT_SSH_PRIVATE_KEYFILE.html)  
[SSH_KNOWNHOSTS](https://curl.haxx.se/libcurl/c/CURLOPT_SSH_KNOWNHOSTS.html)

---

Signature of callback method

```
abort:=method(curlInfo;userInfo)
```

Parameter|Type|Description
------------|------------|----
curlInfo|TEXT|``JSON`` (``curl_easy_getinfo``)
userInfo|TEXT|the text passed as the ``PRIVATE`` property of ``option``
abort|BOOLEAN|
