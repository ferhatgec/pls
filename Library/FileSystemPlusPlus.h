/*# MIT License
# 
# Copyright (c) 2020 Ferhat Geçdoğan All Rights Reserved.
# Distributed under the terms of the MIT License.
#*/

#ifndef FILE_SYSTEM_PLUS_PLUS_H
#define FILE_SYSTEM_PLUS_PLUS_H

#include <cstring>
#include <iostream>
#include <pwd.h>
#include <dirent.h>
#include <fstream>
#include <sys/stat.h>

#ifdef WINDOWS
#include <direct.h>
#define GetCurrentDir _getcwd
#else
#include <unistd.h>
#define GetCurrentDir getcwd
#endif

#define FS_PLUS_PLUS_VERSION "0.2-beta-1"

namespace fsplusplus {
	static std::string EraseAllSubString(std::string & mainString, const std::string & erase) {
   	 size_t pos = std::string::npos;
   	 while((pos = mainString.find(erase)) != std::string::npos) {
   	     	mainString.erase(pos, erase.length());
   	 }
   		return mainString;
    	}

	// Get Between String    
	static void GetBtwString(std::string oStr, std::string sStr1, std::string sStr2, std::string &rStr) {  
    		int start = oStr.find(sStr1);   
    	if (start >= 0) {       
      		std::string tstr = oStr.substr(start + sStr1.length());        
      		int stop = tstr.find(sStr2);      
      		if (stop >1)          
        		rStr = oStr.substr(start + sStr1.length(), stop);
      		else
        		rStr ="error";  
    		}
    		else
       		rStr = "error"; 
	}
	
	static std::string GetCurrentWorkingDir(void) {
  		char buff[FILENAME_MAX];
  		GetCurrentDir( buff, FILENAME_MAX );
  		std::string current_working_dir(buff);
  		return current_working_dir;
	}

	static bool IsExistFile(std::string path) {
    		struct stat buffer;
    		return (stat(path.c_str(), &buffer) == 0);
	}

	static std::string CDFunction(std::string path) {
		return fsplusplus::GetCurrentWorkingDir() + path;
	}
	
    	static std::string ReadFileWithReturn(std::string file) {
		std::string line, data;
    		std::ifstream readfile((fsplusplus::GetCurrentWorkingDir() + "/" + file).c_str());
    		if(readfile.is_open()) {
        	while (std::getline(readfile, line)) {
			      data.append(line + "\n");
        	}
        	readfile.close();
    		} else {
        		printf("Unable to open file\n");
    		}
		return data;
    	}
                       
    	static std::string FindStringWithReturn(std::string file, std::string str) {
		std::string line;
    		std::ifstream readfile((fsplusplus::GetCurrentWorkingDir() + "/" + file).c_str());
    		if(readfile.is_open()) {
        	while (std::getline(readfile, line)) {
			if(strstr(line.c_str(), str.c_str()))
				return line + "\n";
        	}
        		readfile.close();
    		}

    		return "null";
    	}
                       
                       
    	static void FindPath(std::string name) {
    	    DIR *directory;
    	    struct dirent *entryname;
	    struct stat filestat;
    	    directory = opendir(fsplusplus::GetCurrentWorkingDir().c_str());
    	    if(directory == NULL) {
            printf("Error: Directory not found.\n");
            return;
    	    }
    	    while ((entryname = readdir(directory))) {
            stat(entryname->d_name, &filestat);
            if(entryname->d_type == DT_DIR) {
                if(strstr(entryname->d_name, ".")) {
                // Null
                } else if(strstr(entryname->d_name, "..")){
	        // Null
	        } else if(strstr(entryname->d_name, name.c_str())) {  
            	  printf("%4s %s\n", "[Dir]", entryname->d_name);
                }
            } 
            else if(strstr(entryname->d_name, name.c_str())){
                 printf("%4s %s\n", "[File]", entryname->d_name);
            }
            }
   	 closedir(directory);
    	}
	
	
	static std::string ReadOSName() {
    		std::string line;
    		std::ifstream readfile("/etc/os-release");
    		if(readfile.is_open()) {
        	while (std::getline(readfile, line)) {
        		if(line.find("PRETTY_NAME=\"") == 0) {
				GetBtwString(line, "\"", "\"", line);
				return line;
        		}
        	}
        	readfile.close();
    		} else {
        		printf("Unable to open file\n");
    		}
		return "null";
	}
	
	static void CreateFile(std::string name, std::string input) {
		std::string path;
    		path.append(fsplusplus::GetCurrentWorkingDir());
    		path.append("/");
    		path.append(name);
    		std::ofstream file(path, std::ios::app);
    		file << input;
    		file.close();
	}
	
	static void CreateFileWithoutAppend(std::string name) {
		std::string path;
    		path.append(fsplusplus::GetCurrentWorkingDir());
    		path.append("/");
    		path.append(name);
    		std::ofstream file(path);
    		file.close();
	}
}

#endif // FILE_SYSTEM_PLUS_PLUS_H
