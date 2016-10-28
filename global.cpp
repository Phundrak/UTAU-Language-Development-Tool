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

const char* UST_HEADER[3] = {
        "[#VERSION]\nUST Version1.2\n[#SETTING]\nTempo=120.00\nTracks=1\nProjectName=",
        "\nVoiceDir=%VOICE%uta\nOutFile=\nCacheDir=",
        ".cache\nTool1=wavtool.exe\nTool2=resampler.exe\nMode2=True\n[#0000]\nLength=480\nLyric=R\nNoteNum=60\nPreUtterance=\n[#0001]\nLength=480\nLyric=R\nNoteNum=60\nPreUtterance=\n[#0002]\nLength=480\nLyric=R\nNoteNum=60\nPreUtterance=\n[#0003]\nLength=480\nLyric=R\nNoteNum=60\nPreUtterance=\n"
};

const char* UST_FOOTER = "[#TRACKEND]\n";

const string NOTE_BODY[5]{
        "[#",
        "]\nLength=",
        "\nLyric=",
        "\nNoteNum=60\nPreUtterance=\nIntensity=100\nModulation=0\nPBS=-43\nPBW=84\n",
        "\nNoteNum=60\nPreUtterance=\n"
};

const string OTO_BODY = ".wav=";