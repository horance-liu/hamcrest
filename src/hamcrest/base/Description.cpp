#include <hamcrest/base/Description.h>

HAMCREST_NS_BEGIN

inline Description& Description::append(const std::string& text)
{
    desc += text;
    return *this;
}

Description& Description::appendText(const std::string& text)
{
    return append(text);
}

Description& Description::appendDescriptionOf(const SelfDescribing& value)
{
    value.describeTo(*this);
    return *this;
}

const std::string& Description::to_s() const
{
    return desc;
}

HAMCREST_NS_END
