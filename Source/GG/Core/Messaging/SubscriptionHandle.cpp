#include "GG/Core/Messaging/SubscriptionHandle.h"

#include "GG/Core/Messaging/MessageQueue.h"

using namespace gg;

SSubscriptionHandle::SSubscriptionHandle()
	: Identifier( 0 )
	, MessageType( 0 )
	, Parent( nullptr )
{
}

SSubscriptionHandle::SSubscriptionHandle( size_t InIdentifier, size_t InMessageType, CMessageQueue* InParent )
	: Identifier( InIdentifier )
	, MessageType( InMessageType )
	, Parent( InParent )
{
}

void SSubscriptionHandle::operator=( const SSubscriptionHandle& InRHS )
{
	Identifier = InRHS.Identifier;
	MessageType = InRHS.MessageType;
	Parent = InRHS.Parent;
}

void SSubscriptionHandle::Unregister()
{
	Parent->Unsubscribe( *this );
}

size_t SSubscriptionHandle::GetIdentifier() const
{
	return Identifier;
}

size_t SSubscriptionHandle::GetMessageType() const
{
	return MessageType;
}
