// This file is part of CaesarIA.
//
// CaesarIA is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// CaesarIA is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with CaesarIA.  If not, see <http://www.gnu.org/licenses/>.

#include "ship.hpp"
#include "core/gettext.hpp"
#include "city/city.hpp"
#include "constants.hpp"
#include "corpse.hpp"
#include "game/resourcegroup.hpp"

using namespace constants;

Ship::Ship(PlayerCityPtr city )
  : Walker( city )
{
  _setType( walker::unknown );
  _setAnimation( gfx::unknown );

  setName( _("##ship##") );
}

void Ship::die()
{
  Walker::die();

  Corpse::create( _getCity(), pos(), ResourceGroup::carts, 265, 272, true );
}

Ship::~Ship()
{

}
