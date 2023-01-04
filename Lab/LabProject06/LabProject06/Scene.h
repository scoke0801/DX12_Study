#pragma once

#include "Timer.h"

class CShader;

class CScene
{
public:
	CScene();
	~CScene();

	//������ ���콺�� Ű���� �޽����� ó���Ѵ�.
	bool OnProcessingMouseMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam);
	bool OnProcessingKeyboardMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam);

	void BuildObjects(ID3D12Device* pd3dDevice, ID3D12GraphicsCommandList * pd3dCommandList);
	void ReleaseObjects();

	bool ProcessInput(UCHAR* pKeysBuffer);
	void AnimateObjects(float fTimeElapsed);

	void Render(ID3D12GraphicsCommandList* pd3dCommandList);

	void ReleaseUploadBuffers();

	//�׷��� ��Ʈ �ñ׳��ĸ� �����Ѵ�. 
	ID3D12RootSignature *CreateGraphicsRootSignature(ID3D12Device *pd3dDevice);

	ID3D12RootSignature* GetGraphicsRootSignature();
protected:
	//���� ���̴����� �����̴�. ���̴����� ���� ��ü���� �����̴�.
	CShader **m_ppShaders = NULL;
	int m_nShaders = 0;

	ID3D12RootSignature* m_pd3dGraphicsRootSignature = NULL;
};
