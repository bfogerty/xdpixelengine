using System;
using System.Collections.Generic;
using System.Text;
using System.IO;
using LitJson;

namespace Md2ModelExporterApp
{
    class Program
    {
        static void Main(string[] args)
        {
            if (args.Length == 2)
            {
                if (args[0] == "-info")
                {
                    DisplayMd2FileInfo(args[1]);
                }
            }
            else if (args.Length == 4)
            {
                string inputFileName = string.Empty;
                string outputFileName = string.Empty;
                for(int i=0; i < args.Length; ++i)
                {
                    if (args[i] == "-i")
                    {
                        inputFileName = args[i + 1];
                    }
                    else if (args[i] == "-o")
                    {
                        outputFileName = args[i + 1];
                    }
                }

                ConvertMd2ToAbm(inputFileName, outputFileName);

                Test(outputFileName);
            }

        }

        static void ConvertMd2ToAbm( string configFileName, string outputFileName )
        {
            MD2Config config = null;
            StreamReader sr = new StreamReader(configFileName);
            string json = sr.ReadToEnd();

            config = LitJson.JsonMapper.ToObject<MD2Config>(json);

            MD2ModelParser md2Parser = new MD2ModelParser();
            MD2ModelInfo md2ModelInfo = md2Parser.Import(config.ModelFileName);

            int frameCounter = 0;
            foreach (Frame f in md2ModelInfo.Frames)
            {
                Console.WriteLine("Name: {0}, Frame: {1}", f.name, frameCounter++);
            }

            Exporter exporter = new Exporter();
            exporter.Export(outputFileName, config, md2ModelInfo);
        }

        static void DisplayMd2FileInfo(string modelFileName)
        {
            MD2ModelParser md2Parser = new MD2ModelParser();
            MD2ModelInfo md2ModelInfo = md2Parser.Import(modelFileName);

            int frameCounter = 0;
            foreach (Frame f in md2ModelInfo.Frames)
            {
                Console.WriteLine("Name: {0}, Frame: {1}", f.name, frameCounter++);
            }
        }

        static void Test(string path)
        {
            BinaryReader brTest = new BinaryReader(new FileStream(path, FileMode.Open));
            char[] id = brTest.ReadChars(4);
            int version = brTest.ReadInt32();
            int numOfTriangles = brTest.ReadInt32();
            int numberOfVerts = brTest.ReadInt32();
            int numberOfTexCoords = brTest.ReadInt32();
            int numberOfFrames = brTest.ReadInt32();
            int sizeofEachFrameInBytes = brTest.ReadInt32();
            int numberOfClips = brTest.ReadInt32();

            string[] clipNames = new string[numberOfClips];
            for (int i = 0; i < numberOfClips; ++i)
            {
                clipNames[i] = new string( brTest.ReadChars(24) ).Trim();
            }

            int offsetToFrames = brTest.ReadInt32();
            int offsetToTextures = brTest.ReadInt32();
            int offsetToTriangles = brTest.ReadInt32();

            brTest.BaseStream.Seek(offsetToFrames, SeekOrigin.Begin);

            Console.WriteLine("Clips:");
            for (int i = 0; i < numberOfClips; ++i)
            {
                char[] arr = brTest.ReadChars(24);
                Console.WriteLine( string.Format("{0}. {1}", i, new string(arr)));
                int framesInClip = brTest.ReadInt32();
                int fps = brTest.ReadInt32();

                if (i < numberOfClips - 1)
                {
                    brTest.BaseStream.Seek(framesInClip * sizeofEachFrameInBytes, SeekOrigin.Current);
                }
            }

            brTest.Close();
        }
    }
}
