cbuffer matrice0
{
    matrix proj;
    matrix view;
    matrix model;
};

struct VSIn
{
    float3 pos : POSITION;
};

struct PSIn
{
    float4 pos : SV_Position;
    float4 depthPos : TEXCOORD0;
};

PSIn VS( VSIn vs )
{
    PSIn ps;
    ps.pos = mul(float4(vs.pos, 1), model);
    ps.pos = mul(ps.pos, view);
    ps.pos = mul(ps.pos, proj);
    ps.depthPos = ps.pos;
	return ps;
}