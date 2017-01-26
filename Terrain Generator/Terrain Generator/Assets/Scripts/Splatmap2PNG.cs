using UnityEngine;
using System.Collections;
using System.IO;

public class Splatmap2PNG : MonoBehaviour
{
    public string fileName = "splatmap";

    void Start()
    {
        TerrainData tData = GetComponent<Terrain>().terrainData;

        int width = tData.alphamapWidth;
        int height = tData.alphamapHeight;

        float[,,] maps = tData.GetAlphamaps(0, 0, width, height);
        int layers = tData.alphamapLayers;

        if (layers > 4)
            layers = 4;

        Texture2D image = new Texture2D(width, height);

        for (int j = 0; j < height; j++)
            for (int i = 0; i < width; i++)
            {
                Color c = new Color();

                float total = 0;
                for (int k = 0; k < layers; k++)
                    total += maps[i, j, k];

                c.r = maps[i, j, 0] / total;

                if (layers > 1)
                    c.g = maps[i, j, 1] / total;

                if (layers > 2)
                    c.b = maps[i, j, 2] / total;

                if (layers > 3)
                    c.a = maps[i, j, 3] / total;

                image.SetPixel(i, j, c);
            }

        File.WriteAllBytes(Application.dataPath + "/Exports/" + fileName + ".png", image.EncodeToPNG());
    }
}
