#include "FS_Texture2D.h"
#include "FS_Mathf.h"

Texture2D Texture2D_Create(Arena *arena, uint16_t width, uint16_t height)
{
	Texture2D result = { 
		width, height, 
		Arena_PushArray(arena, width * height, Color)
	};
	return result;
}

Texture2D Texture2D_CreateCircle(Arena *arena, uint16_t size, float innerRadius, float outerRadius)
{
	Texture2D texture = { size, size, Arena_PushArray(arena, size * size, Color) };

	Color transparent = { 0, 0, 0, 0 };
	Color white = { 255, 255, 255, 255 };
	Color red = { 255, 0, 0, 255};

	float inner = innerRadius * 0.5f;
	float outer = outerRadius * 0.5f;
	
	for (size_t i = 0; i < texture.height; i++)
	{
		for (size_t j = 0; j < texture.width; j++)
		{
			float s = (float)j / (texture.width - 1);
			float t = (float)i / (texture.height - 1);

			float dist = Mathf_Sqrt((s - 0.5f) * (s - 0.5f) + (t - 0.5f) * (t - 0.5f));

			Color *pixel = texture.pixels + (i * texture.width + j);
			if (dist <= outer)
			{
				if (dist <= inner)
				{
					*pixel = white;
				}
				else
				{
					float alpha = Mathf_MapToRange(dist, inner, outer, 1.0f, 0.0f);
					Color mixed = { 255, 255, 255, Mathf_Ease(alpha, Ease_QuadOut) * 255 };
					*pixel = mixed;
				}
			}
			else
			{
				*pixel = transparent;
			}
		}
	}

	return texture;
}