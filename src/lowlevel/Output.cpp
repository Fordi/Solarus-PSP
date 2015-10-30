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
#include "solarus/lowlevel/Output.h"
#include "solarus/Arguments.h"

namespace Solarus {

namespace Output {

namespace {
bool initialized = false;
}

/**
 * \brief Performs initializations depending on arguments.
 *
 * Does nothing if it was already called.
 *
 * \param args Command-line arguments.
 */
void initialize(const Arguments& args) {

  if (initialized) {
    return;
  }
}

/**
 * \brief Cleanups what was done by initialize().
 *
 * initialize() can then be called again later.
 * Does nothing if output was not initialized.
 */
void quit() {

  if (!initialized) {
    return;
  }
}

}

}

