struct VS_INPUT
{
    float3 pos : POSITION;
    float3 color : NORMAL; // On a détourné NORMAL pour la couleur
    float2 tex : TEXCOORD;
};

struct PS_INPUT
{
    float4 pos : SV_POSITION;
    float4 color : COLOR;
};

PS_INPUT mainVS(VS_INPUT input)
{
    PS_INPUT output;
    output.pos = float4(input.pos, 1.0f); // Pas de matrice pour l'instant
    output.color = float4(input.color, 1.0f);
    return output;
}

float4 mainPS(PS_INPUT input) : SV_TARGET
{
    return input.color;
}