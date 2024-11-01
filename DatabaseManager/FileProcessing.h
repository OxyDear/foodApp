//
// Created by Ivan Potyomin on 18.10.24.
//

#ifndef DONERAPP_FILEPROCESSING_H
#define DONERAPP_FILEPROCESSING_H


#include <iostream>
#include <string>
#include <fcntl.h>
#include <unistd.h>

class FileException {
protected:
    std::string filename;
public:
    FileException(const std::string& fname);

    virtual std::string Message() const = 0;
};

class CreateException : public FileException {
public:
    CreateException(const std::string& fname);
    std::string Message() const override;
};

class OpenException : public FileException {
public:
    OpenException(const std::string& fname);
    std::string Message() const override;
};

class ReadException : public FileException {
public:
    ReadException(const std::string& fname);
    std::string Message() const override;
};

class WriteException : public FileException {
public:
    WriteException(const std::string& fname);
    std::string Message() const override;
};

class File {
public:
    int CreateFile(const std::string& fname);
    int OpenFile(const std::string& fname);
    void ReadFile(int fd, void* buf, size_t count);
    void WriteFile(int fd, const void* buf, size_t count);
};

#endif //DONERAPP_FILEPROCESSING_H
