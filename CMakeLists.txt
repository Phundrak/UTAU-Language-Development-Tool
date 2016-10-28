######################################################################
# Copyright © 2016-2017 Lucien Cartier-Tilet
#
# This file is part of the UTAU Language Development Tool (ULDT).
#
# The ULDT is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# The ULDT is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with Foobar.  If not, see <http://www.gnu.org/licenses/>.
######################################################################


cmake_minimum_required(VERSION 3.6)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)

project(ULDT_GUI)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++14 -O3")

set(SOURCE_FILES main.cpp stdafx.hpp MainWindow.cpp MainWindow.hpp additionalfunc.cpp additionalfunc.hpp global.cpp global.hpp)
add_executable(ULDT_GUI ${SOURCE_FILES} stdafx.hpp MainWindow.cpp MainWindow.hpp)

find_package( Qt5Core REQUIRED )
find_package( Qt5Widgets REQUIRED )
find_package( Qt5Gui REQUIRED )

qt5_use_modules( ULDT_GUI Core Widgets Gui )