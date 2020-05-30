
If InitNetwork() = 0
	MessageRequester("Error", "Can't initialize the network !", 0)
	End
EndIf


IP = MakeIPAddress(192, 168, 1, 82)
Port = 6832
*Buffer = AllocateMemory(65537)
Query.q = $BEEF0001
LastQueryMillis = ElapsedMilliseconds()
ReceivedDataLength.q = 0
PacketID.l = 0

If CreateNetworkServer(0, Port)
	Debug "Server created (Port "+Str(Port)+")."
	
	Repeat
		
		SEvent = NetworkServerEvent()
		
		If SEvent
			
			ClientID = EventClient()
			
			Select SEvent
					
				Case #PB_NetworkEvent_Connect
					Debug "A new client has connected !"
					
				Case #PB_NetworkEvent_Data
					Debug "Client "+Str(ClientID)+" has send a packet !"
					ReceivedDataLength = ReceiveNetworkData(ClientID, *Buffer, 65537)
					
					If ReceivedDataLength >= 4
						If CompareMemory(*Buffer, @Query, 4)
							Debug "Query received !"
							SendNetworkString(ClientID,
							                  Str(PacketID)+";"+
							                  "hum="+StrF(Random(100, 0) * 0.01, 2)+";"+
							                  "tmp="+StrF(Random(100, 0) * 0.01, 2)+";"+
							                  "co2="+StrF(Random(100, 0) * 0.01, 2)+";"+
							                  "no="+StrF(Random(100, 0) * 0.01, 2))
							PacketID = PacketID + 1
						Else
							Debug "Unsure how to handle received packet !"
							Debug "> "+Str(ReceivedDataLength)
							Debug "> "+Hex(PeekL(*Buffer), #PB_Long)
							Debug Str($BEEF0001)
							Debug Str(PeekL(*Buffer))
						EndIf
					Else
						Debug "Invalid packet !"
					EndIf
					
				Case #PB_NetworkEvent_Disconnect
					Debug "Client "+Str(ClientID)+" has closed the connection..."
			EndSelect
		EndIf
		
	Until Quit
	
	CloseNetworkServer(0)
Else
	Debug "Can't create the server (port in use ?)."
EndIf


