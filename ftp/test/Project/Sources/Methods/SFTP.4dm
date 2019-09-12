//%attributes = {}
  //(P) cURL_EASY_SFTP_Send
  //----------------------------------------------------
  //Simpler SFTP-Upload (Port 22)
  //----------------------------------------------------
  //Compiler: Compiler_cURL
  //----------------------------------------------------

C_LONGINT:C283($0)  //<-- Fehler
C_TEXT:C284($1)  //--> ftp-Server
C_TEXT:C284($2)  //--> Name der Datei auf dem ftp-Server
C_TEXT:C284($3)  //--> Kompletter Pathname der zu übertragenden Datei
C_TEXT:C284($4)  //--> Username
C_TEXT:C284($5)  //--> Kennwort
C_BLOB:C604($6)  //--> {optional: Private Key für Public Key Authentication}
C_BLOB:C604($7)  //--> {optional: Public Key für Public Key Authentication}

C_TEXT:C284($errMethod;$path)
C_LONGINT:C283($createMissingDir)
C_OBJECT:C1216($options)

If (Count parameters:C259>=5)
	If (Test path name:C476($3)=Is a document:K24:1)
		If (Get document size:C479($3)<MAXLONG:K35:2)  //Mehr als 2 GB geht (theoretisch) leider nicht :-(
			$options:=New object:C1471
			$options.USERNAME:=$4
			$options.PASSWORD:=$5
			
			  //===== weitere Optionen =====
			If (Count parameters:C259>=7)
				$path:=Temporary folder:C486+Generate UUID:C1066
				BLOB TO DOCUMENT:C526($path;$6)
				$options.SSH_PRIVATE_KEYFILE:=$path
				
				$path:=Temporary folder:C486+Generate UUID:C1066+".pub"
				BLOB TO DOCUMENT:C526($path;$7)
				$options.SSH_PUBLIC_KEYFILE:=$path
				$options.SSH_AUTH_TYPES:=0  //CURLSSH_AUTH_ANY
				
				$CURLSSH_AUTH_PUBLICKEY:=(1 << 0)
				$CURLSSH_AUTH_PASSWORD:=(1 << 1)
				
				$options.SSH_AUTH_TYPES:=$CURLSSH_AUTH_PUBLICKEY  //| $CURLSSH_AUTH_PASSWORD
				
				$options.SSL_VERIFYPEER:=0
				$options.SSL_VERIFYHOST:=0
			End if 
			
			$createMissingDir:=1
			
			  //Die komplette URL zusammensetzen
			$options.URL:="sftp://"+$1+"/"+$2
			$0:=cURL_FTP_Send (JSON Stringify:C1217($options);$3;$createMissingDir;"")
		Else 
			$0:=-253  //Datei ist zu groß (Maximale Blob-Größe von 4D überschritten)
		End if 
	Else 
		$0:=-254  //Zu übertragende Datei nicht gefunden 
	End if 
Else 
	$0:=-255  //zu wenig Parameter
End if 
