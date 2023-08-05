
#include "test.h"

#include "streams.h"
#include "unicode_streams.h"
#include "text_document.h"
#include <fstream>
#include "parser.h"

#include "virtual_machine.h"
#include "string.h"
#include "chunk.h"
#include "instruction_type.h"
#include "routine.h"

#include "source_project.h"

#include "mem/tracker.h"
#include "instructions.h"
#include <memory>

void test()
{
	chunk chunk;
	chunk.write(instruction_PUSH_INT{111});
	chunk.write(instruction_PUSH_INT{222});
	chunk.write(instruction_INT_ADD{});
	chunk.write(instruction_PRINT{});

	chunk.write(instruction_PUSH_INT{ 2 });
	chunk.write(instruction_PUSH_INT{ 4 });
	chunk.write(instruction_INT_POWER{});
	chunk.write(instruction_PRINT{});
	chunk.write(instruction_END{});

	routine routine(chunk.get_start_pointer());	
	routine.run();


	kuku::string s1("abc");
	kuku::string s2(u"abc");
	kuku::string s3(U"abc");

	auto a1 = s1.get_character(1);
	auto a2 = s2.get_character(1);
	auto a3 = s3.get_character(1);
	s3.try_shrink();
	auto a3s = s3.get_character(1);


	source_project project;
	project.add_file("C:/kuku/data/main.kuku");
	project.process_all();
	project.print_info();

	project.clear_all();
}