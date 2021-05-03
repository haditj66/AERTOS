using System.Collections;
using System.Collections.Generic;
using System.IO;
using System.Xml.Serialization;
using UnityEngine;

public class AODeclaredReader : MonoBehaviour
{
    // Start is called before the first frame update
    void Start()
    {
        XmlSerializer xmlser = new XmlSerializer(typeof(AODeclareds));
        AODeclareds aODeclared = new AODeclareds();
        aODeclared.AllAODeclared = new List<AODeclared>();
        aODeclared.AllAODeclared.Add(new AODeclared() {
            HeaderFileName = "AODeclaredTest.h",
            AOType = (int)AOTypeEnum.SPB,
            ClassName = "AODeclaredTest"
        });

        using (FileStream fs = new FileStream("AODeclaredTest.xml", FileMode.Open))
        {
            xmlser.Serialize(fs, aODeclared);
            //p = (AODeclareds)xmlser.Deserialize(fs);
        }
    }

    // Update is called once per frame
    void Update()
    {
        
    }
}
