using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Md2ModelExporterApp
{
    class MD2ClipConfig
    {
        public string Name { get; set; }
        public int StartFrame { get; set; }
        public int EndFrame { get; set; }

        protected int framesPerSecond = 60;
        public int FramesPerSecond 
        { 
            get
            {
                return framesPerSecond;
            } 
            
            set
            {
                framesPerSecond = value;
            } 
        }

        public MD2ClipConfig()
        {

        }
    }
}
