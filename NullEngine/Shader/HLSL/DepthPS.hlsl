struct PSIn
{
    float4 pos : SV_Position;
    float4 depthPos : TEXCOORD0;
};


float4 PS(PSIn ps) : SV_TARGET
{
    float depth;
    depth = ps.depthPos.z / ps.depthPos.w;
	return float4(depth, depth, depth, 1.0f);
}