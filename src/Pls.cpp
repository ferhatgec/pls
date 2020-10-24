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
    
    std::cout << "huh " << data << "\n";
    
    data = stringtools::GetBetweenString(data, "pls {", "} pls <");
    
    search.Hmm_Search_Ok(data);
}    

int main(int argc, char** argv) {
    Pls pls;
    std::cout << "pls.\n";
    
    pls.Hmm();
    
    return 0;
}
