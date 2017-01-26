using UnityEngine;
using System.Collections;
using System.IO;

public class Heightmap2PNG : MonoBehaviour
{
    public string fileName = "heightmap";

	void Start()
    {
        TerrainData tData = GetComponent<Terrain>().terrainData;

        int width  = tData.heightmapWidth;
        int height = tData.heightmapHeight;

        float[,] heights = tData.GetHeights(0, 0, width, height);
        Texture2D image = new Texture2D(width, height);

        for (int j = 0; j < height; j++)
            for (int i = 0; i < width; i++)
            {
                float p = heights[i, j] * 255.0f;
                image.SetPixel(i, j, new Color(p, p, p));
            }

        File.WriteAllBytes(Application.dataPath + "/Exports/" + fileName + ".png", image.EncodeToPNG());
	}
}
