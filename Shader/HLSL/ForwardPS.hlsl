Texture2D Texture0 : register(t0);
SamplerState Sampler0 : register(s0);

struct PS_IN {
	float4 pos : SV_POSITION;
	float3 normal : NORMAL;
	float2 st  : TEXCOORD;
};

float4 PS(PS_IN ps) : SV_TARGET {
	float4 albedo = Texture0.Sample(Sampler0,ps.st);
	clip(albedo.a-0.1);
	return albedo;
};