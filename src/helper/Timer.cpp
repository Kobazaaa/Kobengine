// -- Standard Library --
#include <iostream>

// -- Kobengine Includes --
#include "Timer.h"
#include "ConsoleTextSettings.h"


//? ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//? ~~	  Timer	
//? ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

//--------------------------------------------------
//    Behavioural
//--------------------------------------------------
void kobengine::Timer::Start()
{
	m_LastTimePoint = std::chrono::high_resolution_clock::now();
	m_CurrentTimePoint = std::chrono::high_resolution_clock::now();
	m_DeltaTimeSeconds = 0;
	m_SleepTimeSeconds = 0;
}
void kobengine::Timer::Update()
{
	++m_Ticks;

	m_CurrentTimePoint = std::chrono::high_resolution_clock::now();
	m_DeltaTimeSeconds = std::chrono::duration<float>(m_CurrentTimePoint - m_LastTimePoint).count();
	m_LastTimePoint = m_CurrentTimePoint;
	m_TotalTimeSeconds += m_DeltaTimeSeconds;
}

void kobengine::Timer::StartBenchmark()
{
	m_BenchmarkStart = std::chrono::high_resolution_clock::now();
}
float kobengine::Timer::EndBenchmark(bool printResults, const std::string& txt)
{
	m_BenchmarkEnd = std::chrono::high_resolution_clock::now();
	const float delta = std::chrono::duration<float, std::milli>(m_BenchmarkEnd - m_BenchmarkStart).count();

	if (printResults)
	{
		std::cout << DARK_YELLOW_TXT << txt << delta << "ms." << RESET_TXT << "\n";
	}

	return delta;
}


//--------------------------------------------------
//    Accessors
//--------------------------------------------------
float kobengine::Timer::GetDeltaSeconds()
{
	return m_DeltaTimeSeconds;
}
float kobengine::Timer::GetTotalTimeSeconds()
{
	return m_TotalTimeSeconds;
}
float kobengine::Timer::TargetFPS()
{
	return TARGET_FPS;
}
std::chrono::nanoseconds kobengine::Timer::SleepDurationNanoSeconds()
{
	constexpr auto msPerFrame = std::chrono::milliseconds(static_cast<int>(1'000.f / TARGET_FPS));
	const std::chrono::nanoseconds sleep = (m_CurrentTimePoint + msPerFrame - std::chrono::high_resolution_clock::now());

	return sleep;
}
