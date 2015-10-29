/*
 * Copyright (C) 2006-2015 Christopho, Solarus - http://www.solarus-games.org
 * 
 * Solarus is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * Solarus is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along
 * with this program. If not, see <http://www.gnu.org/licenses/>.
 */
#ifndef SOLARUS_MAP_LOADER_H
#define SOLARUS_MAP_LOADER_H

#include "solarus/Common.h"

struct lua_State;

namespace Solarus {

class Game;
class Map;

/**
 * \brief Parses a map file.
 *
 * This class loads a map and its content from a map file.
 */
class MapLoader {

  public:

    MapLoader();

    void load_map(Game& game, Map& map);

  private:

    static int l_properties(lua_State* l);
};

}

#endif

