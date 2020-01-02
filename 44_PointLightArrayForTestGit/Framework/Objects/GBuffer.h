#pragma once

#define MAX_DEFFERED_POINT_LIGHT 128

class GBuffer
{
public:
	GBuffer(Shader * shader, UINT width = 0, UINT height = 0);
	~GBuffer();

	void PackGBuffer();
	void Lighting();
	void DebugRender();

	void SetDebug(bool val) { bDebug = val; }

private:

	void CreateDepthStencilView();
	void CreateDepthStencilState();
	void CreateRasterizerState();
	//void CreateBlendState();

private:
	bool bDebug = false;

	struct PointLightDesc
	{
		float TessFactor = 16.0f;
		float Padding[3];

		Matrix Projection[MAX_DEFFERED_POINT_LIGHT];

		PointLight PointLight[MAX_DEFFERED_POINT_LIGHT];
	}pointLightDesc;

private:

	Shader * shader;
	UINT width, height;

	RenderTarget * diffuseRTV; //color(24) Alpha(8)
	RenderTarget * specularRTV; //Color(24) power(8)
	RenderTarget * emissiveRTV; //Color(24) power(8)
	RenderTarget * normalRTV; //normal(24)
	RenderTarget * tangentRTV; //normal(24)
	DepthStencil * depthStencil;

	Viewport * viewport;


	ID3D11DepthStencilView * depthStencilReadOnly;
	ID3D11DepthStencilState * packDSS;
	ID3D11DepthStencilState * noDepthWriteLessDSS;
	ID3D11DepthStencilState * noDepthWriteGreatorDSS;
	ID3DX11EffectDepthStencilVariable * sDSS;

	ID3D11RasterizerState * debugRSS;
	ID3D11RasterizerState * lightRSS;
	ID3DX11EffectRasterizerVariable * sRSS;

	RenderTarget * renderRTV;
	DepthStencil * renderDSV;

	ID3D11BlendState * additiveBS;
	ID3DX11EffectBlendVariable * sBS;





	ID3DX11EffectShaderResourceVariable * sSrvs;

	//PointLight pointLights[MAX_POINT_LIGHT];
	ConstantBuffer * pointLightBuffer;
	ID3DX11EffectConstantBuffer * sPointLightBuffer;

	Render2D * debug2D[6];

};