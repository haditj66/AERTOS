using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Xml.Serialization;



public enum AOTypeEnum
{
    SPB
}

[XmlRoot(ElementName = "AO")]
public class AODeclareds
{
    [XmlArray(ElementName = "AODeclareds")]
    public List<AODeclared> AllAODeclared;
}


[XmlRoot(ElementName = "AO")]
public class AODeclared
{
    [XmlElement(ElementName = "HeaderFileName", DataType = "string")]
    public string HeaderFileName;
    [XmlElement(ElementName = "ClassName", DataType = "string")]
    public string ClassName;
    [XmlElement(ElementName = "AOType", DataType = "int")]
    public int AOType; 

}