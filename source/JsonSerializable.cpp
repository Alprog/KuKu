
#include "JsonSerializable.h"
#include "JsonScheme.h"
#include "JsonField.h"

nlohmann::json JsonSerializable::toJson()
{
    auto json = nlohmann::json::object();

    for (auto field : this->GetJsonScheme().fields)
    {
        field->write(json, this);
    }

    return json;
}