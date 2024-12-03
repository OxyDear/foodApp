#include "../hfiles/encrypt.h"

std::string bytesToHexString(const unsigned char* bytes, size_t length) {
    std::ostringstream oss;
    for (size_t i = 0; i < length; ++i) {
        oss << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(bytes[i]);
    }
    return oss.str();
}

// Функция для хэширования пароля с использованием SHA-256
std::string hashPassword(const std::string& password) {
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;

    // SHA256_Init(&sha256); // Инициализация
    // SHA256_Update(&sha256, password.c_str(), password.size()); // Обновление хэш-данных
    // SHA256_Final(hash, &sha256); // Финализация

    return bytesToHexString(hash, SHA256_DIGEST_LENGTH);
}
