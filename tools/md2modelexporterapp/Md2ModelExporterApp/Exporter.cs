using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.IO;
using System.Threading.Tasks;

namespace Md2ModelExporterApp
{
    class Exporter
    {
        static readonly int ExportVersion = 1;

        public void Export(string path, MD2Config config, MD2ModelInfo md2ModelInfo)
        {
            byte[] frameStream = WriteFrameDataToStream( config, md2ModelInfo.Frames);
            byte[] texCoordStream = WriteTextureCoordinatesToStream(md2ModelInfo.TextureCoordinates);
            byte[] triangleStream = WriteTrianglesToStream(md2ModelInfo);

            byte[] headerStream = WriteHeaderToStream(config, md2ModelInfo.Header, frameStream, texCoordStream, triangleStream);

            if (!File.Exists(path))
            {
                File.Create(path).Close();
            }

            using (BinaryWriter bw = new BinaryWriter(new FileStream(path, FileMode.Open), Encoding.ASCII))
            {
                WriteBytesToStream(bw, headerStream);
                WriteBytesToStream(bw, frameStream);
                WriteBytesToStream(bw, texCoordStream);
                WriteBytesToStream(bw, triangleStream);
            }
        }

        void WriteBytesToStream(BinaryWriter sw, byte[] bytes)
        {
            foreach (byte b in bytes)
            {
                sw.Write(b);
            }
        }

        byte[] WriteHeaderToStream(         MD2Config config,
                                            MD2Header Header,
                                            byte[] frameStream,
                                            byte[] texCoordStream,
                                            byte[] triangleStream)
        {
            MemoryStream ms = new MemoryStream();
            BinaryWriter bw = new BinaryWriter(ms, Encoding.ASCII);

            int frameLength = frameStream.Length;
            int texCoordLength = texCoordStream.Length;
            int triangleLength = triangleStream.Length;

            int sizeofEachFrameInBytes = (frameLength - (28*config.Clips.Count)) / Header.TotalNumberOfFrames;
            //sizeofEachFrameInBytes = sizeofEachFrameInBytes + ((24 + 4)*config.Clips.Count);

            char[] exportName = "xdbm".ToCharArray();
            bw.Write(exportName);
            bw.Write(ExportVersion);
            bw.Write(Header.NumberOfTriangles);
            bw.Write(Header.NumberOfVerticies);
            bw.Write(Header.NumberOfTextureCoordinates);
            bw.Write(Header.TotalNumberOfFrames);
            bw.Write(sizeofEachFrameInBytes);
            bw.Write(config.Clips.Count);

            foreach (MD2ClipConfig clip in config.Clips)
            {
                char[] finalNameArray = new char[24];
                char[] nameArray = clip.Name.ToCharArray();
                Array.Copy(nameArray, finalNameArray, nameArray.Length);
                bw.Write(finalNameArray);
            }

            int headerLength = (int)(ms.Length) + (sizeof(int) * 3);

            bw.Write(headerLength); // to Frames
            bw.Write(headerLength + frameLength); // to Textures
            bw.Write(headerLength + frameLength + texCoordLength); // To triangles

            bw.Flush();
            bw.Close();
            ms.Close();

            return ms.ToArray();
        }

        byte[] WriteFrameDataToStream( MD2Config config, Frame[] frames)
        {
            MemoryStream ms = new MemoryStream();
            BinaryWriter bw = new BinaryWriter(ms, Encoding.ASCII);

            bool newClip = true;
            int clipIndex = 0;
            int frameCounter = 0;
            int numberOfFramesInClip = 0;

            long startLength = 0;

            foreach (Frame f in frames)
            {
                if (newClip)
                {
                    char[] finalNameArray = new char[24];
                    char[] nameArray = config.Clips[clipIndex].Name.ToCharArray();

                    Array.Copy(nameArray, finalNameArray, nameArray.Length);

                    bw.Write(finalNameArray);

                    numberOfFramesInClip = (config.Clips[clipIndex].EndFrame - config.Clips[clipIndex].StartFrame) + 1;
                    bw.Write(numberOfFramesInClip);
                    newClip = false;

                    bw.Write(config.Clips[clipIndex].FramesPerSecond);

                    frameCounter = 0;

                    startLength = bw.BaseStream.Length;
                }

                foreach (MD2Vertex v in f.verticies)
                {
                    bw.Write(v.Position.x); bw.Write(v.Position.y); bw.Write(v.Position.z);
                    bw.Write(v.Normal.x); bw.Write(v.Normal.y); bw.Write(v.Normal.z);
                }

                if (++frameCounter >= numberOfFramesInClip)
                {
                    newClip = true;
                    ++clipIndex;

                    long length = bw.BaseStream.Length - startLength;
                }
            }

            bw.Flush();
            bw.Close();
            ms.Close();

            return ms.ToArray();
        }

        byte[] WriteTextureCoordinatesToStream(TextureCoordinate[] texCoords)
        {
            MemoryStream ms = new MemoryStream();
            BinaryWriter bw = new BinaryWriter(ms, Encoding.ASCII);

            foreach (TextureCoordinate texCoord in texCoords)
            {
                bw.Write(texCoord.u);
                bw.Write(texCoord.v);
            }

            bw.Flush();
            bw.Close();
            ms.Close();

            return ms.ToArray();
        }

        byte[] WriteTrianglesToStream(MD2ModelInfo modelInfo)
        {
            MemoryStream ms = new MemoryStream();
            BinaryWriter bw = new BinaryWriter(ms, Encoding.ASCII);

            foreach (Triangle triangle in modelInfo.Triangles)
            {
                bw.Write(triangle.VertexIndicies[0]); bw.Write(triangle.VertexIndicies[1]); bw.Write(triangle.VertexIndicies[2]);
                bw.Write(triangle.UVIndicies[0]); bw.Write(triangle.UVIndicies[1]); bw.Write(triangle.UVIndicies[2]);
                bw.Write(triangle.normal.x); bw.Write(triangle.normal.y); bw.Write(triangle.normal.z);

                /*
                Vector3 v0 = modelInfo.Frames[0].verticies[triangle.VertexIndicies[0]].Position;
                Vector3 v1 = modelInfo.Frames[0].verticies[triangle.VertexIndicies[1]].Position;
                Vector3 v2 = modelInfo.Frames[0].verticies[triangle.VertexIndicies[2]].Position;

                Vector3 fromV0ToV1 = v1 - v0;
                fromV0ToV1 = Vector3.Normalized(fromV0ToV1);

                Vector3 fromV0ToV2 = v2 - v0;
                fromV0ToV2 = Vector3.Normalized(fromV0ToV2);

                Vector3 cross = Vector3.Cross(fromV0ToV1, fromV0ToV2);
                cross = Vector3.Normalized(cross);

                bw.Write(cross.x); bw.Write(cross.y); bw.Write(cross.z);
                */
            }

            bw.Flush();
            bw.Close();
            ms.Close();

            return ms.ToArray();
        }
    }
}
