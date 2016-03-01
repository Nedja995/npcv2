/**
 * @file	D:\Projects\CompVision\npcv2\include\npcv\Application.h
 *
 * @brief	Declares the application class.
 */

#pragma once

/**
 * @namespace	npcv
 *
 * @brief	.
 */

namespace npcv {

	/**
	 * @class	Application
	 *
	 * @brief	An application.
	 */

	class Application {
	public:

		/**
		 * @enum	Platform
		 *
		 * @brief	Values that represent platforms.
		 */

		enum Platform {
			///< An enum constant representing the windows option
			Windows = 0,
			///< An enum constant representing the unix option
			Unix = 1,
			///< An enum constant representing the android option
			Android = 2
		};

		/**
		 * @brief	Gets runtime platform.
		 *
		 * @return	The runtime platform.
		 */
		static Platform getRuntimePLatform();

	};



}
