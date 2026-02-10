// Dans ton fichier shader.hlsl
cbuffer PerFrame : register(b0)
{
    matrix view;
    matrix projection;
};

cbuffer PerObject : register(b1)
{
    matrix world;
    float4 meshColor;
};