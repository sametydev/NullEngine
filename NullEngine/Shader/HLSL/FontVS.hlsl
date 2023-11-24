cbuffer matrice : register(b1)
{
    matrix screen;
}


struct VS_In
{
    float4 bpos : POSITION;
    float4 buv : TEXCOORD;
    float4 color : COLOR;
};

struct PS_In
{
    float4 pos : SV_POSITION;
    float2 st : TEXCOORD;
    float4 color : COLOR;
    float alpha : PSIZE;
};

PS_In VS(VS_In vs, uint id : SV_VertexID)
{
    PS_In ps;
    float4 pos = vs.bpos;
    float4 uv = vs.buv;

    const float3 quad[6] =
    {
        { pos.x          , pos.y, 0 },         // 0 index
        { pos.x + pos.z  , pos.y, 0 },         // 1 index
        { pos.x          , pos.y + pos.w, 0 }, // 2 index
        { pos.x          , pos.y + pos.w, 0 }, // 2 index
        { pos.x + pos.z  , pos.y, 0 },         // 1 index
        { pos.x + pos.z  , pos.y + pos.w, 0 }  // 3 index

    };
    const float2 st[6] =
    {
        { uv.x, uv.y }, //0 index
        { uv.z, uv.y }, //1 index
        { uv.x, uv.w }, //2 index
        { uv.x, uv.w }, //2 index
        { uv.z, uv.y }, //1 index
        { uv.z, uv.w } //3 index

    };

    float3 curVtx = quad[id];
    float2 curST = st[id];
    ps.pos = mul(float4(curVtx, 1), screen);
    ps.st = curST;
    ps.color = vs.color;
    return ps;
}