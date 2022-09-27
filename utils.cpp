#include "Server/Server.hpp"

std::vector<std::string>	div_string(std::string str, char c)
{
	std::vector<std::string>	res;
	size_t						n = 0;
	size_t 						i = 0;

	while (str[i])
	{
		if (str[i] == c)
		{
			res.push_back(str.substr(n, i - n));
			n = ++i;
		}
		i++;
	}
	res.push_back(str.substr(n, str.length()));
	std::cout << "div_string :" << std::endl;
	for (std::vector<std::string>::iterator it = res.begin(); it != res.end(); it++)
	{
		std::cout << "|" << *it << "|" << std::endl;
	}
	return (res);
}

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
	std::cout << "mask_off ok" << std::endl;
	return (true);
}