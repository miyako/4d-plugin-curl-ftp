//%attributes = {}
  //see

C_OBJECT:C1216($options)
$options:=New object:C1471

$options.USERNAME:=""
$options.PASSWORD:=""
$options.SSL_VERIFYPEER:=0
$options.SSL_VERIFYHOST:=0

$options.URL:="ftp://tsftp.4d.com/abcde.txt"

  //FTP: "rename to" can be relative path (no / prefix) or absolute path (with / prefix) 
$status:=cURL_FTP_Rename (JSON Stringify:C1217($options);"/TEST_(KM)/123456789.txt")