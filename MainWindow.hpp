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

class MainWindow : public QWidget {
Q_OBJECT
public:
    MainWindow();

    const int return_error(const int error_code) noexcept ;
private:
    // methods

    // members
    QGridLayout *m_mainLayout;
    QGridLayout *m_recTypeLayout;

    QLabel *m_labelChoseCons;
    QLabel *m_labelChoseVow;
    QLabel *m_labelChoseRecType;
    QLabel *m_labelchoseOutDir;
    QLabel *m_labelChoseNumSyl;
    QLabel *m_labelValNumSyl;

    QPushButton *m_buttonChoseCons;
    QPushButton *m_buttonChoseVow;
    QPushButton *m_buttonQuit;
    QPushButton *m_buttonGenerate;
    QPushButton *m_buttonChoseOutDir;

    QCheckBox *m_buttonCV;
    QCheckBox *m_buttonVC;
    QCheckBox *m_buttonCVVC;
    QCheckBox *m_buttonVCCV;
    QCheckBox *m_buttonVCV;
    QCheckBox *m_buttonVV;
    QCheckBox *m_buttonStat;

    QSlider *m_numberSyl;

    QProgressBar *m_mainProgress;
    QProgressBar *m_secondaryProgress;

    QString m_outputDir;
    QString m_inputCons;
    QString m_inputVow;
    QString m_vccv_vowel;

    const QString ERROR_MESSAGE = "\") could not be open. Please check that this file\n\texist in the same directory as this tool. It might also be opened in another software\n\twhich prevents the file from being opened by another software (such as this tool). Please\n\tclose it first and after that run again this tool.\n\n\t";

signals:
    bool check(bool);
    void done();

public slots:
    void vvChecked(bool checked);
    void openCons();
    void openVow();
    void openOutDir();
    void generate();
    void generationDone();
    void estimateGenerationDone(int progression);
    void updateNumSyl(int i);
};


