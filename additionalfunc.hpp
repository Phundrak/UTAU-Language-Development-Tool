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
 * along with Foobar.  If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once

#include "stdafx.hpp"
#include "global.hpp"

void openfolder(const char* folder);

void load_phonemes(std::ifstream& in_consonants, std::ifstream& in_vowels);

enum class OtoType{ VV, V, CV, VC, CC, CCV, VCC, STAT};

enum class RecType{ VV, V, CV, CVVC, VC, VCV, VCCV, STAT};

enum NoteLength{ large = 960, full = 480, threequarter = 360, half = 240, quarter = 120};

std::string get_preset_oto(const OtoType preset) noexcept;

std::ofstream generateUST(const RecType recordingType, int& filecounter, int& notecounter) noexcept;

std::ofstream generateUST(const RecType rectype, int& filecounter, int& notecounter, std::ofstream& oldfile) noexcept;

void closeUST(std::ofstream& file) noexcept ;

template<typename T>
std::string num_to_string(T&& num);

void writeNote(std::ofstream &ustFile, int notecounter, int &filecounter, const RecType rectype, const NoteLength length, const std::string lyrics);

void writeAlias(std::ofstream& otoini, const std::string& filename, const std::string &alias, const OtoType otoType) noexcept ;

void writeRecOto(std::ofstream &reclist, std::ofstream &otoini, std::ofstream &ust, int &notecounter, int &filecounter, RecType recType, std::string &filename, std::vector<std::string> &aliases, OtoType otoType) noexcept ;
