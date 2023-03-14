#pragma once

namespace gg
{
	class CTimer
	{
	public:
		CTimer();

		float Restart();

		float GetTotalTime() const;

	private:
		unsigned long _previous;
		unsigned long _start;
	};
} // namespace gg