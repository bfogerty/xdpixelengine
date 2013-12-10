using UnityEngine;
using UnityEditor;
using System.Collections;
using System.IO;

public class ObjExporter
{
    [MenuItem("XdPixel/Exporters/Obj")]
    static public void Export()
    {
        GameObject meshObj = Selection.activeGameObject;
        if (meshObj == null)
        {
            Message("No mesh is currently selected.");
            return;
        }

        MeshFilter meshFilter = meshObj.GetComponent<MeshFilter>() as MeshFilter;
        Mesh mesh = meshFilter.sharedMesh;

        //string path = @"Export\obj";
        string path = @"Assets\models";
        if (!System.IO.Directory.Exists(path))
        {
            System.IO.Directory.CreateDirectory(path);
        }

        string fileName = string.Format(@"{0}\{1}.obj", path, meshObj.name);
        Export( fileName, mesh );

        Message(string.Format("Exported \"{0}\".", meshObj.name));

    }

    static void Message(string msg)
    {
        EditorUtility.DisplayDialog("OBJ Exporter", msg , "Ok");
    }

    static void Export(string fileName, Mesh m)
    {
        using (StreamWriter sw = new StreamWriter(fileName))
        {
            sw.WriteLine(string.Format("# Vertex Count = {0}", m.vertexCount));
            for (int i = 0; i < m.vertexCount; ++i)
            {
                sw.WriteLine( string.Format("v {0} {1} {2}", m.vertices[i].x, m.vertices[i].y , m.vertices[i].z));
            }

            sw.WriteLine();
            sw.WriteLine(string.Format("# Normal Count = {0}", m.normals.Length));
            for (int i = 0; i < m.normals.Length; ++i)
            {
                sw.WriteLine(string.Format("vn {0} {1} {2}", m.normals[i].x, m.normals[i].y, m.normals[i].z));
            }

            sw.WriteLine();
            sw.WriteLine(string.Format("# UV Count = {0}", m.uv.Length));
            for (int i = 0; i < m.uv.Length; ++i)
            {
                sw.WriteLine(string.Format("vt {0} {1}", m.uv[i].x, m.uv[i].y));
            }

            int faceCount = m.triangles.Length / 3;
            sw.WriteLine();
            sw.WriteLine(string.Format("# Face Count = {0}", faceCount));
            for (int i = 0; i < m.triangles.Length; i+=3)
            {
                int f0 = m.triangles[i + 0] + 1;
                int f1 = m.triangles[i + 1] + 1;
                int f2 = m.triangles[i + 2] + 1;

                sw.WriteLine(string.Format("f {0}/{0}/{0} {1}/{1}/{1} {2}/{2}/{2}", f0, f1, f2));
            }
        }
    }

}
