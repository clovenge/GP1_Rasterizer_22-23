#pragma once

#include <cstdint>
#include <vector>

#include "Camera.h"
#include "DataTypes.h"

#include <memory>


struct SDL_Window;
struct SDL_Surface;

namespace dae
{
	class Texture;
	struct Mesh;
	struct Vertex;
	class Timer;
	class Scene;

	class Renderer final
	{
	public:
		Renderer(SDL_Window* pWindow);
		~Renderer();

		Renderer(const Renderer&) = delete;
		Renderer(Renderer&&) noexcept = delete;
		Renderer& operator=(const Renderer&) = delete;
		Renderer& operator=(Renderer&&) noexcept = delete;

		void Update(Timer* pTimer);
		void Render();

		bool SaveBufferToImage() const;
		SDL_Window* m_pWindow{};

		void ToggleColorOutput();
		void ToggleRenderOutput();
		void ToggleNormalMap();
		void ToggleRotation();
	private:

		SDL_Surface* m_pFrontBuffer{ nullptr };
		SDL_Surface* m_pBackBuffer{ nullptr };
		uint32_t* m_pBackBufferPixels{};

		std::unique_ptr<Texture> m_pDiffuseTexture{ nullptr };
		std::unique_ptr<Texture> m_pNormalTexture{ nullptr };
		std::unique_ptr<Texture> m_pGlossTexture{ nullptr };
		std::unique_ptr<Texture> m_pSpecularTexture{ nullptr };
		

		float* m_pDepthBufferPixels{};

		Camera m_Camera{};

		int m_Width{};
		int m_Height{};
		std::vector<Vector3> m_Veritces_ScreenSpace;
		//std::vector<Vertex> m_Veritces_world;
		float m_AspectRatio;
		int m_ColorOutput{0};
		bool m_NormalMapToggle{true};
		bool m_RotationToggle{true};

		//triangle worldSpace
		std::vector<Mesh> m_Meshes =
		{
			Mesh
			{
				{
				},
				{
				},
			PrimitiveTopology::TriangleList
			}
		};

		bool m_IsMeshLoadedIn;
		

		//Function that transforms the vertices from the mesh from World space to Screen space
		void VertexTransformationFunction(Mesh& mesh) const; //W1 Version
		bool IsInTriangle(const std::vector<Vector2>& verticesScreenspace, const Vector2& pixelPos);
		void render_W1_Part1();
		void render_W1_Part2();
		void render_W1_Part3();
		void render_W1_Part4();
		void render_W1_Part5();

		void render_W2_Part1();

		void render_W3_Part1();
		void render_W3_Part2();
		void render_W4_Part1();

		float Remap(float value, float minValue, float maxValue);
		bool FustrumCulling(const Vector3 v0, const Vector3 v1, const Vector3 v2);
		void ToScreenSpace(Vector4& v0, Vector4& v1, Vector4& v2);

		void BoundingBox(Vector2& topLeft, Vector2& bottomRight, std::vector<Vector2> v);
		

		ColorRGB PixelShading(const Vertex_Out& v);

		enum class RenderState
		{
			observedArea, lambert, phong, combined
		};

		RenderState m_CurrentRenderState;


		

	};
}
