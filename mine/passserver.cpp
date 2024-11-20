#include "passserver.h"
#include <fstream>
#include <iostream>

namespace cop4530 
{
    PassServer::PassServer(size_t size) : table(size) {}

    PassServer::~PassServer() 
    {
        table.clear();
    }

    bool PassServer::load(const char* filename) 
    {
        return table.load(filename);
    }

    bool PassServer::addUser(std::pair<std::string, std::string>& kv) 
    {
        kv.second = encrypt(kv.second); // Encrypt the password before insertion
        return table.insert(kv);
    }

    bool PassServer::addUser(std::pair<std::string, std::string>&& kv) 
    {
        kv.second = encrypt(kv.second); // Encrypt the password before insertion
        return table.insert(std::move(kv));
    }

    bool PassServer::removeUser(const std::string& k) 
    {
        return table.remove(k);
    }

    bool PassServer::changePassword(const std::pair<std::string, std::string>& p, const std::string& newpassword) 
    {
        auto encryptedOldPassword = encrypt(p.second);
        auto encryptedNewPassword = encrypt(newpassword);

        if (encryptedOldPassword == encryptedNewPassword)
            return false;

        auto user = table.contains(p.first);
        if (!user)
            return false;

        std::pair<std::string, std::string> stored = std::make_pair(p.first, encryptedOldPassword);
        if (!table.match(stored))
            return false;

        std::pair<std::string, std::string> updated = std::make_pair(p.first, encryptedNewPassword);
        return table.insert(std::move(updated));
    }

    bool PassServer::find(const std::string& user) const 
    {
        return table.contains(user);
    }

    void PassServer::dump() const 
    {
        table.dump();
    }

    size_t PassServer::size() const 
    {
        return table.size();
    }

    bool PassServer::write_to_file(const char* filename) const 
    {
        return table.write_to_file(filename);
    }

    std::string PassServer::encrypt(const std::string& str) 
    {
        const char* salt = "$1$########";
        
		// this line fails currently, rendering the whole project useless.
		// trying to do *anything* with `encrypted` (printing, reading, etc etc)
		// causes the program to jump to the throw "Invalid encryption format"
		// error.
		// 			THEORY:
		// the crypt() function is failing at something and causing encrypted
		// to be set to a nullptr which is not handled via iostream, and in the
		// creation of encryptedStr from encrypted which is also not handled by
		// the STL for std::string. 
		char* encrypted = crypt(str.c_str(), salt);


        if (encrypted == nullptr)
            throw std::runtime_error("Encryption failed");

        // Extract the last 22 characters after the 3rd '$'
        std::string encryptedStr(encrypted);
        size_t pos = encryptedStr.rfind('$');
        if (pos != std::string::npos && pos + 1 + 22 <= encryptedStr.length()) 
            return encryptedStr.substr(pos + 1, 22);

        throw std::runtime_error("Invalid encryption format");
    }

}
