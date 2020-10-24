/*# MIT License
# 
# Copyright (c) 2020 Ferhat Geçdoğan All Rights Reserved.
# Distributed under the terms of the MIT License.
#*/

#include <iostream>
#include "../include/Pls.hpp"
#include "../include/Search_Pls.hpp"

#include "../Library/FileSystemPlusPlus.h"
#include "../Library/StringTools.hpp"


void Oh_No(char* file, char* argument) {
    std::cout << "Oh, no! Use Pls with only " << file << "\n" <<
    "Don't use with " << argument << "\n"; 
}

/* make.pls
    pls {
        add: webkit2gtk3 <
        add: vala <
    } pls <
*/
void
Pls::Hmm() {
    Search_Pls search;
    
    data = fsplusplus::ReadFileWithReturn("make.pls");
    
    data = stringtools::GetBetweenString(data, "pls {", "} pls <");
    
    search.Hmm_Search_Ok(data);
}    

int main(int argc, char** argv) {
    if(argc > 1) {
        Oh_No(argv[0], argv[1]);
        return 0;
    }
    
    Pls pls;
    std::cout << "Pls.\n";
    
    pls.Hmm();
    
    return 0;
}
