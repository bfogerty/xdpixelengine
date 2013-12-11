using UnityEngine;
using UnityEditor;
using System.Collections;
using System.Collections.Generic;
using System.IO;
using System.Text;

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

        Mesh mesh = null;
        SkinnedMeshRenderer sm = meshObj.GetComponent<SkinnedMeshRenderer>() as SkinnedMeshRenderer;
        if (sm != null)
        {
            mesh = sm.sharedMesh;
        }
        else
        {

            MeshFilter meshFilter = meshObj.GetComponent<MeshFilter>() as MeshFilter;
            mesh = meshFilter.sharedMesh;
        }

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

    static string GenerateKey(Vector3 vec)
    {
        string s = string.Format("{0}:{1}:{2}", vec.x, vec.y, vec.z);
        return s;
    }

    static string GenerateKey(Vector2 vec)
    {
        string s = string.Format("{0}:{1}", vec.x, vec.y);
        return s;
    }

    static void FlushStringBuilderToFile(StreamWriter sw, StringBuilder sb)
    {
        sw.WriteLine(sb.ToString());
    }

    static void Export(string fileName, Mesh m)
    {
        Dictionary<string, int> vertMap = new Dictionary<string, int>();
        Dictionary<string, int> normalMap = new Dictionary<string, int>();
        Dictionary<string, int> uvMap = new Dictionary<string, int>();

        StringBuilder sb = null;

        int faceCount = m.triangles.Length / 3;

        using (StreamWriter sw = new StreamWriter(fileName))
        {
            int vertIndex = 0;
            int normalIndex = 0;
            int uvIndex = 0;

            sw.WriteLine(string.Format("# Vertex Count = {0}", m.vertexCount));
            sb = new StringBuilder(3000);
            for (int i = 0; i < m.vertexCount; ++i)
            {
                string key = GenerateKey(m.vertices[i]);
                if( !vertMap.ContainsKey(key) )
                {
                    vertMap.Add(key, vertIndex++);
                    //sw.WriteLine(string.Format("v {0} {1} {2}", m.vertices[i].x, m.vertices[i].y, m.vertices[i].z));
                    sb.AppendLine(string.Format("v {0} {1} {2}", m.vertices[i].x, m.vertices[i].y, m.vertices[i].z));
                }
            }
            sw.WriteLine(string.Format("# Vertex Optimized Count = {0}", vertIndex));
            FlushStringBuilderToFile(sw, sb);

            sw.WriteLine();
            sw.WriteLine(string.Format("# Normal Count = {0}", m.normals.Length));
            sb = new StringBuilder(3000);
            for (int i = 0; i < m.normals.Length; ++i)
            {
                string key = GenerateKey(m.normals[i]);
                if (!normalMap.ContainsKey(key))
                {
                    normalMap.Add(key, normalIndex++);
                    //sw.WriteLine(string.Format("vn {0} {1} {2}", m.normals[i].x, m.normals[i].y, m.normals[i].z));
                    sb.AppendLine(string.Format("vn {0} {1} {2}", m.normals[i].x, m.normals[i].y, m.normals[i].z));
                }
            }
            sw.WriteLine(string.Format("# Normal Optimized Count = {0}", normalIndex));
            FlushStringBuilderToFile(sw, sb);

            sw.WriteLine();
            sw.WriteLine(string.Format("# UV Count = {0}", m.uv.Length));
            sb = new StringBuilder(3000);
            for (int i = 0; i < m.uv.Length; ++i)
            {
                string key = GenerateKey(m.uv[i]);
                if (!uvMap.ContainsKey(key))
                {
                    uvMap.Add(key, uvIndex++);
                    sb.AppendLine(string.Format("vt {0} {1}", m.uv[i].x, m.uv[i].y));
                }

                //sw.WriteLine(string.Format("vt {0} {1}", m.uv[i].x, m.uv[i].y));
            }
            sw.WriteLine(string.Format("# UV Optimized Count = {0}", uvIndex));
            FlushStringBuilderToFile(sw, sb);
            

            sw.WriteLine();
            sw.WriteLine(string.Format("# Face Count = {0}", faceCount));
            for (int i = 0; i < m.triangles.Length; i+=3)
            {
                string vk0 = GenerateKey(m.vertices[m.triangles[i + 0]]);
                string vk1 = GenerateKey(m.vertices[m.triangles[i + 1]]);
                string vk2 = GenerateKey(m.vertices[m.triangles[i + 2]]);

                string nk0 = GenerateKey(m.normals[m.triangles[i + 0]]);
                string nk1 = GenerateKey(m.normals[m.triangles[i + 1]]);
                string nk2 = GenerateKey(m.normals[m.triangles[i + 2]]);

                string uvk0 = GenerateKey(m.uv[m.triangles[i + 0]]);
                string uvk1 = GenerateKey(m.uv[m.triangles[i + 1]]);
                string uvk2 = GenerateKey(m.uv[m.triangles[i + 2]]);

                int v0 = vertMap[vk0] + 1;
                int v1 = vertMap[vk1] + 1;
                int v2 = vertMap[vk2] + 1;

                int n0 = normalMap[nk0] + 1;
                int n1 = normalMap[nk1] + 1;
                int n2 = normalMap[nk2] + 1;

                int uv0 = uvMap[uvk0] + 1;
                int uv1 = uvMap[uvk1] + 1;
                int uv2 = uvMap[uvk2] + 1;

                //int f0 = m.triangles[i + 0] + 1;
                //int f1 = m.triangles[i + 1] + 1;
                //int f2 = m.triangles[i + 2] + 1;

                sw.WriteLine(string.Format("f {0}/{1}/{2} {3}/{4}/{5} {6}/{7}/{8}", v0, uv0, n0,
                                                                                    v1, uv1, n1,
                                                                                    v2, uv2, n2));
            }
        }
    }

}
