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

struct PS_IN
{
    float4 pos : SV_POSITION;
    float3 normal : TEXCOORD0;
    float2 st : TEXCOORD1;
    float3 world : TEXCOORD2;
};

PS_IN VS(VS_IN vs) {
	PS_IN ps;
	ps.pos = mul(float4(vs.pos,1),model);
	ps.pos = mul(ps.pos,view);
	ps.pos = mul(ps.pos,proj);
	ps.normal = vs.normal;
    ps.world = mul(float4(vs.pos, 1), model).xyz;
	ps.st  = vs.st;
	
	return ps;
};
