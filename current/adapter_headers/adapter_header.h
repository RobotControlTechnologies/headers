
#ifndef ADAPTER_HEADER_H
#define ADAPTER_HEADER_H

#ifdef _WIN32
#define PREFIX_FUNC_DLL __declspec(dllexport)
#else
#define PREFIX_FUNC_DLL
#endif

#include "vRobot_header.h"
#include <string>

class CAdapter
{
public:
    virtual bool Init() = 0;
    virtual CvRobot* GetRobot(vRobotParams Params) = 0;
    virtual void FreeRobot(std::string ID) = 0;
    virtual void Release() = 0;
    virtual void PauseSim(bool value) = 0;
    virtual void CreateWorld(double x, double y, double z) = 0;
    virtual void DestroyWorld() = 0;
    virtual void AddCollisionToExcept(std::string collision) = 0;
    virtual void RemoveCollisionFromExcept(std::string collision) = 0;
    virtual bool IsCollisionInExcept(std::string collision) = 0;
    virtual ~CAdapter() {};
};

PREFIX_FUNC_DLL CAdapter* GetAdapter();

#endif /* ADAPTER_HEADER_H */

