#pragma once

#define HV_DEBUG_ON 1

#if HV_DEBUG_ON
	#include <iostream>

	#define HV_DEBUG_ASSERT(VAR) if(!(VAR))	__debugbreak();
	#define HV_LOG(...)						DEBUG_MESSAGE_LOG(__VA_ARGS__)
	#define HV_DEBUG(VAR)					VAR	

	template<typename ...Args>
	constexpr static void DEBUG_MESSAGE_LOG(Args&&... args)
	{
		(std::cout << ... << args);
	}
#else
	#define HV_DEBUG_ASSERT(VAR)
	#define HV_LOG(...)
	#define HV_DEBUG(VAR)
#endif