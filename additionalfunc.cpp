/*
 * Copyright © 2016-2017 Lucien Cartier-Tilet
 *
 * This file is part of the UTAU Language Development Tool (ULDT).
 *
 * The ULDT is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * The ULDT is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with the ULDT.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "stdafx.hpp"

using namespace std;

std::string replaceAll(std::string str, const std::string&& from, const std::string&& to) {
    if (str.empty()) {    //if the string from is empty, there is no need to process it
        return "";
    } else if(from.empty()){
        return str;
    }
    size_t start_pos = 0;
    while ((start_pos = str.find(from, start_pos)) != string::npos) {
        str.replace(start_pos, from.length(), to);
        start_pos += to.length();
    }
    return str;
}

QString standardize_name(QString str){
#if (defined (__WIN32__) || defined (_WIN32)) && !defined (__MINGW32__)
    return "\"" + str + "\"";
#else
    if(str.isEmpty()){
        return "";
    }
    return QString::fromStdString(replaceAll(str.toStdString(), " ", "\\ "));
#endif
}

void openfolder(const std::string &&folder) noexcept {
    string command;

    // the system command is chosen depending on the OS the software has been compiled on
#if (defined (__WIN32__) || defined (_WIN32)) && !defined (__MINGW32__)
    command = "explorer.exe ";
#else
    command = "xdg-open ";
#endif
    string cmdcommand = command + folder;
    QMessageBox::information(nullptr, "", QString::fromStdString(cmdcommand));
    std::system(cmdcommand.c_str());
    return;
}

void load_phonemes(ifstream& in_consonants, ifstream& in_vowels) noexcept{
    string line;
    while (getline(in_consonants, line)){
        // if a line begins with a blank character, a number sign or if the line is empty, it will be ignored
        if(line[0] != ' ' && line[0] != '#' && line != ""){
            consonants.push_back(line);
        }
    }

    while (getline(in_vowels, line)){
        if(line[0] != ' ' && line[0] != '#' && line != ""){
            vowels.push_back(line);
        }
    }

    in_consonants.close();
    in_vowels.close();
}

std::string get_preset_oto(const OtoType preset) noexcept {
    switch(preset){
        case OtoType::VV:
            return ",1000,200,1000,100,60";
        case OtoType::V:
            return ",100,200,100,60,60";
        case OtoType::CV:
            return ",1000,200,1000,30,60";
        case OtoType::VC:
            return ",1000,90,1000,60,60";
        case OtoType::CC:
            return ",1000,40,1000,20,10";
        case OtoType::CCV:
            return ",1000,200,1000,20,60";
        case OtoType::VCC:
            return ",1000,90,1000,15,30";
        case OtoType::STAT:
            return ",1000,60,1000,60,60";
    }
}

std::ofstream generateUST(const RecType recordingType, int& filecounter, int& notecounter) noexcept {
    string recType;
    switch(recordingType){
        case RecType::VV:
            recType = "VV";
            break;
        case RecType::V:
            recType = "V";
            break;
        case RecType::CV:
            recType = "CV";
            break;
        case RecType::CVVC:
            recType = "CVVC";
            break;
        case RecType::VC:
            recType = "VC";
            break;
        case RecType::VCV:
            recType = "VCV";
            break;
        case RecType::VCCV:
            recType = "VCCV";
            break;
        case RecType::STAT:
            recType = "Stat";
            break;
    }
    const string filename = recType + "_" + to_string(++filecounter) + "_debug.ust";
    notecounter = 3;
    ofstream file(filename);

    if(!file){
        QMessageBox::critical(nullptr, "Error", "Error while writting a ust file, please check if you have the rights writing into the output folder and/or if there is already a file with the same name opened in another process.");
    }

    file << UST_HEADER[0] << recType << " debug" << UST_HEADER[1] << filename << UST_HEADER[2];

    return file;
}

std::ofstream generateUST(const RecType rectype, int& filecounter, int& notecounter, std::ofstream& oldfile) noexcept {
    closeUST(oldfile);
    return generateUST(rectype, filecounter, notecounter);
}

void closeUST(std::ofstream &file) noexcept {
    file << UST_FOOTER;
    file.close();
}

template<typename T>
string num_to_string(T&& num){
    if (num < 10){
        return "000" + to_string(num);
    } else if (num < 100) {
        return "00" + to_string(num);
    } else if (num < 1000) {
        return "0" + to_string(num);
    } else {
        return to_string(num);
    }
}

void writeNote(std::ofstream &ustFile, int notecounter, int &filecounter, const RecType rectype, const NoteLength length, const std::string lyrics = "R"){
    string notecount;
    if(notecounter > 950){
        ustFile = generateUST(rectype, filecounter, notecounter, ustFile);
    }

    notecount = num_to_string(notecounter);

    ustFile << NOTE_BODY[0] << notecount << NOTE_BODY[1] << length << NOTE_BODY[2] << lyrics;
    if(lyrics == "R"){
        ustFile << NOTE_BODY[4];
    } else {
        ustFile << NOTE_BODY[3];
    }
}

void writeAlias(std::ofstream& otoini, const std::string& filename, const std::string &alias, const OtoType otoType) noexcept {
    otoini << filename + OTO_BODY + alias + get_preset_oto(otoType) + "\n";
    return;
}

void writeRecOto(std::ofstream &reclist, std::ofstream &otoini, std::ofstream &ust, int &notecounter, int &filecounter, RecType recType, std::string &filename, std::vector<std::string> &aliases, OtoType otoType) noexcept {
    reclist << filename + "\n";

    for(string& alias : aliases){
        writeAlias(otoini, filename, alias, otoType);
        writeNote(ust, notecounter, filecounter, recType, NoteLength::full, alias);
    }



}

