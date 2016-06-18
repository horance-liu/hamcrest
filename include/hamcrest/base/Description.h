#ifndef HB4FDA3F1_A2B1_407F_922D_FF7A05FBB0D4
#define HB4FDA3F1_A2B1_407F_922D_FF7A05FBB0D4

#include <hamcrest/internal/SelfDescribingContainer.h>
#include <ccinfra/algo/String.h>

HAMCREST_NS_BEGIN

struct Description
{
    Description& appendText(const std::string& text);
    Description& appendDescriptionOf(const SelfDescribing& value);

    template<typename T>
    Description& appendValue(const T& value)
    {
        desc += "<";
        desc += cub::toTypeAndValueString(value);
        desc += ">";
        return *this;
    }

    template <typename C>
    Description& appendList
        ( const std::string& start
        , const std::string& separator
        , const std::string& end
        , const C& container)
    {
        return append(start)
              .doAppendList(separator, container)
              .append(end);
    }

    template <typename C>
    Description& appendValueList
        ( const std::string& start
        , const std::string& separator
        , const std::string& end
        , const C& container)
    {
        return appendList(start, separator, end, SelfDescribingContainer<C>(container));
    }

    const std::string& to_s() const;

private:
    template <typename C>
    Description& doAppendList
        (const std::string& separator, const C& c)
    {
        auto separate = false;
        for (auto &e : c)
        {
            if (separate) append(separator);
            appendDescriptionOf(e);
            separate = true;
        }
        return *this;
    }

    Description& append(const std::string&);

private:
    std::string desc;
};

// !!! because of circular dependency, must implement here.
template <typename T>
void SelfDescribingValue<T>::describeTo(Description& desc) const
{
    desc.appendValue(value);
}

HAMCREST_NS_END

#endif
