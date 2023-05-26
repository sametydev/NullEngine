Texture2D GTexture : register(t0);
SamplerState GSampler : register(s0);

struct PSIn
{
    float4 pos : SV_Position;
    float3 normal : TEXCOORD0;
    float2 st : TEXCOORD1;
};


float4 PS(PSIn ps) : SV_TARGET
{
    float4 diffuse = GTexture.Sample(GSampler, ps.st);

    return diffuse;
};