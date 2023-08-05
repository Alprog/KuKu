#pragma once

#include <string>
#include "json/object.h"
#include "ide_connection.h"
#include "source_project.h"

class language_server
{
public:
	language_server();

private:
	void process_message(json::object& message);
	void on_initialize(json::object& message);
	void on_did_open(json::object& message);
	void on_did_change(json::object& message);
	void on_hover(json::object& message);
	void on_code_action(json::object& message);
	void on_execute_command(json::object& message);
	void on_completion(json::object& message);

	void show_message(std::string text);
	void publish_diagnostics(translation_module& module);

	source_project source_project;
	Ide_connection ide_connection;
};