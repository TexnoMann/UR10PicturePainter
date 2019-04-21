#include "property_manager.h"

namespace prop
{
	static std::unique_ptr<ptree> propTree;
	void init(std::string path)
	{
		propTree.reset(new ptree());
		boost::property_tree::read_json(path, *propTree);
	}

	ptree & tree()
	{
		return *propTree;
	}

}