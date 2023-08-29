#pragma once
#include "Model.h"
#include "framework.h"
#include "STL.h"
/// <summary>
/// Format Member as Json
/// </summary>
/// <param name="member"></param>
/// <param name="buffer">Will set this buffer to Json.There will be no \r\n</param>
/// <returns>If success will return STATE_SUCCESS else -1</returns>
int Member2Json(Member* const , char*);
int Json2Member(char* const, Member*);

