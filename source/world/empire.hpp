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
// Copyright 2012-2014 Dalerank, dalerankn8@gmail.com

#ifndef __CAESARIA_EMPIRE_H_INCLUDED__
#define __CAESARIA_EMPIRE_H_INCLUDED__

#include "core/scopedptr.hpp"
#include "predefinitions.hpp"
#include "vfs/path.hpp"
#include "core/referencecounted.hpp"
#include "core/serializer.hpp"
#include "good/good.hpp"

namespace world
{

class Empire : public ReferenceCounted, public Serializable
{
public:
  static EmpirePtr create();
  virtual ~Empire();
  CityList cities() const;

  CityPtr findCity( const std::string& name ) const;
  CityPtr addCity( CityPtr city );
  CityPtr initPlayerCity( CityPtr city );
  void payTax( const std::string& cityname, unsigned int money );

  ObjectList objects() const;
  ObjectPtr findObject( const std::string& name ) const;
  void addObject( ObjectPtr obj );

  void initialize( vfs::Path filename, vfs::Path filemap );
  void timeStep( unsigned int time );

  const EmpireMap& map() const;
  Emperor& emperor();
  CityPtr rome() const;

  void createTradeRoute( std::string start, std::string stop );

  TraderoutePtr findRoute( unsigned int index );
  TraderoutePtr findRoute( const std::string& start, const std::string& stop );  

  TraderouteList tradeRoutes( const std::string& startCity );
  TraderouteList tradeRoutes();

  virtual void save( VariantMap& stream ) const;
  virtual void load( const VariantMap& stream );

  void setCitiesAvailable( bool value );
  unsigned int workerSalary() const;
  bool isAvailable() const;
  void setAvailable( bool value );

  void setPrice( Good::Type gtype, int buy, int sell );
  void changePrice( Good::Type gtype, int buy, int sell );
  void getPrice( Good::Type gtype, int& buy, int& sell ) const;

private:
  Empire();

  class Impl;
  ScopedPtr< Impl > _d;
};

struct GovernorRank
{
  std::string rankName;
  std::string prettyName;
  unsigned int salary;
};

typedef std::vector<GovernorRank> GovernorRanks;

class EmpireHelper 
{
public:
  static unsigned int getTradeRouteOpenCost( EmpirePtr empire, const std::string& start, const std::string& stop );
  static GovernorRanks getRanks();
};

}//end namespace world

#endif //__CAESARIA_EMPIRE_H_INCLUDED__
