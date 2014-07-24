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
//
// Copyright 2012-2013 Dalerank, dalerankn8@gmail.com

#include "market_kid.hpp"
#include "market_lady.hpp"
#include "objects/market.hpp"
#include "city/helper.hpp"
#include "pathway/pathway.hpp"
#include "good/goodstore.hpp"
#include "game/resourcegroup.hpp"
#include "name_generator.hpp"
#include "constants.hpp"
#include "corpse.hpp"
#include "thinks.hpp"

using namespace constants;

class MarketKid::Impl
{
public:
  GoodStock basket;
  unsigned long delay;
  TilePos marketPos;
  unsigned long birthTime;
};

MarketKidPtr MarketKid::create(PlayerCityPtr city )
{
  MarketKidPtr ret( new MarketKid( city ) );
  ret->drop();

  return ret;
}

MarketKidPtr MarketKid::create( PlayerCityPtr city, MarketLadyPtr lady )
{
  MarketKidPtr ret( new MarketKid( city ) );
  ret->setPos( lady->pos() );
  ret->_pathwayRef() = lady->pathway();

  ret->drop();

  return ret;
}

MarketKid::MarketKid(PlayerCityPtr city )
  : Walker( city ), _d( new Impl )
{
  _d->delay = 0;
  _d->birthTime = 0;
  _d->basket.setCapacity( 100 );
  _setType( walker::marketKid );

  setName( NameGenerator::rand( NameGenerator::male ) );
}

void MarketKid::setDelay( int delay ) {  _d->delay = delay; }

void MarketKid::send2City( MarketPtr destination )
{
  if( destination.isValid() )
  {
    _d->marketPos = destination->pos();
    _pathwayRef().rbegin();
    _centerTile();
    _city()->addWalker( this );
  }
  else
  {
    deleteLater();
  }
}

void MarketKid::save(VariantMap& stream) const
{
  Walker::save( stream );
  stream[ "basket" ] = _d->basket.save();
  stream[ "delay"  ] = (int)_d->delay;
  stream[ "market" ] = _d->marketPos;
  stream[ "birthTime" ] = (int)_d->birthTime;
}

void MarketKid::load(const VariantMap& stream)
{
  Walker::load( stream );
  _d->basket.load( stream.get( "basket" ).toList() );
  _d->delay = (int)stream.get( "delay" );
  _d->marketPos = stream.get( "market" ).toTilePos();
  _d->birthTime = (int)stream.get( "birthTime" );
}

void MarketKid::timeStep( const unsigned long time )
{
  if( _d->birthTime == 0 )
  {
    _d->birthTime = time;
  }

  if( time - _d->birthTime < _d->delay )
  {
    return;
  }

  Walker::timeStep( time );
}

void MarketKid::_reachedPathway()
{
  Walker::_reachedPathway();

  deleteLater();

  city::Helper cityh( _city() );
  MarketPtr market = cityh.find<Market>( building::market, _d->marketPos );
  if( market.isValid() )
  {
    market->getGoodStore().store( _d->basket, _d->basket.qty() );
  }
}

bool MarketKid::die()
{
  bool created = Walker::die();

  if( !created )
  {
    Corpse::create( _city(), pos(), ResourceGroup::carts, 465, 472 );
    return true;
  }

  return created;
}

void MarketKid::_updateThinks()
{
  StringArray ownThinks;
  ownThinks << "##market_kid_say_1##";
  ownThinks << "##market_kid_say_2##";
  ownThinks << "##market_kid_say_3##";

  setThinks( WalkerThinks::check( this, _city(), ownThinks ) );
}

GoodStock& MarketKid::getBasket(){  return _d->basket;}
