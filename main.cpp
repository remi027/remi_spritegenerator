#include <string>
#include <iostream>
#include <filesystem>
#include <vector>

// Compile with
// g++ -std=c++17 {filename}.cpp
// Don't use (for now) -c 

/***************/


// Global variables
const std::string DATAPATH = "./data/";             // global variable, folder: ./data/ 
const std::string ASSETSPATH = "./data/assets";     // global variable, folder: ./data/assets
const std::string SPRITESPATH = "./data/sprites";   // global variable, folder: ./data/sprites

void DirCheck()
{
    /***
    Checks if the data folder and its subfolders exists, if they don't, it will create it
    ***/
    bool assetsCheck = false, spritesCheck = false;
    std::string subDir;

    // Check if data folder is there
    if(!std::filesystem::exists(DATAPATH))
    {
        std::filesystem::create_directory(DATAPATH);
    }
    
    for (const auto& entry : std::filesystem::directory_iterator(DATAPATH))
    {
        subDir = entry.path();
        if(subDir == ASSETSPATH)
        {
            assetsCheck = true;
        }
        if(subDir == SPRITESPATH)
        {
            spritesCheck = true;
        }
    }

    // If they are, just exit the function
    if(assetsCheck && spritesCheck)
    {
        return;
    }
    // If they are not, create the missing folder
    if(assetsCheck == false)
    {
        std::filesystem::create_directory(ASSETSPATH);
    }
    if(spritesCheck == false)
    {
        std::filesystem::create_directory(SPRITESPATH);
    }
    return;
}

std::vector<std::string> FileCheck()
{
    std::vector<std::string> dirArray;                                      // Initializing vector that will hold all 
    dirArray.reserve(0);                                                    // Setting array to zero, it'll be pushed later
    std::string getDirs, getFile, assetPath, found;                         // Some strings for later use
    bool materialCheck = false, chromaCheck = false, propCheck = false;     // Booleans checks
    int i = 0;                                                              // Counter for array size
    auto dataFolderIterator = std::filesystem::directory_iterator(ASSETSPATH);

    for (const auto& folder : dataFolderIterator)
    {
        getDirs = folder.path();
        if(std::filesystem::is_directory(getDirs))
        {
            auto assetsIterator = std::filesystem::directory_iterator(getDirs);
            for (const auto& subFolder : assetsIterator)
            {
                getFile = subFolder.path();
                if(getFile.find("material.png") != std::string::npos)
                {
                    materialCheck = true;
                }
                if(getFile.find("chroma.png") != std::string::npos)
                {
                    chromaCheck = true;
                }
                if(getFile.find("properties.info") != std::string::npos)
                {
                    propCheck = true;
                }
            }
            if(materialCheck && chromaCheck && propCheck)
            {
                std::cout << "Asset: " << getDirs << " ok." << std::endl;
                dirArray.push_back(getDirs);            // If given dir is ok, add it as an array position
                i++;
            }
            if(materialCheck == false)
            {
                std::cout << "Material not found in asset: " << getDirs << std::endl;
            }
            if(chromaCheck == false)
            {
                std::cout << "Chroma not found in asset: " << getDirs << std::endl;
            }
            if(propCheck == false)
            {
                std::cout << "Property file not found in asset: " << getDirs << std::endl;
            }
        }
    }
    if(i == 0)
    {
        std::string error_return = "ERROR";
        dirArray.push_back(error_return);
        std::cout << "No assets found!\nAdd some to start, refer to the manual on how to." << std::endl;
        return dirArray;
    }
    else
    {
        return dirArray;
    }
}

int main(int argc, char** argv)
{
    std::cout << "Init done.\n";
    DirCheck();     // Checks if the data folder and its subfolders exists, if they don't, it will create it
    std::vector<std::string> a = FileCheck();       // PLACEHOLDER

    std::cout << a[0] << a[1] << std::endl;                 // PLACEHOLDER



    return 0;
}
