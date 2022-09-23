#include "Server/Server.hpp"

bool	mask_off(std::string mask, std::string str)
{
	std::vector<std::string>	mask_div;
	std::size_t					i = 0;
	std::size_t					j;
	std::size_t					n = 0;

	while (i < mask.length())
	{
		j = i;
		if ((i = mask.find("*")) != std::string::npos)
		{
			mask_div[n++] = mask.substr(j, i - j);
			std::cout << "|" << mask_div[n - 1] << "|" << std::endl;
		}
		else
			i = mask.length();
	}
	if (mask_div.empty())
		mask_div[0] = mask;
	i = 0;
	n = 0;
	while (n < mask_div.size())
	{
		j = i;
		if ((i = str.find(mask_div[n], j)) == std::string::npos)
		{
			std::cout << "false :" << mask_div[n] << std::endl;
			return (false);
		}
		else
			n++;
	}
	return (true);
}