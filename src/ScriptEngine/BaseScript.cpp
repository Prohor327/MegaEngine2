#include "BaseScript.h"

void Scripts::BaseScript::RegisterProperties()
{

}

void Scripts::BaseScript::Serialize(YAML::Node& node)
{
	for(std::shared_ptr<Property> prop : _properties)
	{
		prop->Serialize(node);
	}
}

void Scripts::BaseScript::Deserialize(YAML::Node& node)
{
	for (std::shared_ptr<Property>  prop : _properties)
	{
		prop->Deserialize(node);
	}
}