Texture2D modelTexture : register(t0);
Texture2D depthTexture : register(t1);

SamplerState SamplerWrap     : register(s0);
SamplerState SamplerClamp : register(s1);

struct PSIn
{
    float4 pos : SV_POSITION;
    float3 normal : TEXCOORD0;
    float2 st : TEXCOORD1;
    
    float4 lightViewPos : TEXCOORD2;
    float3 lightDir : TEXCOORD3;
};

float4 PS(PSIn ps) : SV_TARGET
{
    float4 lightColor = float4(0.9, 0.9, 0.9, 1);
    float4 finalColor = float4(0.3, 0.3, 0.3, 1);

    float2 screenUV;
    float depth;
    float lightDepth;
    float NdotL; //WoL

    float offset = 0.0001;
    //decarte to appine
    screenUV.x = ps.lightViewPos.x / ps.lightViewPos.w / 2.f + 0.5f;
    screenUV.y = -ps.lightViewPos.y / ps.lightViewPos.w / 2.f + 0.5f;

    if ((saturate(screenUV.x) == screenUV.x) &&
        (saturate(screenUV.y) == screenUV.y))
    {
        depth = depthTexture.Sample(SamplerClamp, screenUV).r;

        lightDepth = ps.lightViewPos.z / ps.lightViewPos.w;
        lightDepth = lightDepth - offset;

        if (lightDepth < depth)
        {
            NdotL = saturate(dot(ps.normal, ps.lightDir)).r;

            if (NdotL > 0.f)
            {
                //finalColor = float4(1, 0, 0, 1);
                finalColor += (lightColor * NdotL);
                finalColor = saturate(finalColor);
            }
        }

    }

    float4 modelColor = modelTexture.Sample(SamplerWrap, ps.st);
    finalColor = finalColor * modelColor;
    return finalColor;
}