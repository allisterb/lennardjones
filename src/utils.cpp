
/*
 * Copyright (C) 2015 James W. Barnett <jbarnet4@tulane.edu>
 *
 * This program is free software; you can redistribute it and/or modify it under
 * the terms of the GNU General Public License as published by the Free Software
 * Foundation; either version 2 of the License, or (at your option) any later
 * version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT ANY
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A
 * PARTICULAR PURPOSE.  See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program; if not, write to the Free Software Foundation, Inc., 51
 * Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 * The full license is located in a text file titled "LICENSE" in the root
 * directory of the source.
 *
 */

#include "utils.h"

coordinates pbc(coordinates a, triclinicbox box)
{
    coordinates b;

    vector <double> box_inv(3);
    double shift;

    b = a;

    box_inv.at(X) = ((float)1.0) / box.at(X).at(X);
    box_inv.at(Y) = ((float)1.0) / box.at(Y).at(Y);
    box_inv.at(Z) = ((float)1.0) / box.at(Z).at(Z);

    shift = round(b.at(Z) * box_inv.at(Z));
    b.at(Z) -= box.at(Z).at(Z) * shift;
    b.at(Y) -= box.at(Z).at(Y) * shift;
    b.at(X) -= box.at(Z).at(X) * shift;

    shift = round(b.at(Y) * box_inv.at(Y));
    b.at(Y) -= box.at(Y).at(Y) * shift;
    b.at(X) -= box.at(Y).at(X) * shift;

    shift = round(b.at(X) * box_inv.at(X));
    b.at(X) -= box.at(X).at(X) * shift;

    return b;
}

double distance(coordinates a, coordinates b, triclinicbox box)
{
    return sqrt(distance2(a, b, box));
}

double distance2(coordinates a, coordinates b, triclinicbox box)
{
    coordinates c = a - b;

    c = pbc(c, box);
    return dot(c, c);
}

double dot(coordinates a, coordinates b)
{
    return a.at(X) * b.at(X) + a.at(Y) * b.at(Y) + a.at(Z) * b.at(Z);
}

double magnitude(coordinates x)
{
    return sqrt(dot(x, x));
}

double volume(triclinicbox box)
{
    return box.at(X).at(X) * box.at(Y).at(Y) * box.at(Z).at(Z) + \
           box.at(X).at(Y) * box.at(Y).at(Z) * box.at(Z).at(X) + \
           box.at(X).at(Z) * box.at(Y).at(X) * box.at(Z).at(Y) - \
           box.at(X).at(Z) * box.at(Y).at(Y) * box.at(Z).at(X) + \
           box.at(X).at(Y) * box.at(Y).at(X) * box.at(Z).at(Z) + \
           box.at(X).at(X) * box.at(Y).at(Z) * box.at(Z).at(Y);
}