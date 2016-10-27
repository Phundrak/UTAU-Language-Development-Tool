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

// TODO: comment all of this before it's too late, add the reclist, otoini and ust generation and stuff, pretty much only the GUI has been made so far. The generators should be added shortly (already written in another project)

#include "stdafx.hpp"

using namespace std;

int main(int argc, char* argv[]){

    QApplication app(argc, argv);

    MainWindow window;
    window.show();

    return app.exec();
}
