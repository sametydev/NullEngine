//Texture2D tex0 : register(t0);
//SamplerState texSampler : register(s0);

struct PS_In
{
    float4 pos : SV_POSITION;
    float2 st : TEXCOORD;
};

float4 PS(PS_In ps) : SV_TARGET
{
    //return tex0.Sample(texSampler, ps.st);
    
    return float4(1, 1, 1, 1);

}