/*
    This source file is part of Rigs of Rods
    Copyright 2005-2012 Pierre-Michel Ricordel
    Copyright 2007-2012 Thomas Fischer
    Copyright 2013-2021 Petr Ohlidal

    For more information, see http://www.rigsofrods.org/

    Rigs of Rods is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License version 3, as
    published by the Free Software Foundation.

    Rigs of Rods is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Rigs of Rods. If not, see <http://www.gnu.org/licenses/>.
*/

/// @file
/// @brief Simple text area which displays dashboard data.

#pragma once

#include "BaseDashOverlayElement.h"

#include <Ogre.h>
#include <OgreOverlay.h>
#include <OgreOverlayElementFactory.h>

#include <vector>

namespace RoR {

/// FIXME: rename to "DashPanelOverlayElement"
/// Generic panel, supports multiple animations: "lamp", "series"
/// 
/// Anim "lamp":
///     switches 2 materials: on/off.
///     Materials must have suffix "-on" and "-off". One must be specified in overlay script - the other will be deduced.
/// Anim "series":
///     switches multiple numbered materials.
///     Material names must end with positive integral number. Minimum is 0, max is 500.
class DashLampOverlayElement:
    public Ogre::PanelOverlayElement,
    public BaseDashOverlayElement
{
public:
    static const Ogre::String OVERLAY_ELEMENT_TYPE_NAME;

    DashLampOverlayElement(const Ogre::String& name);
    virtual ~DashLampOverlayElement() {}

    virtual const Ogre::String& getTypeName(void) const override;

    // Animation "lamp"
    void                        locateMaterials();
    bool                        checkMaterialsOk() const;
    void                        setLampOn(bool on);
    // Animation "series"
    bool                        setupAnimSeries();
    void                        updateAnimSeries(int val);
    int                         analyzeSeriesMaterial(Ogre::String material_name);

private:

    // Anim "lamp" data
    Ogre::MaterialPtr m_off_material;
    Ogre::MaterialPtr m_on_material;
    // Anim "series" data
    std::vector<Ogre::MaterialPtr> m_series_materials;
    Ogre::String m_series_base_name;
};

/// Mandatory factory class
class DashLampOverlayElementFactory: public Ogre::OverlayElementFactory
{
public:
    virtual Ogre::OverlayElement* createOverlayElement(const Ogre::String& instanceName) override;
    virtual const Ogre::String& getTypeName() const override;
};

} // namespace RoR
