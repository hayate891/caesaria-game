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

#include "dictionary.hpp"
#include "game/settings.hpp"
#include "pushbutton.hpp"
#include "core/stringhelper.hpp"
#include "texturedbutton.hpp"
#include "label.hpp"
#include "core/logger.hpp"
#include "objects/metadata.hpp"

namespace gui
{

class DictionaryWindow::Impl
{
public:
  Label* lbTitle;
  Label* lbText;
  TexturedButton* btnExit;
};

DictionaryWindow::DictionaryWindow( Widget* parent )
  : Widget( parent, -1, Rect( 0, 0, 1, 1 ) ), _d( new Impl )
{
  setupUI( GameSettings::rcpath( "/gui/dictionary.gui" ) );

  setPosition( Point( parent->getWidth() - getWidth(), parent->getHeight() - getHeight() ) / 2 );

  _d->btnExit = findChild<TexturedButton*>( "btnExit", true );
  _d->lbText = findChild<Label*>( "lbText", true );

  CONNECT( _d->btnExit, onClicked(), this, DictionaryWindow::deleteLater );
}

void DictionaryWindow::show(Widget* parent, TileOverlay::Type type)
{
  DictionaryWindow* wnd = new DictionaryWindow( parent );
  wnd->_d->lbText->setText( MetaDataHolder::getDescription( type ) );
}

DictionaryWindow::~DictionaryWindow( void )
{
}

}//end namespace gui
