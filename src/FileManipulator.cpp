/*
 * FileManipulator.cpp
 *
 *  Created on: Jan 5, 2017
 *      Author: daniel
 */

#include "FileManipulator.h"

#include <asm-generic/errno.h>
#include <asm-generic/errno-base.h>
#include <dirent.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <cerrno>
#include <cstring>

#include "Exception.h"
#include "Stringify.h"

using std::to_string;

namespace elladan {

void checkForFileError(const std::string& filename, int errCode) {
    switch (errCode) {
        case 0: // No error.
        case ENOENT: // File don't exist. This is normal.
            break;
        case EFBIG:
            throw Exception("Could not " + filename + " : File too big.");
        case ENAMETOOLONG:
            throw Exception("Could not " + filename + " : Filename too long.");
        case EROFS:
        case EACCES:
            throw Exception("Could not " + filename + " : missing permission.");
        case EMFILE:
            throw Exception("Could not " + filename + " : too many file opened.");
        default:
            throw Exception("Could not " + filename + " : Unknown reason " + to_string(errCode));
    }
}

void createFolder(const std::string& folderPath) {
    auto tok = tokenize(folderPath, "/");

    // Clean the path, removing any down then up.
    std::string currentFolder;
    for (auto& ite : tok) {
        // Skip  "//" and "..".
        if (ite == "" || ite.empty() || ite == "..") {
            currentFolder += "/";
            continue;
        }

        currentFolder += (currentFolder.empty() ? "" : "/") + ite;

        if (!mkdir(currentFolder.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH))
        {
            switch (errno) {
                case EEXIST:
                case 0:
                    break; // Sucess, or already exist.
                case EACCES:
                case EROFS:
                    throw Exception(
                            "Could not create folder " + currentFolder + ": we don't have permission.");
                case ELOOP:
                case EMLINK:
                    throw Exception(
                            "Could not create folder " + currentFolder + ": Too many link (self looping?).");
                case ENAMETOOLONG:
                    throw Exception(
                            "Could not create folder " + currentFolder + ": Name or path too long.");
                case ENOENT:
                    throw Exception("Could not create folder " + currentFolder + ": Parent don't exist.");
                case ENOTDIR:
                    throw Exception(
                            "Could not create folder " + currentFolder + ": Parent is not a directory.");
                case ENOSPC:
                    throw Exception("Could not create folder " + currentFolder + ": Filesystem is full.");
                default:
                    throw Exception("Could not create folder " + currentFolder + ": Unkown error " + std::to_string(errno) + " -> " + strerror(errno) + ".");
            };
        }
    }
}

std::vector<std::string> listFile(std::string path, const std::string& extension) {
    std::vector<std::string> matchingFile;
    path = removeDoubleSlash(path + "/");

    // List all json file in directory.
    ::DIR *dp;
    struct dirent *dirp;
    struct stat sb;

    dp = opendir(path.c_str());
    if (dp == nullptr) {
        return matchingFile;
    }

    while ((dirp = readdir(dp)) != nullptr) {
        std::string name(dirp->d_name);
        if ((dirp->d_type == DT_DIR) ||
            (name.size() < extension.size())   ||
            (name.rfind(extension) != (name.size() - extension.size())))
            continue;
        matchingFile.push_back(dirp->d_name);
    }

    closedir(dp);

    return matchingFile;
}

std::vector<std::string> listFolder(const std::string& path) {
    std::vector<std::string> folders;

    // List all json file in directory.
    ::DIR *dp;
    struct dirent *dirp;
    struct stat sb;

    int dfd = open(path.c_str(), O_RDONLY);
    if (dfd == -1) throw Exception("Folder " + path + " don't exist");

    dp = opendir(path.c_str());
    if (dp == nullptr) return folders;

    while ((dirp = readdir(dp)) != nullptr) {
        if (dirp->d_type != DT_DIR && dirp->d_type != DT_LNK)
            continue;
        folders.push_back(dirp->d_name);
    }

    closedir(dp);

    return folders;
}

std::string removeDoubleSlash(std::string txt) {
    if (!txt.empty()) {
        int pos = 0;
        while ((pos = txt.find("//", pos)) != std::string::npos)
            txt.replace(pos, 2, "/");
    }
    return txt;
}

}// namespace elladan
