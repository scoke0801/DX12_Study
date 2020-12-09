#pragma once
#include"Object.h"

#include "Mesh.h"

struct CB_TERRAIN_OBJECT_INFO
{
	XMFLOAT4X4						m_xmf4x4World;
};
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
class CHeightMapTerrain : public CGameObject
{
public:
	CHeightMapTerrain(ID3D12Device* pd3dDevice, ID3D12GraphicsCommandList* pd3dCommandList, ID3D12RootSignature* pd3dGraphicsRootSignature,
		LPCTSTR pFileName, int nWidth, int nLength, int nBlockWidth, int nBlockLength, XMFLOAT3 xmf3Scale, XMFLOAT4 xmf4Color, bool setTessellation = false);
	virtual ~CHeightMapTerrain();

private:
	CHeightMapImage				* m_pHeightMapImage;

	int							m_nWidth;
	int							m_nLength;

	XMFLOAT3					m_xmf3Scale;

	CMesh						**m_ppMeshes;
	int							m_nMeshes;

	void SetMesh(int nIndex, CMesh* pMesh);

	virtual void ReleaseShaderVariables();

public:
	float GetHeight(float x, float z, bool bReverseQuad = false) { return(m_pHeightMapImage->GetHeight(x, z, bReverseQuad) * m_xmf3Scale.y); } //World
	XMFLOAT3 GetNormal(float x, float z) { return(m_pHeightMapImage->GetHeightMapNormal(int(x / m_xmf3Scale.x), int(z / m_xmf3Scale.z))); }

	int GetRawImageWidth() { return(m_pHeightMapImage->GetRawImageWidth()); }
	int GetRawImageLength() { return(m_pHeightMapImage->GetRawImageLength()); }

	XMFLOAT3 GetScale() { return(m_xmf3Scale); }
	float GetWidth() { return(m_nWidth * m_xmf3Scale.x); }
	float GetLength() { return(m_nLength * m_xmf3Scale.z); }

	void Render(ID3D12GraphicsCommandList* pd3dCommandList, CCamera* pCamera = NULL);
};
//struct VS_TERRAIN_TESSELLATION_OUTPUT
//{
//	XMFLOAT3 position;
//	XMFLOAT3 positionW;
//	XMFLOAT4 color;
//	XMFLOAT2 uv0;
//	XMFLOAT2 uv1;
//};
//struct HS_TERRAIN_TESSELLATION_CONSTANT
//{
//	float fTessEdges[4];
//	float fTessInsides[2];
//};
//
//struct HS_TERRAIN_TESSELLATION_OUTPUT
//{
//	XMFLOAT3 position;
//	XMFLOAT4 color;
//	XMFLOAT2 uv0;
//	XMFLOAT2 uv1;
//};
//
//struct DS_TERRAIN_TESSELLATION_OUTPUT
//{
//	XMFLOAT4 position;
//	XMFLOAT4 color;
//	XMFLOAT2 uv0;
//	XMFLOAT2 uv1;
//	XMFLOAT4 tessellation;
//};
//VS_TERRAIN_TESSELLATION_OUTPUT VSTerrainTessellation(VS_TERRAIN_INPUT input)
//{
//	VS_TERRAIN_TESSELLATION_OUTPUT output;
//
//	output.position = input.position;
//	output.positionW = mul(float4(input.position, 1.0f), gmtxGameObject).xyz;
//	output.color = input.color;
//	output.uv0 = input.uv0;
//	output.uv1 = input.uv1;
//
//	return(output);
//}
//
//
//void BernsteinCoeffcient5x5(float t, float fBernstein[5])
//{
//	float tInv = 1.0f - t;
//	fBernstein[0] = tInv * tInv * tInv * tInv;
//	fBernstein[1] = 4.0f * t * tInv * tInv * tInv;
//	fBernstein[2] = 6.0f * t * t * tInv * tInv;
//	fBernstein[3] = 4.0f * t * t * t * tInv;
//	fBernstein[4] = t * t * t * t;
//}
//
//XMFLOAT3 CubicBezierSum5x5(HS_TERRAIN_TESSELLATION_OUTPUT patch[25], float uB[5], float vB[5])
//{
//	XMFLOAT3 f3Sum = XMFLOAT3(0.0f, 0.0f, 0.0f);
//	f3Sum = vB[0] * (uB[0]  * patch[0].position + uB[1]  * patch[1].position + uB[2]  * patch[2].position + uB[3]  * patch[3].position + uB[4]  * patch[4].position);
//	f3Sum += vB[1] * (uB[0] * patch[5].position + uB[1]  * patch[6].position + uB[2]  * patch[7].position + uB[3]  * patch[8].position + uB[4]  * patch[9].position);
//	f3Sum += vB[2] * (uB[0] * patch[10].position + uB[1] * patch[11].position + uB[2] * patch[12].position + uB[3] * patch[13].position + uB[4] * patch[14].position);
//	f3Sum += vB[3] * (uB[0] * patch[15].position + uB[1] * patch[16].position + uB[2] * patch[17].position + uB[3] * patch[18].position + uB[4] * patch[19].position);
//	f3Sum += vB[4] * (uB[0] * patch[20].position + uB[1] * patch[21].position + uB[2] * patch[22].position + uB[3] * patch[23].position + uB[4] * patch[24].position);
//
//	return(f3Sum);
//}
//
//float CalculateTessFactor(XMFLOAT3 f3Position)
//{
//	float fDistToCamera = distance(f3Position, gvCameraPosition);
//	float s = saturate((fDistToCamera - 10.0f) / (500.0f - 10.0f));
//
//	return(lerp(64.0f, 1.0f, s));
//	//	return(pow(2, lerp(20.0f, 4.0f, s)));
//}
//
//[domain("quad")]
//[partitioning("fractional_even")]
////[partitioning("integer")]
//[outputtopology("triangle_cw")]
//[outputcontrolpoints(25)]
//[patchconstantfunc("HSTerrainTessellationConstant")]
//[maxtessfactor(64.0f)]
//HS_TERRAIN_TESSELLATION_OUTPUT HSTerrainTessellation(InputPatch<VS_TERRAIN_TESSELLATION_OUTPUT, 25> input, uint i : SV_OutputControlPointID)
//{
//	HS_TERRAIN_TESSELLATION_OUTPUT output;
//
//	output.position = input[i].position;
//	output.color = input[i].color;
//	output.uv0 = input[i].uv0;
//	output.uv1 = input[i].uv1;
//
//	return(output);
//}
//
//HS_TERRAIN_TESSELLATION_CONSTANT HSTerrainTessellationConstant(InputPatch<VS_TERRAIN_TESSELLATION_OUTPUT, 25> input)
//{
//	HS_TERRAIN_TESSELLATION_CONSTANT output;
//
//	if (gnRenderMode & DYNAMIC_TESSELLATION)
//	{
//		float3 e0 = 0.5f * (input[0].positionW + input[4].positionW);
//		float3 e1 = 0.5f * (input[0].positionW + input[20].positionW);
//		float3 e2 = 0.5f * (input[4].positionW + input[24].positionW);
//		float3 e3 = 0.5f * (input[20].positionW + input[24].positionW);
//
//		output.fTessEdges[0] = CalculateTessFactor(e0);
//		output.fTessEdges[1] = CalculateTessFactor(e1);
//		output.fTessEdges[2] = CalculateTessFactor(e2);
//		output.fTessEdges[3] = CalculateTessFactor(e3);
//
//		float3 f3Sum = float3(0.0f, 0.0f, 0.0f);
//		for (int i = 0; i < 25; i++) f3Sum += input[i].positionW;
//		float3 f3Center = f3Sum / 25.0f;
//		output.fTessInsides[0] = output.fTessInsides[1] = CalculateTessFactor(f3Center);
//	}
//	else
//	{
//		output.fTessEdges[0] = 20.0f;
//		output.fTessEdges[1] = 20.0f;
//		output.fTessEdges[2] = 20.0f;
//		output.fTessEdges[3] = 20.0f;
//
//		output.fTessInsides[0] = 20.0f;
//		output.fTessInsides[1] = 20.0f;
//	}
//
//	return(output);
//}
//
//[domain("quad")]
//DS_TERRAIN_TESSELLATION_OUTPUT DSTerrainTessellation(HS_TERRAIN_TESSELLATION_CONSTANT patchConstant, float2 uv : SV_DomainLocation, OutputPatch<HS_TERRAIN_TESSELLATION_OUTPUT, 25> patch)
//{
//	DS_TERRAIN_TESSELLATION_OUTPUT output = (DS_TERRAIN_TESSELLATION_OUTPUT)0;
//
//	float uB[5], vB[5];
//	BernsteinCoeffcient5x5(uv.x, uB);
//	BernsteinCoeffcient5x5(uv.y, vB);
//
//	output.color = lerp(lerp(patch[0].color, patch[4].color, uv.x), lerp(patch[20].color, patch[24].color, uv.x), uv.y);
//	output.uv0 = lerp(lerp(patch[0].uv0, patch[4].uv0, uv.x), lerp(patch[20].uv0, patch[24].uv0, uv.x), uv.y);
//	output.uv1 = lerp(lerp(patch[0].uv1, patch[4].uv1, uv.x), lerp(patch[20].uv1, patch[24].uv1, uv.x), uv.y);
//
//	float3 position = CubicBezierSum5x5(patch, uB, vB);
//	matrix mtxWorldViewProjection = mul(mul(gmtxGameObject, gmtxView), gmtxProjection);
//	output.position = mul(float4(position, 1.0f), mtxWorldViewProjection);
//
//	output.tessellation = float4(patchConstant.fTessEdges[0], patchConstant.fTessEdges[1], patchConstant.fTessEdges[2], patchConstant.fTessEdges[3]);
//
//	return(output);
//}















//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
class CTerrainWater : public CGameObject
{
public:
	CTerrainWater(ID3D12Device* pd3dDevice, ID3D12GraphicsCommandList* pd3dCommandList, ID3D12RootSignature* pd3dGraphicsRootSignature, float nWidth, float nLength);
	virtual ~CTerrainWater();

private:
	int							m_nWidth;
	int							m_nLength;

	XMFLOAT3					m_xmf3Scale;

	XMFLOAT4X4					m_xmf4x4WaterAnimation;

	CMesh** m_ppMeshes;
	int							m_nMeshes;
	void SetMesh(int nIndex, CMesh* pMesh);

	virtual void ReleaseShaderVariables();

public:
	XMFLOAT4X4					m_xmf4x4Texture;

	virtual void UpdateShaderVariables(ID3D12GraphicsCommandList* pd3dCommandList);

	virtual void Animate(float fTimeElapsed);

	void Render(ID3D12GraphicsCommandList* pd3dCommandList, CCamera* pCamera = NULL);
};