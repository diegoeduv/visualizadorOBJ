#version 330 core
in float vHeight;
out vec4 FragColor;

// Mínimo, máximo y medio de la altura
uniform float uMinY;
uniform float uMaxY;

void main()
{
    // Calcular valor normalizado de altura [0, 1]
    float t = clamp((vHeight - uMinY) / (uMaxY - uMinY), 0.0, 1.0);

    // Azul (bajo), Amarillo (medio), Rojo (alto)
    vec3 colorLow  = vec3(0.0, 0.0, 1.0); // azul
    vec3 colorMid  = vec3(1.0, 1.0, 0.0); // amarillo
    vec3 colorHigh = vec3(1.0, 0.0, 0.0); // rojo

    vec3 color;

    // Interpolación: azul - amarillo - rojo
    if (t < 0.5)
        color = mix(colorLow, colorMid, t * 2.0);   // 0–0.5
    else
        color = mix(colorMid, colorHigh, (t - 0.5) * 2.0); // 0.5–1.0

    FragColor = vec4(color, 1.0);
}
