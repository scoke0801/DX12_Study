#pragma once

#include "Timer.h"

class CScene
{
public:
	CScene();
	~CScene();

	bool OnProcessingMouseMessage(HWND hWnd, UINT nMessagID, WPARAM wParam, LPARAM lParam);
	bool OnProcessingKeyboardMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam);

	void BuildObjects(ID3D12Device* pd3dDevice);
	void ReleaseObjects();

	bool ProcessInput();
	void AnimateObjects(float fTimeElapsed);
	void Render(ID3D12GraphicsCommandList* pd3dCommandList);
	
public:
	ID3D12RootSignature* m_pd3dGraphicsRootSignature; //��Ʈ �ñ׳��ĸ� ��Ÿ���� �������̽� �������̴�. 
	
	ID3D12PipelineState *m_pd3dPipelineState; //���������� ���¸� ��Ÿ���� �������̽� �������̴�.
};

