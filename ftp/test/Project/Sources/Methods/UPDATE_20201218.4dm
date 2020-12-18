//%attributes = {}
/*

{
"features": 99599261,
"host": "x86_64-apple-darwin19.6.0",
"libssh_version": "libssh2/1.9.0",
"libz_version": "1.2.11",
"protocols": [
"dict",
"file",
"ftp",
"ftps",
"gopher",
"http",
"https",
"imap",
"imaps",
"ldap",
"ldaps",
"mqtt",
"pop3",
"pop3s",
"rtmp",
"rtsp",
"scp",
"sftp",
"smb",
"smbs",
"smtp",
"smtps",
"telnet",
"tftp"
],
"ssl_version": "(SecureTransport) OpenSSL/1.1.1i",
"ssl_version_num": 0,
"version": "7.74.0",
"version_num": 477696
}

*/

$versionInfo:=cURL_FTP_VersionInfo 

SET TEXT TO PASTEBOARD:C523(JSON Stringify:C1217(JSON Parse:C1218($versionInfo);*))