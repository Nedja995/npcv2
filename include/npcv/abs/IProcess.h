#ifndef _INTERFACE_PROCESS__
#define _INTERFACE_PROCESS__

namespace npcv {

	/**
	 * @class	IProcess
	 *
	 * @brief	A process.
	 */
	class IProcess {

	public:

		//virtual ~IProcess() = 0;

		/**
		 * @brief	Initializes this process.
		 */
		virtual void initialize() = 0;

		/**
		 * @brief	Executes this process.
		 */
		virtual void execute() = 0;

		/**
		 * @brief	Frees this process resources.
		 */
		virtual void free() = 0;

		/**
		 * @brief	Is initialized.
		 *
		 * @return	true if initialized, false if not.
		 */
		virtual bool isInitialized() = 0;

		/**
		 * @brief	Is processing in progress.
		 *
		 * @return	true if processing, false if not.
		 */
		virtual bool isProcessing() = 0;
	};
}

#endif
