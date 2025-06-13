#include "coin_manager.h"

void CoinManager::_bind_methods() {
}

void CoinManager::add_coin()
{
	coins++;
	print_line("adding coin");
}
