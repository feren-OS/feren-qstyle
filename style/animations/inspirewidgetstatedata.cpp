/*************************************************************************
 * Copyright (C) 2014 by Hugo Pereira Da Costa <hugo.pereira@free.fr>    *
 *                                                                       *
 * This program is free software; you can redistribute it and/or modify  *
 * it under the terms of the GNU General Public License as published by  *
 * the Free Software Foundation; either version 2 of the License, or     *
 * (at your option) any later version.                                   *
 *                                                                       *
 * This program is distributed in the hope that it will be useful,       *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 * GNU General Public License for more details.                          *
 *                                                                       *
 * You should have received a copy of the GNU General Public License     *
 * along with this program; if not, write to the                         *
 * Free Software Foundation, Inc.,                                       *
 * 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA .        *
 *************************************************************************/

#include "inspirewidgetstatedata.h"

namespace Inspire
{

    //______________________________________________
    bool WidgetStateData::updateState( bool value )
    {
        if( !_initialized )
        {

            _state = value;
            _initialized = true;
            return false;

        } else if( _state == value ) {

            return false;

        } else {

            _state = value;
            animation().data()->setDirection( _state ? Animation::Forward : Animation::Backward );
            if( !animation().data()->isRunning() ) animation().data()->start();
            return true;

        }

    }

}
