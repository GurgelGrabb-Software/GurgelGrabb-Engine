#pragma once
#include <string>

#define DECLARE_COMPONENT( type ) virtual const std::string GetName() const override;
#define DEFINE_COMPONENT( type )                                                                                                                                                                       \
	const std::string gg::type::GetName() const                                                                                                                                                        \
	{                                                                                                                                                                                                  \
		return #type;                                                                                                                                                                                  \
	}

namespace gg
{
	class CEntity;

	class CComponent
	{
	public:
		template < typename TType, typename... TArgs >
		static TType* Instantiate( CEntity& owner, TArgs&&... args )
		{
			return new TType( owner, args... );
		}

	public:
		CComponent() = delete;
		CComponent( CEntity& owner );
		virtual ~CComponent();
		virtual const std::string GetName() const;

		CEntity& GetOwner();
		const CEntity& GetOwner() const;

	private:
		CEntity* _ownerPtr;
	};
} // namespace gg