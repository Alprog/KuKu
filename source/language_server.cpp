
#include "language_server.h"

#include <iostream>
#include <fstream>
#include "types.h"
#include "lsp_enums.h"
#include "opened_text_document.h"

Language_server::Language_server()
{
    while (true)
    { 
        nlohmann::json message;
        ide_connection >> message;
        process_message(message);           
    }
}

void Language_server::process_message(nlohmann::json& message)
{
    auto method = message["method"].get<std::string>();

    if (method == "initialize")
        on_initialize(message);
    else if (method == "initialized")
        {} // nothing to do
    else if (method == "textDocument/didOpen")
        on_did_open(message);
    else if (method == "textDocument/didChange")
        on_did_change(message);
    else if (method == "textDocument/completion")
        on_completion(message);
    else if (method == "$/cancelRequest")
        {} // nothing to do
    else
        throw new std::exception("unknown method");
}

void Language_server::on_initialize(nlohmann::json& message)
{
    auto name = message["params"]["clientInfo"]["name"].get<std::string>();

    auto id = message["id"].get<int>();

    nlohmann::json result = {
        { "capabilities", {
            { "textDocumentSync", Text_document_sync_kind::Incremental },
            { "completionProvider", {
                { "resolveProvider", true }
            }},
            { "workspace", {
                { "workspaceFolders", {
                    { "supported", true }
                }}
            }}
        }}
    };

    nlohmann::json response = {
        { "jsonrpc", "2.0" },
        { "id", id },
        { "result", result }
    };

    ide_connection << response;
}

void Language_server::on_did_open(nlohmann::json& message)
{
    auto json = message["params"]["textDocument"];
    auto document = from_json<Opened_text_document>(json);
    auto t = document.text;

    auto b = t.size();
}

void Language_server::on_did_change(nlohmann::json& message)
{
    /*
        "textDocument": {
            "uri": "file:///c%3A/Users/alpro/Desktop/2.txt"
        },
        "position": {
            "line": 5,
            "character": 1
        },
        "context": {
            "triggerKind": 1
        }
    */
}

void Language_server::on_completion(nlohmann::json& message)
{
     /*
        "textDocument": {
            "uri": "file:///c%3A/Users/alpro/Desktop/2.txt",
            "version": 4
        },
        "contentChanges": [
            {
                "range": {
                    "start": {
                        "line": 5,
                        "character": 1
                    },
                    "end": {
                        "line": 5,
                        "character": 1
                    }
                },
                "rangeLength": 0,
                "text": "A"
            }
        ]
    */
}