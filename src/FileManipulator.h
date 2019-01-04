/*
 * FileManipulator.h
 *
 *  Created on: Jan 5, 2017
 *      Author: daniel
 */
#pragma once

#include <string>
#include <vector>

namespace elladan{

// Create all parent directory.
void createFolder(const std::string& folderPath);

// Transform "//" into "/".
std::string removeDoubleSlash(std::string txt);

// Throws a human readable exepction if the last file cmd failed.
void checkForFileError(const std::string& filename, int errCode);

// List all files of matching extension in the folder. Does not search recursively.
// The returned filenames does not include the search path.
std::vector<std::string> listFile(std::string path, const std::string& extension);

// List all folder at location.. Does not search recursively.
// The returned folder names does not include the search path.
std::vector<std::string> listFolder(const std::string& path);


} // namespace elladan
