//-----------------------------------------------------------------------------
// File: Scene.h
//-----------------------------------------------------------------------------

#pragma once

#include "Shader.h"
#include "Player.h"


struct LIGHT
{
	XMFLOAT4				m_xmf4Ambient;
	XMFLOAT4				m_xmf4Diffuse;
	XMFLOAT4				m_xmf4Specular;
	XMFLOAT3				m_xmf3Position;
	float 					m_fFalloff;
	XMFLOAT3				m_xmf3Direction;
	float 					m_fTheta; //cos(m_fTheta)
	XMFLOAT3				m_xmf3Attenuation;
	float					m_fPhi; //cos(m_fPhi)
	bool					m_bEnable;
	int						m_nType;
	float					m_fRange;
	float					padding;
};

struct LIGHTS
{
	LIGHT					m_pLights[MAX_LIGHTS];
	XMFLOAT4				m_xmf4GlobalAmbient;
};

struct MATERIAL
{
	XMFLOAT4				m_xmf4Ambient;
	XMFLOAT4				m_xmf4Diffuse;
	XMFLOAT4				m_xmf4Specular; //(r,g,b,a=power)
	XMFLOAT4				m_xmf4Emissive;
};

struct MATERIALS
{
	MATERIAL				m_pReflections[MAX_SCENE_MATERIALS];
};

class CScene
{
public:
    CScene();
    ~CScene();

	bool OnProcessingMouseMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam);
	bool OnProcessingKeyboardMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam);

	void BuildObjects(ID3D12Device *pd3dDevice, ID3D12GraphicsCommandList *pd3dCommandList);
	void ReleaseObjects();

	void BuildLightsAndMaterials();

	ID3D12RootSignature *CreateGraphicsRootSignature(ID3D12Device *pd3dDevice);
	ID3D12RootSignature *GetGraphicsRootSignature() { return(m_pd3dGraphicsRootSignature); }
	void SetGraphicsRootSignature(ID3D12GraphicsCommandList *pd3dCommandList) { pd3dCommandList->SetGraphicsRootSignature(m_pd3dGraphicsRootSignature); }

	virtual void CreateShaderVariables(ID3D12Device *pd3dDevice, ID3D12GraphicsCommandList *pd3dCommandList);
	virtual void UpdateShaderVariables(ID3D12GraphicsCommandList *pd3dCommandList);
	virtual void ReleaseShaderVariables();

	bool ProcessInput(UCHAR *pKeysBuffer);
    void AnimateObjects(float fTimeElapsed);
    void Render(ID3D12GraphicsCommandList *pd3dCommandList, CCamera *pCamera=NULL);

	void ReleaseUploadBuffers();

	CPlayer						*m_pPlayer = NULL;

protected:
	ID3D12RootSignature			*m_pd3dGraphicsRootSignature = NULL;

	CShader						**m_ppShaders = NULL;
	int							m_nShaders = 0;

	LIGHTS						*m_pLights = NULL;
	//22.06.23
	LIGHTS* m_pLights2 = NULL;
	//

	ID3D12Resource				*m_pd3dcbLights = NULL;
	LIGHTS						*m_pcbMappedLights = NULL;
	LIGHTS* m_pcbMappedLights2 = NULL;

	MATERIALS					*m_pMaterials = NULL;
	MATERIALS* m_pMaterials2 = NULL;

	ID3D12Resource				*m_pd3dcbMaterials = NULL;
	MATERIAL					*m_pcbMappedMaterials = NULL;
	MATERIAL* m_pcbMappedMaterials2 = NULL;
	//22.06.22
public:
	bool choose = false;

	//22.05.09
//float						mpTime = 0.f;
	vector<XMFLOAT3> mpObjVec;
	XMFLOAT3 tmp;
	vector<XMFLOAT3> mpObjVec2;
	bool wakeUp = false;
	//

	//22.06.23
	void CheckObjectByObjectCollisions();
	void UpdateBoundingBox();

	XMFLOAT4X4					m_xmf4x4World = Matrix4x4::Identity();

	BoundingBox			m_xmOOBB = BoundingBox();
	//
};
