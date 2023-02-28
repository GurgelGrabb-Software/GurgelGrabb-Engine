#pragma once

namespace gg
{
	class IServiceProvider;

	enum class ESystemTickGroup
	{
		PreRender,
		PostRender,
	};

	class CSystem
	{
	public:
		virtual ~CSystem() { }
		virtual ESystemTickGroup GetTickGroup() const = 0;

		/// @brief Called before first tick
		/// @param serviceProvider Service provider
		virtual void Start( IServiceProvider& serviceProvider ) { }

		/// @brief Called each frame
		/// @param serviceProvider Service provider
		virtual void Tick( IServiceProvider& serviceProvider ) { }
	};
} // namespace gg
