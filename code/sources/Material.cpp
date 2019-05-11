#include "Material.hpp"

namespace prz
{
	PSPtr< Material > Material::default_material()
	{
		return PSPtr< Material >();
	}
}