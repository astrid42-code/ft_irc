/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asgaulti <asgaulti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 16:21:31 by asgaulti          #+#    #+#             */
/*   Updated: 2022/06/08 14:13:24 by asgaulti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>

int main(int ac, char **av){
    // nbr d'args obligatoires a verifier (il peut aussi y en avoir des optionnels?)
    
    if (ac != 3){
        std::cout << "There is an error in arguments : ./ircserv <port> <password>" << std::endl;
        return (1);
    }
    // 1 verifier le port > si c'est le bon continuer, sinon modifier
    // comment verifier le port (qui le choisit?)
    // 2 verifier le pwd > idem que pour le port
    // ATTENTION : msgs d'erreurs a reproduire comme dans le veritable irc en fct du type d'erreur
    // 3 tout est ok lancer le programme
    
    return (0);
}

