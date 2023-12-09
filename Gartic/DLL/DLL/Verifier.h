#include <iostream>
#include <string_view>
#include <regex>

__declspec(dllexport) bool VerifyLogin(const char* username, const char* password);
__declspec(dllexport) bool VerifyRegister(const char* username, const char* password);


