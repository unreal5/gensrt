/*=============================================================================
    Copyright (c) 2001-2010 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/

#include <iostream>
#include <filesystem>
#include <string>
#include <vector>
using namespace std;
vector<string> AllMp4Files;

void GetMP4FilesInDirectory(filesystem::path path)
{
    for (auto& p : filesystem::directory_iterator(path))
    {
        if (p.is_directory())
        {
            GetMP4FilesInDirectory(p.path());
        }
        else
        {
            if (p.path().extension() == ".mp4")
            {
                AllMp4Files.push_back(p.path().string());
            }
        }
    }
}

const char* szCmd =
    "\"D:\\Tools\\Whisper-Faster\\whisper-faster --model_dir \"D:\\Tools\\Whisper-Faster\\_models\" -d cuda -o source -f srt --task transcribe --language English --beep_off --model large-v";

int main(int argc, char** argv)
{
    int ModelDefault = 2;
    if (argc > 1)
    {
        ModelDefault = atoi(argv[1]);
    }
    if (ModelDefault != 2 && ModelDefault != 3)
    {
        ModelDefault = 2;
    }
    cout << "use large-v" << ModelDefault << " model" << endl;
    string strCmd = szCmd;
    strCmd += to_string(ModelDefault);
    strCmd += ' ';

    //string strPath = "E:\\Advanced Locomotion Series in UE5 and C++";
    string strPath =".\\";
    GetMP4FilesInDirectory(strPath);
    for (auto& strFile : AllMp4Files)
    {
        string strConsole = strCmd;
        strConsole += "\"";
        strConsole += strFile;
        strConsole += "\"";
        //cout << strConsole << endl;
        cout << "start===== " << strFile << " =====" << endl;
        system(strConsole.c_str());
        cout << "end=====  " << strFile << " =====" << endl;
    }
    //    cout << strCmd << endl;
    cout << "all done!!!!!!" << endl;
}
