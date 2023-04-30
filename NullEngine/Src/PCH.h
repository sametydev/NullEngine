#pragma once

#define _CRT_SECURE_WARNINGS
#define WIN32_LEAN_AND_MEAN

#include <Windows.h>

#include <string>
#include <vector>
#include <memory>

#include <Core/TypeDecl.h>
#include <Core/Log.h>

#define SAFE_RELEASE(x) if(x) {x->Release(); x = nullptr;}
#define SAFE_DELETE(x) if(x) {delete x; x = nullptr;}

