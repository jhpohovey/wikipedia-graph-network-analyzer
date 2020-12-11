/**
 * @file file_bot.hpp
 * @author John Pohovey
 * @brief Contains functions responsible for parsing through .TXT files and storing them in 
 *        a data structure for use by the NetworkBuilder class when construction the graph
 *        with all vertices and edges
 * @version 0.1
 * @date December 2020
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#include <string>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

/**
 * Takes a filename and reads in all the text from the file
 * Newline characters are also just characters in ASCII
 * 
 * @param filename The name of the file that will fill the string
 */
std::string file_to_string(const std::string& filename);

std::vector<std::string> file_to_vector(const std::string & filename);

std::string readLine(const std::string & filename);

/**
 * @brief Parses the text file and stores the read data into a 2D vector of strings, aka vertices
 * 
 * @param filename 
 * @return std::vector<std::vector<std::string>> 
 * http://www.cplusplus.com/reference/cstring/strtok/?kw=strtok
 * https://www.tutorialspoint.com/how-to-convert-string-to-char-array-in-cplusplus
 * 
 */
std::vector<std::vector<std::string>> file_to_struct(const std::string & filename);
