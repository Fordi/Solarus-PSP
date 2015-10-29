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
#include "solarus/movements/PlayerMovement.h"
#include "solarus/entities/MapEntity.h"
#include "solarus/entities/Stream.h"
#include "solarus/entities/StreamAction.h"
#include "solarus/lowlevel/Geometry.h"
#include "solarus/lowlevel/Debug.h"
#include "solarus/Game.h"
#include "solarus/GameCommands.h"

namespace Solarus {

/**
 * \brief Constructor.
 * \param moving_speed movement speed
 */
PlayerMovement::PlayerMovement(int moving_speed):
  StraightMovement(false, true),
  moving_speed(moving_speed),
  direction8(-1) {

}

/**
 * \brief Updates this movement.
 */
void PlayerMovement::update() {

  StraightMovement::update();

  const MapEntity* entity = get_entity();
  if (entity == nullptr || !entity->is_on_map()) {
    return; // the entity is not ready yet
  }

  if (entity->has_stream_action() &&
      !entity->get_stream_action()->get_stream().get_allow_movement()) {
    // A stream blocks the control from the player.
    stop();
  }

  // Someone may have stopped the movement
  // (e.g. Hero::reset_movement() or a blocking stream).
  if (is_stopped() && direction8 != -1) {
    direction8 = -1;
    compute_movement();
  }
  else {

    // check whether the wanted direction has changed
    const GameCommands& commands = get_entity()->get_game().get_commands();
    int wanted_direction8 = commands.get_wanted_direction8();
    if (wanted_direction8 != direction8 && !is_suspended()) {
      direction8 = wanted_direction8;
      compute_movement();
    }
  }
}

/**
 * \brief Returns the direction this movement is trying to move towards.
 * \return the direction (0 to 7), or -1 if the player is not trying to go
 * to a direction or the movement is disabled
 */
int PlayerMovement::get_wanted_direction8() const {
  return direction8;
}

/**
 * \brief Returns the moving speed of the entity.
 * \return the moving speed of the entity
 */
int PlayerMovement::get_moving_speed() const {
  return moving_speed;
}

/**
 * \brief Sets the moving speed of the entity.
 * \param moving_speed the moving speed of the entity
 */
void PlayerMovement::set_moving_speed(int moving_speed) {

  this->moving_speed = moving_speed;
  set_wanted_direction();
  compute_movement();
}

/**
 * \brief Determines the direction defined by the directional keys currently pressed
 * and computes the corresponding movement.
 */
void PlayerMovement::set_wanted_direction() {

  if (get_entity() != nullptr && get_entity()->is_on_map()) {
    GameCommands& commands = get_entity()->get_game().get_commands();
    direction8 = commands.get_wanted_direction8();
  }
  else {
    direction8 = -1;
  }
}

/**
 * \brief Changes the movement of the entity depending on the direction wanted.
 *
 * This function is called when the direction is changed.
 */
void PlayerMovement::compute_movement() {

  // compute the speed vector corresponding to the direction wanted by the player

  if (direction8 == -1) {
    // no movement
    stop();
  }
  else { // the directional keys currently pressed define a valid movement
    set_speed(moving_speed);
    set_angle(Geometry::degrees_to_radians(direction8 * 45));
  }

  // Notify the entity that the properties of its movement have just changed.
  notify_movement_changed();
}

}

