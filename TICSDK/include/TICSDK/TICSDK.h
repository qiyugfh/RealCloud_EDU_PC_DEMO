#pragma once
#ifndef TICSDK_H_
#define TICSDK_H_

#ifdef TICSDK_EXPORTS
#define TICSDK_API __declspec(dllexport)
#else
#define TICSDK_API __declspec(dllimport)
#endif

#include "TICManager.h"
#include "TICWindowShareMgr.h"
#include "TICClassroomOption.h"







#endif