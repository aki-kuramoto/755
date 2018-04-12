template <typename NUMBER_TYPE>
NUMBER_TYPE calculateGcdWithEuclidean(NUMBER_TYPE fst, NUMBER_TYPE snd)
{
	if (fst <= 0) { fst *= -1; }
	if (snd <= 0) { snd *= -1; }
	
	while (fst != snd)
	{
		if (fst > snd)
		{
			fst -= snd;
		}
		else
		{
			snd -= fst;
		};
	};
	
	return fst;
};

#include <iostream>
#include <stdlib.h>
int main(int argc, const char** argv)
{
	long timesPerSecond = 1000000; // 1000
	long framesPerSecond = 60; // 60
	long baseTime = timesPerSecond / framesPerSecond; // 16
	long remaindered = timesPerSecond % framesPerSecond; // 40
	
	long gcd = calculateGcdWithEuclidean(framesPerSecond, remaindered); // 20
	long cycle = framesPerSecond / gcd; // 3
	long longSpanCount = remaindered / gcd; // 2
	std::cout << "baseTime:" << baseTime << std::endl;
	std::cout << "remaindered:" << remaindered << std::endl;
	std::cout << "gcd:" << gcd << std::endl;
	std::cout << "cycle:" << cycle << std::endl;
	std::cout << "longSpanCount:" << longSpanCount << std::endl;
	
	// assertEqual(timesPerSecond, (cycle * gcd * baseTime) + (longSpanCount * gcd));
	long* pTimeTable = (long*)malloc(sizeof(long) * cycle);
	for (int i = 0; i < cycle; i += 1)
	{
		pTimeTable[i] = baseTime + ((i < longSpanCount) ? 1 : 0);
		std::cout << i << ":" << pTimeTable[i] << std::endl;
	}
	free(pTimeTable);
	
	return 0;
}
