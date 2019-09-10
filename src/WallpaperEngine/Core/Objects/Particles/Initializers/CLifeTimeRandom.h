#pragma once

#include "WallpaperEngine/Core/Objects/Particles/CInitializer.h"

#include <nlohmann/json.hpp>
#include <irrlicht/irrlicht.h>

namespace WallpaperEngine::Core::Objects::Particles::Initializers
{
    class CLifeTimeRandom : CInitializer
    {
    public:
        const irr::u32 getMinimum () const;
        const irr::u32 getMaximum () const;
    protected:
        friend class CInitializer;

        static CLifeTimeRandom* fromJSON (json data, irr::u32 id);

        CLifeTimeRandom (irr::u32 id, irr::u32 min, irr::u32 max);
    private:
        irr::u32 m_max;
        irr::u32 m_min;
    };
};
