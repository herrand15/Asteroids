#pragma once

#ifndef TIME_MANAGER_HPP
#define TIME_MANAGER_HPP

#if defined(_WIN32) || defined(_WIN64)   // Windows system specific
#include <windows.h>
#else					// Unix based system specific
#include <sys/time.h>
#endif

namespace Engine
{
	class TimeManager
	{
	public:
		/* =============================================================
		* CTOR
		* ============================================================= */

		TimeManager();

		/* =============================================================
		* DTOR
		* ============================================================= */

		~TimeManager();

		/* =============================================================
		* PUBLIC FUNCTIONS
		* ============================================================= */

		void    Start();
		void    Stop();
		double  getElapsedTime();  // By default elapsed time is returned in seconds.
		double  getElapsedTimeInSeconds();  // Returns elapsed time in seconds.
		double  getElapsedTimeInMicroseconds();  // Returns elapsed time in microseconds.
		double  getElapsedTimeInMilliseconds();  // Returns elapsed time in milliseconds.
	private:
		/* =============================================================
		* MEMBERS
		* ============================================================= */

		double m_startTimeInMicroSeconds;
		double m_endTimeInMicroSeconds;
		int    m_stopped;

#ifdef WIN32
		LARGE_INTEGER m_frequency;
		LARGE_INTEGER m_startCount;
		LARGE_INTEGER m_endCount;
#else
		timeval m_startCount;
		timeval m_endCount;
#endif
	};
}

#endif // _TIME_MANAGER_H_