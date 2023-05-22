Texture2D GTexture : register(t0);
SamplerState GSampler : register(s0);

struct PS_IN {
	float4 pos : SV_POSITION;
	float3 normal : TEXCOORD0;
	float2 st  : TEXCOORD;
};

struct PS_Out {
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