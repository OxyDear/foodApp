//
// Created by Ivan Potyomin on 18.10.24.
//

#include "FileProcessing.h"

FileException::FileException(const std::string& fname) : filename(fname) {}

CreateException::CreateException(const std::string& fname) : FileException(fname) {}
std::string CreateException::Message() const {
    return "Error creating file: " + this->filename;
}

OpenException::OpenException(const std::string& fname) : FileException(fname) {}
std::string OpenException::Message() const {
    return "Error opening file: " + this->filename;
}

ReadException::ReadException(const std::string& fname) : FileException(fname) {}
std::string ReadException::Message() const {
    return "Error reading file: " + this->filename;
}

WriteException::WriteException(const std::string& fname) : FileException(fname) {}
std::string WriteException::Message() const {
    return "Error writing to file: " + this->filename;
}

int File::CreateFile(const std::string& fname) {
    int fd = open(fname.c_str(), O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd < 0) {
        throw CreateException(fname);
    }
    return fd;
}

int File::OpenFile(const std::string& fname) {
    int fd = open(fname.c_str(), O_RDONLY);
    if (fd < 0) {
        throw OpenException(fname);
    }
    return fd;
}

void File::ReadFile(int fd, void* buf, size_t count) {
    ssize_t bytesRead = read(fd, buf, count);
    if (bytesRead < 0) {
        throw ReadException("Unknown file");
    }
}

void File::WriteFile(int fd, const void* buf, size_t count) {
    ssize_t bytesWritten = write(fd, buf, count);
    if (bytesWritten < 0) {
        throw WriteException("Unknown file");
    }
}

// Пример использования
//int main() {
//    File fileManager;
//    try {
//        int fd = fileManager.CreateFile("/Users/oxydear/Documents/Ivan's Mac/IDEs/CLion/semester3/lab7_2/protect/test.txt");
//        std::string data;
//        std::getline(std::cin, data);
//        const int dbl = data.size();
//        std::cout << data.size() << std::endl;
//        fileManager.WriteFile(fd, data.c_str(), dbl);
//        close(fd);
//
//        fd = fileManager.OpenFile("/Users/oxydear/Documents/Ivan's Mac/IDEs/CLion/semester3/lab7_2//protect/test.txt");
//        char* buffer = new char[dbl];
//        fileManager.ReadFile(fd, buffer, dbl);
//        buffer[dbl-1] = '\0';
//        std::cout << "Read from file: " << buffer << std::endl;
//        delete[] buffer;
//        close(fd);
//    } catch (const FileException& e) {
//        std::cerr << e.Message() << std::endl;
//    }
//    return 0;
//}
