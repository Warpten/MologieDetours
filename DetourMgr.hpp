// Made via github, no hate if its broken tyvm
#ifndef DETOURMGR_H
#define DETOURMGR_H

#include "./detours.h"

#include <stdlib.h>
#include <map>

// We could use MologieDetours::adress_type but that's fugly and I don't usually rewrite 3rd party stuff
#if defined(MOLOGIE_DETOURS_HDE_32)
typedef uint32_t ADRESS;
#elif defined(MOLOGIE_DETOURS_HDE_64)
typedef uint64_t ADRESS;
#endif

class DetourManager
{
    public:
        template <class T> static MologieDetours::Detour<T>* GetDetour(ADRESS offset) const
        {
            return reinterpret_cast<MologieDetours::Detour<T>*>(_detours[offset]);
        }
        
        template <class T> static bool CreateDetour(ADRESS offset, T source, T detour)
        {
            try
            {
                _detours[offset] = new MologieDetours::Detour<T>(source, detour);
                return true;
            }
            catch (DetourException &)
            {
                return false;
            }
        }
        
        template <class T> T GetOriginalFunction(ADRESS offset) const
        {
            return _detours[offset].GetOriginalFunction();
        }
        
        static bool ClearDetour(ADRESS offset)
        {
            if (_detours.find(offset) == _detours.end())
                return false;
            delete _detours[offset];
            _detours.erase(offset);
            return true;
        }
        
    private:
        static std::map<ADRESS, MonologieDetours::DetourBase*> _detours;
};

#endif // DETOURMGR_H
