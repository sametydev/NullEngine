Texture2D tex0;
SamplerState samplerState;

struct PS_In
{
    float4 pos : SV_POSITION;
    float2 st : TEXCOORD;
    float4 color : COLOR;
};


float4 PS(PS_In ps) : SV_Target
{
    float4 color = ps.color;
    float4 texColor = tex0.Sample(samplerState, ps.st);
    color.a = texColor.r;
    return color;
}