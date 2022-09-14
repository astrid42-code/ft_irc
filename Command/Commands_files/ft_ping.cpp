#include "../Cmd.hpp"
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

void ping(Cmd &command){
    if (!command.get_value().size())
		command._server->get_msg(ERR_NOORIGIN, NULL, command);
	else if (command.get_value().size() > 2)
        return ;
	else if (command.get_value().size() == 1){
		if (command.get_value()[0] != SERVER){
			command._server->get_msg(ERR_NOSUCHSERVER(command.get_value()[0]), NULL, command);
		}
		else{
			// fct send PONG msg to server
			pong(command);
			std::cout << "blob" << '\n';
		}
	}
    else if (command.get_value().size() == 2){
        // std::cout << "bla" << '\n';
		std::map< std::string, User * >::iterator it;
		
		if (command.get_value()[1] != SERVER){
			command._server->get_msg(ERR_NOSUCHSERVER(command.get_value()[1]), NULL, command);
        // fct qui send ping msg to server (arg2) par le user (arg1)
		// donc identifier arg1 (trouver le user dans la map du server?)
		//  et verifier que arg2 == SERVER
		// puis send ping msg to server
    	}
	}
}

// Command: PONG
//    Parameters: <server> [ <server2> ]

//    PONG message is a reply to ping message.  If parameter <server2> is
//    given, this message MUST be forwarded to given target.  The <server>
//    parameter is the name of the entity who has responded to PING message
//    and generated this message.

//    Numeric Replies:

//            ERR_NOORIGIN                  ERR_NOSUCHSERVER

//    Example:

//    PONG csd.bu.edu tolsun.oulu.fi  ; PONG message from csd.bu.edu to
//                                    tolsun.oulu.fi

void pong(Cmd & command){
	if (!command.get_value().size())
		command._server->get_msg(ERR_NOORIGIN, NULL, command);
	else if (command.get_value().size() > 2)
        return ;
		else if (command.get_value().size() == 1){
		if (command.get_value()[0] != SERVER){
			command._server->get_msg(ERR_NOSUCHSERVER(command.get_value()[0]), NULL, command);
		}
		else{
			
			std::cout << "fish" << '\n';
		}
	}else if (command.get_value().size() == 2){
        // std::cout << "bla" << '\n';
		std::map< std::string, User * >::iterator it;
		
		if (command.get_value()[1] != SERVER){
			command._server->get_msg(ERR_NOSUCHSERVER(command.get_value()[1]), NULL, command);
        // fct qui send pong msg to server (arg2) par le user (arg1)
		// donc identifier arg1 (trouver le user dans la map du server?)
		//  et verifier que arg2 == SERVER
		// puis send pong msg to server
    	}
	}
}