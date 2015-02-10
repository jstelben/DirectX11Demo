#include "ModelClass.h"


ModelClass::ModelClass(void)
{
	VertexBuffer = nullptr;
	IndexBuffer = nullptr;
	Texture = nullptr;
	Model = nullptr;
}


ModelClass::~ModelClass(void)
{
}


bool ModelClass::Initialize(ID3D11Device* device)
{
	bool result;

	result = InitializeBuffers(device);
	if(!result)
	{
		return false;
	}

	return true;
}

bool ModelClass::Initialize(ID3D11Device* device, WCHAR* textureFileName)
{
	bool result;

	result = InitializeBuffers(device);
	if(!result)
	{
		return false;
	}

	result = LoadTexture(device, textureFileName);
	if(FAILED(result))
	{
		return false;
	}

	return true;
}

bool ModelClass::Initialize(ID3D11Device* device, char* modelFileName, WCHAR* textureFileName)
{
	bool result;

	result = LoadModel(modelFileName);
	if(!result)
	{
		return false;
	}

	result = InitializeBuffers(device);
	if(!result)
	{
		return false;
	}

	result = LoadTexture(device, textureFileName);
	if(FAILED(result))
	{
		return false;
	}

	return true;
}

void ModelClass::Shutdown()
{
	ReleaseTexture();
	ShutdownBuffers();
	ReleaseModel();
}

void ModelClass::Render(ID3D11DeviceContext* deviceContext)
{
	RenderBuffers(deviceContext);
}

int ModelClass::GetIndexCount()
{
	return IndexCount;
}

ID3D11ShaderResourceView* ModelClass::GetTexture()
{
	return Texture->GetTexture();
}

bool ModelClass::InitializeBuffers(ID3D11Device* device)
{
	LightVertexType* vertices;
	unsigned long* indices;
	D3D11_BUFFER_DESC vertexBufferDesc;
	D3D11_BUFFER_DESC indexBufferDesc;
	D3D11_SUBRESOURCE_DATA vertexData;
	D3D11_SUBRESOURCE_DATA indexData;
	HRESULT result;

	vertices = new LightVertexType[VertexCount];
	if(!vertices)
	{
		return false;
	}

	indices = new unsigned long[IndexCount];
	if(!indices)
	{
		return false;
	}

	for(int i = 0; i < VertexCount; i++)
	{
		vertices[i].position = D3DXVECTOR3(Model[i].x, Model[i].y, Model[i].z);
		vertices[i].texture= D3DXVECTOR2(Model[i].tu, Model[i].tv);
		vertices[i].normal= D3DXVECTOR3(Model[i].nx, Model[i].ny, Model[i].nz);

		indices[i] = i;
	}

	vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	vertexBufferDesc.ByteWidth = sizeof(LightVertexType) * VertexCount;
	vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertexBufferDesc.CPUAccessFlags = 0;
	vertexBufferDesc.MiscFlags = 0;
	vertexBufferDesc.StructureByteStride = 0;

	vertexData.pSysMem = vertices;
	vertexData.SysMemPitch = 0;
	vertexData.SysMemSlicePitch = 0;

	result = device->CreateBuffer(&vertexBufferDesc, &vertexData, &VertexBuffer);
	if(FAILED(result))
	{
		return false;
	}

	indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	indexBufferDesc.ByteWidth = sizeof(unsigned long) * IndexCount;
	indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	indexBufferDesc.CPUAccessFlags = 0;
	indexBufferDesc.MiscFlags = 0;
	indexBufferDesc.StructureByteStride = 0;

	indexData.pSysMem = indices;
	indexData.SysMemPitch = 0;
	indexData.SysMemSlicePitch = 0;

	result = device->CreateBuffer(&indexBufferDesc, &indexData, &IndexBuffer);
	if(FAILED(result))
	{
		return false;
	}

	delete[] vertices;
	vertices = nullptr;

	delete[] indices;
	indices = nullptr;

	return true;
}


void ModelClass::ShutdownBuffers()
{
	if(IndexBuffer)
	{
		IndexBuffer->Release();
		IndexBuffer = nullptr;
	}

	if(VertexBuffer)
	{
		VertexBuffer->Release();
		VertexBuffer = nullptr;
	}
}

void ModelClass::RenderBuffers(ID3D11DeviceContext* deviceContext)
{
	unsigned int stride;
	unsigned int offset;

	if(Texture)
	{
		stride = sizeof(LightVertexType);
	}
	else
	{
		stride = sizeof(VertexType);
	}
	offset = 0;

	deviceContext->IASetVertexBuffers(0, 1, &VertexBuffer, &stride, &offset);
	deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	deviceContext->IASetIndexBuffer(IndexBuffer, DXGI_FORMAT_R32_UINT, 0);


}

bool ModelClass::LoadTexture(ID3D11Device* device, WCHAR* filename)
{
	bool result;

	Texture = new TextureClass();
	if(!Texture)
	{
		return false;
	}

	result = Texture->Initialize(device, filename);
	if(!result)
	{
		return false;
	}

	return true;
}

void ModelClass::ReleaseTexture()
{
	if(Texture)
	{
		Texture->Shutdown();
		delete Texture;
		Texture = nullptr;
	}
}
bool ModelClass::LoadModel(char* fileName)
{
	std::ifstream stream;
	char input;
	
	stream.open(fileName);
	if(stream.fail())
	{
		return false;
	}

	stream.get(input);
	while(input != ':')
	{
		stream.get(input);
	}

	stream >> VertexCount;
	IndexCount = VertexCount;

	Model = new ModelType[VertexCount];
	if(!Model)
	{
		return false;
	}

	stream.get(input);
	while(input != ':')
	{
		stream.get(input);
	}
	stream.get(input);
	stream.get(input);

	for(int i = 0; i < VertexCount; i++)
	{
		stream >> Model[i].x >> Model[i].y >> Model[i].z;
		stream >> Model[i].tu >> Model[i].tv;
		stream >> Model[i].nx >> Model[i].ny >> Model[i].nz;
	}

	stream.close();

	return true;
}

bool ModelClass::LoadBlenderModel(char* fileName)
{
	std::ifstream stream;
	char* input;

	stream.open(fileName);
	if(stream.fail())
	{
		return false;
	}

	while(!stream.eof())
	{
		
	}

}

void ModelClass::ReleaseModel()
{
	if(Model)
	{
		delete[] Model;
		Model = nullptr;
	}
}
