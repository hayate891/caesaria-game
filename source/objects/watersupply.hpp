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
// Copyright 2012-2015 Dalerank, dalerankn8@gmail.com

#ifndef __CAESARIA_WATER_BUILDGINDS_INCLUDED__
#define __CAESARIA_WATER_BUILDGINDS_INCLUDED__

#include "core/position.hpp"
#include "service.hpp"
#include "core/direction.hpp"

class WaterSource : public Construction
{
public:
  WaterSource( const object::Type type, const Size& size );
  ~WaterSource();
  
  virtual void addWater( const WaterSource& source );
  virtual bool haveWater() const;  
  virtual void timeStep(const unsigned long time);
  virtual void save(VariantMap &stream) const;
  virtual void load(const VariantMap &stream);
  virtual std::string errorDesc() const;
  virtual void broke();

  int water() const;

protected:
  void _setError( const std::string& error );
  virtual void _waterStateChanged() {}
  virtual void _produceWater(const TilePos* points, const int size);
  void _setIsRoad( bool value );
  bool _isRoad() const;
  
  class Impl;
  ScopedPtr< Impl > _d;
};

class Reservoir : public WaterSource
{
public:
  Reservoir();
  ~Reservoir();

  virtual bool build(const city::AreaInfo &info);
  virtual bool canBuild(const city::AreaInfo& areaInfo) const;
  virtual bool isNeedRoad() const;
  virtual void initTerrain(gfx::Tile& terrain);
  virtual void timeStep(const unsigned long time);
  virtual gfx::TilesArray aquifer() const;
  virtual bool getMinimapColor(int &color1, int &color2) const;
  virtual void destroy();
  virtual std::string troubleDesc() const;
  virtual void addWater( const WaterSource& source );
  virtual void initialize(const object::Info& mdata);
  virtual void broke();

  TilePos entry( Direction direction );

private:
  bool _isWaterSource;
  void _dropWater();
  void _waterStateChanged();
  bool _isNearWater( PlayerCityPtr city, const TilePos& pos ) const;
};

#endif // __CAESARIA_WATER_BUILDGINDS_INCLUDED__
