#pragma once

#include "npcv/types/Image.h"
#include <SFGUI/Image.hpp>

namespace npcvGui{

	/**
	 * \brief Abstraction of Image Gui element.
	 */
	class IImageGUI {
	public:

		/**
		 * \brief Load image file from filesystem.
		 *
		 * \param imagePath path to image (platform specific)
		 */
		virtual bool load(const char* imagePath) = 0;

		/**
		* \brief Load npcv::Image.
		*
		* \param npImage npcv::Image
		*/
		virtual bool load(npcv::Image* npImage) = 0;

		/**
		* \brief Load image file from memory.
		*
		* \param imageFile pointer to image file
		* \param sizeBytes data size
		*/
		virtual bool load(unsigned char* imageFile, size_t sizeBytes) = 0;

		/**
		* \brief Call refresh GUI.
		*/
		virtual bool refresh() = 0;

		/**
		* \brief Get processed image
		*
		* \param npImage npcv::Image
		*/
		virtual npcv::Image* GetProcessedImageNp() = 0;

		/**
		* \brief Get processed image
		*
		* \param npImage npcv::Image
		*/
		virtual sfg::Image::Ptr GetProcessedImageSfg() = 0;

		/**
		* \brief Get image
		*
		* \param npImage npcv::Image
		*/
		virtual npcv::Image* GetImageNp() = 0;

		/**
		* \brief Get image
		*
		* \param npImage npcv::Image
		*/
		virtual sfg::Image::Ptr GetImageSfg() = 0;

		/**
		* \brief Resize image
		*
		* \param width New width
		* \param height New height
		*/
		virtual void resize(float x, float y) = 0;

	};

}
