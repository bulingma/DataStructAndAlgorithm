/******************************************************************************************
* Data Structures and Algorithm in C++ .
* Author: Yuguang Ma
* All rights reserved.
******************************************************************************************/

#include <chrono>
#include "../../_share/util.h"
#include "LRUCache.h"
#define EXPAND_MULTIPLE		(20)					//测试数据扩大倍数
#define CAHCE_SIZE_MUTIPLE	(EXPAND_MULTIPLE/4)		//Cache容量扩大倍数
int testID = 0;										//测试编号

/******************************************************************************************
* 测试两种不同解决方案的性能
******************************************************************************************/
template <typename T_KEY, typename T_VALUE>			//元素类型
void  testLRUCachePerformance(int CacheSize) {
	printf("\n  ==== Test %2d. testLRUCachePerformance() ,which size = %d \n", testID++, CacheSize);
	LRUCacheUseMap<int, int> oLRUcache;
	LRUCacheUseHashtable<int, int> oLRUcacheUseHashtable;

	std::chrono::steady_clock::time_point  timeForLRUCacheUseMapBegin = std::chrono::steady_clock::now();
	for (int i = 0; i < EXPAND_MULTIPLE * CacheSize; i++)
	{
		oLRUcache.setCacheSize(CAHCE_SIZE_MUTIPLE * CacheSize);
		oLRUcache.set(i, i);
		oLRUcache.get(i);
	}
	auto timeForLRUCacheUseMapEnd = std::chrono::steady_clock::now();
	std::chrono::duration<double> time_span = std::chrono::duration_cast<std::chrono::duration<double>>(timeForLRUCacheUseMapEnd - timeForLRUCacheUseMapBegin);
	std::cout << "set and get " << EXPAND_MULTIPLE * CacheSize << " times using LRUCacheUseMap takes " << time_span.count() << " seconds." << endl;


	timeForLRUCacheUseMapBegin = std::chrono::steady_clock::now();
	for (int i = 0; i < EXPAND_MULTIPLE * CacheSize; i++)
	{
		oLRUcacheUseHashtable.setCacheSize(CAHCE_SIZE_MUTIPLE * CacheSize);
		oLRUcacheUseHashtable.set(i, i);
		oLRUcacheUseHashtable.get(i);
	}
	timeForLRUCacheUseMapEnd = std::chrono::steady_clock::now();
	time_span = std::chrono::duration_cast<std::chrono::duration<double>>(timeForLRUCacheUseMapEnd - timeForLRUCacheUseMapBegin);
	std::cout << "set and get " << EXPAND_MULTIPLE * CacheSize << " times using LRUcacheUseHashtable takes " << time_span.count() << " seconds." << endl;

}

/******************************************************************************************
* 测试LRUCache
******************************************************************************************/
template <typename T_KEY, typename T_VALUE>			//元素类型
void  testLRUCache(int CacheSize) {
	printf("\n  ==== Test %2d. Generate one LRUCacheUseMap ,which size %d by random insertions\n", testID++, CacheSize);
	LRUCacheUseMap<int, int> oLRUcache;
	oLRUcache.setCacheSize((unsigned int)CacheSize);
	int imaxElement = 10 * CacheSize;
	int ivalue = 0;
	for (int i = 0; i < imaxElement; i++) {
		Rank k = dice(imaxElement);
		if (dice(2))
		{
			//printf("set(%d) ", k);				//set(k,k)
			oLRUcache.set(k, k);
			//printf(" = %d  \n ", k);				//set(k,k)
		}
		else
		{
			//printf("get(%d) ", k);				//get(k)
			ivalue = oLRUcache.get(k);
			//printf(" = %d \n", ivalue );		
		}
	}
	//oLRUcache.printLRUCacheList();

	printf("\n  ==== Test %2d. Generate one LRUCacheUseHashtable ,which size %d by random insertions\n", testID++, CacheSize);
	LRUCacheUseHashtable<int, int> oLRUcacheUseHashtable;
	oLRUcacheUseHashtable.setCacheSize((unsigned int)CacheSize);
	for (int i = 0; i < imaxElement; i++) {
		Rank k = dice(imaxElement);
		if (dice(2))
		{
			//printf("set(%d) ", k);				//set(k,k)
			oLRUcacheUseHashtable.set(k, k);
			//printf(" = %d  \n ", k);				//set(k,k)
		}
		else
		{
			//printf("get(%d) ", k);				//get(k)
			ivalue = oLRUcacheUseHashtable.get(k);
			//printf(" = %d \n", ivalue);
		}
	}
	//oLRUcacheUseHashtable.printLRUCacheList();

	//性能对比
	testLRUCachePerformance<int, int>(CacheSize);

	return;
}

/******************************************************************************************
* 测试LRUCache
******************************************************************************************/
int main()
{
	int iTestSize = 2000;
	srand((unsigned int)time(NULL));
	testLRUCache<int, int>(iTestSize); //元素类型可以在这里任意选择
	return 0;
}

