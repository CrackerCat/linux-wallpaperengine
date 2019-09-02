#include "CParticle.h"
#include "../../../FileSystem/utils.h"

#include <irrlicht/irrlicht.h>

using namespace WallpaperEngine::Core::Objects::Particles;

CParticle* CParticle::fromFile (
    const irr::io::path& filename,
    irr::u32 id,
    std::string name,
    const irr::core::vector3df& origin,
    const irr::core::vector3df& scale)
{
    json data = json::parse (WallpaperEngine::FileSystem::loadFullFile (filename));
    json::const_iterator controlpoint_it = data.find ("controlpoint");
    json::const_iterator starttime_it = data.find ("starttime");
    json::const_iterator maxcount_it = data.find ("maxcount");
    json::const_iterator emitter_it = data.find ("emitter");
    json::const_iterator initializer_it = data.find ("initializer");

    if (starttime_it == data.end ())
    {
        throw std::runtime_error ("Particles must have start time");
    }

    if (maxcount_it == data.end ())
    {
        throw std::runtime_error ("Particles must have maximum count");
    }

    if (emitter_it == data.end ())
    {
        throw std::runtime_error ("Particles must have emitters");
    }

    if (initializer_it == data.end ())
    {
        throw std::runtime_error ("Particles must have initializers");
    }

    CParticle* particle = new CParticle (
        *starttime_it,
        *maxcount_it,
        id,
        name,
        origin,
        scale
    );

    if (controlpoint_it != data.end ())
    {
        json::const_iterator cur = (*controlpoint_it).begin ();
        json::const_iterator end = (*controlpoint_it).end ();

        for (; cur != end; cur ++)
        {
            particle->insertControlPoint (
                    CControlPoint::fromJSON (*cur)
            );
        }
    }

    json::const_iterator cur = (*emitter_it).begin ();
    json::const_iterator end = (*emitter_it).end ();

    for (; cur != end; cur ++)
    {
        particle->insertEmitter (
                CEmitter::fromJSON (*cur)
        );
    }

    cur = (*initializer_it).begin ();
    end = (*initializer_it).end ();

    for (; cur != end; cur ++)
    {
        particle->insertInitializer (
                CInitializer::fromJSON (*cur)
        );
    }

    return particle;
}

CParticle::CParticle (
        irr::u32 starttime,
        irr::u32 maxcount,
        irr::u32 id,
        std::string name,
        const irr::core::vector3df& origin,
        const irr::core::vector3df& scale):
        CObject (true, id, std::move(name), origin, scale, irr::core::vector3df ()),
        m_starttime (starttime),
        m_maxcount (maxcount)
{
}

std::vector<CEmitter*>* CParticle::getEmitters ()
{
    return &this->m_emitters;
}

std::vector<CControlPoint*>* CParticle::getControlPoints ()
{
    return &this->m_controlpoints;
}

std::vector<CInitializer*>* CParticle::getInitializers ()
{
    return &this->m_initializers;
}

void CParticle::insertControlPoint (CControlPoint* controlpoint)
{
    this->m_controlpoints.push_back (controlpoint);
}

void CParticle::insertEmitter (CEmitter* emitter)
{
    this->m_emitters.push_back (emitter);
}

void CParticle::insertInitializer (CInitializer* initializer)
{
    this->m_initializers.push_back (initializer);
}