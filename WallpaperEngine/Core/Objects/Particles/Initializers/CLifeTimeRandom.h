#pragma once

#include "../CInitializer.h"

#include <nlohmann/json.hpp>
#include <irrlicht/irrlicht.h>

namespace WallpaperEngine::Core::Objects::Particles::Initializers
{
    class CLifeTimeRandom : CInitializer
    {
    public:
        irr::u32 getMinimum ();
        irr::u32 getMaximum ();
    protected:
        friend class CInitializer;

        static CLifeTimeRandom* fromJSON (json data, irr::u32 id);

        CLifeTimeRandom (irr::u32 id, irr::u32 min, irr::u32 max);
    private:
        irr::u32 m_max;
        irr::u32 m_min;
    };
};