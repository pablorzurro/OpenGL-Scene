/**
 * @file Renderer.hpp
 * @author Pablo Rodriguez (przuro@gmail.com)
 * @brief
 * @version 0.1
 * @date 09-05-2019
 *
 * @copyright Copyright (c) 2019
 *
 */

#ifndef OPENGL_SCENE_RENDERER_H_
#define OPENGL_SCENE_RENDERER_H_

#include <Model.hpp>
#include <Mesh.hpp>
#include <Material.hpp>

#include <Declarations.hpp>

namespace prz
{

	using ObjectMeshes = PMap< Transform*, PList< Mesh* > >;
	using ObjMeshesByMaterial  = PMap< Material*, ObjectMeshes >;
	using ObjMeshesByMaterialPerShaderProg =  PMap< Shader_Program*, ObjMeshesByMaterial>;

	class Renderer
	{
	public:

		Renderer(Scene& sceneOwner) :
			owner_(sceneOwner)
		{}

		~Renderer()
		{}

	public:

		void render()
		{
			for (auto& shaderMaterialPair : shaderPrograms_)
			{
				// bind the shader program if the materials in use is more than zero 

				for (auto& materialTransformPair : shaderMaterialPair.second)
				{
					bool isUsed = 0;
					for (auto& transformModelPair : materialTransformPair.second)
					{
						if (transformModelPair.first->isVisible())
						{
							isUsed = true;
							break;
						}
					}
					if (isUsed)
					{
						materialTransformPair.first->use();

						for (auto& transformMeshListPair : materialTransformPair.second)
						{
							// Use material

							for (auto& piece : transformMeshListPair.second)
							{
								piece->draw();
							}
						}
					}
				}
			}
		}

	private:

		ObjMeshesByMaterialPerShaderProg shaderPrograms_;

	private:

		Scene& owner_;

	};

} // !namespace prz 

#endif // !OPENGL_SCENE_RENDERER_H_
