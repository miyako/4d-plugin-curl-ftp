![version](https://img.shields.io/badge/version-17%2B-3E8B93)
![platform](https://img.shields.io/static/v1?label=platform&message=osx-64%20|%20win-32%20|%20win-64&color=blue)
[![license](https://img.shields.io/github/license/miyako/4d-plugin-curl-ftp)](LICENSE)
![downloads](https://img.shields.io/github/downloads/miyako/4d-plugin-curl-ftp/total)

# 4d-plugin-curl-ftp
HTTP client based on libcurl-7.62.0

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

### Points of interest

* Missing directories can be created with ``_MakeDir`` and ``_Send``

* ``_Receive`` supports [wildcards](https://curl.haxx.se/libcurl/c/CURLOPT_WILDCARDMATCH.html)

* reduced CPU consumption

* callback method to monitor progress or abort if necessary

although the API is optimsied for FTP, ``_Send`` and ``_Receive`` actually work with other protocols such as HTTP or TFTP.

* Encoding support

For servers that do not support ``OPTS UTF8 ON`` the plugin can convert non-unicode text. Any ``iconv`` charset can be specified.

```
C_OBJECT($options)

$URL:="ftp://ftp.server.com/"

OB SET($options;\
"URL";$URL;\
"ENCODING_OUT";"cp932";\
"USERNAME";"user";\
"PASSWORD";"pass")

C_TEXT($list)

$error:=cURL_FTP_PrintDir (JSON Stringify($options);$list)
```

Commands that support ``ENCODING_IN`` (outgoing text)

* cURL_FTP_Delete
* cURL_FTP_MakeDir
* cURL_FTP_RemoveDir
* cURL_FTP_Rename

Commands that support ``ENCODING_OUT`` (incoming text)

* cURL_FTP_System
* cURL_FTP_PrintDir
* cURL_FTP_GetDirList

### Note on FTPS

set the protocol to ``ftps://`` if you want to use **implicit** FTPS

set the protocol to ``ftp://`` and add the option ``USE_SSL`` if you want to use **explicit** FTPS

use the option ``CAINFO`` for server ceritificate verification

to skip verification, set ``SSL_VERIFYPEER`` to ``0``

see also [forums.4d.com](https://forums.4d.com/Post/FR/31497545/1/33294227#33294227) for discussion on SFTP.

---

## Syntax

```
error:=cURL_FTP_Delete(options{;callbackMethod})
```

Parameter|Type|Description
------------|------------|----
options|TEXT|``JSON``
callbackMethod|TEXT|optional
error|LONGINT|[Error code](https://curl.haxx.se/libcurl/c/libcurl-errors.html)

calls ``DELE`` or ``rm`` (``sftp:``)

```
C_OBJECT($options)

OB SET($options;\
"URL";"ftp://ftp.example.com/a/b/sample.txt";\
"USERNAME";"user";\
"PASSWORD";"pass")

$error:=cURL_FTP_Delete (JSON Stringify($options))
```

```
error:=cURL_FTP_GetDirList(options;list{;callbackMethod})
```

Parameter|Type|Description
------------|------------|----
options|TEXT|``JSON``
list|TEXT|
callbackMethod|TEXT|optional
error|LONGINT|[Error code](https://curl.haxx.se/libcurl/c/libcurl-errors.html)

calls ``LIST`` via [CURLOPT_CUSTOMREQUEST](https://curl.haxx.se/libcurl/c/CURLOPT_CUSTOMREQUEST.html)

the url must end with a delimiter (``/``)

```
C_OBJECT($options)

OB SET($options;"URL";"ftp://ftp.4d.com/SAMPLE_DATABASES/4D/4D_v13/demo_dbs/")

$error:=cURL_FTP_GetDirList (JSON Stringify($options);$list)
```

```
-r--r--r-- 1 ftp ftp        2845148 Jul 17  2015 4DHierarchicalLists.zip
-r--r--r-- 1 ftp ftp       72547498 Jul 17  2015 4DIndexes.zip
-r--r--r-- 1 ftp ftp        5575780 Jul 17  2015 4DListboxes.zip
-r--r--r-- 1 ftp ftp        4269584 Jul 17  2015 4DObjects.zip
-r--r--r-- 1 ftp ftp       98552632 Jul 17  2015 4DPictures.zip
-r--r--r-- 1 ftp ftp        8482751 Jul 17  2015 4DSQL.zip
-r--r--r-- 1 ftp ftp        5429818 Jul 17  2015 4DStaticWebBuilder.zip
```

example of splitting elements

```
$error:=cURL_FTP_GetDirList (JSON Stringify($options);$dir)

If ($error=0)
  ARRAY LONGINT($pos;0)
  ARRAY LONGINT($len;0)
  $i:=1

  While (Match regex("(?m)^(\\S+)\\s+(\\d+)\\s+(\\S+)\\s+(\\S+)\\s+(\\d+)\\s+([:L:]{3}\\s+\\d+)\\s+(\\d+:\\d+)\\s+(.+)$";$dir;$i;$pos;$len))
    $f1:=Substring($dir;$pos{1};$len{1})
    $f2:=Num(Substring($dir;$pos{2};$len{2}))
    $f3:=Substring($dir;$pos{3};$len{3})
    $f4:=Substring($dir;$pos{4};$len{4})
    $f5:=Num(Substring($dir;$pos{5};$len{5}))
    $f6:=Substring($dir;$pos{6};$len{6})
    $f7:=Time(Substring($dir;$pos{7};$len{7}))
    $f8:=Substring($dir;$pos{8};$len{8})
    $i:=$pos{Size of array($pos)}+$len{Size of array($len)}
  End while 

End if
```

```
error:=cURL_FTP_GetFileInfo(options;info{;callbackMethod})
```

Parameter|Type|Description
------------|------------|----
options|TEXT|``JSON``
info|TEXT|
callbackMethod|TEXT|optional
error|LONGINT|[Error code](https://curl.haxx.se/libcurl/c/libcurl-errors.html)

uses [curl_easy_getinfo](https://curl.haxx.se/libcurl/c/curl_easy_getinfo.html) with [CURLOPT_FILETIME](https://curl.haxx.se/libcurl/c/CURLOPT_FILETIME.html) and [CURLINFO_FILETIME](https://curl.haxx.se/libcurl/c/CURLINFO_FILETIME.html)

```
C_OBJECT($options)

OB SET($options;\
"URL";"ftp://test.rebex.net/readme.txt";\
"USERNAME";"demo";\
"PASSWORD";"password")

$error:=cURL_FTP_GetFileInfo (JSON Stringify($options);$info)
```

```
{"size":"403","date":"2014-04-08T14:09:39Z"}
```

```
error:=cURL_FTP_MakeDir(options{;createMissingDir{;callbackMethod}})
```

Parameter|Type|Description
------------|------------|----
options|TEXT|``JSON``
createMissingDir|LONGINT|
callbackMethod|TEXT|optional
error|LONGINT|[Error code](https://curl.haxx.se/libcurl/c/libcurl-errors.html)

calls ``MKD`` or ``mkdir`` (``sftp:``)

[CURLOPT_FTP_CREATE_MISSING_DIRS](https://curl.haxx.se/libcurl/c/CURLOPT_FTP_CREATE_MISSING_DIRS.html) is ``CURLFTP_CREATE_DIR_RETRY `` if ``createMissingDir`` is ``1``

```
C_OBJECT($options)

OB SET($options;\
"URL";"ftp://ftp.example.com/a/b/c";\
"USERNAME";"user";\
"PASSWORD";"pass")

$createMissingDir:=1

$error:=cURL_FTP_MakeDir (JSON Stringify($options);$createMissingDir)
```

```
error:=cURL_FTP_PrintDir(options;dir{;callbackMethod})
```

Parameter|Type|Description
------------|------------|----
options|TEXT|``JSON``
dir|TEXT|
callbackMethod|TEXT|optional
error|LONGINT|[Error code](https://curl.haxx.se/libcurl/c/libcurl-errors.html)

calls ``NLST`` via [CURLOPT_DIRLISTONLY](https://curl.haxx.se/libcurl/c/CURLOPT_DIRLISTONLY.html)

the url must end with a delimiter (``/``)

```
C_OBJECT($options)

OB SET($options;"URL";"ftp://ftp.4d.com/SAMPLE_DATABASES/4D/4D_v13/demo_dbs/")

$error:=cURL_FTP_PrintDir (JSON Stringify($options);$list)
```

```
4DHierarchicalLists.zip
4DIndexes.zip
4DListboxes.zip
4DObjects.zip
4DPictures.zip
4DSQL.zip
4DStaticWebBuilder.zip
```

```
error:=cURL_FTP_Receive(options;path{;wildcardMatch{;callbackMethod}})
```

Parameter|Type|Description
------------|------------|----
options|TEXT|``JSON``
path|TEXT|local system path (folder or file)
wildcardMatch|LONGINT|optional
callbackMethod|TEXT|optional
error|LONGINT|[Error code](https://curl.haxx.se/libcurl/c/libcurl-errors.html)

[CURLOPT_WILDCARDMATCH](https://curl.haxx.se/libcurl/c/CURLOPT_WILDCARDMATCH.html) is used if ``wildcardMatch`` is ``1``

specify a folder in ``path`` when using ``wildcardMatch``

otherwise, specify a file

```
C_OBJECT($options)

OB SET($options;\
"URL";"ftp://ftp.4d.com/SAMPLE_DATABASES/4D/4D_v13/demo_dbs/*.zip")

$path:=System folder(Desktop)+"sample_ftp"+Folder separator

$error:=cURL_FTP_Receive (JSON Stringify($options);$path;1)
```

```
C_OBJECT($options)

OB SET($options;\
"URL";"ftp://ftp.4d.com/SAMPLE_DATABASES/4D/4D_v13/demo_dbs/4DIndexes.zip")

$path:=System folder(Desktop)+"sample_ftp"+Folder separator+"sample.zip"

$error:=cURL_FTP_Receive (JSON Stringify($options);$path;0)
```

```
error:=cURL_FTP_RemoveDir(options{;callbackMethod}})
```

Parameter|Type|Description
------------|------------|----
options|TEXT|``JSON``
callbackMethod|TEXT|optional
error|LONGINT|[Error code](https://curl.haxx.se/libcurl/c/libcurl-errors.html)

calls ``RMD`` or ``rmdir`` (``sftp:``)

```
C_OBJECT($options)

OB SET($options;\
"URL";"ftp://ftp.example.com/a/b/c";\
"USERNAME";"user";\
"PASSWORD";"pass")

$error:=cURL_FTP_RemoveDir (JSON Stringify($options))
```

```
error:=cURL_FTP_Rename(options;name{;callbackMethod})
```

Parameter|Type|Description
------------|------------|----
options|TEXT|``JSON``
name|TEXT|
callbackMethod|TEXT|optional
error|LONGINT|[Error code](https://curl.haxx.se/libcurl/c/libcurl-errors.html)

calls ``RNFR`` followed by ``RNTO`` or ``rename`` (``sftp:``)

```
C_OBJECT($options)

OB SET($options;\
"URL";"ftp://ftp.example.com/a/b/c";\
"USERNAME";"user";\
"PASSWORD";"pass")

$name:="/a/b/c/d" 

$error:=cURL_FTP_Rename (JSON Stringify($options);$name)
```

```
error:=cURL_FTP_Send(options;path{;createMissingDir{;callbackMethod}}})
```

Parameter|Type|Description
------------|------------|----
options|TEXT|``JSON``
path|TEXT|local system path
createMissingDir|LONGINT|optional
callbackMethod|TEXT|optional
error|LONGINT|[Error code](https://curl.haxx.se/libcurl/c/libcurl-errors.html)

[CURLOPT_FTP_CREATE_MISSING_DIRS](https://curl.haxx.se/libcurl/c/CURLOPT_FTP_CREATE_MISSING_DIRS.html) is ``CURLFTP_CREATE_DIR_RETRY`` if ``createMissingDir`` is ``1``

```
$path:=System folder(Desktop)+"test.txt"

C_OBJECT($options)

OB SET($options;\
"URL";"ftp://ftp.example.com/a/b/c/test.txt";\
"USERNAME";"user";\
"PASSWORD";"pass")

$createMissingDir:=1

$error:=cURL_FTP_Send (JSON Stringify($options);$path;$createMissingDir)
```

```
error:=cURL_FTP_System(options;system{;callbackMethod})
```

Parameter|Type|Description
------------|------------|----
options|TEXT|``JSON``
system|TEXT|
callbackMethod|TEXT|optional
error|LONGINT|[Error code](https://curl.haxx.se/libcurl/c/libcurl-errors.html)

calls ``SYST``

not supported for SFTP because [CURLOPT_PREQUOTE](https://github.com/curl/curl/issues/1514) is unavailable

```
C_OBJECT($options)

OB SET($options;"URL";"ftp://ftp.4d.com/")

$error:=cURL_FTP_System (JSON Stringify($options);$system)
```

```
UNIX emulated by FileZilla
```


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

values: ``MULTICWD``, ``NOCWD``, ``SINGLECWD``

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

values: ``AUTH_DEFAULT``, ``AUTH_SSL``, ``AUTH_TLS``

[FTP_SSL_CCC](https://curl.haxx.se/libcurl/c/CURLOPT_FTP_SSL_CCC.html)  

values: ``CCC_NONE``, ``CCC_PASSIVE``, ``CCC_ACTIVE``

* added in ``1.1``

[USE_SSL](https://curl.haxx.se/libcurl/c/CURLOPT_USE_SSL.html)  

values: ``USESSL_NONE`` ``USESSL_TRY`` ``USESSL_CONTROL`` ``USESSL_ALL``

* SSH

[SSH_AUTH_TYPES](https://curl.haxx.se/libcurl/c/CURLOPT_SSH_AUTH_TYPES.html)  
[SSH_COMPRESSION](https://curl.haxx.se/libcurl/c/CURLOPT_SSH_COMPRESSION.html)  
[SSH_HOST_PUBLIC_KEY_MD5](https://curl.haxx.se/libcurl/c/CURLOPT_SSH_HOST_PUBLIC_KEY_MD5.html)  
[SSH_PUBLIC_KEYFILE](https://curl.haxx.se/libcurl/c/CURLOPT_SSH_PUBLIC_KEYFILE.html)  
[SSH_PRIVATE_KEYFILE](https://curl.haxx.se/libcurl/c/CURLOPT_SSH_PRIVATE_KEYFILE.html)  
[SSH_KNOWNHOSTS](https://curl.haxx.se/libcurl/c/CURLOPT_SSH_KNOWNHOSTS.html)

* added in ``2.8``

[TLS13_CIPHERS](https://curl.haxx.se/libcurl/c/CURLOPT_TLS13_CIPHERS.html)  
[PROXY_TLS13_CIPHERS](https://curl.haxx.se/libcurl/c/CURLOPT_PROXY_TLS13_CIPHERS.html)  
[UPKEEP_INTERVAL_MS](https://curl.haxx.se/libcurl/c/CURLOPT_UPKEEP_INTERVAL_MS.html)  
[HAPROXYPROTOCOL](https://curl.haxx.se/libcurl/c/CURLOPT_HAPROXYPROTOCOL.html)  
[DISALLOW_USERNAME_IN_URL](https://curl.haxx.se/libcurl/c/CURLOPT_DISALLOW_USERNAME_IN_URL.html)  
[DNS_SHUFFLE_ADDRESSES](https://curl.haxx.se/libcurl/c/CURLOPT_DNS_SHUFFLE_ADDRESSES.html)  
[HAPPY_EYEBALLS_TIMEOUT_MS](https://curl.haxx.se/libcurl/c/CURLOPT_HAPPY_EYEBALLS_TIMEOUT_MS.html)  
[UPLOAD_BUFFERSIZE](https://curl.haxx.se/libcurl/c/CURLOPT_UPLOAD_BUFFERSIZE.html)  
[DOH_URL](https://curl.haxx.se/libcurl/c/CURLOPT_DOH_URL.html)

---

Signature of ``callbackMethod``

```
abort:=method(curlInfo;userInfo)
```

Parameter|Type|Description
------------|------------|----
curlInfo|TEXT|``JSON`` (``curl_easy_getinfo``)
userInfo|TEXT|the text passed as the ``PRIVATE`` property of ``option``
abort|BOOLEAN|

[``CURLcode``](https://curl.haxx.se/libcurl/c/libcurl-errors.html) is returned in ``error``. when ``True`` is returned from the callback method, ``CURLE_ABORTED_BY_CALLBACK (42)`` is returned. same if the process has been aborted via the runtime explorer. aborting the debugger will not kill the process immediately.
