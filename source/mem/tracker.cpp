
#include "tracker.h"
#include "Console.h"
#include "unicode.h"

mem::tracker mem::tracker::instance;

mem::tracker::~tracker()
{
	print_diagnostics();
}

void mem::tracker::print_diagnostics()
{
	instance.enabled = false;
	{
		Console::write_line("Memory: " + std::to_string(instance.count) + " (" + std::to_string(instance.total_size) + " bytes)");
	}
	instance.enabled = true;
}

void mem::tracker::allocate(int size)
{
	if (enabled)
	{
		count++;
		total_size += size;
	}
}

void mem::tracker::deallocate(int size)
{
	if (enabled)
	{
		count--;
		total_size -= size;
	}
}