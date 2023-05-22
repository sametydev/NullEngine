cbuffer matrices : register(b0) {
	matrix proj;
	matrix view;
	matrix model;
};


struct VS_IN {
	float3 pos : POSITION;
	float3 normal : TEXCOORD0;
	float2 st  : TEXCOORD1;
};

struct PS_IN {
	float4 pos : SV_POSITION;
	float3 normal : NORMAL;
	float2 st  : TEXCOORD;
};

PS_IN VS(VS_IN vs) {
	PS_IN ps;
	ps.pos = mul(float4(vs.pos,1),model);
	ps.pos = mul(ps.pos,view);
	ps.pos = mul(ps.pos,proj);
	ps.normal = vs.normal;
	ps.st  = vs.st;
	
	return ps;
};

Texture2D GTexture : register(t0);
SamplerState GSampler : register(s0);

struct PS_Out{
	float4 pos : SV_TARGET0;
	float4 normal : SV_TARGET1;
};

PS_Out PS(PS_IN ps) : SV_TARGET
{
	PS_Out output;
	output.pos = GTexture.Sample(GSampler, ps.st);
	output.normal = float4(ps.normal, 1);
	return output;
};