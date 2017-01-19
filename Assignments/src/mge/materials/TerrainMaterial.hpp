#ifndef TERRAINMATERIAL_H
#define TERRAINMATERIAL_H

#include "mge/core/ShaderProgram.hpp"
#include "mge/core/Texture.hpp"
#include "mge/materials/LitMaterial.hpp"

class TerrainMaterial : public LitMaterial
{
    public:
        TerrainMaterial (std::string pHeight, std::string pDifR, std::string pDifG, std::string pDifB, std::string pDifA, std::string pSplat);
        virtual ~TerrainMaterial ();

        virtual void render(Mesh* pMesh, const glm::mat4& pModelMatrix, const glm::mat4& pViewMatrix, const glm::mat4& pProjectionMatrix) override;

    private:
        Texture* _difR;
		Texture* _difG;
		Texture* _difB;
		Texture* _difA;

		Texture* _heightMap;
		Texture* _splatMap;
};

#endif // TEXTUREMATERIAL_H
