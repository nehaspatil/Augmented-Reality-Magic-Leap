#include <ml_logging.h>
#include <lumin/ui/UiKit.h>
#include <glm/ext.hpp>
#include <ml_logging.h>
#include <L3DImageController.h>
#include <lumin/resource/Texture3dResource.h>
#include <lumin/node/VolumeCubeNode.h>

const int TWidth = 100;
const int THeight = 100;
const int TDepth = 100;
using namespace lumin;
using namespace lumin::ui;
using namespace lumin::utils;
using namespace glm;

void L3DImageController::onAttachPrism(lumin::Prism* prism)
{
	 CurrentPrism = prism;
	 
	 // 3d texture descriptor used for creating 3d texture resource which is used to create a 3dImage volume
	 // this volume is not hollow unlike 3d models 

	 Desc3d m_textureDesc;
	 m_textureDesc.params.uCoordWrap = utils::Wrap::kClampToEdge;
	 m_textureDesc.params.vCoordWrap = utils::Wrap::kClampToEdge;
	 m_textureDesc.params.wCoordWrap = utils::Wrap::kClampToEdge;
	 
	 // image3d asset to create 3d texture 
	 std::unique_ptr < AssetPacker::Image3d> m_Image3D = prism->createImage3d(utils::Format::RGBA, TWidth, THeight, TDepth);
	 
	 // get the raw memory pointer to initialize later 
	 uint8_t* rawMemory = m_Image3D->getData();
	 	 
	 const size_t imageSize = 4 * TWidth * THeight; 
	 const glm::vec4 startColor = glm::vec4(255.0f, 0.0f, 0.0f, 255.0f);
	 const glm::vec4 endColor = glm::vec4(0.0f, 0.0f, 255.0f, 255.0f);
	 
	 ML_LOG(Info, "The size of the image 3D data = %d", (int)m_Image3D->getDataSize());

	 // initialize every plane with different color , alpha is constant to 1
	 // color range from red(startcolor) to blue(endcolor)
	 for (size_t i = 0; i < m_Image3D->getDataSize(); i += 4) {
		 size_t zSlice = i / imageSize; // give z buffer index
		 glm::vec4 finalColor = startColor + (endColor - startColor) * ((float)zSlice / (float)TDepth);
		 rawMemory[i] =  (uint8_t)finalColor.x;
		 rawMemory[i + 1] = (uint8_t)finalColor.y;
		 rawMemory[i + 2] = (uint8_t)finalColor.z;
		 rawMemory[i + 3] =255;// (uint8_t)finalColor.a;
	 }
	 // creating 3d texture using 3dimage asset and 3dimage descriptor

	 ResourceIDType m_TextureResourceID = prism->createTexture3dResourceId(std::move(m_Image3D), m_textureDesc);

	 // create 3d volume using 3d texture resource 
	 VolumeCubeNode* volumeCube = prism->createVolumeCubeNode(m_TextureResourceID);
	 volumeCube->setLocalScale(glm::vec3(.25f, .25f, .25f));

	 std::vector<glm::vec3> texCoords;
	 texCoords.push_back(glm::vec3{ 0, 1, 0 });
	 texCoords.push_back(glm::vec3{ 1, 1, 0 });
	 texCoords.push_back(glm::vec3{ 1, 0, 0 });
	 texCoords.push_back(glm::vec3{ 0, 0, 0 });
	 texCoords.push_back(glm::vec3{ 0, 1, 1 });
	 texCoords.push_back(glm::vec3{ 1, 1, 1 });
	 texCoords.push_back(glm::vec3{ 1, 0, 1 });
	 texCoords.push_back(glm::vec3{ 0, 0, 1 });

	 // set 3d texture co-ordinates 
	 volumeCube->setTexCoords(texCoords);
	 volumeCube->setSampleClipRanges({ glm::vec3{0, 0, 0}, glm::vec3{1, 1, 1} });

	 // add 3d volume to the scene graph
	 getRoot()->addChild(volumeCube);
}




