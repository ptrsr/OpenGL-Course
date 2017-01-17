using UnityEngine;
using System.Collections;
using System.IO;

public class ExporterScript : MonoBehaviour {

	public string path;

	//----------------------------------------------------------------------------------------------------------------
	//												Start()
	//----------------------------------------------------------------------------------------------------------------
	private void Start () {
		ExportScene();
	}

	//----------------------------------------------------------------------------------------------------------------
	//												ExportScene()
	//----------------------------------------------------------------------------------------------------------------
	private void ExportScene () {

		string toExport = "";

		foreach (Transform child in GetComponent<Transform>()) {
			toExport += ExportObject(child.gameObject);
		}

		Debug.Log(toExport);
		File.WriteAllText(path, toExport);
	}

	//----------------------------------------------------------------------------------------------------------------
	//												ExportObject()
	//----------------------------------------------------------------------------------------------------------------
	private string ExportObject (GameObject gameObject) {
		string result = "";

		MeshRenderer meshRenderer = gameObject.GetComponent<MeshRenderer>();
		if (meshRenderer != null) {
			result += ExportCube(meshRenderer);
		}

		foreach (Transform child in gameObject.GetComponent<Transform>()) {
			result += ExportObject(child.gameObject);
		}

		return result;
	}

	//----------------------------------------------------------------------------------------------------------------
	//												ExportCube()
	//----------------------------------------------------------------------------------------------------------------
	private string ExportCube(MeshRenderer meshRenderer) {
		Color32 color = meshRenderer.sharedMaterial.color;

        string hex = color.r.ToString("X2") + color.g.ToString("X2") + color.b.ToString("X2");

        Vector3 position = meshRenderer.transform.position;
		float x = Mathf.Floor(position.x * 10.0f) / 10.0f;
		float y = Mathf.Floor(position.y * 10.0f) / 10.0f;
		float z = Mathf.Floor(position.z * 10.0f) / 10.0f;

		Vector3 scale = meshRenderer.transform.lossyScale;
		float scaleX = Mathf.Floor(scale.x * 10.0f) / 10.0f;
		float scaleY = Mathf.Floor(scale.y * 10.0f) / 10.0f;
		float scaleZ = Mathf.Floor(scale.z * 10.0f) / 10.0f;

		string toExport =
			"createObject(\"" + meshRenderer.gameObject.name + "\", " +
			x + "," + y + "," + z + ", " +
			scaleX + "," + scaleY + "," + scaleZ + ", " +
			"\"" + hex + "\");\n";

		return toExport;
	}
	
}
