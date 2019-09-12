//%attributes = {}
  //(P) cURL_Test
  //----------------------------------------------------

C_TEXT:C284($desktop;$localName;$hostName)
C_BLOB:C604($keyPub;$keyPriv)
C_LONGINT:C283($error)

$desktop:=System folder:C487(Desktop:K41:16)

DOCUMENT TO BLOB:C525($desktop+"miyako.pub";$keyPub)
DOCUMENT TO BLOB:C525($desktop+"miyako";$keyPriv)
$localName:=$desktop+"1.pdf"
$hostName:="1.pdf"

$error:=SFTP ("192.168.1.154";$hostName;$localName;"miyako";"";$keyPriv;$keyPub)