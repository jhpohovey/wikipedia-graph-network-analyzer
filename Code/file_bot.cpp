
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
std::string file_to_string(const std::string& filename){
  std::ifstream file(filename);

  std::stringstream strStream;
  if (file.is_open()) {
    strStream << file.rdbuf();
  }
  return strStream.str();
}

std::vector<std::string> file_to_vector(const std::string & filename) {
	std::ifstream text(filename);
	std::vector<std::string> out;

	if (text.is_open()) {
		std::istream_iterator<std::string> iter(text);
		while (!text.eof()) {
			out.push_back(*iter);
			++iter;
		}
	}

	return out;
} 

std::string readLine(const std::string & filename) {
    std::string line;
    std::ifstream file(filename);
    std::getline(file, line);
    return line;
}

/**
 * @brief 
 * 
 * @param filename 
 * @return std::vector<std::vector<std::string>> 
 * http://www.cplusplus.com/reference/cstring/strtok/?kw=strtok
 * https://www.tutorialspoint.com/how-to-convert-string-to-char-array-in-cplusplus
 * 
 */
std::vector<std::vector<std::string>> file_to_struct(const std::string & filename) {
  std::vector<std::vector<std::string>> out;
  std::ifstream file(filename);

  if (!file) {
    std::cout << "Error: File " << filename << " failed to be opened for reading" << std::endl;
    abort();
  }

  std::string str;
  //char delimeters [] = {';','\n'}; //ununsed array at the moment
  while(std::getline(file, str)) {
    std::vector<std::string> line;

    //change string into a char* for strtok
    char links[1000];
    strcpy(links, str.c_str());

    char* token = strtok(links, ";\n"); //strtok supports multiple delimeters, while getline only supports one
    while (token != nullptr) {
      line.push_back(token);
      token = strtok (NULL, ";\n");
    }

    std::cout << "{";
    for (size_t i = 0; i < line.size(); ++i) { // this print helps with formatting for test case solutions
        std::cout << "\"" << line[i] << "\""; //also helps with checking that it works
        if (i != line.size() - 1) {
          std::cout << ", ";
        }
    }
    std::cout << "}" << std::endl;
    out.push_back(line);
  } 
  return out;
}
