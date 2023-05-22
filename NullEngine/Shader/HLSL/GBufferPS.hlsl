Texture2D GTexture : register(t0);
SamplerState GSampler : register(s0);

struct PS_IN
{
    float4 pos : SV_POSITION;
    float3 normal : TEXCOORD0;
    float2 st : TEXCOORD1;
    float3 world : TEXCOORD2;
};

struct PS_Out {
	float4 diffuse : SV_TARGET0;
	float4 normal : SV_TARGET1;
    float4 position : SV_TARGET2;
};

PS_Out PS(PS_IN ps) : SV_TARGET
{
	PS_Out output;
    output.diffuse = GTexture.Sample(GSampler, ps.st);
	output.normal = float4(ps.normal, 1);
    output.position = float4(ps.world,1);
	return output;
};