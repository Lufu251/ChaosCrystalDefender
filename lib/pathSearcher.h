#pragma once
#ifdef _WIN64
#include <Shlwapi.h>
#pragma comment(lib, "shlwapi.lib")
#else
#include <unistd.h>
#endif
#include <filesystem>
#include <string>

class PathSearcher
{
public:
    PathSearcher(){}
    ~PathSearcher(){}
private:
    // returns the directory of the executable
    std::string getExecutableDirPath() {
        #ifdef _WIN64
        TCHAR dest[MAX_PATH];
        GetModuleFileName(NULL, dest, MAX_PATH); // returns executable path
        PathRemoveFileSpec(dest); // removes executable name from path
        return dest;
        #else
        char buf[4096] = {0};
        ssize_t len = readlink("/proc/self/exe", buf, 4096);
        return std::string(buf, buf + len);
        #endif
    }

public:
    // returns the folder path if it was found
    // dir = folder name you want to search
    // searchDepth = the amount of layer to search going down from executable path
    std::filesystem::path getDirPath(std::string dir, int searchDepth) {
        std::filesystem::path curSP = getExecutableDirPath(); // get executable directory
    
        for(int i=0; i< searchDepth; i++) {


            if(!std::filesystem::exists(curSP / dir)){
                // path doesn't exist
                curSP = curSP.parent_path(); // go down one layer
            }
            else{
                // path exists return the current path
                return curSP / dir;
            }
        }
        return curSP;
    }
};