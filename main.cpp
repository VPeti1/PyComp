#include <chrono>
#include <cstdlib>
#include <iostream>
#include <string>
#include <thread>
#include <fstream>
#include <stdio.h>
#include <unistd.h>
#include <filesystem>
#include <vector>
#define wait1 std::this_thread::sleep_for(std::chrono::seconds(1));
#define clear system("cls");
using namespace std;
namespace fs = std::filesystem;

bool checkInternet() {
    int status = system("ping -c 1 google.com");
    return (status == 0);
}

void check() {
    if (checkInternet()) {
        std::cout << "Internet check passed!" << std::endl;
    }
    else {
        // No internet or admin privileges detected
        clear
        std::cout << "No internet or admin privileges detected! Please connect to the internet or rerun the program." << std::endl;
        system("pause");
        system("exit");
    }
}

void copy() {
        std::vector<std::string> paths;
    std::string path;

    std::cout << "Enter file paths (one per line). Type 'done' when finished:\n";

    while (true) {
        std::cout << "> ";
        std::getline(std::cin, path);

        if (path == "done") {
            break;
        }

        paths.push_back(path);
    }

    // Create the target directory if it doesn't exist
    fs::path targetDir = "C:/PoPy"; 
    fs::create_directories(targetDir);

    // Copy each file to the target directory
    for (const auto& p : paths) {
        fs::path sourcePath(p);
        fs::path targetPath = targetDir / sourcePath.filename();

        try {
            fs::copy_file(sourcePath, targetPath, fs::copy_options::overwrite_existing);
            std::cout << "Copied: " << sourcePath << " to " << targetPath << std::endl;
        } catch (const std::exception& e) {
            std::cerr << "Error copying " << sourcePath << ": " << e.what() << std::endl;
        }
    }

    std::cout << "Files copied to: " << targetDir << std::endl;
}

void cmd() {
    // Ask the user for the Python script filename
    std::cout << "Enter the Python script filename: ";
    std::string scriptFilename;
    std::cin >> scriptFilename;
    // Create a .cmd file in C:\PoPy
    std::ofstream cmdFile("C:\\PoPy\\run.cmd");
    if (cmdFile.is_open()) {
        cmdFile << "python.exe \"" << scriptFilename << "\"" << std::endl;
        cmdFile.close();
        std::cout << "run.cmd file created successfully!" << std::endl;
    } else {
        std::cerr << "Error creating run.cmd file." << std::endl;
    }
}

void sfx() {
    // Replace with the actual path to your 7-Zip executable
    const std::string sevenZipPath = "C:\\PoPy\\7z.exe";
    // Replace with the path to your archive files
    const std::string archiveFilesPath = "C:\\PoPy";
    // Specify the extraction path (temp directory)
    const std::string extractionPath = "%TEMP%\\pycomp";
    // Specify the command to run after extraction (run.cmd)
    const std::string postExtractionCommand = "run.cmd";
    // Create the command for creating the SFX archive
    std::string command = sevenZipPath + " a -sfx7z.sfx -y -o" + extractionPath + " -sfxConfig" + postExtractionCommand + " pycomp.exe " + archiveFilesPath;
    // Execute the command
    int result = std::system(command.c_str());
    if (result == 0) {
        std::cout << "SFX archive created successfully!" << std::endl;
    } else {
        std::cerr << "Error creating SFX archive." << std::endl;
    }

}

int main() {
    clear
    check();
    clear
    std::cout << "PyComp Wizard for Windows" << std::endl;
    std::cout << "By VPeti" << std::endl;
    sleep(2);
    copy();
    system("pause");
    system("powershell Invoke-WebRequest -Uri $ https://raw.githubusercontent.com/VPeti1/CWAcces/main/popy.zip -OutFile C:\\PoPy\\popy.zip");
    system("powershell Expand-Archive -Path C:\\PoPy\\popy.zip -DestinationPath C:\\PoPy");
    cmd();
    system("pause");
    sfx();
    std::cout << "PyComp Wizard Completed!" << std::endl;
    wait1
    system("exit");
}