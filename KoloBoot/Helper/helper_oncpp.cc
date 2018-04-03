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
