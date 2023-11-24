cbuffer matrice : register(b1)
{
    matrix screen;
}


struct VS_In
{
    float3 pos : POSITION;
    float2 st  : TEXCOORD;
};

struct PS_In
{
    float4 pos : SV_POSITION;
    float2 st  : TEXCOORD;
};

PS_In VS(VS_In vs)
{
    PS_In ps;
    ps.pos = mul(float4(vs.pos, 1),screen);
    ps.st = vs.st;
	return ps;
}