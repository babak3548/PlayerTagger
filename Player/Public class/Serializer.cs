using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Xml;
using System.Xml.Serialization;
using System.IO;
using System.Runtime.Serialization;
using System.Security.Cryptography;

namespace Player
{
    public class Serializer
    {
        
        public static string Serialize(object obj)
        {
            DataContractSerializer ser = new DataContractSerializer(obj.GetType());
            StringWriter sw = new StringWriter();
            XmlTextWriter tw = new System.Xml.XmlTextWriter(sw);
            ser.WriteObject(tw, obj);
            
            string str = sw.ToString();
            tw.Close();
            sw.Close();
            return str;
        }
        public static void Serialize(object obj, string filename)
        {
            DataContractSerializer ser = new DataContractSerializer(obj.GetType());
            StringWriter sw = new StringWriter();
            XmlTextWriter tw = new System.Xml.XmlTextWriter(sw);
            FileStream writer = new FileStream(filename,FileMode.Create);
            ser.WriteObject(writer, obj);
            writer.Close();
                        tw.Close();
            sw.Close();
        }
        public static void DESSerialize(object obj, string filename)
        {
            string str = Serialize(obj);
            string encStr = DES.Encrypt(str);
            File.WriteAllText(filename, encStr);
        }

        public static T DeSerialize<T>(string xmlstr) where T : class
        {
            DataContractSerializer ser = new DataContractSerializer(typeof(T));
            StringReader sw = new StringReader(xmlstr);
            XmlTextReader tw = new System.Xml.XmlTextReader(sw);
            var obj = ser.ReadObject(tw);
            tw.Close();
            sw.Close();
            return obj as T;
        }
        public static T DeSerializeFromFile<T>(string FileName) where T : class
        {
            try
            {
             DataContractSerializer ser = new DataContractSerializer(typeof(T));
             FileStream fs = new FileStream(FileName, FileMode.OpenOrCreate);

            //StringReader sw = new StringReader(fs);
            XmlTextReader tw = new System.Xml.XmlTextReader(fs);
            var obj = ser.ReadObject(tw);
            tw.Close();
            fs.Close();
           // sw.Close();
            return obj as T;
            }
            catch (Exception ex)
            {

                return null;
            }

   
        }

        public static T DESDeSerializeFromFile<T>(string FileName) where T : class
        {
            DataContractSerializer ser = new DataContractSerializer(typeof(T));
            string encStr= File.ReadAllText(FileName);
            string str=DES.Decrypt(encStr);
            if(string.IsNullOrEmpty(str))
                return null;
            StringReader sw = new StringReader(str);
            XmlTextReader tw = new System.Xml.XmlTextReader(sw);
            var obj = ser.ReadObject(tw);
            tw.Close();
            sw.Close();
            return obj as T;
        }
    }
}
