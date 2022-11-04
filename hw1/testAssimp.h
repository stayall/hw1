#include "DrawableBase.h"
#include <assimp\Importer.hpp>
#include <assimp\postprocess.h>

class Ass : DrawableBase<Ass>
{
public:
	Ass(const char* filename);
};


