cbuffer matrices : register(b0)
{
    matrix proj;
    matrix view;
    matrix model;
};

struct VSIn
{
    float3 pos : POSITION;
    float3 normal : TEXCOORD0;
    float3 tangent : TEXCOORD1;
    float2 st : TEXCOORD2;
    
    float4x4 inst : INSTANCE;
    //float4 inst0 : INSTANCE0;
    //float4 inst1 : INSTANCE1;
    //float4 inst2 : INSTANCE2;
    //float4 inst3 : INSTANCE3;
    
};

struct PSIn
{
    float4 pos : SV_Position;
    float3 normal : TEXCOORD0;
    float2 st : TEXCOORD1;
};

PSIn VS(VSIn vs)
{
    PSIn ps;
    
    matrix localInst = vs.inst;
    
    ps.pos = mul(float4(vs.pos, 1), localInst);
    ps.pos = mul(ps.pos, view);
    ps.pos = mul(ps.pos, proj);
    
    ps.normal = mul(vs.normal, (float3x3) localInst);
    ps.st = vs.st;
	return ps;
}