#include <lemonxx/luabind/lstate.hpp>


LEMONXX_API LemonFixObjectAllocator LemonCreateLuaBindAllocator(__lemon_inout LemonErrorInfo *errorCode)
{
	return LemonCreateFixObjectAllocator(256,errorCode);
}

LEMONXX_API void LemonReleaseLuaBindAllocator(__lemon_inout LemonFixObjectAllocator allocator)
{
	LemonReleaseFixObjectAllocator(allocator);
}