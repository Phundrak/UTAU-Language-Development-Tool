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

constexpr int MAXCHARBUTTON = 22;
constexpr int MAXCHARBUTTON2 = 60;
vs consonants;
vs vowels;
std::string vccv_vowels;
// selection of either \ or / as the separator in folder and file path depending on the OS the tool has been compiled on
#if (defined (__WIN32__) || defined (_WIN32)) && !defined (__MINGW32__)
    std::string SEP = "\\";
#else
    std::string SEP = "/";
#endif


MainWindow::MainWindow() : QWidget()
{
    //setFixedSize(565,650);
    //setFixedHeight(500);

    m_mainLayout = new QGridLayout;
    m_recTypeLayout = new QGridLayout;


    m_labelChoseCons = new QLabel("1. Choose your consonant file:", this);

    m_buttonChoseCons = new QPushButton("No file chosen...", this);
    m_buttonChoseCons->setFixedWidth(200);
    m_buttonChoseCons->setCursor(Qt::PointingHandCursor);

    m_labelChoseVow = new QLabel("2. Choose your vowel file:", this);

    m_buttonChoseVow = new QPushButton("No file chosen...", this);
    m_buttonChoseVow->setFixedWidth(200);
    m_buttonChoseVow->setCursor(Qt::PointingHandCursor);

    m_labelChoseRecType = new QLabel("3. Choose here the recording style desired:", this);

    m_buttonCV = new QCheckBox("CV", this);
    m_buttonCV->setCursor(Qt::PointingHandCursor);
    m_buttonCV->setChecked(true);

    m_buttonVC = new QCheckBox("VC", this);
    m_buttonVC->setCursor(Qt::PointingHandCursor);

    m_buttonVCV = new QCheckBox("VCV", this);
    m_buttonVCV->setCursor(Qt::PointingHandCursor);

    m_buttonVV = new QCheckBox("VV", this);
    m_buttonVV->setCursor(Qt::PointingHandCursor);

    m_buttonStat = new QCheckBox("Stationaries", this);
    m_buttonStat->setCursor(Qt::PointingHandCursor);
    m_buttonStat->setChecked(true);
    m_buttonStat->setDisabled(true);

    m_buttonCVVC = new QCheckBox("CVVC", this);
    m_buttonCVVC->setCursor(Qt::PointingHandCursor);

    m_buttonVCCV = new QCheckBox("VCCV", this);
    m_buttonVCCV->setCursor(Qt::PointingHandCursor);

    m_recTypeLayout->addWidget(m_buttonCV, 0, 0);
    m_recTypeLayout->addWidget(m_buttonVC, 0, 1);
    m_recTypeLayout->addWidget(m_buttonVCV, 1, 0);
    m_recTypeLayout->addWidget(m_buttonVV, 1, 1);
    m_recTypeLayout->addWidget(m_buttonStat, 1, 2);
    m_recTypeLayout->addWidget(m_buttonCVVC, 2, 0);
    m_recTypeLayout->addWidget(m_buttonVCCV, 2, 1);


    m_labelChoseNumSyl = new QLabel("4. Chose the maximum number of syllables:", this);
    m_numberSyl = new QSlider(Qt::Horizontal, this);
    m_numberSyl->setValue(5);
    m_numberSyl->setTickInterval(1);
    m_numberSyl->setMinimum(3);
    m_numberSyl->setMaximum(10);
    m_labelValNumSyl = new QLabel(QString::number(m_numberSyl->value()), this);

    m_labelchoseOutDir = new QLabel("5. Choose the output directory:", this);

    m_buttonChoseOutDir = new QPushButton("No folder selected...", this);
    m_buttonChoseOutDir->setCursor(Qt::PointingHandCursor);

    m_buttonGenerate = new QPushButton("6. Generate", this);
    m_buttonGenerate->setCursor(Qt::PointingHandCursor);

    m_secondaryProgress = new QProgressBar(this);

    m_mainProgress = new QProgressBar(this);

    m_buttonQuit = new QPushButton("&Quit", this);
    m_buttonQuit->setCursor(Qt::PointingHandCursor);


    m_mainLayout->addWidget(m_labelChoseCons, 0, 0);
    m_mainLayout->addWidget(m_labelChoseVow, 0, 1);
    m_mainLayout->addWidget(m_buttonChoseCons, 1, 0);
    m_mainLayout->addWidget(m_buttonChoseVow, 1, 1);
    m_mainLayout->addWidget(m_labelChoseRecType, 2, 0);
    m_mainLayout->addLayout(m_recTypeLayout, 3, 0, 1, 2);
    m_mainLayout->addWidget(m_labelChoseNumSyl, 7, 0);
    m_mainLayout->addWidget(m_numberSyl, 8, 0);
    m_mainLayout->addWidget(m_labelValNumSyl, 8, 1);
    m_mainLayout->addWidget(m_labelchoseOutDir, 9, 0);
    m_mainLayout->addWidget(m_buttonChoseOutDir, 10, 0, 1, 2);
    m_mainLayout->addWidget(m_buttonGenerate, 11, 0, 1, 2);
    m_mainLayout->addWidget(m_secondaryProgress, 12, 0, 1, 2);
    m_mainLayout->addWidget(m_mainProgress, 13, 0, 1, 2);
    m_mainLayout->addWidget(m_buttonQuit, 14, 1);

    this->setLayout(m_mainLayout);

    // if the slider is moved, the value next to it is modified
    QObject::connect(m_numberSyl, SIGNAL(valueChanged(int)), this, SLOT(updateNumSyl(int)));

    // these call the functions used to select the input files and the output directory
    QObject::connect(m_buttonChoseCons, SIGNAL(clicked(bool)), this, SLOT(openCons()));
    QObject::connect(m_buttonChoseVow, SIGNAL(clicked(bool)), this, SLOT(openVow()));
    QObject::connect(m_buttonGenerate, SIGNAL(clicked(bool)), this, SLOT(generate()));

    //makes the application close if the Quit button is clicked
    QObject::connect(m_buttonQuit, SIGNAL(clicked(bool)), qApp, SLOT(quit()));

    // if the CVVC option is selected, it will automatically select the CV and VC options
    QObject::connect(m_buttonCVVC, SIGNAL(toggled(bool)), m_buttonCV, SLOT(setDisabled(bool)));
    QObject::connect(m_buttonCVVC, SIGNAL(toggled(bool)), m_buttonCV, SLOT(setChecked(bool)));
    QObject::connect(m_buttonCVVC, SIGNAL(toggled(bool)), m_buttonVC, SLOT(setDisabled(bool)));
    QObject::connect(m_buttonCVVC, SIGNAL(toggled(bool)), m_buttonVC, SLOT(setChecked(bool)));

    QObject::connect(m_buttonVV, SIGNAL(toggled(bool)), this, SLOT(vvChecked(bool)));

    QObject::connect(m_buttonVCCV, SIGNAL(toggled(bool)), m_buttonCVVC, SLOT(setChecked(bool)));
    QObject::connect(m_buttonVCCV, SIGNAL(toggled(bool)), m_buttonCVVC, SLOT(setDisabled(bool)));

    // this is supposed to show progress in the progress bars, not sure these will be used though
    QObject::connect(m_mainProgress, SIGNAL(valueChanged(int)), this, SLOT(estimateGenerationDone(int)));
    // calls the end of generation function which will tell the user the tool finished running
    QObject::connect(this, SIGNAL(done()), this, SLOT(generationDone()));

    // choose the output directory
    QObject::connect(m_buttonChoseOutDir, SIGNAL(clicked(bool)), this, SLOT(openOutDir()));

}

// until the VV checkbox is checked, the stationaries checkbox is checked and grayed out
// it becomes available and modifiable if the VV checkbox
void MainWindow::vvChecked(bool checked){
    m_buttonStat->setChecked(!checked);
    m_buttonStat->setDisabled(!checked);
}

// if the main progress bar is full, calls the function telling the user the tool is done running
void MainWindow::estimateGenerationDone(int progression){
    if(progression >= 100)
            emit done();
}

// this function updates the value selected with the slider displayed in the label next to it
void MainWindow::updateNumSyl(int i) {
    m_labelValNumSyl->setText(QString::number(i));
}

// function called once the generation is done
void MainWindow::generationDone(){
    QMessageBox::information(this, "Done", "The generation of your files is done!");
    qApp->quit();
}

// function used to select the input consonant file
void MainWindow::openCons(){
//    QMessageBox::information(this, "Choose your consonant file", "Please chose your consonnat file");
    m_inputCons = QFileDialog::getOpenFileName(this, "Choose your consonant file", QString(), "Text (*.txt)");
//    if(m_inputCons != "") {
//        QMessageBox::information(this, "", "You opened the file " + m_inputCons);
//    }
    if(m_inputCons.size() > MAXCHARBUTTON && !m_inputCons.isEmpty()) {
        m_buttonChoseCons->setText("[...] " + m_inputCons.right(MAXCHARBUTTON));
    } else if(!m_inputCons.isEmpty()) {
        m_buttonChoseCons->setText(m_inputCons);
    }

}

// function used to select the input vowel file
void MainWindow::openVow(){
//    QMessageBox::information(this, "Choose your vowel file", "Please chose your vowel file");
    m_inputVow = QFileDialog::getOpenFileName(this, "Choose your vowelfile", QString(), "Text (*.txt)");
//    if(m_inputVow != ""){
//        QMessageBox::information(this, "", "You opened the file " + m_inputVow);
//    }
    if(m_inputVow.size() > MAXCHARBUTTON && !m_inputVow.isEmpty()){
        m_buttonChoseVow->setText("[...] " + m_inputVow.right(MAXCHARBUTTON));
    } else if(!m_inputVow.isEmpty()){
        m_buttonChoseVow->setText(m_inputVow);
    }
}

// function used in order to select the output directory
void MainWindow::openOutDir(){
//    QMessageBox::information(this, "Choose your output directory", "Please chose your output directory");
    m_outputDir = QFileDialog::getExistingDirectory(this);
//    if(m_outputDir != ""){
//        QMessageBox::information(this, "", "You opened the directory " + m_outputDir);
//    } else {
//        QMessageBox::critical(this, "", "Could not open the folder, please try again.");
//        return;
//    }



    if(m_outputDir.size() > MAXCHARBUTTON2 && !m_outputDir.isEmpty()){
        m_buttonChoseOutDir->setText("[...] " + m_outputDir.right(MAXCHARBUTTON2));
    }
    else if(!m_outputDir.isEmpty()){
        m_buttonChoseOutDir->setText(m_outputDir);
    }
}

// displays an error message if a file could not be loaded
const void MainWindow::return_error(const int& error_code) noexcept {
    const QString title{"Fatal Error"};
    switch (error_code) {
        case 1:
            QMessageBox::critical(this, title, "Error:\nThe consonant input file (\"consonant.txt" + ERROR_MESSAGE);
            return;

        case 2:
            QMessageBox::critical(this, title, "Error:\nThe vowel input file (\"vowels.txt" + ERROR_MESSAGE);
            return;

        case 3:
            QMessageBox::critical(this, title, "Error:\nThe reclist output could not be written (\"reclist.txt" + ERROR_MESSAGE);
            return;

        case 4:
            QMessageBox::critical(this, title, "Error:\nThe oto.ini output file could not be written (\"oto.ini" + ERROR_MESSAGE);
            return;

        case 5:
            QMessageBox::critical(this, title, "Error:\nA ust file couldn't be written." + ERROR_MESSAGE);
            return;

        default:
            QMessageBox::critical(this, title, "Error:\nA file" + ERROR_MESSAGE);
            return;
    }
}



//////////////////////////////////////////////////////////////////////////////////////////////
/// body of the function called once the "generate" button is clicked
//////////////////////////////////////////////////////////////////////////////////////////////

using namespace std;
void MainWindow::generate(){
    ifstream in_consonants{m_inputCons.toStdString()}, in_vowels{m_inputVow.toStdString()};
    if(m_outputDir == "" || m_inputCons == "" || m_inputVow == ""){
        QMessageBox::critical(this, "Error in selected file", "Error:\nYou haven't chosen either a file or an output directory.\nPlease check your settings and try again.");
        return;
    }
    // if there is any issue with the output file, end the generation
    if(!in_consonants){
        return_error(1);
        return;
    } else if (!in_vowels){
        return_error(2);
        return;
    }
    // for debug purpose only
//    QMessageBox::information(this, "", m_outputDir + QString::fromStdString(SEP) + "reclist.txt");
    ofstream reclist{m_outputDir.toStdString() + SEP + "reclist.txt"}, otoini{m_outputDir.toStdString() + SEP + "oto.ini"};
    // if there is any issue with the output file, end the generation
    if(!reclist) {
        return_error(3);
        return;
    } else if(!otoini){
        return_error(4);
        return;
    }


    load_phonemes(in_consonants, in_vowels);
    if(m_buttonVCCV->isChecked()){
        QStringList q_list_vowels;
        for(auto vowel : vowels){
            q_list_vowels.append(QString::fromStdString(vowel));
        }
        bool ok;
        QString vccv_vowel = QInputDialog::getItem(this, tr("QInputDialog::getItem()"), tr("VCCV vowel:"), q_list_vowels, 0, false, &ok);
        if(ok && !vccv_vowel.isEmpty()){
            m_vccv_vowel = vccv_vowel;
        } else {
            QMessageBox::critical(this, "No vowel chosen", "Error:\nNo vowel was chosen for the VCCV recordings. Please try again and choose a vowel.");
        }
    }

    // this part is used for debug purposes
    string recap{"Alright, here is the recap so far: \n\n\tConsonants:\n\n"};
    REP(i, 0u, consonants.size()){
        recap += consonants[i];
        if((i+1)%5 == 0 && i != 0){
            recap+="\n";
        } else {
            recap += "\t";
        }
    }
    recap += "\n\n\tVowels:\n\n";
    REP(i, 0u, vowels.size()){
        recap += vowels[i] + "\t";
        if((i+1)%5 == 0 && i != 0){
            recap+="\n";
        }
    }
    recap += "\n";
    recap += "\nInput files:\n" + m_inputCons.toStdString() + "\n" + m_inputVow.toStdString() + "\n";
    recap += "\nOutput directory:\n" + m_outputDir.toStdString() + "\n";
    QMessageBox::information(this, "Recap", QString::fromStdString(recap));

    /*
     * generation of the reclist, oto.ini and ust's goes there
     * */

    openfolder(standardize_name(m_outputDir).toStdString());
    return;
}