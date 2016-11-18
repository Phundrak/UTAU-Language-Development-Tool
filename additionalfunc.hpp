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

#pragma once

#include "stdafx.hpp"
#include "global.hpp"

// replaces all substrings in a string to another substring
std::string replaceAll(std::string str, const std::string&& from, const std::string&& to);

// standardizes the name of the output folder so that the folder can be opened at the end of the generation
QString standardize_name(QString str);

// opens with the default file manager the output folder
void openfolder(const QString &folder) noexcept;

// loads the phonemes from the input files
void load_phonemes(std::ifstream& in_consonants, std::ifstream& in_vowels) noexcept;

// type of oto.ini, used when writing the oto.ini file
enum class OtoType{ VV, V, CV, VC, CC, CCV, VCC, STAT};

// type of recording, used when writing ust files
enum class RecType{ VV, V, CV, CVVC, VC, VCV, VCCV, STAT};

// length of the notes in the ust files
enum NoteLength{ large = 960, full = 480, threequarter = 360, half = 240, quarter = 120};

// returns the oto.ini preset based on the oto.ini style
std::string get_preset_oto(const OtoType preset) noexcept;

// returns an output ust file numbered, and resets the note number
std::ofstream generateUST(const RecType recordingType, int& filecounter, int& notecounter) noexcept;

// closes the file passed through oldfile and returns a new file
// this function is generally called when the maximum number of notes is reached in the previous ust file
std::ofstream generateUST(const RecType rectype, int& filecounter, int& notecounter, std::ofstream& oldfile) noexcept;

// closes the ust file
void closeUST(std::ofstream& file) noexcept ;

// converts a numeral to a string
template<typename T>
std::string num_to_string(T&& num);

// writes a note to the passed ust file using the lyrics passed in the last argument
void writeNote(std::ofstream &ustFile, int notecounter, int &filecounter, const RecType rectype, const NoteLength length, const std::string lyrics);

// writes a oto.ini line in the passed oto.ini file with the alias passed in the alias argument and uses the
// oto.ini preset fetched with the otoType
void writeAlias(std::ofstream& otoini, const std::string& filename, const std::string &alias, const OtoType otoType) noexcept ;

// writes the recording's name to the reclist and its aliases to the oto.ini file
void writeRecOto(std::ofstream &reclist, std::ofstream &otoini, std::ofstream &ust, int &notecounter, int &filecounter, RecType recType, std::string &filename, std::vector<std::string> &aliases, OtoType otoType) noexcept ;