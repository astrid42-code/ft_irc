/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asgaulti <asgaulti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 16:21:31 by asgaulti          #+#    #+#             */
/*   Updated: 2022/06/06 17:03:15 by asgaulti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>

int main(int ac, char **av){
    while (ac != 3){ // ou if et return (0) 
        std::cout << "There is an error in arguments" << std::endl;
        // return (0);
    }
    // 1 verifier le port > si c'est le bon continuer, sinon modifier
    // comment verifier le port (qui le choisit?)
    // 2 verifier le pwd > idem que pour le port
    // ATTENTION : msgs d'erreurs a reproduire comme dans le veritable irc en fct du type d'erreur
    // 3 tout est ok lancer le programme
    
    return (0);
}

