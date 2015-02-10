#pragma once

#include <D3D11.h>
#include <D3DX10math.h>
#include <fstream>
#include <sstream>
#include "TextureClass.h"

struct VertexType
{
	D3DXVECTOR3 position;
	D3DXVECTOR4 color;
};

struct TextureVertexType
{
	D3DXVECTOR3 position;
	D3DXVECTOR2 texture;
};

struct LightVertexType
{
	D3DXVECTOR3 position;
	D3DXVECTOR2 texture;
	D3DXVECTOR3 normal;
};

struct ModelType
{
	float x;
	float y;
	float z;
	float tu;
	float tv;
	float nx;
	float ny;
	float nz;
};

class ModelClass
{
public:
	ModelClass(void);
	~ModelClass(void);
	bool Initialize(ID3D11Device*);
	bool Initialize(ID3D11Device*, WCHAR*);
	bool Initialize(ID3D11Device*, char*, WCHAR*);
	void Shutdown();
	void Render(ID3D11DeviceContext*);
	int GetIndexCount();
	ID3D11ShaderResourceView* GetTexture();

private:
	bool InitializeBuffers(ID3D11Device*);
	void ShutdownBuffers();
	void RenderBuffers(ID3D11DeviceContext*);
	bool LoadTexture(ID3D11Device*, WCHAR*);
	void ReleaseTexture();
	bool LoadModel(char*);
	bool LoadBlenderModel(char*);
	void ReleaseModel();

	ID3D11Buffer* VertexBuffer;
	ID3D11Buffer* IndexBuffer;
	int VertexCount;
	int IndexCount;
	TextureClass* Texture;
	ModelType* Model;
};

