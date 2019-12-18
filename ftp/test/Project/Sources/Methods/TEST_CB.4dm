//%attributes = {}
C_OBJECT:C1216($1;$options)

$PRIVATE:=$1

OB SET:C1220($options;\
"URL";"ftp://...";\
"USERNAME";"...";\
"PASSWORD";"...";"PRIVATE";JSON Stringify:C1217($PRIVATE))

$path:=System folder:C487(Desktop:K41:16)+"video-server-example.4dbase.zip"

$error:=cURL_FTP_Send (JSON Stringify:C1217($options);$path;1;"callbackMethod")