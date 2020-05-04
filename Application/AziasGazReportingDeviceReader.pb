
; This is a proof of concept !

If InitNetwork() = 0
	Debug "Can't init networking library"
	End
EndIf

IP = MakeIPAddress(192, 168, 1, 82)
Port = 6832
*Buffer = AllocateMemory(65537)
Query.q = $BEEF0001
LastQueryMillis = ElapsedMilliseconds()

ConnectionID = OpenNetworkConnection(IPString(IP) , Port)

If ConnectionID
	Debug "Connected !"
	
	Repeat
		Event = NetworkClientEvent(ConnectionID) 
		
		Select Event
			Case #PB_NetworkEvent_Data
				Debug "Received data !"
				
				If ReceiveNetworkData(ConnectionID, *Buffer, MemorySize(*Buffer)) <> -1
					Debug ">" + PeekS(*Buffer, 256, #PB_Ascii)
				Else
					Debug "Data corrupted !"
				EndIf
				
			Case #PB_NetworkEvent_Disconnect
				Debug "Disconnected !"
				CloseNetworkConnection(ConnectionID)
				End 0
		EndSelect
		
		If LastQueryMillis + 10000 < ElapsedMilliseconds()
			SendNetworkData(ConnectionID, @Query, 4)
		EndIf
	ForEver
Else
	Debug "Couldn't connect !"
EndIf
