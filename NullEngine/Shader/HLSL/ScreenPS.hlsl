Texture2D Texture0 : register(t0);
Texture2D Texture1 : register(t1);
Texture2D Texture2 : register(t2);
SamplerState Sampler0 : register(s0);

struct PS_IN {
	float4 pos : SV_POSITION;
	float2 st  : TEXCOORD0;
};

float4 PS(PS_IN ps) : SV_TARGET {
	float4 albedo = Texture2.Sample(Sampler0,ps.st);
	return albedo;
};