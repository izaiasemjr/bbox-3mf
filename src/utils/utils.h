#include "lib3mf_implicit.hpp"

using namespace Lib3MF;
// Utility functions to create vertices and triangles
sLib3MFPosition fnCreateVertex(float x, float y, float z)
{
	sLib3MFPosition result;
	result.m_Coordinates[0] = x;
	result.m_Coordinates[1] = y;
	result.m_Coordinates[2] = z;
	return result;
}
sLib3MFTriangle fnCreateTriangle(int v0, int v1, int v2)
{
	sLib3MFTriangle result;
	result.m_Indices[0] = v0;
	result.m_Indices[1] = v1;
	result.m_Indices[2] = v2;
	return result;
}

void readMesh3MF(std::string pathFile, PMeshObject &meshObject){

  // Import Model from 3MF File
  PWrapper wrapper = CWrapper::loadLibrary();
  PModel modelIn = wrapper->CreateModel();
  PReader reader = modelIn->QueryReader("3mf");
  // And deactivate the strict mode (default is "false", anyway. This just demonstrates where/how to use it).
  reader->SetStrictModeActive(false);
  reader->ReadFromFile(pathFile.c_str());
  
  for (Lib3MF_uint32 iWarning = 0; iWarning < reader->GetWarningCount(); iWarning++) {
    Lib3MF_uint32 nErrorCode;
    std::string sWarningMessage = reader->GetWarning(iWarning, nErrorCode);
    std::cout << "Encountered warning #" << nErrorCode << " : " << sWarningMessage << std::endl;
  }
  PObjectIterator objectIterator = modelIn->GetObjects();
  while (objectIterator->MoveNext()) {
		PObject object = objectIterator->GetCurrentObject();
		if (object->IsMeshObject()) {
             meshObject = modelIn->GetMeshObjectByID(object->GetResourceID());
		}
	}
}

void writeMesh3MF(std::string pathFile,
                  const Lib3MF::CInputVector<Lib3MF::sPosition> &VerticesBuffer, 
                  const Lib3MF::CInputVector<Lib3MF::sTriangle> &IndicesBuffer){
  
  PWrapper wrapper = CWrapper::loadLibrary();
  PModel modelOut = wrapper->CreateModel();
	PMeshObject meshObjectOut = modelOut->AddMeshObject();
	meshObjectOut->SetName("BoundingBox");
	meshObjectOut->SetGeometry(VerticesBuffer, IndicesBuffer);

	// Add build item
	modelOut->AddBuildItem(meshObjectOut.get(), wrapper->GetIdentityTransform());
	PWriter writer = modelOut->QueryWriter("3mf");
  writer->WriteToFile(pathFile);


}


void getMinMax3D(PMeshObject &meshObject, std::vector<float> &pMin,std::vector<float> &pMax){
    auto maxFloat = std::numeric_limits<float>::max();
    auto minFloat = std::numeric_limits<float>::min(); 
    pMin = {maxFloat,maxFloat,maxFloat};
    pMax = {minFloat,minFloat,minFloat};
    
    std::vector<Lib3MF::sPosition> VerticesBuffer; 
    meshObject->GetVertices(VerticesBuffer);
    for (std::size_t i = 0; i<VerticesBuffer.size();i++){
        auto x=VerticesBuffer[i].m_Coordinates[0];
        auto y=VerticesBuffer[i].m_Coordinates[1];
        auto z=VerticesBuffer[i].m_Coordinates[2];
        // max
        if(x>pMax[0])pMax[0]=x;
        if(y>pMax[1])pMax[1]=y;
        if(z>pMax[2])pMax[2]=z;
        
        if(x<pMin[0])pMin[0]=x;
        if(y<pMin[1])pMin[1]=y;
        if(z<pMin[2])pMin[2]=z;
    }

}


