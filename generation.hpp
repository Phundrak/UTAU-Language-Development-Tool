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

// generates CV recordings
void generate_cv(std::ofstream &reclist, std::ofstream &otoini) noexcept;

// generates CVVC recordings
void generate_cvvc(std::ofstream &reclist, std::ofstream &otoini) noexcept;

// generates VV recordings
void generate_vv(std::ofstream &reclist, std::ofstream &otoini, const int &SYL_MAX) noexcept;

// generates stationaries recordings
void generate_v(std::ofstream &reclist, std::ofstream &otoini) noexcept;

// generates VCV recordings
void generate_vcv(std::ofstream &reclist, std::ofstream &otoini, const int &SYL_MAX, const std::string &outputDir) noexcept;

// generates VCCV recordings, calls also generate_cvvc()
void generate_vccv(std::ofstream &reclist, std::ofstream &otoini, const std::string &VCCV_SYL, const int &SYL_MAX) noexcept;