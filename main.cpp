#include <string>
#include <iostream>
#include <filesystem>
#include <vector>

// Compile with
// g++ -std=c++17 {filename}.cpp
// Don't use (for now) -c 

void DirCheck()
{
    /***
    Checks if the data folder and its subfolders exists, if they don't, it will create it
    ***/
    // Check if folders are there
    bool assetsCheck = false, spritesCheck = false;
    std::string subDir;
    std::string path = "./data/";

    if(!std::filesystem::exists("./data"))
    {
        std::filesystem::create_directory("data");
    }
    
    for (const auto& entry : std::filesystem::directory_iterator(path))
    {
        subDir = entry.path();
        if(subDir == "./data/assets")
        {
            assetsCheck = true;
        }
        if(subDir == "./data/sprites")
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
        std::filesystem::create_directory("data/assets");
    }
    if(spritesCheck == false)
    {
        std::filesystem::create_directory("data/sprites");
    }
}

int * FileCheck()
{
    std::string path = "./data/assets";
    std::vector<std::string> dirArray;
    std::string getDirs, getFile, assetPath, found;
    bool materialCheck = false, chromaCheck = false, propCheck = false;
    int i = 0;
    
    for (const auto& folder : std::filesystem::directory_iterator(path))
    {
        getDirs = folder.path();
        if(std::filesystem::is_directory(getDirs))
        {
            dirArray.push_back(getDirs);
            for (const auto& subFolder : std::filesystem::directory_iterator(getDirs))
            {
                getFile = subFolder.path();
                size_t pos1 = getFile.find("material.png");
                if(pos1 != std::string::npos)
                {
                    materialCheck = true;
                }
                size_t pos2 = getFile.find("chroma.png");
                if(pos2 != std::string::npos)
                {
                    chromaCheck = true;
                }
                size_t pos3 = getFile.find("properties.info");
                if(pos3 != std::string::npos)
                {
                    propCheck = true;
                }
            }
            if(materialCheck && chromaCheck && propCheck)
            {
                std::cout << "Asset: " << getDirs << " ok." << std::endl;
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
        std::cout << "No assets found!\nAdd some to start, refer to the manual on how to." << std::endl;
    }
    return 0;
}

int main(int argc, char** argv)
{
    std::cout << "Init done.\n";
    DirCheck();     // Checks if the data folder and its subfolders exists, if they don't, it will create it
    FileCheck();    

    return 0;
}
