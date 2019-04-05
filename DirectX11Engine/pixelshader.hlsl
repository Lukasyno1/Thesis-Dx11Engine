struct PS_INPUT
{
    float4 inPosition : SV_POSITION; // sv_pos -> we will return position
    //float3 inColor : COLOR;
    float3 inTexCoord : TEXCOORD;
};
Texture2D objTexture : TEXTURE : register(t0);
SamplerState objSamplerState : SAMPLER : register(s0);

float4 main(PS_INPUT input) : SV_TARGET //SC -> SYSTEM VALUE 
{
    float3 pixelColor = objTexture.Sample(objSamplerState, input.inTexCoord);
    return float4(pixelColor, 1.0f);
}
