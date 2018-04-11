//
//  helper_oncpp.cpp
//  Al Munawwir
//
//  Created by Abu Muhammad on 17/03/18.
//  Copyright © 2018 Abu Muhammad. All rights reserved.
//

#include "helper_oncpp.h"
#include <fstream>
#include <sys/time.h>
#include <iostream>
#include <locale>
#include <sstream>

std::vector<std::wstring>
Koloboot::Helper::read_file(const std::string& path) {
    std::vector<std::wstring> kosakata;
    std::wifstream in_stream(path);
    setlocale(LC_ALL, "en_US.UTF-8");
    in_stream.imbue(std::locale(""));
    std::wstring line;
    if (!in_stream.is_open()) {
        perror(("error while opening file " + path).c_str());
    }
    std::mutex mtx;
    mtx.lock();
    while (std::getline(in_stream, line)) {
        std::wstring st;
        std::remove_copy(line.begin(), line.end(), std::back_inserter(st), '\0');
        std::wcout << st << std::endl;
        kosakata.push_back(st);
    }
    mtx.unlock();
    if (in_stream.bad()) {
        perror(("error while reading file " + path).c_str());
    }
    in_stream.close();
    //remove(path.c_str());
    return kosakata;
}

bool Koloboot::Helper::fexists(const std::string &path) {
    std::ifstream ifile(path);
    return (bool)ifile;
}

bool Koloboot::Helper::delete_file(const std::string &path) {
    std::ifstream ifile(path);
    if (fexists(path)) {
        std::remove(path.c_str());
    }
    return fexists(path);
}

int Koloboot::Helper::create_timestampt() {
    struct timeval val;
    gettimeofday(&val, NULL);
    int tm_val = (int)val.tv_sec;
    return tm_val;
}

const char * Koloboot::Helper::MYCFStringCopyUTF8String(CFStringRef aString) {
    if (aString == NULL) {
        return NULL;
    }
    
    CFIndex length = CFStringGetLength(aString);
    CFIndex maxSize =
    CFStringGetMaximumSizeForEncoding(length, kCFStringEncodingUTF8) + 1;
    char *buffer = (char *)malloc(maxSize);
    if (CFStringGetCString(aString, buffer, maxSize,
                           kCFStringEncodingUTF8)) {
        return buffer;
    }
    free(buffer); // If we failed
    return NULL;
}

CFStringRef Koloboot::Helper::UUID() {
    CFUUIDRef uuidRef = CFUUIDCreate(kCFAllocatorDefault);
    CFStringRef uuid = CFUUIDCreateString(kCFAllocatorMalloc, uuidRef);
    return uuid;
}

std::string Koloboot::Helper::getUserDefault(CFStringRef key) {
    CFStringRef dta = (CFStringRef)CFPreferencesCopyAppValue(key, kCFPreferencesCurrentApplication);
    if (dta) {
        const char *conver = MYCFStringCopyUTF8String(dta);
        if (conver) {
            return std::string(conver);
        }
        return "";
    }
    return "";
}

void Koloboot::Helper::setUserDefault(CFStringRef key, CFStringRef val) {
    CFPreferencesSetAppValue(key, val, kCFPreferencesCurrentApplication);
    //CFRelease(val);
}

std::string Koloboot::Helper::fileInfoLocation(const std::string &file) {
    std::string home = std::string(getenv("HOME"));
    std::string subdir = "/Documents";
    std::string location = home + subdir + "/" + file;
    location.erase(0, strlen("/private"));
    return location;
}

const std::vector<std::string> Koloboot::Helper::splitStr(const std::string &str, char delim) {
    std::vector<std::string> temp;
    std::istringstream strem(str);
    std::string s;
    while (std::getline(strem, s, delim)) {
        temp.push_back(s);
    }
    return temp;
}

const std::string Koloboot::Helper::fileBundleLocation(const std::string &file) {
    CFBundleRef mainBundle = CFBundleGetMainBundle();
    std::vector<std::string> splits = splitStr(file, '.');
    CFURLRef locUrl = CFBundleCopyResourceURL(mainBundle, CFStringCreateWithCString(NULL, splits[0].c_str(), kCFStringEncodingUTF8), CFStringCreateWithCString(NULL, splits.at(1).c_str(), kCFStringEncodingUTF8), NULL);
    CFStringRef locPath = CFURLCopyFileSystemPath(locUrl, kCFURLPOSIXPathStyle);
    CFStringEncoding encoding = CFStringGetSystemEncoding();
    const char *path = CFStringGetCStringPtr(locPath, encoding);
    CFRelease(locUrl);
    return std::string(path);
}

CFStringRef Koloboot::Helper::toCFString(const std::string &str) {
    return CFStringCreateWithCString(kCFAllocatorDefault, str.c_str(), kCFStringEncodingUTF8);
}
