#include <limits>
#include <lemonxx/memory/smallobj.hpp>
#include <lemonxx/utility/utility.hpp>

#ifdef max
#undef max
#endif //max

#define MAX_BLOCKSIZE sizeof(ptrdiff_t) * 8

namespace lemon{namespace memory{

	class SmallObjectAllocator : private nocopyable
	{
	private:
		SmallObjectAllocator()
		{
			LEMON_DECLARE_ERRORINFO(errorCode);

			_allocator = LemonCreateSmallObjAllocator(MAX_BLOCKSIZE,sizeof(ptrdiff_t),std::numeric_limits<char>::max(),&errorCode);

			if(LEMON_FAILED(errorCode)) throw Exception(errorCode);
		}
		~SmallObjectAllocator()
		{
			LEMON_DECLARE_ERRORINFO(errorCode);

			LemonReleaseSmallObjAllocator(_allocator);

			if(LEMON_FAILED(errorCode)) throw Exception(errorCode);
		}

	public:

		static SmallObjectAllocator * Instance()
		{
			static SmallObjectAllocator allocator;

			return &allocator;
		}

		void* Alloc(size_t blockSize,LemonErrorInfo * errorCode)
		{
			if(MAX_BLOCKSIZE < blockSize) return new byte_t[blockSize];

			lemon::mutex::scope_lock lock(_mutex);

			return LemonSmallObjAlloc(_allocator,blockSize,errorCode);
		}

		void Free(void * block,size_t blockSize,LemonErrorInfo * errorCode)
		{
			if(MAX_BLOCKSIZE < blockSize) {delete[] (byte_t*)block;return;}

			lemon::mutex::scope_lock lock(_mutex);

			LemonSmallObjFree(_allocator,block,blockSize,errorCode);
		}

	private:

		LemonSmallObjAllocator _allocator;

		lemon::mutex		   _mutex;
	};
}}

LEMONXX_API void* 
	LemonXXGlobalSmallObjAlloc(
	__lemon_in size_t size,
	__lemon_inout LemonErrorInfo *errorCode)
{
	LEMON_RESET_ERRORINFO(*errorCode);

	try
	{
		return lemon::memory::SmallObjectAllocator::Instance()->Alloc(size,errorCode);
	}
	catch(const lemon::Exception &e)
	{
		*errorCode = e.ErrorInfo();
	}

	return NULL;
}

LEMONXX_API void 
	LemonXXGlobalSmallObjFree(
	__lemon_free void * block __lemon_buffer(size),
	__lemon_in size_t size,
	__lemon_inout LemonErrorInfo *errorCode)
{
	LEMON_RESET_ERRORINFO(*errorCode);

	try
	{
		lemon::memory::SmallObjectAllocator::Instance()->Free(block,size,errorCode);
	}
	catch(const lemon::Exception &e)
	{
		*errorCode = e.ErrorInfo();
	}
}
