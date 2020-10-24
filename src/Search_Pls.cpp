/*# MIT License
# 
# Copyright (c) 2020 Ferhat Geçdoğan All Rights Reserved.
# Distributed under the terms of the MIT License.
#*/

#include <iostream>
#include <sstream>

#include <Pls.hpp>
#include <Search_Pls.hpp>

/* PlusPlus libraries. */
#include <FileSystemPlusPlus.h>
#include <StringTools.hpp>
#include <ExecutePlusPlus.hpp>

/* make.pls
    pls:
        add: webkit2gtk3
        add: vala
*/
void
Search_Pls::Hmm_Search_Ok(std::string data) {
    ExecutePlusPlus exec_pls;
    
    std::string get_pls, os_pls, install_pls;
	std::istringstream argline_pls(data);
    
    os_pls = fsplusplus::ReadOSName();
    
    if(strstr(os_pls.c_str(), "Pop!_OS") || strstr(os_pls.c_str(), "Ubuntu") ||
        strstr(os_pls.c_str(), "Linux Mint") || strstr(os_pls.c_str(), "Debian") ||
        strstr(os_pls.c_str(), "elementary"))
        std::cout << "Hmm. Your package manager: " << "apt\n";
    
    
    while (std::getline(argline_pls, get_pls)) {

        if(strstr(get_pls.c_str(), "add:")) {
            get_pls = stringtools::GetBetweenString(get_pls, "add: ", " <");
            
            std::cout << "Hmm: " << get_pls << "\n";
            
            if(strstr(os_pls.c_str(), "Pop!_OS") || strstr(os_pls.c_str(), "Ubuntu") ||
                strstr(os_pls.c_str(), "Linux Mint") || strstr(os_pls.c_str(), "Debian") ||
                strstr(os_pls.c_str(), "elementary")) {
                exec_pls.RunFunction("apt search " + get_pls);
            
                std::cout << "Which? : ";
                
                std::getline(std::cin, install_pls);
                
                if(install_pls != "n" && install_pls != "N")
                    std::cout << exec_pls.ExecWithOutput("sudo apt-get install " + install_pls);
                else
                    std::cout << "Ok.\n";
            }
        }
        /* Only for Ubuntu | Debian based systems */
        else if(strstr(get_pls.c_str(), "quick:")) {
            get_pls = stringtools::GetBetweenString(get_pls, "quick: ", " <");
            
            std::cout << "Hmm: " << get_pls << "\n";
            
            if(strstr(os_pls.c_str(), "Pop!_OS") || strstr(os_pls.c_str(), "Ubuntu") ||
                strstr(os_pls.c_str(), "Linux Mint") || strstr(os_pls.c_str(), "Debian") || 
                strstr(os_pls.c_str(), "elementary")) {
                    std::cout << exec_pls.ExecWithOutput("sudo apt-get install " + install_pls);
            }
        }
    }
}   
