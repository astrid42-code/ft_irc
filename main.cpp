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
    // 1 creer un objet de la class irc::Server server > définir ce que l'objet server contient
    // > un objet config dans lequel on récupère port et pwd (en vérifiant qu'ils suivent les règles de taille d'irc?)
    // + récupérer le user (prévoir qu'il peut y en avoir plsrs, les mettre dans un tableau / vector)
    // + pvr delete les users
    // + de même avec les channels
    // 2 signal?
    // 3 set le port et le pwd du server avec av1 et 2 (des possibilités d'erreurs ici???)
    // 4 initialiser (lancer?) le server
    // 5 lancer le programme dans une boucle (while (!end) end = c'est pas fini ici)
    
    return (0);
}

