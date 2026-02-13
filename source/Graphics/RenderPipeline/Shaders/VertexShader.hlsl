// 1. Structures de données
struct VertexInput
{
    float3 position : POSITION;
    float3 normal : NORMAL;
    float2 texCoord : TEXCOORD;
};

struct PixelInput
{
    float4 position : SV_POSITION;
    float3 normal : NORMAL;
    float2 texCoord : TEXCOORD0;
};

// 2. Constant Buffers
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

// 3. Fonction Principale
PixelInput main(VertexInput input)
{
    PixelInput output;

    // Transformation de la position : Local -> World -> View -> Projection
    float4 worldPosition = mul(float4(input.position, 1.0f), world);
    float4 viewPosition = mul(worldPosition, view);
    output.position = mul(viewPosition, projection);

    // Transformation de la normale : Local -> World
    // On utilise 0.0f en W car on ne veut pas appliquer la translation à une direction
    output.normal = mul(float3(input.normal), (float3x3) world);

    // Transmission des UVs sans modification
    output.texCoord = input.texCoord;

    return output;
}