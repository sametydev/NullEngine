struct VS_IN {
	float3 pos : POSITION;
	float2 st  : TEXCOORD0;
};

struct PS_IN {
	float4 pos : SV_POSITION;
	float2 st  : TEXCOORD0;
};

PS_IN VS(VS_IN vs) {
	PS_IN ps;
	ps.pos = float4(vs.pos,1);
	ps.st = vs.st;
	return ps;
};