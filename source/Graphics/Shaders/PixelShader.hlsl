// Structure d'entrée : doit matcher l'output de ton Vertex Shader
struct PixelInput
{
    float4 position : SV_POSITION; // Coordonnées écran (système)
    float3 normal : NORMAL; // Normale interpolée
    float2 texCoord : TEXCOORD0; // Coordonnées de texture
};

// Constant Buffer pour les réglages de rendu (optionnel mais recommandé)
cbuffer PerObject : register(b1)
{
    float4 meshColor;
};

float4 main(PixelInput input) : SV_TARGET
{
    // 1. Normalisation de la normale (crucial après interpolation)
    float3 N = normalize(input.normal);

    // 2. Éclairage directionnel très basique (Lambert)
    // On simule une lumière venant du haut (0, 1, 0)
    float3 lightDir = normalize(float3(0.5f, 1.0f, -0.5f));
    float intensity = max(dot(N, lightDir), 0.2f); // 0.2f de lumière ambiante minimum

    // 3. Retourne la couleur finale (RGBA)
    return meshColor * intensity;
}