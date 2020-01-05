#include <ml_logging.h>
#include <lumin/ui/UiKit.h>
#include <lumin/event/ServerEvent.h>
#include <glm/ext.hpp>
#include <ml_logging.h>
#include <string.h>
#include <lumin/node/ModelNode.h>
#include <lumin/utils/RendererInterface.h>
#include <Image3DTexture.h>
#include <lumin/resource/Texture3dResource.h>
#include <lumin/node/Quad3dNode.h>
#include <lumin/Consts.h>
#include <Quad3D.h>

const int TWidth = 100;
const int THeight = 100;
const int TDepth = 100;
using namespace lumin;
using namespace lumin::ui;
using namespace lumin::utils;
using namespace glm;

void Quad3DTexture::onAttachPrism(lumin::Prism* prism)
{

	 // meshing - fbx for disk , not looping
	 CurrentPrism = prism;
	 BaseExample::onAttachPrism(prism);
	
	
	 Desc3d m_textureDesc;
	 m_textureDesc.params.uCoordWrap = utils::Wrap::kClampToEdge;
	 m_textureDesc.params.vCoordWrap = utils::Wrap::kClampToEdge;
	 m_textureDesc.params.wCoordWrap = utils::Wrap::kClampToEdge;
	
	 std::unique_ptr < AssetPacker::Image3d> m_Image3D = prism->createImage3d(utils::Format::RGBA, TWidth, THeight, TDepth);
	 uint8_t* rawMemory = m_Image3D->getData();
	
	 // add data 

	 const size_t imageSize = 4 * TWidth * THeight; 
	 const glm::vec4 startColor = glm::vec4(255.0f, 0.0f, 0.0f, 255.0f);
	 const glm::vec4 endColor = glm::vec4(0.0f, 0.0f, 255.0f, 255.0f);

	 for (size_t i = 0; i < m_Image3D->getDataSize(); i += 4) {
		 size_t zSlice = i / imageSize; // give z buffer index
		 glm::vec4 finalColor = startColor + (endColor - startColor) * ((float)zSlice / (float)TDepth);
		 rawMemory[i] = 0;// finalColor.x;
		 rawMemory[i + 1] = 0;// finalColor.y;
		 rawMemory[i + 2] = finalColor.z;
		 rawMemory[i + 3] = finalColor.a;
	 }

	 ResourceIDType m_TextureResourceID = prism->createTexture3dResourceId(std::move(m_Image3D));

	 m_Quad3DNode = prism->createQuad3dNode(m_TextureResourceID);
	 m_Quad3DNode->setLocalScale(glm::vec3(.25f, .25f, .25f));
	 getRoot()->addChild(m_Quad3DNode);
	 GetQuad3DProperties();

	 /* This is default set my lumin system to point to center of 3D volume 
	 const Quad3dNode::TexCoords DEFAULT_TEX_COORDS{
 { 0.0f, 1.0f, 0.5f },
 { 1.0f, 1.0f, 0.5f },
 { 1.0f, 0.0f, 0.5f },
 { 0.0f, 0.0f, 0.5f },
	 };*/
}



bool Quad3DTexture::onEvent(lumin::ServerEvent* a_pEvent)
{
	
	lumin::ServerEventTypeValue serverEventType = a_pEvent->getServerEventTypeValue();
	Prism* prism = getPrism();
		
	return false;
}

void Quad3DTexture::onUpdate(float a_fDelta)
{
	
	static float z = 0.0f;
	static float elapsedTime = 0;

	if (shouldAnimate) {
	
		
		elapsedTime += a_fDelta;

		if (elapsedTime > 10.0f*scale)
		{
			scale = scale + 0.2f;
			std::vector<glm::vec3> texCoords;
			texCoords.push_back(glm::vec3{ 0, 1,z});
			texCoords.push_back(glm::vec3{ 1, 1,z});
			texCoords.push_back(glm::vec3{ 1, 0,z});
			texCoords.push_back(glm::vec3{ 0, 0,z});
			m_Quad3DNode->setTexCoords(texCoords);
			z = z + 0.25f;
			if (z > 1.0f)
				z = 0.0f;
			
		}

		
	}
	
}
void Quad3DTexture::GetQuad3DProperties()
{

	UiButton* Button;
	Button = lumin::ui::UiButton::CreateEclipseButton(CurrentPrism, EclipseButtonParams(EclipseButtonType::kText, "Get Quad3d Info", .05f));
	Button->setLocalPosition(glm::vec3(-.3f, -.3f, 0));
	Button->setLocalScale(glm::vec3(1.1f, 1.1f, 1.1f));
	Button->setTextColor(glm::vec4(.1f, 1, .1f, 1));
	getRoot()->addChild(Button);

	ui::UiText* UiTextNode1 = ui::UiText::Create(CurrentPrism, "");
	getRoot()->addChild(UiTextNode1);
	UiTextNode1->setTextSize(.05f);
	UiTextNode1->setLocalPosition(glm::vec3(.3f, -.3f, 0));

	Button->onActivateSub([=](const UiEventData&) {

		std::string outputString;


		const  Resource* m_ReturnRenderResource = m_Quad3DNode->getRenderResource();
		outputString.append("ResourceValid = ");
		if (m_ReturnRenderResource != NULL)
		{
			bool isResourceValid = m_ReturnRenderResource->isResourceValid();
			const std::string resourcePath = m_ReturnRenderResource->getBasePath();
			const std::string FilePathName = m_ReturnRenderResource->getFileName();
			resources::LoadStatus m_loadStatus = m_ReturnRenderResource->getLoadStatus();
			ResourceIDType m_ResourceID = m_ReturnRenderResource->getResourceId();
			ResourceType m_ResourceType = m_ReturnRenderResource->getResourceType();

			if (isResourceValid)
				outputString.append("1");

			outputString.append("\n ResourcePath = "); outputString.append(resourcePath);
			outputString.append("\n FilePath = "); outputString.append(FilePathName);
			//outputString.append("\n LoadStatus = "); outputString.append((m_loadStatus));
			outputString.append("\n m_ResourceID = "); outputString.append(std::to_string(m_ResourceID));

		}
		else
		{
			outputString.append("0");
		}


		Quad3dNode::TexCoords  m_TexCoords = m_Quad3DNode->getTexCoords();
		outputString.append(" \n Tex Coords: Size =  ");
		outputString.append( std::to_string(m_TexCoords.size()));
		outputString.append("\n");
		glm::vec3 temp;
		for (int i = 0; i < m_TexCoords.size(); i++)
		{
			temp = m_TexCoords[i];
			outputString += "[" + glm::to_string(temp) + "]\n";


		}
		glm::vec2 QuadSize = m_Quad3DNode->getSize();
		outputString.append("Quad Size = ");
		outputString.append("x = ");
		outputString.append(std::to_string(QuadSize.x));
		outputString.append("\n y = ");
		outputString.append(std::to_string(QuadSize.y));
		UiTextNode1->setText(outputString);
	});

	

}

