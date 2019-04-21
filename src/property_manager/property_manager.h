#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

#include <memory>

using boost::property_tree::ptree;

namespace prop
{

	void init(std::string path);
	ptree & tree();

	template <typename T>
	std::vector<T> getVector(ptree const& pt, std::string key)
	{
		std::vector<T> r;
		for (auto& item : pt.get_child(key))
			r.push_back(item.second.get_value<T>());
		return r;
	}
}