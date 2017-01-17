#ifndef TERRAINMATERIAL_H
#define TERRAINMATERIAL_H

#include "mge/core/ShaderProgram.hpp"
#include "mge/core/Texture.hpp"
#include "mge/materials/AbstractMaterial.hpp"

/**
 * Simple single texture material, this is a sample which doesn't cache anything upfront and
 * passes in separate matrices for the MVP calculation
 */
class TerrainMaterial : public AbstractMaterial
{
    public:
        TerrainMaterial (Texture* pDiffuseTexture, Texture* pHeightMap);
        virtual ~TerrainMaterial ();

        virtual void render(Mesh* pMesh, const glm::mat4& pModelMatrix, const glm::mat4& pViewMatrix, const glm::mat4& pProjectionMatrix) override;

        void setDiffuseTexture (Texture* pDiffuseTexture);

    protected:
    private:
        static ShaderProgram* _shader;
        static void _lazyInitializeShader();

		static GLint _uMVPMatrix;

        Texture* _diffuseTexture;
		Texture* _heightMap;

        TerrainMaterial(const TerrainMaterial&);
        TerrainMaterial& operator=(const TerrainMaterial&);

};

#endif // TEXTUREMATERIAL_H
