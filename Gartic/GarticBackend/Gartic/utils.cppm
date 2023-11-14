export module utils;
import <unordered_map>;
import <string>;
import <vector>;

export std::vector<std::string> split(const std::string& str, const std::string& delim);


export std::unordered_map<std::string, std::string> parseUrlArgs(const std::string& urlArgs);
