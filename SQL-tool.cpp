#include <windows.h>
#include <wininet.h>
#include <iostream>
#include <string>
#include <vector>
#include <openssl/bio.h>
#include <openssl/evp.h>

#pragma comment(lib, "wininet.lib")

class SQL {
public:
    LPCWSTR host = L"http://api.sql.net/sql.php";
    LPCWSTR api = L"?request=";

    std::string SendRequest(const std::string& input) {
        std::string base64Request = Base64Encode(input);
        HINTERNET hInternet, hConnect;
        DWORD bytesRead;
        char buffer[4096];

        hInternet = InternetOpen(L"UserAgent", INTERNET_OPEN_TYPE_DIRECT, NULL, NULL, 0);
        if (hInternet == NULL) {
            std::cerr << "InternetOpen failed: " << GetLastError() << std::endl;
            return "";
        }

        std::wstring fullUrl = std::wstring(host) + api + std::wstring(base64Request.begin(), base64Request.end());
        hConnect = InternetOpenUrl(hInternet, fullUrl.c_str(), NULL, 0, INTERNET_FLAG_RELOAD, 0);
        if (hConnect == NULL) {
            std::cerr << "InternetOpenUrl failed: " << GetLastError() << std::endl;
            InternetCloseHandle(hInternet);
            return "";
        }

        std::string response;
        while (InternetReadFile(hConnect, buffer, sizeof(buffer) - 1, &bytesRead) && bytesRead != 0) {
            buffer[bytesRead] = '\0';
            response.append(buffer, bytesRead);
        }

        InternetCloseHandle(hConnect);
        InternetCloseHandle(hInternet);

        return response;
    }

    std::string Base64Encode(const std::string& input) {
        BIO* bio;
        BIO* b64;
        char* bufferPtr;
        long length;

        b64 = BIO_new(BIO_f_base64());
        bio = BIO_new(BIO_s_mem());
        bio = BIO_push(b64, bio);

        BIO_write(bio, input.c_str(), input.length());
        BIO_flush(bio);

        length = BIO_get_mem_data(bio, &bufferPtr);

        std::string encoded(bufferPtr, length);

        BIO_free_all(bio);

        return encoded;
    }

    std::string Base64Decode(const std::string& input) {
        BIO* bio, * b64;
        char* buffer = new char[input.size()];

        b64 = BIO_new(BIO_f_base64());
        bio = BIO_new_mem_buf(input.c_str(), -1);
        bio = BIO_push(b64, bio);

        BIO_read(bio, buffer, input.size());
        BIO_free_all(bio);

        std::string decoded(buffer);
        delete[] buffer;

        return decoded;
    }

};

int main() {
    SetConsoleTitleA("SQL Tool");
    SQL sql;
    std::string request = "SELECT `password` FROM `users` WHERE `username` = 'admin'";
    std::string response = sql.SendRequest(request);
    std::cout << "Request: " << request << std::endl;
    std::cout << "Response: " << response << std::endl;
    std::cin.get();
    return 0;
}
