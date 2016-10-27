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

#define REP(i, a, b) for(auto i = a; i < b; i++)

//Qt-related libraries
#include <QtWidgets/QApplication>
#include <QString>
#include <QMessageBox>
#include <QtWidgets>
#include <QPushButton>
#include <QProgressBar>
#include <QFile>
#include <QLabel>
#include <QCheckBox>
#include <QGridLayout>
#include <QSlider>

//C++ standard libraries
#include <vector>
#include <string>
#include <fstream>
#include <stdlib.h>

//user-created libraries
#include "MainWindow.hpp"
#include "additionalfunc.hpp"
#include "global.hpp"



using vs = std::vector<std::string>;
