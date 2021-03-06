#include <signal.h>
#include <iostream>

#include "ManiaPP.h"
#include "../lib/pugixml/src/pugixml.hpp"

/**
 * Mania++ is a Server Controller for TrackMania 2 servers, written in C++.
 * Copyright (C) 2016 Max Klaversma <maxklaversma@gmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.

 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

ManiaPP* controller;

int main(int argc, char *argv[])
{
    controller = new ManiaPP();
    if(controller->ConnectToServer())
    {
        controller->MainLoop();
        controller->Terminate();
    }

    delete controller; controller = NULL;
}
