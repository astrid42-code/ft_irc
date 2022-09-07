#include "../Cmd.hpp"
#include "../RPL_answer.hpp"
#include "../../Server/Server.hpp"

// Command: PING
//    Parameters: <server1> [ <server2> ]

//    The PING command is used to test the presence of an active client or
//    server at the other end of the connection.  Servers send a PING
//    message at regular intervals if no other activity detected coming
//    from a connection.  If a connection fails to respond to a PING
//    message within a set amount of time, that connection is closed.  A
//    PING message MAY be sent even if the connection is active.

//    When a PING message is received, the appropriate PONG message MUST be
//    sent as reply to <server1> (server which sent the PING message out)
//    as soon as possible.  If the <server2> parameter is specified, it
//    represents the target of the ping, and the message gets forwarded
//    there.

//    Numeric Replies:

//            ERR_NOORIGIN                  ERR_NOSUCHSERVER

//    Examples:

//    PING tolsun.oulu.fi             ; Command to send a PING message to
//                                    server

//    PING WiZ tolsun.oulu.fi         ; Command from WiZ to send a PING
//                                    message to server "tolsun.oulu.fi"

//    PING :irc.funet.fi              ; Ping message sent by server
//                                    "irc.funet.fi"

void ping(Cmd::Command & command){
    if (!command._value.size())
		command._server.get_msg(ERR_NOORIGIN);
	else if (command._value.size() > 2)
        return ;
	else if (command._value.size() == 1){
		if (command._value[0] != SERVER){
			command._server.get_msg(ERR_NOSUCHSERVER(command._value[0]));
		}
		else{
			// fct send ping msg to server
			std::cout << "blob" << '\n';
		}
	}
    else if (command._value.size() == 2){
        // std::cout << "bla" << '\n';
		std::map< std::string, User * >::iterator it;
		
		if (command._value[1] != SERVER){
			command._server.get_msg(ERR_NOSUCHSERVER(command._value[1]));
        // fct qui send ping msg to server (arg2) par le user (arg1)
		// donc identifier arg1 (trouver le user dans la map du server?)
		//  et verifier que arg2 == SERVER
		// puis send ping msg to server
    	}
	}
}