cbuffer matrice0 : register(b0)
{
    matrix proj;
    matrix view;
    matrix model;
};

cbuffer lightMatrice0 : register(b1)
{
    matrix lproj;
    matrix lview;
    float3 lightPosition;
    float padding;
};

struct VSIn
{
    float3 pos : POSITION;
    float3 normal : TEXCOORD0;
    float3 tangent : TEXCOORD1;
    float2 st : TEXCOORD2;
};

struct PSIn
{
    float4 pos : SV_POSITION;
    float3 normal : TEXCOORD0;
    float2 st : TEXCOORD1;
    
    float4 lightViewPos : TEXCOORD2;
    float3 lightDir : TEXCOORD3;
};

PSIn VS(VSIn vs)
{
    PSIn ps;
    ps.pos = mul(float4(vs.pos, 1), model);
    ps.pos = mul(ps.pos, view);
    ps.pos = mul(ps.pos, proj);

    ps.lightViewPos = mul(float4(vs.pos, 1), model);
    ps.lightViewPos = mul(ps.lightViewPos, lview);
    ps.lightViewPos = mul(ps.lightViewPos, lproj); //to 2D ortho

    ps.st = vs.st;
    ps.normal = mul(vs.normal, (float3x3) model);
    ps.normal = normalize(ps.normal);

    float4 worldPos = mul(float4(vs.pos, 1), model);

    ps.lightDir = lightPosition.xyz - worldPos.xyz;
    ps.lightDir = normalize(ps.lightDir);
    return ps;
}