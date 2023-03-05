#include "GG/Core/EntitySystem/ComponentNotifier.h"

using namespace gg;

SNotifierList::~SNotifierList()
{
	for ( auto notifier : list )
	{
		notifier->RemoveListener( owner );
	}
	list.Clear();
}