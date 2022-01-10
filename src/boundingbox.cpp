#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include "utils/utils.h"
#include "lib3mf_implicit.hpp"

using namespace Lib3MF;

/*
 This code get a generic file i 3mf object and return bounding box built from this object 
*/

int main(int argc, char **argv)
{
  if(argc!=2){
    std::cout<<"usage: ./executable <path_file_in> "<<argc<<std::endl;exit(1);
  }
  std::string cloudInStr = argv[1];

  PMeshObject meshObjectIn;
  readMesh3MF(cloudInStr,meshObjectIn);

  std::vector<float> pMin;
  std::vector<float> pMax;
  getMinMax3D(meshObjectIn,pMin,pMax);

	// Create mesh structure of a cube
	std::vector<sLib3MFPosition> vertices(8);
	std::vector<sLib3MFTriangle> triangles(12);

  vertices[0] = fnCreateVertex(pMax[0],pMin[1],pMin[2]);
  vertices[1] = fnCreateVertex(pMax[0],pMax[1],pMin[2]);
  vertices[2] = fnCreateVertex(pMax[0],pMax[1],pMax[2]);
  vertices[3] = fnCreateVertex(pMax[0],pMin[1],pMax[2]);
  vertices[4] = fnCreateVertex(pMin[0],pMin[1],pMin[2]);
  vertices[5] = fnCreateVertex(pMin[0],pMax[1],pMin[2]);
  vertices[6] = fnCreateVertex(pMin[0],pMax[1],pMax[2]);
  vertices[7] = fnCreateVertex(pMin[0],pMin[1],pMax[2]);
    
/*---------------------|
                       |
|Z                     | 
|                      |
|                      | 
|7_______6             | 
|\       |\            |   
| \      | \           | 
|  \3____|__\2         |   
4___|____5___|______Y  |      
 \  |     \  |         |
  \ |      \ |         | 
   \0_______\1         |
    \                  | 
     \                 |
      \ X              |
*///-------------------|
 
  // front
  triangles[0] = fnCreateTriangle(0,2,1);
	triangles[1] = fnCreateTriangle(0,2,3);
  // back
	triangles[2] = fnCreateTriangle(4,6,5);
	triangles[3] = fnCreateTriangle(4,6,7);
  // left
  triangles[4] = fnCreateTriangle(4,3,0);
  triangles[5] = fnCreateTriangle(4,3,7);
  // right
  triangles[6] = fnCreateTriangle(5,2,1);
  triangles[7] = fnCreateTriangle(5,2,6);
  // top
  triangles[8] = fnCreateTriangle(7,2,3);
  triangles[9] = fnCreateTriangle(7,2,6);
  // down
  triangles[10] = fnCreateTriangle(4,1,0);
  triangles[11] = fnCreateTriangle(4,1,5);


  auto filename = cloudInStr.substr(0,cloudInStr.rfind("."));
  writeMesh3MF(filename.c_str() + std::string("_bb.3mf"),vertices,triangles);


	std::cout << "boundingBox done!" << std::endl;
  

  return 0;
}

