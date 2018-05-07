using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Md2ModelExporterApp
{
    class MD2Config
    {
        public string ModelFileName { get; set; }
        public List<MD2ClipConfig> Clips { get; set; }

        public MD2Config()
        {

        }
    }
}
