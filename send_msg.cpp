#include "Server/Server.hpp"
#include "Command/Cmd.hpp"

#include "User/User.hpp"
#include "RPL_answer.hpp"

std::string    send_msg(int rpl, User *user, Cmd &cmd)
{
	std::string	res = ":";
	std::string num_rpl(std::to_string(rpl));
	std::string arg = "\n\
dHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHb \n\
HHP%%#%%%%%%%%%%%%%%%%#%%%%%%%#%%VHH \n\
HH%%%%%%%%%%#%v~~~~~~\\%%%#%%%%%%%%HH \n\
HH%%%%%#%%%%v'        ~~~~\\%%%%%#%HH \n\
HH%%#%%%%%%v'dHHb      a%%%#%%%%%%HH \n\
HH%%%%%#%%v'dHHHA     :%%%%%%#%%%%HH \n\
HH%%%#%%%v' VHHHHaadHHb:%#%%%%%%%%HH \n\
HH%%%%%#v'   `VHHHHHHHHb:%%%%%#%%%HH \n\
HH%#%%%v'      `VHHHHHHH:%%%#%%#%%HH \n\
HH%%%%%'        dHHHHHHH:%%#%%%%%%HH \n\
HH%%#%%        dHHHHHHHH:%%%%%%#%%HH \n\
HH%%%%%       dHHHHHHHHH:%%#%%%%%%HH \n\
HH#%%%%       VHHHHHHHHH:%%%%%#%%%HH \n\
HH%%%%#   b    HHHHHHHHV:%%%#%%%%#HH \n\
HH%%%%%   Hb   HHHHHHHV'%%%%%%%%%%HH \n\
HH%%#%%   HH  dHHHHHHV'%%%#%%%%%%%HH \n\
HH%#%%%   VHbdHHHHHHV'#%%%%%%%%#%%HH \n\
HHb%%#%    VHHHHHHHV'%%%%%#%%#%%%%HH \n\
HHHHHHHb    VHHHHHHH:%odHHHHHHbo%dHH \n\
HHHHHHHHboodboooooodHHHHHHHHHHHHHHHH \n\
HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH \n\
HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH \n\
VHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHGGN94\r\n";

	res.append(SERVER);
	res.append(" ");
	if (rpl < 10){
		res.append("00" + num_rpl);
	}
	else
		res.append(num_rpl);
	res.append(" ");
	if (user->get_nick() == "")
		res.append("*");
	else
		res.append(user->get_nick());
	switch(rpl){
		case 1:
				res.append(RPL_WELCOME);
				break;
		case 2:
				res.append(RPL_YOURHOST);
				break;
		case 3:
				res.append(RPL_CREATED);
				break;
		case 4:
				res.append(RPL_MYINFO);
				break;
		case 375:
				res.append(RPL_MOTDSTART(arg));
				break;
		case 376:
				res.append(RPL_ENDOFMOTD);
				break;
		default:
				break;
	}

	std::cout << "send msg : |" << res << "|" << std::endl;
	send(cmd._sfd, res.c_str(), res.length(), MSG_CONFIRM);
	return (res);
}