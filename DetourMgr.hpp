#ifndef DETOURMGR_H
#define DETOURMGR_H

#include "./detours.h"

class DetourManager
{
    public:
        template <class T> static MonologieDetours::Detour<T> GetDetour<T>(DWORD offset)
        {
            return reinterpret_cast<MonologieDetours::Detour<T>*>(_detours[offset]);
        }
        
    private:
        static std::map<DWORD, MonologieDetours::DetourBase*> _detours;
};

#endif // DETOURMGR_H
