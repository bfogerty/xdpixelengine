using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.IO;
using System.Threading.Tasks;

namespace Md2ModelExporterApp
{

    public class MD2Header
    {
        public string MagicNumber { get; set; }
        public int Version { get; set; }
        public int SkinWidth { get; set; }
        public int SkinHeight { get; set; }
        public int SizeOfFrameInBytes { get; set; }
        public int NumberOfSkins { get; set; }
        public int NumberOfVerticies { get; set; }
        public int NumberOfTextureCoordinates { get; set; }
        public int NumberOfTriangles { get; set; }
        public int NumberOfGLCommands { get; set; }
        public int TotalNumberOfFrames { get; set; }

        public int OffsetToSkinNames { get; set; }
        public int OffsetToTextureCoordinates { get; set; }
        public int OffsetToTriangles { get; set; }
        public int OffsetToFrames { get; set; }
        public int OffsetToGLCommands { get; set; }
        public int OffsetToEndOfFile { get; set; }

        public MD2Header()
        {

        }
    }

    class Vector3
    {
        public float x;
        public float y;
        public float z;

        public Vector3()
        {
            this.x = 0.000f;
            this.y = 0.000f;
            this.z = 0.000f;
        }

        public Vector3( float[] array )
        {
            this.x = array[0];
            this.y = array[1];
            this.z = array[2];
        }

        public Vector3(float x, float y, float z)
        {
            this.x = x;
            this.y = y;
            this.z = z;
        }

        public static Vector3 operator +(Vector3 vec1, Vector3 vec2)
        {
            Vector3 vecResult = new Vector3();
            vecResult.x = vec1.x + vec2.x;
            vecResult.y = vec1.y + vec2.y;
            vecResult.z = vec1.z + vec2.z;

            return vecResult;
        }

        public static Vector3 operator -(Vector3 vec1, Vector3 vec2)
        {
	        Vector3 vecResult = new Vector3();
            vecResult.x = vec1.x - vec2.x;
            vecResult.y = vec1.y - vec2.y;
            vecResult.z = vec1.z - vec2.z;

	        return vecResult;
        }

        public static float Magnitude( Vector3 vec1 )
        {
	        float fResult = (float)(Math.Sqrt( SqrMagnitude(vec1) ));

	        return fResult;
        }

        public static float SqrMagnitude( Vector3 vec1 )
        {
            float fResult = (vec1.x * vec1.x) +
                            (vec1.y * vec1.y) +
                            (vec1.z * vec1.z);

	        return fResult;
        }

        public static Vector3 Normalized(Vector3 vec1)
        {
            Vector3 vecResult = new Vector3();
            float fNorm = Magnitude(vec1);

            vecResult.x = vec1.x / fNorm;
            vecResult.y = vec1.y / fNorm;
            vecResult.z = vec1.z / fNorm;

            return vecResult;
        }

        public static float Dot(Vector3 vec1, Vector3 vec2)
        {
            float fResult = 0.0000f;
            fResult = (vec1.x * vec2.x) + (vec1.y * vec2.y) + (vec1.z * vec2.z);

            return fResult;
        }

        public static Vector3 Cross(Vector3 vec1, Vector3 vec2)
        {
            Vector3 vecResult = new Vector3();
            vecResult.x = (vec2.y * vec1.z) - (vec1.y * vec2.z);
            vecResult.y = (vec2.z * vec1.x) - (vec1.z * vec2.x);
            vecResult.z = (vec2.x * vec1.y) - (vec1.x * vec2.y);

            return vecResult;
        }
    }

    class MD2Vertex
    {
        public Vector3 Position;
        public int LightNormalIndex;
        public Vector3 Normal;

    }

    class Triangle
    {
        public short[] VertexIndicies = new short[3];
        public short[] UVIndicies = new short[3];
        public Vector3 normal = new Vector3();

    }

    class TextureCoordinate
    {
        public float u;
        public float v;

    }

    class Frame
    {
        public MD2Vertex[] verticies;
        public Vector3 scale = new Vector3();
        public Vector3 translate = new Vector3();
        public string name;

        public Frame()
        {
            this.name = string.Empty;
            verticies = null;
        }

        public Frame(string name, int vertCount)
        {
            this.name = name;
            verticies = new MD2Vertex[vertCount];
        }
    }

    class MD2ModelInfo
    {
        public MD2Header Header {get; set;}
        public Frame[] Frames;
        public TextureCoordinate[] TextureCoordinates;
        public Triangle[] Triangles;
        public Vector3[] Normals;

        public MD2ModelInfo()
        {

        }
    }
}
