
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
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with the ULDT. If not, see <http://www.gnu.org/licenses/>.
 */

#include "stdafx.hpp"

using namespace std;

void generate_cv(std::ofstream &reclist, std::ofstream &otoini) noexcept {
	string filename;
	string alias;
	int filecounter = 0;
	int notecounter = 0;
	int recCounter = 0;
	ofstream ust = generateUST(RecType::CV, filecounter, notecounter);
	
	for(size_t i = 0; i < consonants.size(); i++){
		for(size_t j = 0; j < vowels.size(); j++){
			if(notecounter > 950){
                ust = generateUST(RecType::CV, filecounter, notecounter, ust);
			}
			alias = consonants[i] + vowels[j];
			filename = "CV" + num_to_string(++recCounter) + "_" + alias;
			reclist << filename + "\n";
			writeAlias(otoini, filename, alias, OtoType::CV);
			writeNote(ust, notecounter, filecounter, RecType::CV, NoteLength::full, alias);
			writeNote(ust, notecounter, filecounter, RecType::CV, NoteLength::full, "R");
		}
	}

	closeUST(ust);
	return;
}

void generate_cvvc(std::ofstream &reclist, std::ofstream &otoini) noexcept {
	string filename;
	string alias;
	int filecounter = 0;
	int notecounter = 0;
	int recCounter = 0;
	ofstream ust = generateUST(RecType::CVVC, filecounter, notecounter);
    for(size_t i = 0; i < consonants.size(); i++){
		bool silToCons = false;
		for(size_t j = 0; j < vowels.size(); j++){
			if(notecounter > 950){
                ust = generateUST(RecType::CVVC, filecounter, notecounter, ust);
			}
			filename = "CVVC" + num_to_string(++recCounter) + "_" + consonants[i] + vowels[j] + consonants[i] + vowels[j] + consonants[i];
            reclist << filename + "\n";
			if(!silToCons){
                writeAlias(otoini, filename, "- " + consonants[i], OtoType::CV);
	            writeAlias(otoini, filename, consonants[i] + " R", OtoType::VC);
	            silToCons = true;
			}
			writeAlias(otoini, filename, "- " + consonants[i] + vowels[j], OtoType::CV);
			writeAlias(otoini, filename, vowels[j] + consonants[i], OtoType::VCC);
			writeAlias(otoini, filename, consonants[i] + vowels[j], OtoType::CCV);
			writeAlias(otoini, filename, vowels[j] + consonants[i] + " R", OtoType::VC);
			writeNote(ust, notecounter, filecounter, RecType::CVVC, NoteLength::full, "- " + consonants[i] + vowels[j]);
			writeNote(ust, notecounter, filecounter, RecType::CVVC, NoteLength::quarter, vowels[j] + consonants[i]);
			writeNote(ust, notecounter, filecounter, RecType::CVVC, NoteLength::full, consonants[i] + vowels[j]);
			writeNote(ust, notecounter, filecounter, RecType::CVVC, NoteLength::half, vowels[j] + consonants[i] + " R");
			writeNote(ust, notecounter, filecounter, RecType::CV, NoteLength::large, "R");
		}
	}
	return;
}

void generate_vv(std::ofstream &reclist, std::ofstream &otoini, const int &SYL_MAX) noexcept {
	string filename;
	//string alias;
	int filecounter = 0, notecounter = 0, reccounter = 0, sylCount = 0;
	vector<string> syllables;
	ofstream ust = generateUST(RecType::VV, filecounter, notecounter);
	for(size_t i = 0; i < vowels.size(); i++){
        bool toSil = false;
		
		
		filename = "VV" + num_to_string(++reccounter) + "_-";
		sylCount++;
        for(size_t j = 0 + i; j < vowels.size(); j++){
            // if we have too much notes in the ust, creates a new ust file
			if(notecounter > 950){
	            ust = generateUST(RecType::VV, filecounter, notecounter, ust);
            }
		    // if we reach the max number of syllables, we create a new recordinh
            if(sylCount >= SYL_MAX - 1){
                if(!toSil){
                    syllables.push_back(vowels[i] + " -");
                    filename += " -";
                    toSil = true;
                }
                writeRecOto(reclist, otoini, ust, notecounter, filecounter, RecType::VV, filename, syllables, OtoType::VV);
                while (syllables.size() > 0){
                    syllables.pop_back();
                }
                sylCount = 0;
                filename = "VV" + num_to_string(++reccounter) + "_" + vowels[i];
            }
            if(j == 0 + i){
                syllables.push_back("- " + vowels[i]);
            }

            filename += " " + vowels[j] + " " + vowels[i];
            if (j != 0 + i) syllables.push_back(vowels[i] + " " + vowels[j]);
            syllables.push_back(vowels[j] + " " + vowels[i]);
            sylCount += 2;
        }
        if(!toSil){
            syllables.push_back(vowels[i] + " -");
            //toSil = true;
        }

		
		writeRecOto(reclist, otoini, ust, notecounter, filecounter, RecType::VV, filename, syllables, OtoType::VV);
		while (syllables.size() > 0){
            syllables.pop_back();
		}
		
		sylCount = 0;
	}

	closeUST(ust);
	return;
}

void generate_v(std::ofstream &reclist, std::ofstream &otoini) noexcept {
	string filename;
	string alias;
	int filecounter = 0, notecounter = 0, recCounter = 0;
	ofstream ust = generateUST(RecType::V, filecounter, notecounter);
	
	for(size_t i = 0; i < vowels.size(); i++){
		if(notecounter > 950){
			ust = generateUST(RecType::V, filecounter, notecounter, ust);
		}
		filename = "V" + num_to_string(++recCounter) + "_" + vowels[i];
		reclist << filename + "\n";
		writeAlias(otoini, filename, vowels[i], OtoType::V);
		writeNote(ust, notecounter, filecounter, RecType::V, NoteLength::full, alias);
		writeNote(ust, notecounter, filecounter, RecType::V, NoteLength::full, "R");
	}
	return;
}

void generate_vcv(std::ofstream &reclist, std::ofstream &otoini, const int &SYL_MAX) noexcept {
	string filename;
	//string alias;
	int filecounter = 0, notecounter = 0, reccounter = 0, sylCount = 0;
	vector<string> syllables;
	auto ust = generateUST(RecType::VCV, filecounter, notecounter);
	
	/*
	 * first we parse consonant per consonant, then we apply the same logic we applied for VV
	 * recordings. We can also try to concatenate in a future update CVVC recordings with VCV
	 * recordings if both are selected, otherwise only do VCV or CVVC separately (maybe add an
	 * option to have both together or separated?)
	 */

    /*
     * TODO: verify if there is no recordings unwritten if the recording has less than SYL_MAX
     * vowels, I (Drak-pa) am suspicious on that but I didn't have the time to verify last time
     */

	for (auto consonant : consonants){
		if(notecounter > 900){
			ust = generateUST(RecType::VCV, filecounter, notecounter, ust);
		}
		for (size_t i = 0; i < vowels.size(); i++){
			filename = "VCV" + num_to_string(++reccounter) + "_-";
			sylCount++;
			for(size_t j = i; j < vowels.size(); j++){
				if(sylCount >= SYL_MAX - 1){
			        writeRecOto(reclist, otoini, ust, notecounter, filecounter, RecType::VCV, filename, syllables, OtoType::VCV);
			        while(syllables.size() > 0){
			            syllables.pop_back();
		            }
		            sylCount = 0;
		            filename = "VCV" + num_to_string(++reccounter) + "_" + vowels[i];
                }
                if(j == 0 + i){
                    syllables.push_back(" - " + consonant + vowels[i]);
                }
                filename += consonant + vowels[j] + consonant + vowels[i];
                if(j != 0 + i) syllables.push_back(vowels[i] + " " + consonant + vowels[j]);
                syllables.push_back(vowels[j] + " " + consonant + vowels[i]);
                sylCount += 2;
			}
			
			writeRecOto(reclist, otoini, ust, notecounter, filecounter, RecType::VCV, filename, syllables, OtoType::VCV);
			while(syllables.size() > 0){
	            syllables.pop_back();
            }
			sylCount = 0;
		}
	}

	generate_vv(reclist, otoini, SYL_MAX);

	closeUST(ust);
	return;
}
void generate_vccv(std::ofstream &reclist, std::ofstream &otoini, const std::string &VCCV_SYL, const int &SYL_MAX) noexcept {
	string filename;
	string alias;
	int filecounter = 0, notecounter = 0, recCounter = 0, sylCount = 0;
	vector<string> syllables;
	ofstream ust = generateUST(RecType::VCCV, filecounter, notecounter);
	
	for(size_t i = 0; i < consonants.size(); i++){
		filename = "VCCV" + num_to_string(++recCounter) + "_";
		for(size_t j = 0; j < consonants.size(); j++){
			if(notecounter > 950){
                generateUST(RecType::VCCV, filecounter, notecounter, ust);
			}
			if(sylCount > SYL_MAX){
                writeRecOto(reclist, otoini, ust, notecounter, filecounter, RecType::VCCV, filename, syllables, OtoType::CC);
                while(syllables.size() > 0){
                    syllables.pop_back();
                }
                sylCount = 0;
                filename = "VCCV" + num_to_string(++recCounter) + "_";
			}
			
			syllables.push_back(consonants[i] + " " + consonants[j]);
			if(sylCount != 0){
                filename += " ";
			}
			filename += VCCV_SYL + consonants[i] + consonants[j] + VCCV_SYL;
			sylCount++;
		}
		writeRecOto(reclist, otoini, ust, notecounter, filecounter, RecType::VCCV, filename, syllables, OtoType::CC);
		while(syllables.size() > 0){
            syllables.pop_back();
		}
		sylCount = 0;
	}
	
	generate_cvvc(reclist, otoini);
	
	closeUST(ust);
	return;
}
