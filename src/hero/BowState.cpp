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
#include "solarus/hero/BowState.h"
#include "solarus/hero/FreeState.h"
#include "solarus/hero/HeroSprites.h"
#include "solarus/entities/MapEntities.h"
#include "solarus/entities/Arrow.h"
#include "solarus/lowlevel/Sound.h"
#include <memory>

namespace Solarus {

/**
 * \brief Constructor.
 * \param hero The hero controlled by this state.
 */
Hero::BowState::BowState(Hero& hero):
  State(hero, "bow") {
}

/**
 * \brief Starts this state.
 * \param previous_state the previous state
 */
void Hero::BowState::start(const State* previous_state) {

  State::start(previous_state);
  get_sprites().set_animation("bow");
}

/**
 * \brief Updates this state.
 */
void Hero::BowState::update() {

  State::update();

  Hero& hero = get_hero();
  if (get_sprites().is_animation_finished()) {
    Sound::play("bow");
    get_entities().add_entity(std::make_shared<Arrow>(hero));
    hero.set_state(new FreeState(hero));
  }
}

/**
 * \copydoc Hero::State::can_avoid_stream
 */
bool Hero::BowState::can_avoid_stream(const Stream& /* stream */) const {
  return true;
}

}

