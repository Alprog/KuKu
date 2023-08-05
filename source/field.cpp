
#include "field.h"

field::field(user_class& owner_class, std::string name, data_type type, int instance_offset)
    : owner_class{ owner_class }
    , name{ name }
    , type{ type }
    , instance_offset{ instance_offset }
{
}
