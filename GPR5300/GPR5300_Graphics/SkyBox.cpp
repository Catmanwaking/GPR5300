#include <d3dcompiler.h>
#include <xutility>
#include "WICTextureLoader11.h"
#include "SkyBox.h"
#include "Utils.h"
#include "MaterialLoaderData.h"
#include "MaterialLoader.h"
#include "MeshLoader.h"

#pragma comment(lib, "d3dcompiler.lib")

INT SkyBox::Init(ID3D11Device* pD3DDevice, std::string fileName, Shader shader)
{
	pMeshData = MeshLoader::LoadFromFile(fileName);

	INT error = InitVertexBuffer(pD3DDevice);
	if (error) return error;

	error = InitIndexBuffer(pD3DDevice);
	if (error) return error;

	error = material.Init(pD3DDevice, pMeshData->materialFileName, shader);
	if (error) return error;

	pMeshData->DeInit();
	pMeshData = nullptr;

	return 0;
}

void SkyBox::Render(ID3D11DeviceContext* pD3DDeviceContext, const XMMATRIX& rViewProjectionMatrix)
{
	material.Render(pD3DDeviceContext, rViewProjectionMatrix);

	static UINT offset = 0;
	pD3DDeviceContext->IASetVertexBuffers(0, 1, &pVertexBuffer, &vertexStride, &offset);
	pD3DDeviceContext->IASetIndexBuffer(pIndexBuffer, DXGI_FORMAT_R16_UINT, 0);
	pD3DDeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	pD3DDeviceContext->DrawIndexed(indexCount, 0, 0);
}

void SkyBox::DeInit()
{
}
