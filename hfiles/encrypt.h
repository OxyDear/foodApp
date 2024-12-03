#ifndef ENCRYPTION_H
#define ENCRYPTION_H

#include <openssl/sha.h>
#include <sstream>
#include <string>
#include <iomanip>

std::string bytesToHexString(const unsigned char* bytes, size_t length);

// Функция для хэширования пароля с использованием SHA-256
std::string hashPassword(const std::string& password);

#endif // ENCRYPTION_H
