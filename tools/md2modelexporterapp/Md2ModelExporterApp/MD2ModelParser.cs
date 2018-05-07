using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.IO;
using System.Threading.Tasks;

namespace Md2ModelExporterApp
{
    class MD2ModelParser
    {
        public MD2ModelInfo Import(string path)
        {
            MD2ModelInfo md2ModelInfo = new MD2ModelInfo();
            using (System.IO.BinaryReader br = new System.IO.BinaryReader(File.Open(path, FileMode.Open)))
            {
                md2ModelInfo.Header = ParseHeader( br );
                md2ModelInfo.Frames = ParseFrameData(br, md2ModelInfo.Header);
                md2ModelInfo.TextureCoordinates = ParseTextureCoordinates(br, md2ModelInfo.Header);
                md2ModelInfo.Triangles = ParseTriangles(br, md2ModelInfo);
            }

            ComputePerVertexNormals( ref md2ModelInfo );

            return md2ModelInfo;
        }

        protected MD2Header ParseHeader(BinaryReader br)
        {
            MD2Header header = new MD2Header();

            header.MagicNumber = ParseString(br, 0, 4);
            header.Version = ParseInt(br, 4, 8);
            header.SkinWidth = ParseInt(br, 8, 12);
            header.SkinHeight = ParseInt(br, 12, 16);
            header.SizeOfFrameInBytes = ParseInt(br, 16, 20);
            header.NumberOfSkins = ParseInt(br, 20, 24);
            header.NumberOfVerticies = ParseInt(br, 24, 28);
            header.NumberOfTextureCoordinates = ParseInt(br, 28, 32);
            header.NumberOfTriangles = ParseInt(br, 32, 36);
            header.NumberOfGLCommands = ParseInt(br, 36, 40);
            header.TotalNumberOfFrames = ParseInt(br, 40, 44);

            header.OffsetToSkinNames = ParseInt(br, 44, 48);
            header.OffsetToTextureCoordinates = ParseInt(br, 48, 52);
            header.OffsetToTriangles = ParseInt(br, 52, 56);
            header.OffsetToFrames = ParseInt(br, 56, 60);
            header.OffsetToGLCommands = ParseInt(br, 60, 64);

            return header;
        }

        Frame[] ParseFrameData(BinaryReader br, MD2Header header)
        {
            Frame[] frames = new Frame[header.TotalNumberOfFrames];

            br.BaseStream.Seek(header.OffsetToFrames, SeekOrigin.Begin);

            for (int frameIndex = 0; frameIndex < header.TotalNumberOfFrames; ++frameIndex)
            {
                // Read in header
                frames[frameIndex] = new Frame();
                frames[frameIndex].scale = ParseVector3(br);
                frames[frameIndex].translate = ParseVector3(br);
                char[] nameBuffer = new char[16];
                br.Read(nameBuffer, 0, 16);
                frames[frameIndex].name = new string(nameBuffer).Trim();
                frames[frameIndex].verticies = new MD2Vertex[header.NumberOfVerticies];

                for (int vertIndex = 0; vertIndex < header.NumberOfVerticies; ++vertIndex)
                {

                    frames[frameIndex].verticies[vertIndex] = ParseMD2Vertex(br,
                                                                            frames[frameIndex].scale,
                                                                            frames[frameIndex].translate);
                }
            }

            return frames;
        }

        TextureCoordinate[] ParseTextureCoordinates(BinaryReader br, MD2Header header)
        {
            TextureCoordinate[] uvs = new TextureCoordinate[header.NumberOfTextureCoordinates];

            br.BaseStream.Seek(header.OffsetToTextureCoordinates, SeekOrigin.Begin);

            for (int i = 0; i < header.NumberOfTextureCoordinates; ++i)
            {
                // Read in header
                TextureCoordinate uv = new TextureCoordinate();
                short s = br.ReadInt16();
                short t = br.ReadInt16();

                uv.u = (float)(s) / header.SkinWidth;
                uv.v = 1.0f - ((float)(t) / header.SkinHeight);
                uvs[i] = uv;
            }

            return uvs;
        }

        Triangle[] ParseTriangles(BinaryReader br, MD2ModelInfo modelInfo)
        {
            MD2Header header = modelInfo.Header;
            Triangle[] triangles = new Triangle[header.NumberOfTriangles];

            br.BaseStream.Seek(header.OffsetToTriangles, SeekOrigin.Begin);

            for (int i = 0; i < header.NumberOfTriangles; ++i)
            {
                // Read in header
                Triangle triangle = new Triangle();
                short x = br.ReadInt16();
                short y = br.ReadInt16();
                short z = br.ReadInt16();

                short u = br.ReadInt16();
                short v = br.ReadInt16();
                short w = br.ReadInt16();

                triangle.VertexIndicies[0] = x;
                triangle.VertexIndicies[1] = y;
                triangle.VertexIndicies[2] = z;

                triangle.UVIndicies[0] = u;
                triangle.UVIndicies[1] = v;
                triangle.UVIndicies[2] = w;

                triangle.normal = ComputeTriangleNormal(modelInfo, triangle);

                triangles[i] = triangle;
            }

            return triangles;
        }

        Vector3 ComputeTriangleNormal(MD2ModelInfo modelInfo, Triangle triangle)
        {
            return ComputeTriangleNormal(modelInfo, modelInfo.Frames[0], triangle);
        }

        Vector3 ComputeTriangleNormal( MD2ModelInfo modelInfo, Frame frame, Triangle triangle)
        {
            Vector3 resultNormal = new Vector3();
            Vector3 v0 = frame.verticies[triangle.VertexIndicies[0]].Position;
            Vector3 v1 = frame.verticies[triangle.VertexIndicies[1]].Position;
            Vector3 v2 = frame.verticies[triangle.VertexIndicies[2]].Position;

            Vector3 v0ToV1 = v1 - v0;
            Vector3 v0ToV2 = v2 - v0;

            v0ToV1 = Vector3.Normalized(v0ToV1);
            v0ToV2 = Vector3.Normalized(v0ToV2);

            resultNormal = Vector3.Cross(v0ToV1, v0ToV2);
            resultNormal = Vector3.Normalized(resultNormal);

            return resultNormal;
        }

        void ComputePerVertexNormals(ref MD2ModelInfo md2ModelInfo)
        {
            foreach (Frame f in md2ModelInfo.Frames)
            {
                // For each vert, find all triangles that reference that vert
                //foreach (MD2Vertex md2Vert in f.verticies)
                for (int vertIndex = 0; vertIndex < f.verticies.Length; ++vertIndex )
                {
                    MD2Vertex md2Vert = f.verticies[vertIndex];
                    Triangle[] triangles = GetTrianglesThatReferenceVert(md2ModelInfo, f.verticies, md2Vert);
                    Vector3[] normals = new Vector3[triangles.Length];
                    for (int i = 0; i < normals.Length; ++i)
                    {
                        normals[i] = ComputeTriangleNormal(md2ModelInfo, f, triangles[i]);
                    }

                    float xSum = 0.00f;
                    float ySum = 0.00f;
                    float zSum = 0.00f;
                    for (int i = 0; i < normals.Length; ++i)
                    {
                        xSum += normals[i].x;
                        ySum += normals[i].y;
                        zSum += normals[i].z;
                    }

                    Vector3 smoothedNormal = new Vector3();
                    smoothedNormal.x = xSum / normals.Length;
                    smoothedNormal.y = ySum / normals.Length;
                    smoothedNormal.z = zSum / normals.Length;
                    smoothedNormal = Vector3.Normalized(smoothedNormal);
                    md2Vert.Normal = smoothedNormal;
                }
            }
        }

        Triangle[] GetTrianglesThatReferenceVert(MD2ModelInfo md2ModelInfo, MD2Vertex[] verticies, MD2Vertex md2Vert)
        {
            List<Triangle> resultTriangles = new List<Triangle>();
            foreach (Triangle t in md2ModelInfo.Triangles)
            {
                if (verticies[t.VertexIndicies[0]] == md2Vert ||
                    verticies[t.VertexIndicies[1]] == md2Vert ||
                    verticies[t.VertexIndicies[2]] == md2Vert )
                {
                    if (!resultTriangles.Contains(t))
                    {
                        resultTriangles.Add(t);
                    }
                }
            }

            return resultTriangles.ToArray();
        }

        Vector3 ParseVector3(BinaryReader br)
        {
            float x, y, z;
            x = br.ReadSingle(); y = br.ReadSingle(); z = br.ReadSingle();

            Vector3 result = new Vector3(x, y, z);

            return result;
        }

        MD2Vertex ParseMD2Vertex(BinaryReader br, Vector3 scale, Vector3 translate)
        {
            int x, y, z;
            x = (int)br.ReadByte(); y = (int)br.ReadByte(); z = (int)br.ReadByte();

            int lightNormalIndex = (int)br.ReadByte();

            Vector3 pos = new Vector3();
            pos.x = x * scale.x + translate.x;
            pos.y = y * scale.y + translate.y;
            pos.z = z * scale.z + translate.z;


            MD2Vertex vertex = new MD2Vertex();
            vertex.Position = pos;
            vertex.LightNormalIndex = lightNormalIndex;

            return vertex;
        }

        string ParseString(BinaryReader br, int startOffset, int nextOffset)
        {
            int length = nextOffset - startOffset;
            char[] buffer = new char[length];
            br.Read(buffer, 0, length);

            string value = new string(buffer);

            return value;
        }

        int ParseInt(BinaryReader br, int startOffset, int nextOffset)
        {
            int length = nextOffset - startOffset;
            byte[] buffer = new byte[length];
            br.Read(buffer, 0, length);
            int value = BitConverter.ToInt32(buffer, 0);

            return value;
        }
    }
}
